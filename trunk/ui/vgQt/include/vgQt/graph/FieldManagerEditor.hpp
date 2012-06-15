// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGQT_GRAPH_FIELDMANAGEREDITOR_HPP_
#define _VGQT_GRAPH_FIELDMANAGEREDITOR_HPP_

#include <vgd/field/FieldManager.hpp>
#include <vgd/field/IFieldObserver.hpp>

#include "vgQt/graph/TreeModelColumnRecord.hpp"

#include <QTreeWidget>

namespace vgUI {
    struct Canvas;
}

namespace vgQt
{

namespace graph
{

/**
 * @brief	Implements a Qt based widget that allows to edit a field manager.
 */

struct FieldManagerEditor : public QTreeWidget, public vgd::field::IFieldObserver
{
    Q_OBJECT
public:
    /**
     * @brief	Constructor
     */
    FieldManagerEditor( QWidget *parent );

    /**
     * @brief	Clears the editor.
     */
    void clear();

    /**
     * @name	Overrides
     */
    //@{
    void updateField( const vgd::field::AbstractField &rField, const vgd::field::Event event );
    //@}

    /**
     * @brief   Assignes the path of the node
     *
     * @param   path    the path of the node
     */
    void setPath (QString path);

    /**
     * @brief	Assignes the canvas to refresh after field changes.
     *
     * @param	canvas	a pointer to a canvas, null if none
     */
    void setCanvas( vgUI::Canvas * canvas );

    /**
     * @brief	Assignes the field manager to editor.
     *
     * @param	fieldManager	a reference to a field manager, empty to clear the editor
     *
     * @see		clear
     */
    void setFieldManager( vgd::Shp< vgd::field::FieldManager > fieldManager );

    void refreshFieldObservation( const bool connect );

private:
    /**
     * @brief	Fills the managed model with the curent field manager.
     */
    void fillModel();

protected:
    vgUI::Canvas							* m_canvas;		///< Points to the canvas to refresh.
    vgd::Shp< vgd::field::FieldManager >	m_fieldManager;	///< References the fied manager to edit.
    QString                                 m_path;

public Q_SLOTS:
    void onRowActivated(QTreeWidgetItem* item, int column);
Q_SIGNALS:
    void onChangeSignal();
};

} // namespace graph

} // namespace vgQt

#endif // _VGQT_GRAPH_FIELDMANAGEREDITOR_HPP_
