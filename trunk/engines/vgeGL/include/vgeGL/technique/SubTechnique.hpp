// VGSDK - Copyright (C) 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_TECHNIQUE_SUBTECHNIQUE_HPP
#define _VGEGL_TECHNIQUE_SUBTECHNIQUE_HPP

#include <vge/visitor/NodeCollectorExtended.hpp>
#include "vgeGL/vgeGL.hpp"

namespace vgeGL { namespace engine { struct Engine; } }



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
	 *
	 * Equivalent to reset()
	 */
	SubTechnique();

	/**
	 * @brief Initializes this object.
	 *
	 * Called during stage 1 by meta-technique
	 *
	 * @post !isEnabled()
	 */
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
	 *
	 * @return this technique state before calling this method
	 */
	const bool setEnabled( const bool enabled = true );

	//@}



	/**
	 * @name Visitor interface
	 *
	 * @todo DP visitor ?
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



} // namespace technique

} // namespace vgeGL

#endif //#ifndef _VGEGL_TECHNIQUE_SUBTECHNIQUE_HPP
