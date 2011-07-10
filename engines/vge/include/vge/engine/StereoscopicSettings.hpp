// VGSDK - Copyright (C) 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_ENGINE_STEREOSCOPICSETTINGS_HPP_
#define _VGE_ENGINE_STEREOSCOPICSETTINGS_HPP_

#include "vge/vge.hpp"
#include <vgd/Shp.hpp>

namespace vgd { namespace node { struct Camera; } }



namespace vge
{

namespace engine
{



struct SceneManager;



/**
 * @brief	Allows to configure a scene.
 */
struct VGE_API StereoscopicSettings
{
	/**
	 * @brief	Constructor
	 */
	StereoscopicSettings();



	/**
	 * @brief	Apply the settings on the given scene manager.
	 */
	void apply( vge::engine::SceneManager & ) const;

	/**
	 * @brief	Apply the settings on the given camera.
	 */
	void apply( vgd::Shp< vgd::node::Camera > ) const;


	/**
	 * @name Serialization interface
	 */
	//@{
	void load();	///< load settings from file
	void save();	///< save settings to file
	//@}


	/**
	 * @name Accessors
	 */
	//@{
	const bool isEnabled() const;
	void setEnabled( const bool enabled = true );

	const float getEyeSeparation() const;
	void setEyeSeparation( const float eyeSeparation );

	/**
	 * @brief Returns the current image shift.
	 */
	const float getImageShift() const;

	/**
	 * @brief Sets the current image shift.
	 *
	 * @param imageShift	set a value from 0 to 100 meaning respectively no shift and a shift of 1/8 of the drawing surface.
	 */
	void setImageShift( const float imageShift );
	//@}


private:
	bool	m_isEnabled;						///< Enabled/disabled stereoscopic rendering
	float	m_eyeSeparation;					///< The eye separation to use in Camera node
	float	m_imageShift;						///< The image shift to use in Camera node

	/**
	 * @brief Tests if image shift is valid
	 *
	 * @return true if 0 <= getImageShift() <= 100
	 */
	const bool isImageShiftValid();
};



} // namespace engine

} // namespace vge

#endif // _VGE_ENGINE_STEREOSCOPICSETTINGS_HPP_
