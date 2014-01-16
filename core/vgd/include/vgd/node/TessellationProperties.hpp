// VGSDK - Copyright (C) 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_TESSELLATIONPROPERTIES_HPP
#define _VGD_NODE_TESSELLATIONPROPERTIES_HPP

#include "vgd/field/Enum.hpp"
#include "vgd/field/Float.hpp"
#include "vgd/field/Vec2f.hpp"
#include "vgd/node/SingleAttribute.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Definition of several properties used by tessellation
 *
 * Specifies if the tessellation is enabled or disabled, which method to use and several parameters to adjust behavior of the tessellation. 
 *
 * New fields defined by this node :
 * - OFVec2f \c [range] = vgm::Vec2f(1.0f, 5.0f)<br>
 *   Specifies the minimum and maximum tessellation level used by the tessellation control shaders to tessellate the incoming primitive (only used if tessellation is enabled).<br>
 *<br>
 * - OFFloat \c [phongBias] = (0.55f)<br>
 *   Specifies the tessellation bias used by the Phong Tessellation algorithm (only used if tessellation is enabled).<br>
 *<br>
 * - OFFloat \c [pixelsPerEdge] = (20.f)<br>
 *   When tessellation method is set to PHONG and TessellationLevel.method==PIXELS_PER_EDGE, then this field specifies the desired number of pixels per edge (if tessellationRange[1] allows the needed subdivision level).<br>
 *<br>
 * - OFEnum \c [tessellation] = (DISABLED)<br>
 *   Specifies if the tessellation is enabled or disabled and which method to use.<br>
 *<br>
 *
 * @ingroup g_nodes
 * @ingroup g_singleAttributeNodes
 * @ingroup g_propertiesNodes
 * @ingroup g_shapeModifierNodes
 * @ingroup g_tessellationNodes
 */
