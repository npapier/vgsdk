// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#include "vgQt/engine/UserSettings.hpp"
#include <QHBoxLayout>
#include <QTreeWidget>
#include <QDialog>

namespace vgQt
{

namespace engine
{

UserSettings::UserSettings( vgd::Shp< vge::engine::UserSettings > settings )
:	m_settings( settings ? settings : vgd::makeShp(new vge::engine::UserSettings() ) )
{
    QLabel* label = new QLabel("To configure rendering settings according to your hardware capabilities,\n select a detail level in the list below.\n\nYou can also activate the appropriate detail level by\n selecting your graphic card in advanced mode.");
    m_description = new QLabel();
    m_selectCard = new QPushButton();
    m_selectCard->setText( "Advanced..." );

    m_levelCombo = new QComboBox();

    // Fills the combo with available levels.
    const int	levelCount = m_settings->getLevelCount();

    for( int i = 0; i != levelCount; ++i )
    {
        m_levelCombo->addItem(QString::fromStdString(m_settings->getName(i)));
    }

    QHBoxLayout* layout = new QHBoxLayout();
    layout->addWidget(m_levelCombo);
    layout->addWidget(m_selectCard);

    addWidget(label);
    addLayout(layout);
    addWidget(m_description);

    connect(m_levelCombo, SIGNAL(currentIndexChanged(int)), (UserSettings*) this, SLOT(onLevelChanged()));
    connect(m_selectCard, SIGNAL(clicked()), this, SLOT(onSelectCardClicked()));
    onLevelChanged();
}


const vgd::Shp< vge::engine::UserSettings > UserSettings::get() const
{
    return m_settings;
}


void UserSettings::set( const vgd::Shp< vge::engine::UserSettings > settings )
{
    m_settings = settings;
    refreshLevel();
}


void UserSettings::onLevelChanged()
{
    const int level = m_levelCombo->currentIndex();

    if( level >= 0 )
    {
        m_settings->setLevel( level );
        m_description->setText(QString::fromStdString(m_settings->getDescription(level)));
    }
    else
    {
        m_description->setText( "No detail level selected." );
    }

	Q_EMIT changed();
}


void UserSettings::onSelectCardClicked()
{
    QDialog* dialog = new QDialog();
    dialog->setWindowTitle("Graphic card selection");
    QLabel* label = new QLabel("In order to adjust the detail level to your hardware capabilities, select a graphic card in list below.");
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(label);
    QTreeWidget* treeView = new QTreeWidget();
    treeView->setRootIsDecorated(false);
    treeView->setHeaderHidden(true);

    // Fills the list with available graphic cards.
    typedef std::vector< std::string >	StringVector;
    const StringVector					cards = m_settings->getGraphicCards< StringVector >();

    for( StringVector::const_iterator i = cards.begin(); i != cards.end(); ++i )
    {
        QTreeWidgetItem* item = new QTreeWidgetItem();
        item->setText(0, QString::fromStdString(*i));
        treeView->addTopLevelItem( item );
    }

    layout->addWidget(treeView);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton* buttonOk = new QPushButton("OK");
    QPushButton* buttonCancel = new QPushButton("Cancel");
    buttonLayout->addStretch();
    buttonLayout->addWidget(buttonOk);
    buttonLayout->addWidget(buttonCancel);
    layout->addLayout(buttonLayout);
    connect(buttonOk, SIGNAL(clicked()), dialog, SLOT(accept()));
    connect(buttonCancel, SIGNAL(clicked()), dialog, SLOT(reject()));
    dialog->setLayout(layout);

    if(dialog->exec() == QDialog::Accepted)
    {
        if(treeView->selectedItems().size() == 1)
        {
            m_settings->setGraphicCard( treeView->selectedItems().last()->text(0).toStdString() );
            refreshLevel();
        }
    }
    dialog->deleteLater();
	Q_EMIT changed();
}


void UserSettings::refreshLevel()
{
    const int	level	= m_settings->getLevel();
    m_levelCombo->setCurrentIndex( level );
}


} // namespace engine

} // namespace vgQt
