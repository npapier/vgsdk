// VGSDK - Copyright (C) 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_TECHNIQUE_DEPTHOFFIELD_HPP
#define _VGEGL_TECHNIQUE_DEPTHOFFIELD_HPP

#include "vge/visitor/NodeCollectorExtended.hpp"
#include "vgeGL/vgeGL.hpp"

namespace glo { struct IResource; }
namespace vgd { namespace node { struct DepthOfField; } }
namespace vgeGL { namespace engine { struct Engine; } }
namespace vgeGL { namespace rc { struct DepthOfField; } }
namespace vgeGL { namespace technique { struct ForwardRendering; } }



namespace vgeGL
{

namespace technique
{


struct VGEGL_API SubTechnique
{
	/**
	 * @name Constructors
	 */
	//@{

	/**
	 * @brief Constructor
	 */
	SubTechnique();

	void reset();

	//@}


	/**
	 * @name Enable/disable
	 */
	//@{

	/**
	 * @brief Determines whether this technique is enabled.
	 *
	 * @return true if this technique is enabled, false otherwise
	 */
	const bool isEnabled() const;

	/**
	 * @brief Enables or disables this technique depending on the value of the parameter isEnabled.
	 *
	 * @param isEnabled		true when this technique must be enabled, false otherwise
	 * @return this technique state before calling this method
	 */
	const bool setEnabled( const bool enabled = true );

	//@}



	/**
	 * @name Visitor interface @todo DP visitor ?
	 */
	//@{

	/**
	 * @brief Invoked on the first stage of rendering to collect informations used by this technique.
	 */
	virtual void stageCollectInformationsBegin( vgeGL::engine::Engine * engine )
	{}

	virtual const bool collectInformationsCallback( vge::visitor::TraverseElementVector::const_iterator iterator )
	{ return false; }

	virtual void stageCollectInformationsEnd( vgeGL::engine::Engine * engine )
	{}
	//@}


	/**
	 * @name
	 */
	//@{
	//@}


private:
	bool m_isEnabled;
};



struct VGEGL_API DepthOfField : public SubTechnique
{
	/**
	 @name Constructors
	 */
	//@{

	/**
	 * @brief Constructors
	 */
	DepthOfField();

	// called during stage 1 by meta-technique
	void reset();
	//@}


	/**
	 * @name Stage 1 (the first) : Extract informations
	 */
	//@{
	virtual void stageCollectInformationsBegin( vgeGL::engine::Engine * engine );
	virtual const bool collectInformationsCallback( vge::visitor::TraverseElementVector::const_iterator iterator );
	//@}


	/**
	 * @name Stage 2 : Initializes RC
	 */
	//@{
	vgd::Shp< vgeGL::rc::DepthOfField > getRC( vgeGL::engine::Engine * engine );

	// colorBuffer and blurFactorBuffer of rc
	void stageInitializeOutputBuffersNodes( vgd::Shp< vgeGL::rc::DepthOfField > rc );

	// rootPostProcessing and postProcessing of rc
	void stageInitializePostProcessing( vgd::node::DepthOfField * node, vgd::Shp< vgeGL::rc::DepthOfField > rc );

	// updates parameters of post-processing : final.numberOfTaps
	void stageUpdatePostProcessingParameters( vgeGL::engine::Engine * engine, vgd::Shp< vgeGL::rc::DepthOfField > rc );

	void stageInitializeRC( vgeGL::technique::ForwardRendering * technique, vgeGL::engine::Engine * engine );
		const bool isRCUpdated( vgd::Shp< glo::IResource > rc );
		// @todo createRC/updateRC ?
		void updateRC( vgeGL::technique::ForwardRendering * technique, vgeGL::engine::Engine * engine, vgd::Shp< glo::IResource > rc );

	//@}


	/**
	 * @name Stage 3 : Pre-paint pass
	 */
	//@{

	/* virtual @todo*/ void stagePrePaint( vgeGL::technique::ForwardRendering * technique, vgeGL::engine::Engine * engine );

	// hasOutputBufferProperties and m_outputBufferProperties of technique
	void stageInitializeOutputBuffers( vgeGL::technique::ForwardRendering * technique, vgeGL::engine::Engine * engine, vgd::Shp< vgeGL::rc::DepthOfField > rc );

	//@}


	/**
	 * @name Stage 4 : Paint pass
	 */
	//@{

	// called after beginPass() of paint pass
	void stageBeginPaint( vgeGL::technique::ForwardRendering * technique, vgeGL::engine::Engine * engine ) {}
	void stagePaint( vgeGL::technique::ForwardRendering * technique, vgeGL::engine::Engine * engine ) {}
	void stageEndPaint( vgeGL::technique::ForwardRendering * technique, vgeGL::engine::Engine * engine ) {}

	//@}


	/**
	 * @name Stage 5 : Post-paint pass
	 */
	//@{

	/* virtual @todo*/ void stagePostPaint( vgeGL::technique::ForwardRendering * technique, vgeGL::engine::Engine * engine );

	//@}


private:
	vgd::node::DepthOfField * m_dof;
};



} // namespace technique

} // namespace vgeGL

#endif //#ifndef _VGEGL_TECHNIQUE_DEPTHOFFIELD_HPP

