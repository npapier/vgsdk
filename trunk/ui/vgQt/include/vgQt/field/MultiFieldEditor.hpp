// VGSDK - Copyright (C) 2012, 2014, Guillaume Brocker, Bryan Schuller, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGQT_FIELD_MULTIFIELDEDITOR_HPP_
#define _VGQT_FIELD_MULTIFIELDEDITOR_HPP_

#include <vgd/field/TMultiField.hpp>

#include "vgQt/field/FieldEditor.hpp"
#include "vgQt/field/adapter/MFAdapter.hpp"
#include "vgQt/field/MultiFieldLayout.hpp"

#include <QGridLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QTreeWidget>
#include <QStringList>
#include <QTreeWidgetItem>

namespace vgQt
{

namespace field
{

template< typename MFAdapter >
struct MultiFieldEditor : public FieldEditor
{
    /**
     * @brief	Constructor
     */
    MultiFieldEditor()
        : m_buttonBox(new QVBoxLayout()),
          m_treeView(new QTreeWidget()),
          m_addButton(new QPushButton("&Add")),
          m_removeButton(new QPushButton("&Remove")),
          m_moveUpButton(new QPushButton("&Up")),
          m_moveDownButton(new QPushButton("&Down"))
    {
        m_widget = new MultiFieldLayout();
        m_status = new QLabel("label status");

        m_buttonBox->addWidget(m_addButton);
        m_buttonBox->addWidget(m_removeButton);
        m_buttonBox->addWidget(m_moveUpButton);
        m_buttonBox->addWidget(m_moveDownButton);
        m_buttonBox->addStretch();

        m_treeView->setRootIsDecorated(false);
        m_treeView->setColumnCount( 2 );
		m_treeView->setUniformRowHeights(true);

        m_adapter.addColumnsToView(m_treeView);

        m_widget->addWidget(m_treeView,0,0);
        m_widget->addLayout(m_buttonBox, 0, 1);
        m_widget->addWidget(m_status, 1, 0);

        updateLabel();

        connect(m_addButton, SIGNAL(clicked()), this, SLOT(addClicked()));
        connect(m_removeButton, SIGNAL(clicked()), this, SLOT(removeClicked()));
        connect(m_moveUpButton, SIGNAL(clicked()), this, SLOT(moveUpClicked()));
        connect(m_moveDownButton, SIGNAL(clicked()), this, SLOT(moveDownClicked()));

        connect(m_treeView, SIGNAL(itemChanged(QTreeWidgetItem*,int)), m_widget, SIGNAL(signalChanged()));
        connect(this, SIGNAL(signalChanged()), m_widget, SIGNAL(signalChanged()));
    }

    ~MultiFieldEditor()
    {
        delete m_widget;
    }

    QLayout* getWidget()
    {
        return m_widget;
    }

    QLayout* getLayout()
    {
        return m_widget;
    }

    void commit()
    {
        typedef vgd::field::TMultiField< typename MFAdapter::value_type > FieldType;
        vgd::field::EditorRW< FieldType >	fieldEditor	= m_fieldManager->getFieldRW< FieldType >( m_fieldName.toStdString() );

        fieldEditor->clear();
		fieldEditor->push_back( m_backupValue );

        for( unsigned int index = 0; index != m_treeView->topLevelItemCount(); ++index )
        {
            typename MFAdapter::value_type value;

            m_adapter.updateFromRow( m_treeView->topLevelItem(index), value );
        }
    }

    void refresh()
    {
		// Disables update/repaint
		m_treeView->setUpdatesEnabled(false);

        // Clears the view
		m_treeView->clear();

        // Gets the editor of the field.
        typedef vgd::field::TMultiField< typename MFAdapter::value_type > FieldType;
		vgd::field::EditorRO< FieldType > fieldEditor = m_fieldManager->getFieldRO< FieldType >( m_fieldName.toStdString() );

		// Creates a copy of data.
        m_backupValue.clear();
		m_backupValue.insert( m_backupValue.begin(), fieldEditor->begin(), fieldEditor->end() );

        // Copies values from the field into the local edition model and backup of the data.
		QList<QTreeWidgetItem*> rows;
        for( unsigned int i = 0; i < fieldEditor->size(); ++i )
        {
            QTreeWidgetItem* row = new QTreeWidgetItem;
            row->setText(0, QString::number(i));
            m_adapter.updateToRow( row, (*fieldEditor)[i]);
			rows << row;
        }
		m_treeView->addTopLevelItems( rows );

        // Updates the status label to show the number of elements.
        updateLabel();

        // Releases field editor
        fieldEditor.release();

		// Renables update/repaint
		m_treeView->setUpdatesEnabled(true);

        // Sends a change notification.
        Q_EMIT signalChanged();
    }


