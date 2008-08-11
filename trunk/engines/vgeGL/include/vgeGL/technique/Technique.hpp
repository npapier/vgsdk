// VGSDK - Copyright (C) 2004, 2007, 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_TECHNIQUE_TECHNIQUE_HPP
#define _VGEGL_TECHNIQUE_TECHNIQUE_HPP

#include <vge/technique/Technique.hpp>

#include "vgeGL/vgeGL.hpp"

namespace vgeGL
{
	namespace engine { struct Engine; }
}



/**
 * @namespace vgeGL::technique
 * 
 * @brief Describes multi-pass strategy used by engine to evaluate a scene graph using OpenGL.
 *
 * @defgroup g_techniques_vgeGL	Technique from vgeGL
 *
 * @brief Specialized techniques using OpenGL
 *
 * @ingroup g_techniques
 */



namespace vgeGL
{

namespace technique
{



/**
 * @brief Base class for all technique using OpenGL.
 */
struct VGEGL_CLASS_API Technique : public vge::technique::Technique
{
	/**
	 * @brief Default constructor
	 */
	VGEGL_API Technique();

	/**
	 * @brief Must be overridden to implements the technique.
	 * 
	 * @param engine			engine used during evaluation
	 * @param traverseElements	elements to evaluate
	 */
	VGEGL_API virtual void apply(	vgeGL::engine::Engine * engine, vge::visitor::TraverseElementVector* traverseElements ) = 0;



protected:
	/**
	 * @copydoc ::vge::technique::Technique::prepareEval(vge::engine::Engine*, vge::visitor::TraverseElementVector*)
	 */
	VGEGL_API void prepareEval( vgeGL::engine::Engine *engine, vge::visitor::TraverseElementVector* traverseElements );
	
	/**
	 * @copydoc ::vge::technique::Technique::evaluatePass(vgd::Shp<vge::pass::Pass>, vgd::Shp<vge::service::Service>)
	 */
	VGEGL_API void evaluatePass( vgd::Shp< vge::pass::Pass > pass, vgd::Shp< vge::service::Service > service );
	

	
private:
	VGEGL_API void prepareEval( vge::engine::Engine * /*engine*/, vge::visitor::TraverseElementVector * /*traverseElements*/ );
	VGEGL_API void apply(		vge::engine::Engine * /*engine*/, vge::visitor::TraverseElementVector * /*traverseElements*/ );
	
	/**
	 * @name Internal data
	 */
	//@{
	vgeGL::engine::Engine	*				m_engine;
	//@}	
};



} // namespace technique

} // namespace vgeGL

#endif //#ifndef _VGEGL_TECHNIQUE_TECHNIQUE_HPP
