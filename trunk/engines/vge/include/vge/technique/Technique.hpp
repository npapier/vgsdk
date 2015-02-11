// VGSDK - Copyright (C) 2004, 2006, 2007, 2008, 2009, 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_TECHNIQUE_TECHNIQUE_HPP
#define _VGE_TECHNIQUE_TECHNIQUE_HPP

#include "vge/visitor/NodeCollectorExtended.hpp" // @todo remove me

namespace vgd { template<class T> struct Shp; }

namespace vge
{
	namespace engine { struct Engine; struct SceneManager; }

	namespace pass { struct Pass; }

	namespace service { struct Painter; struct Service; }
}



/**
 * @defgroup g_techniques Techniques
 *
 * @brief Describes multi-pass strategy used by engine to evaluate a scene graph.
 */

/**
 * @defgroup g_techniques_vge Techniques from vge
 *
 * @brief Techniques using CPU
 *
 * @ingroup g_techniques
 */



namespace vge
{

/** 
 * @namespace vge::technique
 * 
 * @brief Describes multi-pass strategy used by engine to evaluate a scene graph.
 */
namespace technique
{

/**
 * @brief Technique describes the strategy to evaluate collected nodes in engine for single or multi-pass evaluation 
 * algorithm.
 * 
 * @code // Example to compute all bounding boxes in a scene graph.
 * #include <vge/engine/Engine.hpp>
 * #include <vge/technique/ComputeBoundingBox.hpp>
 * #include <vge/visitor/NodeCollectorExtended.hpp>
 * 
 * void apply( vge::engine::Engine *pEngine )
 * {
 * 	// Step 1 : Collect nodes.
 * 	vge::visitor::NodeCollectorExtended<> collector;
 * 	getRoot()->traverse( collector );
 * 
 * 	// Step 2 : Compute bounding box for the scene graph
 * 	vge::technique::ComputeBoundingBox computeBB;
 * 	computeBB.apply( pEngine, collector.getTraverseElements() );
 * 
 * 	// Step 3 : Use accessors of the technique to retrieve additionnal informations (if any).
 * 	...
 * }
 * @endcode
 * 
 * @todo cleans this class (see commented code)
 *
 * @todo more documentation...
 * @todo virtual void push(); and virtual void pop();
 */
struct VGE_API Technique
{
	/**
	 * @name Constructor/destructor
	 */
	//@{

	/**
	 * @brief Constructor
	 */
	Technique();

	/**
	 * @brief Virtual destructor
	 */
	virtual ~Technique();

	//@}



	/**
	 * @name Input parameters accessors
	 */
	//@{

	/**
	 * @brief Sets input parameters of the technique
	 *
	 * @pre engine != 0 and valid
	 * @pre traverseElements != 0 and valid
	 *
	 * @param engine			engine used during evaluation
	 * @param traverseElements	elements to evaluate
	 * @param sceneManager		a scene manager (containing scene graph root, engine and vgsdk startup/shutdown api)
	 */
	void setParameters( vge::engine::Engine * engine, vge::visitor::TraverseElementVector * traverseElements, vge::engine::SceneManager * sceneManager = 0 );


	/**
	 * @brief Returns the engine
	 *
	 * @return a reference on the engine
	 * @todo remove me
	 */
	vge::engine::Engine * engine() const;

	/**
	 * @brief Returns collected nodes
	 *
	 * @return the traverse element vector
	 * @todo remove me
	 */
	vge::visitor::TraverseElementVector * traverseElements() const;

	/**
	 * @brief Returns the scene manager
	 *
	 * @return a reference on the scene manager
	 * @todo remove me
	 */
	vge::engine::SceneManager * sceneManager() const;

	//@}



	/**
	 * @brief Must be overridden to implements the technique.
	 * 
	 * @param engine			engine used during evaluation	@todo remove me
	 * @param traverseElements	elements to evaluate			@todo remove me
	 */
	virtual void apply( vge::engine::Engine * engine/*ignored*/, vge::visitor::TraverseElementVector* traverseElements /* ignored */) = 0;



protected:

	/**
	 * @brief Initializes the technique to prepare evaluation.
	 * 
	 * @remark Must be called before starting nodes evaluation.
	 * 
	 * @pre engine != 0 and valid
	 * @pre traverseElements != 0 and valid
	 * @pre isInsideAPass() == false
	 * 
	 * @param engine			engine used during evaluation
	 * @param traverseElements	elements to evaluate
	 * 
	 * @post getCurrentPass() == 0
	 * @post isInsideAPass() == false
	 */
	/*virtual */void prepareEval( vge::engine::Engine *engine, vge::visitor::TraverseElementVector* traverseElements );

