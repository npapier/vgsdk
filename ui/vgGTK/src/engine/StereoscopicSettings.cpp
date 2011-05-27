// VGSDK - Copyright (C) 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgGTK/engine/StereoscopicSettings.hpp"

#include <vgUI/helpers.hpp>



namespace vgGTK
{

namespace engine
{



StereoscopicSettings::StereoscopicSettings( vgd::Shp< vge::engine::StereoscopicSettings > settings )
:	m_settings( settings )
{
	// EYE SEPARATION
	// label
	m_eyeSeparationLabel.set_alignment(0.f, 0.f);
	m_eyeSeparationLabel.set_text( "Eye separation distance." );

	// slider
	m_eyeSeparation.set_value( 0.f );
	m_eyeSeparation.set_range( 0.f, 10.f );
	m_eyeSeparation.signal_value_changed().connect( sigc::mem_fun(this, &StereoscopicSettings::onEyeSeparationChanged) );

	// Fills box
	set_spacing( 12 );
	pack_start( m_eyeSeparationLabel, Gtk::PACK_SHRINK );
	pack_start( m_eyeSeparation, Gtk::PACK_SHRINK );

	// Updates GUI from settings
	refresh();
}



const vgd::Shp< vge::engine::StereoscopicSettings > StereoscopicSettings::get() const
{
	return m_settings;
}



void StereoscopicSettings::onEyeSeparationChanged()
{
	const float eyeSeparation = static_cast< float >( m_eyeSeparation.get_value() );
	m_settings->setEyeSeparation( eyeSeparation );

	signalChanged().emit();
}



void StereoscopicSettings::refresh()
{
	m_eyeSeparation.set_value( get()->getEyeSeparation() );
}



} // namespace engine

} // namespace vgGTK
