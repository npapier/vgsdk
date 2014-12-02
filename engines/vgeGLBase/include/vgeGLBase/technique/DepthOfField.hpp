//// VGSDK - Copyright (C) 2011, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_TECHNIQUE_DEPTHOFFIELD_HPP
//#define _VGEGLBASE_TECHNIQUE_DEPTHOFFIELD_HPP
//
//#include "vgeGLBase/technique/SubTechnique.hpp"
//
//namespace glo { struct IResource; }
//namespace vgd { namespace node { struct DepthOfField; } }
//namespace vgeGLBase { namespace rc { struct DepthOfField; } }
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
//struct VGEGLBASE_API DepthOfField : public SubTechnique
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
//	// colorBuffer and blurFactorBuffer of rc
//	void stageInitializeOutputBuffersNodes( vgd::Shp< vgeGLBase::rc::DepthOfField > rc );
//
//	// rootPostProcessing and postProcessing of rc
//	void stageInitializePostProcessing( vgd::node::DepthOfField * node, vgd::Shp< vgeGLBase::rc::DepthOfField > rc );
//
//	// updates parameters of post-processing : final.numberOfTaps
//	void stageUpdatePostProcessingParameters( vgeGLBase::engine::Engine * engine, vgd::Shp< vgeGLBase::rc::DepthOfField > rc );
//
//
//	void stageInitializeRC( vgeGLBase::technique::ForwardRendering * technique, vgeGLBase::engine::Engine * engine );
//
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
//	void stageInitializeOutputBuffers( vgeGLBase::technique::ForwardRendering * technique, vgeGLBase::engine::Engine * engine, vgd::Shp< vgeGLBase::rc::DepthOfField > rc );
//
//	//@}
//
//
//	/**
//	 * @name Stage 4 : Paint pass
//	 */
//	//@{
//	void stageBeginPaint( vgeGLBase::technique::ForwardRendering * technique, vgeGLBase::engine::Engine * engine );
//	//@}
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
//	vgd::node::DepthOfField * getDOFNode() const;
//};
//
//
//
//} // namespace technique
//
//} // namespace vgeGLBase
//
//#endif //#ifndef _VGEGLBASE_TECHNIQUE_DEPTHOFFIELD_HPP
//