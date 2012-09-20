// VGSDK - Copyright (C) 2012, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_TECHNIQUE_ANTIALIASING_HPP
#define _VGEGL_TECHNIQUE_ANTIALIASING_HPP

#include "vgeGL/technique/SubTechnique.hpp"

namespace glo { struct IResource; }	// @todo in SubTechnique
namespace vgd { namespace node { struct Antialiasing; } }
namespace vgeGL { namespace rc { struct Antialiasing; } }
namespace vgeGL { namespace technique { struct ForwardRendering; } } // @todo Technique



namespace vgeGL
{

namespace technique
{



/**
 * @brief Technique implementing antialiasing.
 *
 * @see vgd::node::Antialiasing
 */
struct VGEGL_API Antialiasing : public SubTechnique
{
	/**
	 * @name Stage 1
	 */
	//@{
	virtual void stageCollectInformationsBegin( vgeGL::engine::Engine * engine );
	virtual const bool collectInformationsCallback( vge::visitor::TraverseElementVector::const_iterator iterator );
	//@}


	/**
	 * @name Stage 2
	 */
	//@{

	// colorBuffer of rc
	void stageInitializeOutputBuffersNodes( vgd::Shp< vgeGL::rc::Antialiasing > rc );

	// rootPostProcessing and postProcessing of rc
	void stageInitializePostProcessing( vgd::node::Antialiasing * node, vgd::Shp< vgeGL::rc::Antialiasing > rc );

	// updates parameters of post-processing
	void stageUpdatePostProcessingParameters( vgeGL::engine::Engine * engine, vgd::Shp< vgeGL::rc::Antialiasing > rc );


	void stageInitializeRC( vgeGL::technique::ForwardRendering * technique, vgeGL::engine::Engine * engine );
	const bool isRCUpdated( vgeGL::technique::ForwardRendering * technique, vgeGL::engine::Engine * engine, vgd::Shp< glo::IResource > rc );
	void updateRC( vgeGL::technique::ForwardRendering * technique, vgeGL::engine::Engine * engine, vgd::Shp< glo::IResource > rc );

	//@}


	/**
	 * @name Stage 3
	 */
	//@{

	void stagePrePaint( vgeGL::technique::ForwardRendering * technique, vgeGL::engine::Engine * engine );

	// hasOutputBufferProperties and m_outputBufferProperties of technique
	void stageInitializeOutputBuffers( vgeGL::technique::ForwardRendering * technique, vgeGL::engine::Engine * engine, vgd::Shp< vgeGL::rc::Antialiasing > rc );

	//@}



	/**
	 * @name Stage 5
	 */
	//@{

	void stagePostPaint( vgeGL::technique::ForwardRendering * technique, vgeGL::engine::Engine * engine );

	//@}


private:
	vgd::node::Antialiasing * getAntialiasingNode() const;
};



} // namespace technique

} // namespace vgeGL

#endif //#ifndef _VGEGL_TECHNIQUE_ANTIALIASING_HPP