    void rollback()
    {
		// Disables update/repaint
		m_treeView->setUpdatesEnabled(false);

        // Gets the editor of the field.
        typedef vgd::field::TMultiField< typename MFAdapter::value_type > FieldType;
        vgd::field::EditorRW< FieldType >	fieldEditor	= m_fieldManager->getFieldRW< FieldType >( m_fieldName.toStdString() );

        // Clears the view and the edited field.
        m_treeView->clear();
        fieldEditor->clear();

        // Copies values from the backup value into the local edition model and the field.
		fieldEditor->push_back( m_backupValue );
		QList<QTreeWidgetItem*> rows;
        for( unsigned int i = 0; i < m_backupValue.size(); ++i )
        {
            QTreeWidgetItem* row = new QTreeWidgetItem;
            row->setText(0, QString::number(i));
            m_adapter.updateToRow( row, m_backupValue[i]);
			rows << row;
        }
		m_treeView->addTopLevelItems( rows );

        // Updates the status label to show the number of elements.
        updateLabel();

        // Releases field editor
        fieldEditor.release();

		// Renables update/repaint
		m_treeView->setUpdatesEnabled(true);

        // Sends a change notification.
        Q_EMIT signalChanged();
    }

    const bool validate()
    {
        return true;
    }

private:
    MFAdapter                                       m_adapter;
    QLabel*                                         m_status;
    std::vector< typename MFAdapter::value_type	>	m_backupValue;			///< Holds a copy of the initial multifield data.
    MultiFieldLayout*                               m_widget;
    QPushButton*                                	m_addButton;
    QPushButton*                                	m_removeButton;
    QPushButton*                                    m_moveUpButton;
    QPushButton*                                	m_moveDownButton;
    QVBoxLayout*                                    m_buttonBox;
    QTreeWidget*                                    m_treeView;

    /**
     * @brief	Rebuilds the row indexes.
     */
    void rebuildRowIndexes()
    {
        unsigned int index;
        for( index = 0; index != m_treeView->topLevelItemCount(); ++index )
        {
            m_treeView->topLevelItem(index)->setText(0, QString::number(index));
        }
    }

    /**
     * @brief	Update the laber which displays the number of elements.
     */
    void updateLabel()
    {
        m_status->setText(QString::number(m_treeView->topLevelItemCount()) + " elements");
    }

    /**
    * @name slots
    */
    //@{
    void addClicked()
    {
        QTreeWidgetItem *newRow = 0;
        QList<QTreeWidgetItem*> selectedPaths = m_treeView->selectedItems();

        if(selectedPaths.empty())
        {
            newRow = new QTreeWidgetItem( m_treeView );
        }
        else
        {
            newRow = new QTreeWidgetItem();
            m_treeView->insertTopLevelItem(m_treeView->indexOfTopLevelItem(selectedPaths.last()) + 1, newRow);
        }

        if(newRow)
        {
            newRow->setFlags(newRow->flags() | Qt::ItemIsEditable);
            m_adapter.updateToRow(newRow, typename MFAdapter::value_type());
            updateLabel();
            rebuildRowIndexes();
        }

        Q_EMIT signalChanged();
    }

    void removeClicked()
    {
        QList<QTreeWidgetItem*> selectedPaths = m_treeView->selectedItems();

        for( int i = selectedPaths.size() - 1; i >= 0; --i )
        {
            m_treeView->takeTopLevelItem( m_treeView->indexOfTopLevelItem( selectedPaths.last() ) );
            selectedPaths.pop_back();
        }

        rebuildRowIndexes();
        updateLabel();

        Q_EMIT signalChanged();
    }

    void moveUpClicked()
    {
        QList<QTreeWidgetItem*> selectedPaths = m_treeView->selectedItems();

        if( selectedPaths.isEmpty() )
        {
            return;
        }
        else if( m_treeView->indexOfTopLevelItem(selectedPaths.last()) == 0 )
        {
            return;
        }
        else
        {
            int index = m_treeView->indexOfTopLevelItem( selectedPaths.last() );
            QTreeWidgetItem*	newRow	= m_treeView->takeTopLevelItem(index);
            if(index < m_treeView->topLevelItemCount())
            {
                m_treeView->topLevelItem(index)->setSelected(false);
            }
            else
            {
                m_treeView->topLevelItem(m_treeView->topLevelItemCount() - 1 )->setSelected(false);
            }
            newRow->setFlags(newRow->flags() | Qt::ItemIsEditable);
            m_treeView->insertTopLevelItem( index - 1, newRow);

            newRow->setSelected(true);
            rebuildRowIndexes();

            // Sends a change notification.
            Q_EMIT signalChanged();
        }
    }

    void moveDownClicked()
    {
        QList<QTreeWidgetItem*> selectedPaths = m_treeView->selectedItems();

        if( selectedPaths.isEmpty() )
        {
            return;
        }
        else if( m_treeView->indexOfTopLevelItem(selectedPaths.last()) == m_treeView->topLevelItemCount() -1)
        {
            return;
        }
        else
        {
            // Retrieves the value that is before the first selected row.
            int index = m_treeView->indexOfTopLevelItem( selectedPaths.last() );
            QTreeWidgetItem*	newRow	= m_treeView->takeTopLevelItem(index);
            newRow->setFlags(newRow->flags() | Qt::ItemIsEditable);
            m_treeView->insertTopLevelItem( index + 1, newRow);

            newRow->setSelected(true);
            m_treeView->topLevelItem(index)->setSelected(false);
            rebuildRowIndexes();

            // Sends a change notification.
            Q_EMIT signalChanged();
        }
    }
    //@}
};

} // namespace field

} // namespace vgQt



#endif // _VGQT_FIELD_MULTIFIELDEDITOR_HPP_
