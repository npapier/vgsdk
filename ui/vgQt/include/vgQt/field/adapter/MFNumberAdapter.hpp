// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGQT_FIELD_ADAPTER_MFNUMBERADAPTER_HPP_
#define _VGQT_FIELD_ADAPTER_MFNUMBERADAPTER_HPP_

#include "vgQt/field/adapter/MFAdapter.hpp"

#include <QTreeWidget>

namespace vgQt
{

namespace field
{

namespace adapter
{

/**
 * @brief	Multi-field editor adapter for numeric values.
 */
template< typename NumberType >
struct MFNumberAdapter : public MFAdapter< NumberType >
{
    void addColumnsToView( QTreeWidget* treeView )
    {
        QStringList titles;
        titles << "Index" << "Value";
        treeView->setHeaderLabels( titles );
    }

    void updateToRow( QTreeWidgetItem* row, const NumberType & value) const
    {
        row->setText(1, QString::number(value));
    }

    void updateFromRow( const QTreeWidgetItem* row, NumberType & value ) const
    {
        value = (NumberType) row->text(1).toDouble();
    }

private:

};

} // namespace adapter

} // namespace field

} // namespace vgQt

#endif // _VGQT_FIELD_ADAPTER_MFNUMBERADAPTER_HPP_
