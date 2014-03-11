// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGQT_FIELD_FIELDEDITOR_HPP_
#define _VGQT_FIELD_FIELDEDITOR_HPP_

#include <vgUI/Canvas.hpp>

#include <vgd/field/IFieldObserver.hpp>
#include <vgd/field/FieldManager.hpp>
#include "vgQt/field/widget/Widget.hpp"

#include <QWidget>
#include <QString>
#include <QLayout>
#include <QPushButton>

namespace vgQt
{

namespace field
{

/**
 * @brief	Provides the abstract implementation for field editors.
 *
 * Implementors should build the user interface widget in the constructor.
 */

struct FieldEditor : QWidget, public vgd::field::IFieldObserver
{
Q_OBJECT
public:
    /**
     * @brief	Constructor
     */
    FieldEditor();

    void updateField( const vgd::field::AbstractField & rField, const vgd::field::Event event );
    /**
	 * @brief	Destructor
	 */
	virtual ~FieldEditor();
	
    /**
     * @brief	Retrieves the widget used to edit the field value.
     */
    virtual QLayout* getWidget() = 0;

    /**
     * @brief	Retrieves the layout
     */
    virtual QLayout* getLayout() = 0;

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
     * @brief	Retrieves the initial value of the edited field.
     */
    virtual void rollback() = 0;

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
    void setField( vgd::Shp< vgd::field::FieldManager > fieldManager, const QString fieldName );

	//@}
    void initialize(QWidget* parent, vgUI::Canvas * canvas);

	vgd::Shp< vgd::field::FieldManager >	m_fieldManager;	///< References the field manager
    QString 								m_fieldName;	///< Holds the name of the field to edit

    /**
     * @brief	Retrieves the signal emited when the content has changed.
     */

private:
    vgUI::Canvas * m_canvas;

Q_SIGNALS:
    void signalChanged();
    void titleChanged(QString);

public Q_SLOTS:
    /**
     * @brief   This is only for the MultiFielEditor
     */
    //@{
    virtual void addClicked(){}
    virtual void removeClicked(){}
    virtual void moveUpClicked(){}
    virtual void moveDownClicked(){}
    //@}
    void refreshLabel();
    void onEditorChanged();
    void onRollback();
};



} // namespace field

} // namespace vgQt

#endif // _VGQT_FIELD_FIELDEDITOR_HPP_
