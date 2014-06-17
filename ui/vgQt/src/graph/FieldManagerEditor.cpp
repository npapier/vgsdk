// VGSDK - Copyright (C) 2012, 2013, Guillaume Brocker, Bryan Schuller.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#include "vgQt/graph/FieldManagerEditor.hpp"

#include <QMessageBox>

#include <vgUI/Canvas.hpp>

#include "vgQt/graph/convenience.hpp"
#include "vgQt/graph/TreeModelColumnRecord.hpp"
#include "vgQt/field/FieldEditorDialog.hpp"


namespace vgQt
{

namespace graph
{

namespace
{
	/**
	 * @name	Node Properties Prefixes
	 */
	//@{
	static const QString	FIELD_PREFIX("f_");
	static const QString	DIRTY_FLAG_PREFIX("df_");
	static const QString	IBOUNDINGBOX_PREFIX("IBoundingBox");
	//@}
}


FieldManagerEditor::FieldManagerEditor(QWidget *parent) : QTreeWidget(parent)
{
	setRootIsDecorated(false);
	setColumnCount( 3 );
	QStringList titles;
	titles << "Name" << "Value" << "Type";
	setHeaderLabels( titles );

	setColumnWidth(0, 320);
	setColumnWidth(1, 200);

	// The user wants to edit the node
	connect( this, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(onRowActivated(QTreeWidgetItem*,int)) );
}


void FieldManagerEditor::setPath(QString path)
{
	m_path = path;
}


void FieldManagerEditor::updateField( const vgd::field::AbstractField &rField, const vgd::field::Event event )
{
	Q_UNUSED(rField);
	Q_UNUSED(event);
}


void FieldManagerEditor::clear()
{
	if( m_fieldManager )
	{
		QTreeWidget::clear();
	}
}


void FieldManagerEditor::fillModel()
{
	clear();

	// Retrieves all field names.
	typedef std::vector< std::string > 						StringContainer;
	typedef std::back_insert_iterator< StringContainer >	InsertIterator;

	StringContainer	fieldNames;
	InsertIterator	inserter( fieldNames );

	m_fieldManager->getFieldNames( inserter );

	// Updates the managed model.
	StringContainer::const_iterator	i;

	for( i = fieldNames.begin(); i != fieldNames.end(); ++i )
	{
		const std::string		name		= *i;
		const std::string		value		= vgUI::graph::getFieldAsString( m_fieldManager, name );
		const std::type_info	& typeInfo	= m_fieldManager->getFieldType( name );

		// Appends a new row to the model.

		QTreeWidgetItem *item = new QTreeWidgetItem( this );
		item->setText( 0, name.c_str() );
		item->setText( 1, value.c_str() );
		item->setText( 2, typeInfo.name() );
	}

	// Retrieves all dirty flags names.
	StringContainer	dirtyFlagNames;
	InsertIterator	dirtyFlagInserter( dirtyFlagNames );

	m_fieldManager->getDirtyFlagNames( dirtyFlagInserter );

	// Updates the managed model.
	for( i = dirtyFlagNames.begin(); i != dirtyFlagNames.end(); ++i )
	{
		const std::string				name		= *i;
		const vgd::field::DirtyFlag *	dirtyFlag	= m_fieldManager->getDirtyFlag( name );
		assert( dirtyFlag != 0 );

		const std::string value = dirtyFlag->isDirty() ? "dirty" : "valid";
		const std::type_info	& typeInfo	= typeid(*dirtyFlag);



		// Appends a new row to the model.
		QTreeWidgetItem *item = new QTreeWidgetItem( this );
		item->setText( 0, name.c_str() );
		item->setText( 1, value.c_str() );
		item->setText( 2, typeInfo.name() );
	}

	// Retrieves bounding box
	using vgd::node::IBoundingBox;
	vgd::Shp< IBoundingBox > ibb = vgd::dynamic_pointer_cast< IBoundingBox >( m_fieldManager );

	if ( ibb != 0 )
	{
		// Retrieves information about bounding box
		const std::string value = vgUI::graph::toString( ibb.get() );

		// Appends a new row to the model.
		QTreeWidgetItem *item = new QTreeWidgetItem( this );
		item->setText( 0, IBOUNDINGBOX_PREFIX );
		item->setText( 1, value.c_str() );
	}
}


void FieldManagerEditor::onRowActivated(QTreeWidgetItem* item, int column)
{
	Q_UNUSED(column);

	// Retrieves the data row.
	TreeModelColumnRecord *selected = (TreeModelColumnRecord *) item;

	// Uses the row for edition, if it is a field.
	const QString fieldName	= selected->text(0);

	if( fieldName.startsWith(DIRTY_FLAG_PREFIX) == true )
	{
		QMessageBox::information(this, "Property Edition", "Sorry this property is not editable.");
	}
	else
	{
		vgQt::field::FieldEditorDialog::create(this, m_fieldManager, fieldName, m_path, m_canvas);
	}
}


void FieldManagerEditor::setCanvas( vgUI::Canvas * canvas )
{
	m_canvas = canvas;
}


void FieldManagerEditor::setFieldManager( vgd::Shp< vgd::field::FieldManager > fieldManager )
{
	// Disconnects observation from all fields.
	if( m_fieldManager )
	{
		refreshFieldObservation( false );
	}


	// Clear the current state.
	m_fieldManager.reset();


	// If a new field manager is passed, then update the state.
	if( fieldManager )
	{
		m_fieldManager = fieldManager;
		fillModel();
		refreshFieldObservation( true );
	}
}


void FieldManagerEditor::refreshFieldObservation( const bool connect )
{
	// Retrieves all field names.
	typedef std::vector< std::string > 						StringContainer;
	typedef std::back_insert_iterator< StringContainer >	InsertIterator;

	StringContainer	fieldNames;
	InsertIterator	inserter( fieldNames );

	m_fieldManager->getFieldNames( inserter );


	// Updates observations connections.
	StringContainer::const_iterator	i;

	for( i = fieldNames.begin(); i != fieldNames.end(); ++i )
	{
		vgd::field::EditorRO< vgd::field::AbstractField >	editor = m_fieldManager->getFieldRO< vgd::field::AbstractField >(*i);

		if( connect )
		{
			editor->attach( this );
		}
		else
		{
			editor->detach( this );
		}
	}
}


} // namespace graph

} // namespace vgQt
