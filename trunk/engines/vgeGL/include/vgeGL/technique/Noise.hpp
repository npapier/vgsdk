// VGSDK - Copyright (C) 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_TECHNIQUE_NOISE_HPP
#define _VGEGL_TECHNIQUE_NOISE_HPP

#include "vgeGL/technique/SubTechnique.hpp"

namespace glo { struct IResource; }
namespace vgd { namespace node { struct Noise; } }
namespace vgeGL { namespace rc { struct Noise; } }
namespace vgeGL { namespace technique { struct ForwardRendering; } }



namespace vgeGL
{

namespace technique
{



/**
 * @brief Technique implementing noise.
 *
 * @see vgd::node::Noise
 */
struct VGEGL_API Noise : public SubTechnique
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
	void stageInitializeOutputBuffersNodes( vgd::Shp< vgeGL::rc::Noise > rc );

	// randomTexture
	void stageInitializeRandomTexture( vgeGL::engine::Engine * engine, vgd::Shp< vgeGL::rc::Noise > rc );

	// rootPostProcessing and postProcessing of rc
	void stageInitializePostProcessing( vgd::node::Noise * node, vgd::Shp< vgeGL::rc::Noise > rc );

	// updates parameters of post-processing : factors
	void stageUpdatePostProcessingParameters( vgeGL::engine::Engine * engine, vgd::Shp< vgeGL::rc::Noise > rc );


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
	void stageInitializeOutputBuffers( vgeGL::technique::ForwardRendering * technique, vgeGL::engine::Engine * engine, vgd::Shp< vgeGL::rc::Noise > rc );

	//@}



	/**
	 * @name Stage 5
	 */
	//@{

	void stagePostPaint( vgeGL::technique::ForwardRendering * technique, vgeGL::engine::Engine * engine );

	//@}


private:
	vgd::node::Noise * getNoiseNode() const;
};



} // namespace technique

} // namespace vgeGL

#endif //#ifndef _VGEGL_TECHNIQUE_NOISE_HPP
