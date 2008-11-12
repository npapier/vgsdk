// VGSDK - Copyright (C) 2008, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGGTK_FIELD_EDITOR_HPP_
#define _VGGTK_FIELD_EDITOR_HPP_

#include <string>
#include <gtkmm/widget.h>
#include <vgd/field/FieldManager.hpp>



namespace vgGTK
{

namespace field
{



/**
 * @brief	Provides the abstract implementation of field editors.
 *
 * Implementors should build the user interface widget in the constructor.
 */
struct Editor
{
	/**
	 * @brief	Destructor
	 */
	virtual ~Editor();
	
	
	/**
	 * @name	Widget Management Interface
	 */
	//@{	
	/**
	 * @brief	Retrieves the widget used to edit the field value.
	 */
	virtual Gtk::Widget& getWidget() = 0;
	
	/**
	 * @brief	Sets the focus on the edition widget.
	 */
	virtual void grabFocus() = 0;
	
	/**
	 * @brief	Tells if the editor is resizable.
	 */
	virtual const bool resizable() const = 0;
	//@}

	
	/**
	 * @name	Data Management Interface
	 */
	//@{
	/**
	 * @brief	Commits the new value to the edited field.
	 */
	virtual void commit() = 0;
	
	/**
	 * @brief	Refreshes the user interface widgets to show the field value.
	 */
	virtual void refresh() = 0;
	
	/**
	 * @brief	Validates the current data.
	 */
	virtual const bool validate() = 0;
	
	/**
	 * @brief	Assignes the field to edit.
	 *
	 * @param	fieldManager	a reference to a field manager
	 * @param	fieldName		the name of the field to edit
	 */
	void setField( vgd::Shp< vgd::field::FieldManager > fieldManager, const std::string & fieldName );	
	//@}
	
protected:

	vgd::Shp< vgd::field::FieldManager >	m_fieldManager;	///< References the field manager
	std::string								m_fieldName;	///< Holds the name of the field to edit
};



} // namespace field

} // namespace vgGTK



#endif // _VGGTK_FIELD_EDITOR_HPP_
