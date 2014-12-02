//// VGSDK - Copyright (C) 2011, 2012, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_TECHNIQUE_NOISE_HPP
//#define _VGEGLBASE_TECHNIQUE_NOISE_HPP
//
//#include "vgeGLBase/technique/SubTechnique.hpp"
//
//namespace glo { struct IResource; }
//namespace vgd { namespace node { struct Noise; } }
//namespace vgeGLBase { namespace rc { struct Noise; } }
//namespace vgeGLBase { namespace technique { struct ForwardRendering; } }
//
//
//
//namespace vgeGLBase
//{
//
//namespace technique
//{
//
//
//
///**
// * @brief Technique implementing noise.
// *
// * @see vgd::node::Noise
// */
//struct VGEGLBASE_API Noise : public SubTechnique
//{
//	/**
//	 * @name Stage 1
//	 */
//	//@{
//	virtual void stageCollectInformationsBegin( vgeGLBase::engine::Engine * engine );
//	virtual const bool collectInformationsCallback( vge::visitor::TraverseElementVector::const_iterator iterator );
//	//@}
//
//
//	/**
//	 * @name Stage 2
//	 */
//	//@{
//
//	// colorBuffer of rc
//	void stageInitializeOutputBuffersNodes( vgd::Shp< vgeGLBase::rc::Noise > rc );
//
//	// randomTexture
//	void stageInitializeRandomTexture( vgeGLBase::engine::Engine * engine, vgd::Shp< vgeGLBase::rc::Noise > rc, vgd::node::Noise * noise );
//
//	// rootPostProcessing and postProcessing of rc
//	void stageInitializePostProcessing( vgd::node::Noise * node, vgd::Shp< vgeGLBase::rc::Noise > rc );
//
//	// updates parameters of post-processing : factors
//	void stageUpdatePostProcessingParameters( vgeGLBase::engine::Engine * engine, vgd::Shp< vgeGLBase::rc::Noise > rc );
//
//
//	void stageInitializeRC( vgeGLBase::technique::ForwardRendering * technique, vgeGLBase::engine::Engine * engine );
//	const bool isRCUpdated( vgeGLBase::technique::ForwardRendering * technique, vgeGLBase::engine::Engine * engine, vgd::Shp< glo::IResource > rc );
//	void updateRC( vgeGLBase::technique::ForwardRendering * technique, vgeGLBase::engine::Engine * engine, vgd::Shp< glo::IResource > rc );
//
//	//@}
//
//
//	/**
//	 * @name Stage 3
//	 */
//	//@{
//
//	void stagePrePaint( vgeGLBase::technique::ForwardRendering * technique, vgeGLBase::engine::Engine * engine );
//
//	// hasOutputBufferProperties and m_outputBufferProperties of technique
//	void stageInitializeOutputBuffers( vgeGLBase::technique::ForwardRendering * technique, vgeGLBase::engine::Engine * engine, vgd::Shp< vgeGLBase::rc::Noise > rc );
//
//	//@}
//
//
//
//	/**
//	 * @name Stage 5
//	 */
//	//@{
//
//	void stagePostPaint( vgeGLBase::technique::ForwardRendering * technique, vgeGLBase::engine::Engine * engine );
//
//	//@}
//
//
//private:
//	vgd::node::Noise * getNoiseNode() const;
//};
//
//
//
//} // namespace technique
//
//} // namespace vgeGLBase
//
//#endif //#ifndef _VGEGLBASE_TECHNIQUE_NOISE_HPP
//