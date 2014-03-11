// VGSDK - Copyright (C) 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGGTK_ENGINE_STEREOSCOPICSETTINGS_HPP_
#define _VGGTK_ENGINE_STEREOSCOPICSETTINGS_HPP_

#include <gtkmm.h>

#include <vge/engine/StereoscopicSettings.hpp>
#include "vgGTK/vgGTK.hpp"

#include "vgGTK/Container.hpp"



namespace vgGTK
{

namespace engine
{



/**
 * @brief	A widget that allows to configure stereoscopic settings.
 */
struct VGGTK_API StereoscopicSettings : public Gtk::VBox, public vgGTK::ContainerElement
{
	/**
	 * @brief	Constructor
	 */
	StereoscopicSettings( vgd::Shp< vge::engine::StereoscopicSettings > settings );

	/**
	 * @brief	Retrieves the user settings.
	 */
	const vgd::Shp< vge::engine::StereoscopicSettings > get() const;


private:

	//
	vgd::Shp< vge::engine::StereoscopicSettings > m_settings;	///< The settings to configure.

	// IS ENABLED
	Gtk::CheckButton			m_enabled;						///< The check button to enable/disable stereoscopic rendering

	// EYE SEPARATION
	Gtk::Label					m_eyeSeparationLabel;			///< The label for eye separation
	Gtk::HScale					m_eyeSeparation;				///< The slider to choose the eye separation.

	// IMAGE SHIFT
	Gtk::Label					m_imageShiftLabel;				///< The label for image shift.
	Gtk::HScale					m_imageShift;					///< The slider to choose the image shift.

	// RIGHT EYE
	Gtk::CheckButton			m_rightEye;						///< The check button to enable/disable right eye rendering in stereoscopic mode.

	/**
	 * @name	Signal Handlers
	 */
	//@{
	void onEnabled();					///< Handles isEnabled changes.
	void onEyeSeparationChanged();		///< Handles eye separation changes.
	void onImageShiftChanged();			///< Handles image shift changes.
	void onRightEye();					///< Handles right eye changes.
	//@}

	void refresh();
};



} // namespace engine

} // namespace vgGTK



#endif // _VGGTK_ENGINE_STEREOSCOPICSETTINGS_HPP_