	/**
	 * @brief Initializes the technique to finish evaluation.
	 * 
	 * @remark Must be called after nodes evaluations
	 * 
	 * @pre isInsideAPass() == false
	 * @pre getCurrentPass() > 0
	 * 
	 * @post m_engine = m_traverseElements = 0
	 */
	virtual void finishEval();



	/**
	 * @name Pass interface
	 */
	//@{

	/**
	 * @brief Isolation policy for a pass
	 */
	enum PassIsolationMask
	{
		RESET_MATRICES	= 1<<0,	///< calls engine->resetMatrices() at the beginning of the pass (in beginPass() method).
		REGARD_ALL		= 1<<1,	///< calls engine->regard() at the beginning of the pass
		PUSH_POP_STATE	= 1<<2,	///< calls engine->push() at the beginning of the pass and engine->pop() at the end of the pass (in endPass() method).
		DEFAULT_PASS_ISOLATION_MASK = RESET_MATRICES|REGARD_ALL|PUSH_POP_STATE
	};

	/**
	 * @brief Sets the description of the pass
	 *
	 * @param description		a string describing the next pass
	 */
	void setPassDescription( const std::string description );

	/**
	 * @brief Must be called at the beginning of each new pass.
	 * 
	 * @param isolationMask	Isolation policy for the pass
	 *
	 * @pre isInsideAPass() == false
	 * @post isInsideAPass() == true
	 *
	 * @post currentPass() = currentPass() + 1
	 */
	/*virtual */void beginPass( const PassIsolationMask isolationMask = PassIsolationMask(DEFAULT_PASS_ISOLATION_MASK) );

	/**
	 * @brief Must be called at the end of each new pass
	 *
	 * @pre isInsideAPass() == true
	 * @post isInsideAPass() == false
	 */
	/*virtual */void endPass();

	// @todo doc and assert()
	/*virtual*/ void applyPassIsolation( vge::engine::Engine *engine, const PassIsolationMask isolationMask = PassIsolationMask(DEFAULT_PASS_ISOLATION_MASK) );

	// @todo doc and assert()
	/*virtual */void unapplyPassIsolation( vge::engine::Engine *engine );

	/**
	 * @brief Returns the current pass (0 if not in a pass, 1 for the first one, 2 for the second and so on).
	 * 
	 * @return the current pass number
	 */
	const uint getCurrentPass() const;

	/**
	 * @brief Tests if the technique is inside a pass.
	 * 
	 * A technique is inside a pass if and only if beginPass() has been called and endPass() has not yet been called.
	 * 
	 * @return true if this technique is inside a pass, false otherwise.
	 */
	const bool isInsideAPass() const;


	/**
	 * @brief Evaluates a single pass
	 * 
	 * @param pass			the pass to evaluate
	 * @param service		the service to evaluate
	 * @param engine		
	 * @param isolationMask	isolation policy for the pass
	 * @param nestedPass
	 *
	 * @todo take care of pass description given by setPassDescription()
	 */
	void evaluatePass(	vgd::Shp< vge::pass::Pass > pass, vgd::Shp< vge::service::Service > service,
						vge::engine::Engine * engine,
						const PassIsolationMask isolationMask = PassIsolationMask(DEFAULT_PASS_ISOLATION_MASK),
						const bool nestedPass = false );
	//@}



	/**
	 * name Helpers
	 */
	//@{

	/**
	 * brief Pushes all engine stacks.
	 */
	//virtual void push();

	/**
	 * brief Pops all engine stacks.
	 */
	//virtual void pop();

	//@}



	vge::visitor::TraverseElementVector	*getTraverseElements() const;
	/*virtual vge::engine::Engine * getEngine() const;*/

	/**
	 * @brief Retrieves an instance of paint service
	 */
	vgd::Shp< vge::service::Service > paintService();

private:
	/**
	 * @name Internal data
	 */
	//@{
	uint									m_currentPass;
	bool									m_inPass;
	std::vector<PassIsolationMask>			m_passIsolationMask;

	vge::engine::Engine *					m_engine;
	vge::visitor::TraverseElementVector *	m_traverseElements;
	vge::engine::SceneManager *				m_sceneManager;

	vgd::Shp< vge::service::Service >		m_paintService;

protected:
	std::string								m_passDescription;
	//@}
};



} // namespace technique

} // namespace vge

#endif //#ifndef _VGE_TECHNIQUE_TECHNIQUE_HPP
