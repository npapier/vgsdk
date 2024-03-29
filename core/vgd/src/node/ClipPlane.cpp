// VGSDK - Copyright (C) 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/ClipPlane.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



vgd::Shp< ClipPlane > ClipPlane::create( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< ClipPlane > node( new ClipPlane(nodeName) );

	/* Adds a vertex (i.e. a node) to boost::graph */
	graph().addNode( node );

	/* Sets fields to their default values */
	node->setToDefaults();

	return node;
}



vgd::Shp< ClipPlane > ClipPlane::create( const std::string nodeName, const uint8 index )
{
	/* Creates a new node */
	vgd::Shp< ClipPlane > node = ClipPlane::create(nodeName);

	/* Sets index of multi-attributes */
	node->setMultiAttributeIndex(index);

	return node;
}



vgd::Shp< ClipPlane > ClipPlane::createWhole( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< ClipPlane > node = ClipPlane::create(nodeName);

	/* Sets optional fields to their default values */
	node->setOptionalsToDefaults();

	return node;
}



ClipPlane::ClipPlane( const std::string nodeName ) :
	vgd::node::MultiAttribute( nodeName )
{
	// Adds field(s)
	addField( new FPlaneType(getFPlane()) );
	addField( new FOnType(getFOn()) );

	// Sets link(s)

	link( getDFNode() );
}



void ClipPlane::setToDefaults( void )
{
	MultiAttribute::setToDefaults();
	setPlane( vgm::Plane(vgm::Vec3f(1.f, 0.f, 0.f), 0.f ) );
}



void ClipPlane::setOptionalsToDefaults()
{
	MultiAttribute::setOptionalsToDefaults();
	setOn( (true) );
}



// Plane

const ClipPlane::PlaneValueType ClipPlane::DEFAULT_PLANE = vgm::Plane(vgm::Vec3f(1.f, 0.f, 0.f), 0.f );



const ClipPlane::PlaneValueType ClipPlane::getPlane() const
{
	return getFieldRO<FPlaneType>(getFPlane())->getValue();
}



void ClipPlane::setPlane( const PlaneValueType value )
{
	getFieldRW<FPlaneType>(getFPlane())->setValue( value );
}



// On

const ClipPlane::OnValueType ClipPlane::DEFAULT_ON = (true);



const bool ClipPlane::getOn( OnValueType& value ) const
{
	return getFieldRO<FOnType>(getFOn())->getValue( value );
}



void ClipPlane::setOn( const OnValueType& value )
{
	getFieldRW<FOnType>(getFOn())->setValue( value );
}



void ClipPlane::eraseOn()
{
	getFieldRW<FOnType>(getFOn())->eraseValue();
}


const bool ClipPlane::hasOn() const
{
	return getFieldRO<FOnType>(getFOn())->hasValue();
}



// Field name accessor(s)
const std::string ClipPlane::getFPlane( void )
{
	return "f_plane";
}



const std::string ClipPlane::getFOn( void )
{
	return "f_on";
}



IMPLEMENT_INDEXABLE_CLASS_CPP( ClipPlane );



const vgd::basic::RegisterNode<ClipPlane> ClipPlane::m_registrationInstance;



} // namespace node

} // namespace vgd

