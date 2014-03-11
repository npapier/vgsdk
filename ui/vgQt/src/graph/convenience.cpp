// VGSDK - Copyright (C) 2008, 2009, 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#include "vgQt/graph/convenience.hpp"

#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#define BOOST_MPL_LIMIT_LIST_SIZE 40
#include <boost/mpl/copy.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/front_inserter.hpp>
#include <boost/mpl/list.hpp>

#include <sstream>

#include <vgd/field/Bool.hpp>
#include <vgd/field/Enum.hpp>
#include <vgd/field/Image.hpp>
#include <vgd/field/Integer.hpp>
#include <vgd/field/Float.hpp>
#include <vgd/field/Matrix.hpp>
#include <vgd/field/NodeShp.hpp>
#include <vgd/field/NodeWkp.hpp>

#include <vgd/field/Plane.hpp>
#include <vgd/field/Primitive.hpp>
#include <vgd/field/Rectangle.hpp>
#include <vgd/field/Rotation.hpp>
#include <vgd/field/String.hpp>
#include <vgd/field/Vector.hpp>

#include <vgd/node/VertexShape.hpp>

#include <vgio/operators.hpp>

/// @todo Moves to vgio



namespace vgUI
{

namespace graph
{



namespace
{

/**
 * @brief Base class for FieldSerializer
 */
struct FieldSerializer
{
	/**
	 * @brief Default constructor
	 */
	FieldSerializer(	const vgd::Shp< vgd::field::FieldManager > fieldManager,
						const std::string & fieldName,
						std::ostream & os )
		:	m_fieldManager( fieldManager ),
			m_fieldName( fieldName ),
			m_os( os ),
			m_done( false )
	{}

	/**
	 * @brief Tests if serialization has been done.
	 */
	const bool done() const { return m_done; }

protected:

	const vgd::Shp< vgd::field::FieldManager >	m_fieldManager;
	const std::string & 						m_fieldName;
	std::ostream &								m_os;
	bool m_done;		///< true when the serialization has been done
};



/**
 * @brief Functor to serializes a field using typelist
 */
template< template<typename> class ContainerType >
struct FieldSerializer1 : public FieldSerializer
{
	/**
	 * @brief Default constructor
	 */
	FieldSerializer1(	const vgd::Shp< vgd::field::FieldManager > fieldManager,
						const std::string & fieldName,
						std::ostream & os )
		:	FieldSerializer( fieldManager, fieldName, os )
	{}

	/**
	 * @brief Serializes the field (if possible)
	 */
	template< typename ValueType >
    void operator() ( ValueType  )
    {
		// Defines an alias for the field type
		typedef ContainerType< ValueType > FieldType;

		// Checks if the field manager contains a field with the desired name and type
		if ( m_fieldManager->isFieldKindOf< FieldType >( m_fieldName ) )
		{
			m_os << m_fieldManager->getFieldRO< FieldType >( m_fieldName );
			m_done = true;
		}
	}
};


/**
 * @brief Functor to serializes a field using typelist
 */
template< typename Key, template<typename Key,typename> class ContainerType >
struct FieldSerializer2 : public FieldSerializer
{
	/**
	 * @brief Default constructor
	 */
	FieldSerializer2(	const vgd::Shp< vgd::field::FieldManager > fieldManager,
						const std::string & fieldName,
						std::ostream & os )
		:	FieldSerializer( fieldManager, fieldName, os )
	{}

