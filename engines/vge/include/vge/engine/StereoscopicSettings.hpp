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
	const float getEyeSeparation() const					{ return m_eyeSeparation; }
	void setEyeSeparation( const float eyeSeparation )		{ m_eyeSeparation = eyeSeparation; }
	//@}


private:
	float m_eyeSeparation;					///< The eye separation to use in Camera node
};



} // namespace engine

} // namespace vge

#endif // _VGE_ENGINE_STEREOSCOPICSETTINGS_HPP_
