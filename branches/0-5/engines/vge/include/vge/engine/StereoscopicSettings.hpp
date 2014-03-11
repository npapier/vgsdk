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

	/**
	 * @brief Returns the distance between the left and right eye
	 *
	 * @return the distance between the left and right eye
	 */
	const float getEyeSeparation() const;

	/**
	 * @brief Sets the distance between the left and right eye
	 *
	 * @param eyeSeparation		set a value greater than zero to translate the left eye in the left direction of eyeSeparation/2.
	 *		A value less than zero to translate the left eye in the right direction of eyeSeparation/2.
	 */
	void setEyeSeparation( const float eyeSeparation );

	/**
	 * @brief Returns the current image shift.
	 */
	const float getImageShift() const;

	/**
	 * @brief Sets the current image shift.
	 *
	 * @param imageShift	set a value from -100 to 100 meaning respectively shift of 1/8 of the drawing surface in the left direction,
	 *						shift of 1/8 of the drawing surface in the right direction. 0 means no shift at all.
	 */
	void setImageShift( const float imageShift );

	const bool isRightEyeEnabled() const;
	void setRightEyeEnabled( const bool enabled = true );
	//@}


private:
	bool	m_isEnabled;						///< Enabled/disabled stereoscopic rendering
	float	m_eyeSeparation;					///< The eye separation to use in Camera node
	float	m_imageShift;						///< The image shift to use in Camera node
	bool	m_isRightEyeEnabled;				///< Enabled/disabled right eye rendering in stereoscopic mode


	/**
	 * @brief Tests if eye separation is valid
	 *
	 * @return Always true
	 */
	const bool isEyeSeparationValid( const float eyeSeparation );

	/**
	 * @brief Tests if image shift is valid
	 *
	 * @return true if -100 <= getImageShift() <= 100
	 */
	const bool isImageShiftValid( const float imageShift );
};



} // namespace engine

} // namespace vge

#endif // _VGE_ENGINE_STEREOSCOPICSETTINGS_HPP_
