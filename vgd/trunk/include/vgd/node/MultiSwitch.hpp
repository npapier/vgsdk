// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_MULTISWITCH_H
#define _VGD_NODE_MULTISWITCH_H

#include "vgd/vgd.hpp"

#include "vgd/node/Group.hpp"



namespace vgd
{
	
namespace node
{

/**
 * @brief MultiSwitch node traverse a set of chosen child.
 * 
 * This group node usually traverses a set of chosen child.
 *
 * It can be switch off(MULTI_SWITCH_OFF) to disable the visit of the chosen child, but without loosing this set.
 * It can be switch on(MULTI_SWITCH_ON) for enable the visit of the chosen child.
 * A value of MULTI_SWITCH_ALL traverses all children, making the switch behave exactly like a regular Group.
 * 
 * MULTI_SWITCH_OFF is the default value.
 *
 * One can use this node to flatten the DAG a little(compared to a Switch) or to switch on and off the effects of some
 * properties or to switch between different properties(or shapes).
 * 
 * @todo add more accessors to field(see tmp.hpp).
 * @todo use a TSingleAssociativeField for optimization and simplification.
 *
 * @todo A value of SWITCH_INHERIT(-2) allows the index to be inherited from a previously-encountered \c Switch node or
 * from certain other nodes (such as \c Array or \c MultipleCopy) that set the switch value.
 * 
 * @ingroup g_nodes
 * @ingroup g_groupNodes
 */
struct VGD_API MultiSwitch : public Group
{
	META_NODE_HPP( MultiSwitch );

	/**
	 * @name Constants.
	 */
	//@{
	enum {
		MULTI_SWITCH_OFF	= 0,
		MULTI_SWITCH_ON		= 1,
		MULTI_SWITCH_ALL	= 2,
		MULTI_SWITCH_DEFAULT= MULTI_SWITCH_OFF
	};

	//@}



	/**
	 * @name Fields accessors.
	 */
	//@{

	/**
	 * @brief Gets the value of \c whichChild field.
	 */
	const int8	getWhichChild		( void ) const;

	/**
	 * @brief Sets the value of \c whichChild field.
	 * 
	 * @param whichChild : one of MULTI_SWITCH_OFF, MULTI_SWITCH_ON, MULTI_SWITCH_ALL or MULTI_SWITCH_DEFAULT.
	 */
	void			setWhichChild		( const int8 whichChild );


	/**
	 * @brief Tests if the set of children to traverse contains this child.
	 * 
	 * @param index : An index value between 0 and getNumChildren()-1 specifies the index of the child.
	 * 
	 * @return true if this child is in the set of children to traverse, false otherwise.
	 */
	bool			isChildChoosen		( const int32 index ) const;

	/**
	 * @brief Adds a new child to the set of children to traverse.
	 * 
	 * @param index : An index value between 0 and getNumChildren()-1 specifies the index of the child to traverse (where the first child has index 0).
	 * 
	 * @remark A chosen child is never insert more than once.
	 */
	void			addToChosenChild	( const int32 index );

	/**
	 * @brief Removes a child from the set of children to traverse.
	 * 
	 * @param index : An index value between 0 and getNumChildren()-1 specifies the index of the child to traverse (where the first child has index 0).
	 * 
	 * @remark Removed only if already inserted, if not inserted nothing is done.
	 */	
	void			removeFromChosenChild	( const int32 index );

	/**
	 * @brief Removes all from the set of children to traverse.
	 */
	void			removeAllFromChosenChild	( void );

	//@}



	/**
	 * @name IGroup interface.
	 */
	//@{
	void	updateGraph	( void );

	//@}



protected:
	/**
	 * @name Constructor.
	 */
	//@{

	/**
	 * @brief Default constructor.
	 */
	MultiSwitch( const std::string nodeName );
	
	void	setToDefaults( void );
	
	void	setOptionalsToDefaults();	

	//@}



	/**
	 * @name Fields names enumeration.
	 */
	//@{

	/**
	 * @brief Returns the name of field \c whichChild.
	 */
	static const std::string getFWhichChild( void );

	/**
	 * @brief Returns the name of field \c chosenChild.
	 */
	static const std::string getFChosenChild( void );

	//@}
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_MULTISWITCH_H
