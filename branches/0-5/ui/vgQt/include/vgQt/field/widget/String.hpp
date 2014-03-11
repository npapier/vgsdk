// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller


#ifndef _VGQT_FIELD_WIDGET_STRING_HPP_
#define _VGQT_FIELD_WIDGET_STRING_HPP_

#include "vgQt/field/widget/Widget.hpp"

#include <QVBoxLayout>
#include <QLineEdit>
#include <QCheckBox>
#include <QTextEdit>

namespace vgQt
{

namespace field
{

namespace widget
{

/**
 * @brief	Implements a widget for std::string edition.
 */
struct String : public QVBoxLayout, public Widget< std::string >
{
Q_OBJECT
public:
    String();

    const std::string getValue() const;
    const bool hasValue() const;
    void setValue( const std::string & value );
    const bool validate();
    void setMultiLine( const bool multi );
    const bool isMultiLine() const;

private:
    QLineEdit * m_entry;
    QTextEdit * m_textView;
    QCheckBox * m_multiLineButton;

public Q_SLOTS:
    void onMultiLineToggled();
    void clear();

Q_SIGNALS:
    void signalChanged();
};



} // namespace widget

} // namespace field

} // namespace vgQt



#endif // _VGQT_FIELD_WIDGET_ENUM_HPP_
