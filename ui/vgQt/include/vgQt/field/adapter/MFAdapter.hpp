// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGQT_FIELD_ADAPTER_MFADAPTER_HPP_
#define _VGQT_FIELD_ADAPTER_MFADAPTER_HPP_

#include <QTreeWidget>

namespace vgQt
{

namespace field
{

namespace adapter
{

/**
 * @brief	Abstract adapter for multi-field value edition.
 *
 * @see	vgQt::field::MultiFieldEditor
 */
template< typename T >
struct MFAdapter
{
    virtual void addColumnsToView( QTreeWidget* treeView ) = 0;
    virtual void updateToRow( QTreeWidgetItem* row, const T & value) const = 0;
    virtual void updateFromRow( const QTreeWidgetItem* row, T & value ) const = 0;

    typedef T value_type;	///< Defines an alias on the value type to edit.

protected:

};

} // namespace adapter

} // namespace field

} // namespace vgQt

#endif // _VGQT_FIELD_ADAPTER_MFADAPTER_HPP_
