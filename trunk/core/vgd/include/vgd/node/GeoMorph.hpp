// VGSDK - Copyright (C) 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_GEOMORPH_HPP
#define _VGD_NODE_GEOMORPH_HPP

#include "vgd/field/Enum.hpp"
#include "vgd/field/Vec2f.hpp"
#include "vgd/field/VertexShapePtr.hpp"
#include "vgd/node/Group.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Blending between a set of meshes
 *
 * Blending between two meshes are supported. 
 *
 * New fields defined by this node :
 * - SFVec2f \c weights = vgm::Vec2f(0.f, 0.f)<br>
 *<br>
 * - SFEnum \c method = (NORMALIZED)<br>
 *   Method used to combine the set of meshes<br>
 *<br>
 * - MFVertexShapePtr \c __meshes__ = vgd::node::VertexShapePtr()<br>
 *   vgSDK internal field<br>
 *<br>
 *
 * @ingroup g_nodes
 * @ingroup g_groupNodes
 * @ingroup g_shapeNodes
 */
struct VGD_API GeoMorph : public vgd::node::Group
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
	static vgd::Shp< GeoMorph > create( const std::string nodeName = "NoName" );

	/**
	 * @brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values and
	 * sets the \c multiAttributeIndex of the multi-attribute.
	 *
	 * @param index		zero-based index of the multi-attribute
	 */
	static vgd::Shp< GeoMorph > create( const std::string nodeName, const uint8 index );
	
	/**
	 *@brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values (optionals fields too).
	 */
	static vgd::Shp< GeoMorph > createWhole( const std::string nodeName = "DefaultWhole" );

	//@}



	/**
	 * @name Accessors to field weights
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c weights.
	 */
	typedef vgm::Vec2f WeightsValueType;

	/**
	 * @brief The default value of field named \c weights.
	 */
	static const WeightsValueType DEFAULT_WEIGHTS;

	/**
	 * @brief Type definition of the field named \c weights
	 */
	typedef vgd::field::TSingleField< WeightsValueType > FWeightsType;


	/**
	 * @brief Gets the value of field named \c weights.
	 */
	const WeightsValueType getWeights() const;

	/**
	 * @brief Sets the value of field named \c weights.
	 */
	void setWeights( const WeightsValueType value );

	//@}



	/**
	 * @name Accessors to field method
	 */
	//@{

	/**
	 * @brief Definition of symbolic values
	 */
	enum  
	{
		DISABLED = 285,	///< Disable this node. So blending between meshes is not computed, but meshes are rendered as usual.
		SKIP = 286,	///< Disable this node. So blending between meshes is not computed, but meshes are NOT rendered as usual.
		NORMALIZED = 287,	///< (Mesh0, Mesh1, ...) * (weights[0], weights[1],...) = (1-weights[0]-weights[1]-...) * Mesh0 + weights[0] * Mesh1 + ... with 0 <= weights[0] + weights[1] + ... <= 1
		DEFAULT_METHOD = NORMALIZED	///< (Mesh0, Mesh1, ...) * (weights[0], weights[1],...) = (1-weights[0]-weights[1]-...) * Mesh0 + weights[0] * Mesh1 + ... with 0 <= weights[0] + weights[1] + ... <= 1
	};

	/**
	 * @brief Type definition of a container for the previous symbolic values
	 */
	struct MethodValueType : public vgd::field::Enum
	{
		MethodValueType()
		{}

		MethodValueType( const int v )
		: vgd::field::Enum(v)
		{}

		MethodValueType( const MethodValueType& o )
		: vgd::field::Enum(o)
		{}

		MethodValueType( const vgd::field::Enum& o )
		: vgd::field::Enum(o)
		{}

		const std::vector< int > values() const
		{
			std::vector< int > retVal;

			retVal.push_back( 285 );
			retVal.push_back( 286 );
			retVal.push_back( 287 );

			return retVal;
		}

		const std::vector< std::string > strings() const
		{
			std::vector< std::string > retVal;

			retVal.push_back( "DISABLED" );
			retVal.push_back( "SKIP" );
			retVal.push_back( "NORMALIZED" );

			return retVal;
		}
	};

	/**
	 * @brief Type definition of the field named \c method
	 */
	typedef vgd::field::TSingleField< vgd::field::Enum > FMethodType;


	/**
	 * @brief Gets the value of field named \c method.
	 */
	const MethodValueType getMethod() const;

	/**
	 * @brief Sets the value of field named \c method.
	 */
	void setMethod( const MethodValueType value );

	//@}



	/**
	 * @name Accessors to field __meshes__
	 *
	 * @todo get__meshes__( const bool rw = false ) ?
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c __meshes__.
	 */
	typedef vgd::node::VertexShapePtr __meshes__ValueType;

	/**
	 * @brief Type definition of the field named \c __meshes__
	 */
	typedef vgd::field::TMultiField< __meshes__ValueType > F__meshes__Type;


	/**
	 * @brief Gets a read-only editor on the multi field named \c __meshes__.
	 */
	vgd::field::EditorRO< F__meshes__Type > get__meshes__RO() const;

	/**
	 * @brief Gets a read-write editor on the multi field named \c __meshes__.
	 */
	vgd::field::EditorRW< F__meshes__Type > get__meshes__RW();

	//@}



	/**
	 * @name Field name accessors
	 */
	//@{

	/**
	 * @brief Returns the name of field \c weights.
	 *
	 * @return the name of field \c weights.
	 */
	static const std::string getFWeights( void );

	/**
	 * @brief Returns the name of field \c method.
	 *
	 * @return the name of field \c method.
	 */
	static const std::string getFMethod( void );

	/**
	 * @brief Returns the name of field \c __meshes__.
	 *
	 * @return the name of field \c __meshes__.
	 */
	static const std::string getF__meshes__( void );

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
	GeoMorph( const std::string nodeName );

public:
	IMPLEMENT_INDEXABLE_CLASS_HPP( , GeoMorph );
private:
	static const vgd::basic::RegisterNode<GeoMorph> m_registrationInstance;
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_GEOMORPH_HPP