	/**
	 * @brief Serializes the field (if possible)
	 */
	template< typename ValueType >
    void operator() ( ValueType )
    {
		// Defines an alias for the field type
		typedef ContainerType< Key, ValueType > FieldType;

		// Checks if the field manager contains a field with the desired name and type
		if ( m_fieldManager->isFieldKindOf< FieldType >( m_fieldName ) )
		{
			m_os << m_fieldManager->getFieldRO< FieldType >( m_fieldName );
			m_done = true;
		}
	}
};

}



const std::string getFieldAsString( const vgd::Shp< vgd::field::FieldManager > fieldManager, const std::string & fieldName )
{
	std::ostringstream	os;

	// Ensures that the field exists.
	if( fieldManager->isField(fieldName) == false )
	{
		os << "Missing field !";
	}
	else
	{
		// Old serialization system, always useful for enum type
		typedef vgd::node::VertexShape::FPrimitiveType	MFPrimitiveType;

		typedef vgd::field::SFBinding						SFBinding;

		typedef vgd::node::DrawStyle::FBoundingBoxType		PAFDrawStyleBoundingBox;
		typedef vgd::node::DrawStyle::FNormalLengthType		PAFDrawStyleNormalLength;
		typedef vgd::node::DrawStyle::FShapeType			PAFDrawStyleShape;
		typedef vgd::node::DrawStyle::FShowOrientationType	PAFDrawStyleShowOrientation;
		
		// Retrieves the field type information
		const std::type_info	& fieldType = fieldManager->getFieldType( fieldName );

		if		( fieldType == typeid(MFPrimitiveType) )				os << fieldManager->getFieldRO< MFPrimitiveType				>( fieldName );
		else if	( fieldType == typeid(SFBinding) )						os << fieldManager->getFieldRO< SFBinding					>( fieldName );
		else if	( fieldType == typeid(PAFDrawStyleBoundingBox) )		os << fieldManager->getFieldRO< PAFDrawStyleBoundingBox		>( fieldName );
		else if	( fieldType == typeid(PAFDrawStyleNormalLength) )		os << fieldManager->getFieldRO< PAFDrawStyleNormalLength    >( fieldName );
		else if	( fieldType == typeid(PAFDrawStyleShape) )				os << fieldManager->getFieldRO< PAFDrawStyleShape           >( fieldName );
		else if	( fieldType == typeid(PAFDrawStyleShowOrientation) )	os << fieldManager->getFieldRO< PAFDrawStyleShowOrientation >( fieldName );
		else
		{
			// Serialization system using typelist

			// Creates serializer instances
			using vgd::field::TSingleField;
			FieldSerializer1< TSingleField >				singleFieldSerializer( fieldManager, fieldName, os );

			using vgd::field::TOptionalField;
			FieldSerializer1< TOptionalField >				optionalFieldSerializer( fieldManager, fieldName, os );

			using vgd::field::TMultiField;
			FieldSerializer1< TMultiField >					multiFieldSerializer( fieldManager, fieldName, os );

			using vgd::field::TPairAssociativeField;
			FieldSerializer2< int, TPairAssociativeField >	paFieldSerializer1( fieldManager, fieldName, os );
			FieldSerializer2< vgd::field::Enum, TPairAssociativeField >	paFieldSerializer2( fieldManager, fieldName, os );

			using vgd::field::TSingleAssociativeField;
			FieldSerializer1< TSingleAssociativeField >		saFieldSerializer( fieldManager, fieldName, os );

			// Defines typelists
			namespace mpl = boost::mpl;

			typedef mpl::list<
				// bool_t
				bool
				> bool_t;
				
			typedef mpl::list<
				vgd::field::Enum
			> enum_t;

			typedef mpl::list<
				// int_t
				int8,	uint8,
				int16,	uint16,
				int32,	uint32
//				int,	uint
			> int_t;

			typedef mpl::list<
				// float_t
				float, double
			> float_t;

			typedef mpl::list<
				// string
				std::string
			> string_t;

			typedef mpl::list<
				// Box_t
				vgm::Box3f,
				vgm::XfBox3f
			> Box_t;

			typedef mpl::list<
				// Rectangle_t
				vgm::Rectangle2i,
				vgm::Rectangle2f,
				vgm::Rectangle2d
			> Rectangle_t;

			typedef mpl::list<
				// Vector_t	@todo vgm::Vector< *, *>
				vgm::Vec2i, vgm::Vec3i, vgm::Vec4i, vgm::Vec5i,
				vgm::Vec2f, vgm::Vec3f, vgm::Vec4f, vgm::Vec5f,
				vgm::Vec2d, vgm::Vec3d, vgm::Vec4d, vgm::Vec5d
			> Vector_t;

			typedef mpl::list<
				// others vgm types
				vgm::MatrixR,
				vgm::Plane,
				vgm::Rotation
			> vgm_t;

			typedef mpl::list<
				// vgd types
				vgd::Shp< vgd::basic::IImage >,
				vgd::Wkp< vgd::node::Node >,
				vgd::Wkp< vgd::node::Group >,
				vgd::Shp< vgd::node::Node >,
				vgd::Shp< vgd::node::Group >
			> vgd_t;

			typedef mpl::copy< bool_t, mpl::front_inserter< enum_t > >::type	l2;
			typedef mpl::copy< l2, mpl::front_inserter< int_t > >::type			l3;
			typedef mpl::copy< l3, mpl::front_inserter< float_t > >::type		l4;
			typedef mpl::copy< l4, mpl::front_inserter< string_t > >::type		l5;
			typedef mpl::copy< l5, mpl::front_inserter< Box_t > >::type			l6;
			typedef mpl::copy< l6, mpl::front_inserter< Rectangle_t > >::type	l7;
			typedef mpl::copy< l7, mpl::front_inserter< Vector_t > >::type		l8;
			typedef mpl::copy< l8, mpl::front_inserter< vgm_t > >::type			l9;
			typedef mpl::copy< l9, mpl::front_inserter< vgd_t > >::type			l10;
			typedef l10 AllTypes;
// @todo for() with break
// @todo debug done() serializer is copied
			boost::mpl::for_each< AllTypes >( singleFieldSerializer );
			boost::mpl::for_each< AllTypes >( optionalFieldSerializer );
			boost::mpl::for_each< AllTypes >( multiFieldSerializer );
			boost::mpl::for_each< AllTypes >( paFieldSerializer1 );
			boost::mpl::for_each< AllTypes >( paFieldSerializer2 );
			boost::mpl::for_each< AllTypes >( saFieldSerializer );
// @todo else os << "Not yet supported!";*/
        }
	}

	return os.str();
}



const std::string toString( const vgd::node::IBoundingBox * ibb )
{
	std::ostringstream	os;

	vgio::configure( os );

	if ( ibb->isBoundingBoxValid() )
	{
		os << ibb->getXfBoundingBox();
	}
	else
	{
		os << "invalid";
	}

	return os.str();
}



} // namespace graph

} // namespace vgUI
