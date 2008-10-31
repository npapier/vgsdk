// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#include <string>

#include <gtkmm/box.h>
#include <gtkmm/dialog.h>
#include <gtkmm/label.h>

#include <vgd/Shp.hpp>
#include <vgd/field/FieldManager.hpp>



namespace vgGTK
{

namespace field
{

struct Editor;



/**
 * @brief	Implements a Gtk::Dialog that is specilized in editing a given field.
 */
struct EditorDialog : public Gtk::Dialog
{
	/**
	 * @brief	Constructor
	 *
	 * @param	parent		a parent window for the dialog
	 * @param	fieldManager	the field manager owning the field to edit
	 * @param	fieldName		the name of the field to edit
	 */
	EditorDialog( Gtk::Window & parent, vgd::Shp< vgd::field::FieldManager > fieldManager, const std::string & fieldName );
	
private:

	vgd::Shp< vgd::field::FieldManager >	m_fieldManager;	///< References the owner of the field to edit.
	const std::string						m_fieldName;	///< Holds the name of the field to edit.
	vgd::Shp< Editor >						m_editor;		///< References the field editor.
	
	Gtk::VBox	m_content;
	Gtk::Label	m_label;
	
	void on_response( int response_id );
};



} // namespace field

} // namespace vgGTK
