// VGSDK - Copyright (C) 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_SEPARATOR_HPP
#define _VGD_NODE_SEPARATOR_HPP

#include "vgd/field/Bool.hpp"
#include "vgd/node/Group.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Group node that saves and restores traversal state
 *
 * This group node performs a push (i.e. save) of the traversal state before traversing its children and a pop (i.e. restore) after traversing them. This isolates the separator's children from the rest of the scene graph. By default, full traversal state is saved/restored. But this operation is relatively expensive and also limited to 10 nested Separator nodes. So try to avoid their use. Contrariwise, the traversal state could be saved/restored partially. In this case, the operation is fast and not limited to 10 nested Separator nodes. @remarks Transformations (projection, geometrical and texture) are NOT saved and restored by this node. See TransformSeparator node for that. @todo A mask that indicates which attributes to save. 
 *
 * New fields defined by this node :
 * - SFBool \c fullSeparation = (true)<br>
 *   True to save/restore the full traversal state, false to do nothing.<br>
 *<br>
 * - SFBool \c tessellationLevelSeparation = (false)<br>
 *   True to save/restore the state associated to TessellationLevel node, false to do nothing.<br>
 *<br>
 * - SFBool \c displacementSeparation = (false)<br>
 *   True to save/restore the state associated to Displacement node, false to do nothing.<br>
 *<br>
 *
 * @ingroup g_nodes
 * @ingroup g_groupNodes
 */
struct VGD_API Separator : public vgd::node::Group
{
	/**
	 * @name Factories
	 */
	//@{

	/**
	 * @brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values
	 */
	static vgd::Shp< Separator > create( const std::string nodeName = "NoName" );

	/**
	 * @brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values and
	 * sets the \c multiAttributeIndex of the multi-attribute.
	 *
	 * @param index		zero-based index of the multi-attribute
	 */
	static vgd::Shp< Separator > create( const std::string nodeName, const uint8 index );
	
	/**
	 *@brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values (optionals fields too).
	 */
	static vgd::Shp< Separator > createWhole( const std::string nodeName = "DefaultWhole" );

	//@}



	/**
	 * @name Accessors to field fullSeparation
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c fullSeparation.
	 */
	typedef bool FullSeparationValueType;

	/**
	 * @brief The default value of field named \c fullSeparation.
	 */
	static const FullSeparationValueType DEFAULT_FULLSEPARATION;

	/**
	 * @brief Type definition of the field named \c fullSeparation
	 */
	typedef vgd::field::TSingleField< FullSeparationValueType > FFullSeparationType;


	/**
	 * @brief Gets the value of field named \c fullSeparation.
	 */
	const FullSeparationValueType getFullSeparation() const;

	/**
	 * @brief Sets the value of field named \c fullSeparation.
	 */
	void setFullSeparation( const FullSeparationValueType value );

	//@}



	/**
	 * @name Accessors to field tessellationLevelSeparation
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c tessellationLevelSeparation.
	 */
	typedef bool TessellationLevelSeparationValueType;

	/**
	 * @brief The default value of field named \c tessellationLevelSeparation.
	 */
	static const TessellationLevelSeparationValueType DEFAULT_TESSELLATIONLEVELSEPARATION;

	/**
	 * @brief Type definition of the field named \c tessellationLevelSeparation
	 */
	typedef vgd::field::TSingleField< TessellationLevelSeparationValueType > FTessellationLevelSeparationType;


	/**
	 * @brief Gets the value of field named \c tessellationLevelSeparation.
	 */
	const TessellationLevelSeparationValueType getTessellationLevelSeparation() const;

	/**
	 * @brief Sets the value of field named \c tessellationLevelSeparation.
	 */
	void setTessellationLevelSeparation( const TessellationLevelSeparationValueType value );

	//@}



	/**
	 * @name Accessors to field displacementSeparation
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c displacementSeparation.
	 */
	typedef bool DisplacementSeparationValueType;

	/**
	 * @brief The default value of field named \c displacementSeparation.
	 */
	static const DisplacementSeparationValueType DEFAULT_DISPLACEMENTSEPARATION;

	/**
	 * @brief Type definition of the field named \c displacementSeparation
	 */
	typedef vgd::field::TSingleField< DisplacementSeparationValueType > FDisplacementSeparationType;


	/**
	 * @brief Gets the value of field named \c displacementSeparation.
	 */
	const DisplacementSeparationValueType getDisplacementSeparation() const;

	/**
	 * @brief Sets the value of field named \c displacementSeparation.
	 */
	void setDisplacementSeparation( const DisplacementSeparationValueType value );

	//@}



	/**
	 * @name Field name accessors
	 */
	//@{

	/**
	 * @brief Returns the name of field \c fullSeparation.
	 *
	 * @return the name of field \c fullSeparation.
	 */
	static const std::string getFFullSeparation( void );

	/**
	 * @brief Returns the name of field \c tessellationLevelSeparation.
	 *
	 * @return the name of field \c tessellationLevelSeparation.
	 */
	static const std::string getFTessellationLevelSeparation( void );

	/**
	 * @brief Returns the name of field \c displacementSeparation.
	 *
	 * @return the name of field \c displacementSeparation.
	 */
	static const std::string getFDisplacementSeparation( void );

	//@}


	/**
	 * @name Dirty flags enumeration
	 */
	//@{


	//@}



	/**
	 * @name Constructor and initializer methods
	 */
	//@{

	void	setToDefaults( void );

	void	setOptionalsToDefaults();

	//@}

protected:
	/**
	 * @brief Default constructor
	 */
	Separator( const std::string nodeName );

public:
	IMPLEMENT_INDEXABLE_CLASS_HPP( , Separator );
private:
	static const vgd::basic::RegisterNode<Separator> m_registrationInstance;
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_SEPARATOR_HPP
