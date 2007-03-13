// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_SWITCH_HPP
#define _VGD_NODE_SWITCH_HPP

#include "vgd/vgd.hpp"

#include "vgd/node/Group.hpp"



namespace vgd
{
	
namespace node
{

/**
 * @brief Group node that traverse none, all or one chosen child.
 * 
 * This group node usually traverses only one, all or none of its children.
 * 
 * One can use this node to switch on and off the effects of some properties or to switch between different properties(or shapes).
 *
 * A value of SWITCH_NONE(the default) means do not traverse any children.
 * A value of SWITCH_ALL traverses all children, making the switch behave exactly like a regular Group.
 * An index value between 0 and getNumChildren()-1 specifies the index of the child to traverse (where the first child has index 0).
 *
 * The \c whichChild field specifies what children to traverse.
 * 
 * @remarks getDFChildrenSelection() is the name of dirty flag that is invalidate when selection of children is changed(when "whichChild" changed).
 * 
 * @todo A value of SWITCH_INHERIT(-2) allows the index to be inherited from a previously-encountered \c Switch node or
 * from certain other nodes (such as \c Array or \c MultipleCopy) that set the switch value.
 * 
 * @todo SoSwitch::SoSwitch(int nChildren ) Constructor that takes approximate number of children.
 * 
 * @ingroup g_nodes
 * @ingroup g_groupNodes
 */
struct VGD_API Switch : public Group
{
	META_NODE_HPP( Switch );
	
	/**
	 * @name Constants.
	 */
	//@{
	enum {
		SWITCH_ALL		= -3,
		SWITCH_NONE		= -1, 
		SWITCH_DEFAULT	= SWITCH_NONE
	};
	//@}



	/**
	 * @name Fields accessors.
	 */
	//@{

	/**
	 * @brief Gets the value of \c whichChild field.
	 */
	const int32	getWhichChild( void ) const;

	/**
	 * @brief Sets the value of \c whichChild field.
	 * 
	 * @param whichChild : Index of the child to traverse, or one of SWITCH_ALL, SWITCH_NONE or SWITCH_DEFAULT.
	 */
	void		setWhichChild( const int32 whichChild );
	//@}



protected:
	/**
	 * @name Constructor.
	 */
	//@{

	/**
	 * @brief Default constructor.
	 */
	Switch( const std::string nodeName );

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
	static const std::string getFWhichChild(void);
	//@}
	
	// Overriden
	void updateGraph( void );
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_SWITCH_HPP
