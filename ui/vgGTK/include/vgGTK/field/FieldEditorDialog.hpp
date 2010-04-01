// VGSDK - Copyright (C) 2008, 2009, 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#ifndef _VGGTK_FIELD_FIELDEDITORDIALOG_HPP_
#define _VGGTK_FIELD_FIELDEDITORDIALOG_HPP_

#include <string>

#include <gtkmm/dialog.h>
#include <gtkmm/label.h>

#include <vgd/Shp.hpp>
#include <vgd/field/FieldManager.hpp>
#include <vgd/field/IFieldObserver.hpp>

namespace vgUI {
	struct Canvas;
}



namespace vgGTK
{

namespace field
{

struct FieldEditor;



/**
 * @brief	Implements a Gtk::Dialog that is specilized in editing a given field.
 */
struct FieldEditorDialog : public Gtk::Dialog, public vgd::field::IFieldObserver
{
	/**
	 * @brief	Shows a modeless dialog for editing the given fieldmanager's field.
	 *
	 * @param	parent			a reference to the parent window for the dialog
	 * @param	fieldManager	a field manager
	 * @param	fieldName		a string containing the name of the field to edit
	 * @param	canvas			a pointer to a canvas to refresh on field changes (null by default)
	 */
	static void show( Gtk::Window & parent, vgd::Shp< vgd::field::FieldManager > fieldManager, const std::string & fieldName, vgUI::Canvas * canvas=0 );

	/**
	 * @brief	Destructor
	 */
	~FieldEditorDialog();

	/**
	 * @name	Overrides
	 */
	//@{
	void updateField( const vgd::field::AbstractField & rField, const vgd::field::Event event );
	//@}

	
private:

	typedef std::list< FieldEditorDialog * >	DialogContainer;

	static DialogContainer					m_dialogs;		///< Holds all opened dialogs

	vgd::Shp< vgd::field::FieldManager >	m_fieldManager;	///< References the owner of the field to edit.
	const std::string						m_fieldName;	///< Holds the name of the field to edit.
	vgd::Shp< FieldEditor >					m_editor;		///< References the field editor.
	vgUI::Canvas							* m_canvas;		///< Points to a canvas to refresh on field changes.

	/**
	 * @name	Widgets
	 */
	//@{
	Gtk::Label	m_label;			///< Holds the description of the field being edited
	Gtk::Button	m_closeButton;		///< The button to dismiss the dialog
	Gtk::Button	m_rollbackButton;	///< The button to revert the field changes
	//@}
	
	/**
	 * @brief	Constructor
	 *
	 * @param	parent			a parent window for the dialog
	 * @param	fieldManager	the field manager owning the field to edit
	 * @param	fieldName		the name of the field to edit
	 * @param	canvas			a pointer to the canvas to refresh on field changes (null by default)
	 */
	FieldEditorDialog( Gtk::Window & parent, vgd::Shp< vgd::field::FieldManager > fieldManager, const std::string & fieldName, vgUI::Canvas * canvas=0 );

	/**
	 * @brief	Refreshes the label.
	 */
	void refreshLabel();	
	
	/**
	 * @name	Signal Handlers
	 */
	//@{
	void onClose();										///< Handles close button clicks.
	static void onDialogHidden( FieldEditorDialog* );	///< Handles dialog hide notifications.
	void onEditorChanged();								///< Handles editor changes.
	void onRollback();									///< Handles rollback button clicks.
	//@}
};



} // namespace field

} // namespace vgGTK



#endif // _VGGTK_FIELD_FIELDEDITORDIALOG_HPP_
