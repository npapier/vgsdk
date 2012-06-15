// VGSDK - Copyright (C) 2008, 2010, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGQT_CONVENIENCEWIDGET_HPP_
#define _VGQT_CONVENIENCEWIDGET_HPP_

#include <limits>
#include <QDoubleSpinBox>

namespace vgQt
{

template< typename NumberType >
void configure( QDoubleSpinBox * sb )
{
    typedef std::numeric_limits< NumberType >	limits;

    const int		digits		= limits::is_integer ? 0 : 5;
    const double	lower		= limits::is_integer ? static_cast<double>(limits::min()) : -static_cast<double>(limits::max());
    const double	upper		= limits::max();
    const double	stepIncr	= limits::is_integer ? 1.0 : 0.1;

    sb->setDecimals( digits );
    sb->setRange(lower, upper);
    sb->setSingleStep( stepIncr );
}

} // namespace vgQt

#endif // _VGQT_CONVENIENCEWIDGET_HPP_
