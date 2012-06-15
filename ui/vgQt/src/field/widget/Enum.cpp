// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#include "vgQt/field/widget/Enum.hpp"

namespace vgQt
{

namespace field
{

namespace widget
{



Enum::Enum()
{
    // Should do the widget creation job here.
}



void Enum::clear()
{
    for( EntryContainer::const_iterator i = m_entries.begin(); i != m_entries.end(); ++i )
    {
        if(i->second->isChecked())
        {
            i->second->setCheckable(false);
            i->second->update();
            i->second->setCheckable(true);
        }
    }
    Q_EMIT signalChanged();
}



const vgd::field::Enum Enum::getValue() const
{
    // Scans entry widgets to get the one active,
    // and if there is one, return the associated enumeration value.
    for( EntryContainer::const_iterator i = m_entries.begin(); i != m_entries.end(); ++i )
    {
        if( i->second->isChecked())
        {
            return vgd::field::Enum( i->first );
        }
    }

    // Default response.
    return vgd::field::Enum();
}

const bool Enum::hasValue() const
{
    // Scans entry widgets to see if there is one begin active.
    for( EntryContainer::const_iterator i = m_entries.begin(); i != m_entries.end(); ++i )
    {
        if( i->second->isChecked() )
        {
            return true;
        }
    }

    // Default response.
    return false;
}

void Enum::buttonClicked()
{
    for( EntryContainer::const_iterator i = m_entries.begin(); i != m_entries.end(); ++i )
    {
        i->second->setChecked( false );
    }

    Q_EMIT signalChanged();
}

void Enum::setValue( const vgd::field::Enum & value )
{
    // First, check the entries for the enumeration values have been created.
    // This should be done in the constructor.
    if( m_entries.empty() )
    {
        typedef std::vector< std::pair< int, std::string > >	EnumEntries;

        const EnumEntries		entries = value.valuesAndStrings();

        for( EnumEntries::const_iterator i = entries.begin(); i != entries.end(); ++i )
        {
            QRadioButton* radioButton = new QRadioButton(QString(i->second.c_str()));
            connect( radioButton, SIGNAL(clicked()), this, SLOT(buttonClicked()) );

            addWidget( radioButton );
            m_entries.push_back( Entry(i->first, radioButton) );
        }
    }


    // Assignes the new value.
    for( EntryContainer::iterator i = m_entries.begin(); i != m_entries.end(); ++i )
    {
        i->second->setChecked( vgd::field::Enum(i->first) == value );
    }

    // Notifies about the change.
    Q_EMIT signalChanged();
}



const bool Enum::validate()
{
    return true;
}



} // namespace widget

} // namespace field

} // namespace vgQt