struct VGD_API TessellationProperties : public vgd::node::SingleAttribute
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
	static vgd::Shp< TessellationProperties > create( const std::string nodeName = "NoName" );

	/**
	 * @brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values and
	 * sets the \c multiAttributeIndex of the multi-attribute.
	 *
	 * @param index		zero-based index of the multi-attribute
	 */
	static vgd::Shp< TessellationProperties > create( const std::string nodeName, const uint8 index );
	
	/**
	 *@brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values (optionals fields too).
	 */
	static vgd::Shp< TessellationProperties > createWhole( const std::string nodeName = "DefaultWhole" );

	//@}



	/**
	 * @name Accessors to field range
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c range.
	 */
	typedef vgm::Vec2f RangeValueType;

	/**
	 * @brief The default value of field named \c range.
	 */
	static const RangeValueType DEFAULT_RANGE;

	/**
	 * @brief Type definition of the field named \c range
	 */
	typedef vgd::field::TOptionalField< RangeValueType > FRangeType;


	/**
	 * @brief Gets the value of field named \c range.
	 */
	const bool getRange( RangeValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c range.
 	 */
	void setRange( const RangeValueType& value );

	/**
	 * @brief Erases the field named \c range.
	 */
	void eraseRange();

	/**
	 * @brief Tests if the value of field named \c range has been initialized.
	 */
	const bool hasRange() const;
	//@}



	/**
	 * @name Accessors to field phongBias
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c phongBias.
	 */
	typedef float PhongBiasValueType;

	/**
	 * @brief The default value of field named \c phongBias.
	 */
	static const PhongBiasValueType DEFAULT_PHONGBIAS;

	/**
	 * @brief Type definition of the field named \c phongBias
	 */
	typedef vgd::field::TOptionalField< PhongBiasValueType > FPhongBiasType;


	/**
	 * @brief Gets the value of field named \c phongBias.
	 */
	const bool getPhongBias( PhongBiasValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c phongBias.
 	 */
	void setPhongBias( const PhongBiasValueType& value );

	/**
	 * @brief Erases the field named \c phongBias.
	 */
	void erasePhongBias();

	/**
	 * @brief Tests if the value of field named \c phongBias has been initialized.
	 */
	const bool hasPhongBias() const;
	//@}



	/**
	 * @name Accessors to field pixelsPerEdge
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c pixelsPerEdge.
	 */
	typedef float PixelsPerEdgeValueType;

	/**
	 * @brief The default value of field named \c pixelsPerEdge.
	 */
	static const PixelsPerEdgeValueType DEFAULT_PIXELSPEREDGE;

	/**
	 * @brief Type definition of the field named \c pixelsPerEdge
	 */
	typedef vgd::field::TOptionalField< PixelsPerEdgeValueType > FPixelsPerEdgeType;


	/**
	 * @brief Gets the value of field named \c pixelsPerEdge.
	 */
	const bool getPixelsPerEdge( PixelsPerEdgeValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c pixelsPerEdge.
 	 */
	void setPixelsPerEdge( const PixelsPerEdgeValueType& value );

	/**
	 * @brief Erases the field named \c pixelsPerEdge.
	 */
	void erasePixelsPerEdge();

	/**
	 * @brief Tests if the value of field named \c pixelsPerEdge has been initialized.
	 */
	const bool hasPixelsPerEdge() const;
	//@}



	/**
	 * @name Accessors to field tessellation
	 */
	//@{

	/**
	 * @brief Definition of symbolic values
	 */
	enum  
	{
		DISABLED = 426,	///< Tessellation is disabled
		PHONG = 427,	///< Phong tessellation is enabled and subdivision of triangles is uniform. The tessellation level used is given by tessellationRange[1]
		DEFAULT_TESSELLATION = DISABLED	///< Tessellation is disabled
	};

	/**
	 * @brief Type definition of a container for the previous symbolic values
	 */
	struct TessellationValueType : public vgd::field::Enum
	{
		TessellationValueType()
		{}

		TessellationValueType( const int v )
		: vgd::field::Enum(v)
		{}

		TessellationValueType( const TessellationValueType& o )
		: vgd::field::Enum(o)
		{}

		TessellationValueType( const vgd::field::Enum& o )
		: vgd::field::Enum(o)
		{}

		const std::vector< int > values() const
		{
			std::vector< int > retVal;

			retVal.push_back( 426 );
			retVal.push_back( 427 );

			return retVal;
		}

		const std::vector< std::string > strings() const
		{
			std::vector< std::string > retVal;

			retVal.push_back( "DISABLED" );
			retVal.push_back( "PHONG" );

			return retVal;
		}
	};

	/**
	 * @brief Type definition of the field named \c tessellation
	 */
	typedef vgd::field::TOptionalField< vgd::field::Enum > FTessellationType;


	/**
	 * @brief Gets the value of field named \c tessellation.
	 */
	const bool getTessellation( TessellationValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c tessellation.
 	 */
	void setTessellation( const TessellationValueType& value );

	/**
	 * @brief Erases the field named \c tessellation.
	 */
	void eraseTessellation();

	/**
	 * @brief Tests if the value of field named \c tessellation has been initialized.
	 */
	const bool hasTessellation() const;
	//@}



	/**
	 * @name Field name accessors
	 */
	//@{

	/**
	 * @brief Returns the name of field \c range.
	 *
	 * @return the name of field \c range.
	 */
	static const std::string getFRange( void );

	/**
	 * @brief Returns the name of field \c phongBias.
	 *
	 * @return the name of field \c phongBias.
	 */
	static const std::string getFPhongBias( void );

	/**
	 * @brief Returns the name of field \c pixelsPerEdge.
	 *
	 * @return the name of field \c pixelsPerEdge.
	 */
	static const std::string getFPixelsPerEdge( void );

	/**
	 * @brief Returns the name of field \c tessellation.
	 *
	 * @return the name of field \c tessellation.
	 */
	static const std::string getFTessellation( void );

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
	TessellationProperties( const std::string nodeName );

public:
	IMPLEMENT_INDEXABLE_CLASS_HPP( , TessellationProperties );
private:
	static const vgd::basic::RegisterNode<TessellationProperties> m_registrationInstance;
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_TESSELLATIONPROPERTIES_HPP
