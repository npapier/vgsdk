// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGQT_FIELD_ADAPTER_MFVECTORADAPTER_HPP_
#define _VGQT_FIELD_ADAPTER_MFVECTORADAPTER_HPP_

#include "vgQt/field/adapter/MFAdapter.hpp"

#include <vector>
#include <vgUI/helpers.hpp>

#include <QTreeWidget>

namespace vgQt
{

namespace field
{

namespace adapter
{

/**
 * @brief	Multi-field editor adapter for vgm::Vector values.
 */
template< typename VectorType >
struct MFVectorAdapter : public MFAdapter< VectorType >
{
    MFVectorAdapter()
    :	m_columns( VectorType().getDim() )
    {}

    void addColumnsToView( QTreeWidget* treeView )
    {
        QStringList titles;
        titles << "index";
        for( unsigned int i = 0; i < m_columns.size(); ++i )
        {
            titles << QString(vgUI::compose("%1%",i).c_str());
        }
        treeView->setHeaderLabels( titles );
    }

    void updateToRow( QTreeWidgetItem* row, const VectorType & value) const
    {
        for( unsigned int i = 1; i <= m_columns.size(); ++i )
        {
            row->setText(i, QString::number(value[i - 1]));
        }
    }

    void updateFromRow( const QTreeWidgetItem* row, VectorType & value ) const
    {
        for( unsigned int i = 1; i <= m_columns.size(); ++i )
        {
            value[i - 1] = row->text(i).toFloat();
        }
    }

private:
    typedef std::vector< QString >	ColumnContainer;

    ColumnContainer	m_columns;
};

} // namespace adapter

} // namespace field

} // namespace vgQt

#endif // _VGQT_FIELD_ADAPTER_MFVECTORADAPTER_HPP_
