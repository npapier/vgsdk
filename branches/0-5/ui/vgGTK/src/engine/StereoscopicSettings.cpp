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
:	m_settings( settings ),
	m_enabled( "Enable stereoscopic rendering" ),
	m_rightEye( "Disable right eye rendering (for debug)" )
{
	// IS ENABLED
	m_enabled.signal_clicked().connect( sigc::mem_fun(this, &StereoscopicSettings::onEnabled) );

	// EYE SEPARATION
	// label
	m_eyeSeparationLabel.set_alignment(0.f, 0.f);
	m_eyeSeparationLabel.set_text( "Eye separation distance." );

	// slider
	m_eyeSeparation.set_value( 0.f );
	m_eyeSeparation.add_mark( 0.f, Gtk::POS_BOTTOM, "No eye separation" );
	m_eyeSeparation.set_range( -10.f, 10.f );
	m_eyeSeparation.signal_value_changed().connect( sigc::mem_fun(this, &StereoscopicSettings::onEyeSeparationChanged) );

	// IMAGE SHIFT
	// label
	m_imageShiftLabel.set_alignment(0.f, 0.f);
	m_imageShiftLabel.set_text( "Image shift (from no shift to 1/8 of the image width)." );

	// slider
	m_imageShift.set_value( 0.f );
	m_imageShift.add_mark( 0.f, Gtk::POS_BOTTOM, "No shift" );
	m_imageShift.set_range( -100.f, 100.f );
	m_imageShift.signal_value_changed().connect( sigc::mem_fun(this, &StereoscopicSettings::onImageShiftChanged) );

	// RIGHT EYE
	m_rightEye.signal_clicked().connect( sigc::mem_fun(this, &StereoscopicSettings::onRightEye) );

	// Fills box
	set_spacing( 12 );
	pack_start( m_enabled, Gtk::PACK_SHRINK );
	pack_start( m_eyeSeparationLabel, Gtk::PACK_SHRINK );
	pack_start( m_eyeSeparation, Gtk::PACK_SHRINK );
	pack_start( m_imageShiftLabel, Gtk::PACK_SHRINK );
	pack_start( m_imageShift, Gtk::PACK_SHRINK );
	pack_start( m_rightEye, Gtk::PACK_SHRINK );

	// Updates GUI from settings
	refresh();
}



const vgd::Shp< vge::engine::StereoscopicSettings > StereoscopicSettings::get() const
{
	return m_settings;
}



void StereoscopicSettings::onEnabled()
{
	get()->setEnabled( m_enabled.get_active() );

	signalChanged().emit();
}


void StereoscopicSettings::onEyeSeparationChanged()
{
	const float eyeSeparation = static_cast< float >( m_eyeSeparation.get_value() );
	get()->setEyeSeparation( eyeSeparation );

	signalChanged().emit();
}



void StereoscopicSettings::onImageShiftChanged()
{
	const float imageShift = static_cast< float >( m_imageShift.get_value() );
	get()->setImageShift( imageShift );

	signalChanged().emit();
}



void StereoscopicSettings::onRightEye()
{
	get()->setRightEyeEnabled( !m_rightEye.get_active() );

	signalChanged().emit();
}



void StereoscopicSettings::refresh()
{
	m_enabled.set_active( get()->isEnabled() );
	m_eyeSeparation.set_value( get()->getEyeSeparation() );
	m_imageShift.set_value( get()->getImageShift() );
	m_rightEye.set_active( !get()->isRightEyeEnabled() );
}



} // namespace engine

} // namespace vgGTK
