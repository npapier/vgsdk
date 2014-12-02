//// VGSDK - Copyright (C) 2012, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_TECHNIQUE_ANTIALIASING_HPP
//#define _VGEGLBASE_TECHNIQUE_ANTIALIASING_HPP
//
//#include "vgeGLBase/technique/SubTechnique.hpp"
//
//namespace glo { struct IResource; }	// @todo in SubTechnique
//namespace vgd { namespace node { struct Antialiasing; } }
//namespace vgeGLBase { namespace rc { struct Antialiasing; } }
//namespace vgeGLBase { namespace technique { struct ForwardRendering; } } // @todo Technique
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
// * @brief Technique implementing antialiasing.
// *
// * @see vgd::node::Antialiasing
// */
//struct VGEGLBASE_API Antialiasing : public SubTechnique
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
//	void stageInitializeOutputBuffersNodes( vgd::Shp< vgeGLBase::rc::Antialiasing > rc );
//
//	// rootPostProcessing and postProcessing of rc
//	void stageInitializePostProcessing( vgd::node::Antialiasing * node, vgd::Shp< vgeGLBase::rc::Antialiasing > rc );
//
//	// updates parameters of post-processing
//	void stageUpdatePostProcessingParameters( vgeGLBase::engine::Engine * engine, vgd::Shp< vgeGLBase::rc::Antialiasing > rc );
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
//	void stageInitializeOutputBuffers( vgeGLBase::technique::ForwardRendering * technique, vgeGLBase::engine::Engine * engine, vgd::Shp< vgeGLBase::rc::Antialiasing > rc );
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
//	vgd::node::Antialiasing * getAntialiasingNode() const;
//};
//
//
//
//} // namespace technique
//
//} // namespace vgeGLBase
//
//#endif //#ifndef _VGEGLBASE_TECHNIQUE_ANTIALIASING_HPP
//