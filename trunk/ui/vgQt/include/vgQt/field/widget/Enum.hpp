// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller


#ifndef _VGQT_FIELD_WIDGET_ENUM_HPP_
#define _VGQT_FIELD_WIDGET_ENUM_HPP_

#include <utility>
#include <vector>

#include <vgd/field/Enum.hpp>

#include "vgQt/field/widget/Widget.hpp"

#include <QVBoxLayout>
#include <QRadioButton>

namespace vgQt
{

namespace field
{

namespace widget
{

/**
 * @brief	Implements a widget for edition vgd::field::Enum edition.
 */
struct Enum : public QVBoxLayout, public Widget< vgd::field::Enum >
{
Q_OBJECT
public:
    Enum();

    const vgd::field::Enum getValue() const;
    const bool hasValue() const;
    void setValue( const vgd::field::Enum & value );
    const bool validate();

private:

    typedef std::pair< int, QRadioButton * >    Entry;
    typedef std::vector< Entry >				EntryContainer;

    EntryContainer                              m_entries;	///< Holds all possible values and the associated widget.

public Q_SLOTS:
    void buttonClicked();
    void clear();

Q_SIGNALS:
    void signalChanged();
};



} // namespace widget

} // namespace field

} // namespace vgQt



#endif // _VGQT_FIELD_WIDGET_ENUM_HPP_
