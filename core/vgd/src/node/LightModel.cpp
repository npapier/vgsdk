// VGSDK - Copyright (C) 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/LightModel.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



vgd::Shp< LightModel > LightModel::create( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< LightModel > node( new LightModel(nodeName) );

	/* Adds a vertex (i.e. a node) to boost::graph */
	graph().addNode( node );

	/* Sets fields to their default values */
	node->setToDefaults();

	return node;
}



vgd::Shp< LightModel > LightModel::createWhole( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< LightModel > node = LightModel::create(nodeName);

	/* Sets optional fields to their default values */
	node->setOptionalsToDefaults();

	return node;
}



LightModel::LightModel( const std::string nodeName ) :
	vgd::node::SingleAttribute( nodeName )
{
	// Adds field(s)
	addField( new FViewerType(getFViewer()) );
	addField( new FModelType(getFModel()) );
	addField( new FShadowType(getFShadow()) );
	addField( new FTwoSidedType(getFTwoSided()) );
	addField( new FAmbientType(getFAmbient()) );

	// Sets link(s)
	link( getDFNode() );
}



void LightModel::setToDefaults( void )
{
	SingleAttribute::setToDefaults();
}



void LightModel::setOptionalsToDefaults()
{
	SingleAttribute::setOptionalsToDefaults();
	setViewer( AT_INFINITY );
	setModel( STANDARD_PER_VERTEX );
	setShadow( SHADOW_OFF );
	setTwoSided( false );
	setAmbient( vgm::Vec4f(0.2f, 0.2f, 0.2f, 0.0f) );
}



// Viewer
const bool LightModel::getViewer( ViewerValueType& value ) const
{
	return getFieldRO<FViewerType>(getFViewer())->getValue( value );
}



void LightModel::setViewer( const ViewerValueType& value )
{
	getFieldRW<FViewerType>(getFViewer())->setValue( value );
}



void LightModel::eraseViewer()
{
	getFieldRW<FViewerType>(getFViewer())->eraseValue();
}


const bool LightModel::hasViewer() const
{
	return getFieldRO<FViewerType>(getFViewer())->hasValue();
}



// Model
const bool LightModel::getModel( ModelValueType& value ) const
{
	return getFieldRO<FModelType>(getFModel())->getValue( value );
}



void LightModel::setModel( const ModelValueType& value )
{
	getFieldRW<FModelType>(getFModel())->setValue( value );
}



void LightModel::eraseModel()
{
	getFieldRW<FModelType>(getFModel())->eraseValue();
}


const bool LightModel::hasModel() const
{
	return getFieldRO<FModelType>(getFModel())->hasValue();
}



// Shadow
const bool LightModel::getShadow( ShadowValueType& value ) const
{
	return getFieldRO<FShadowType>(getFShadow())->getValue( value );
}



void LightModel::setShadow( const ShadowValueType& value )
{
	getFieldRW<FShadowType>(getFShadow())->setValue( value );
}



void LightModel::eraseShadow()
{
	getFieldRW<FShadowType>(getFShadow())->eraseValue();
}


const bool LightModel::hasShadow() const
{
	return getFieldRO<FShadowType>(getFShadow())->hasValue();
}



// TwoSided
const bool LightModel::getTwoSided( TwoSidedValueType& value ) const
{
	return getFieldRO<FTwoSidedType>(getFTwoSided())->getValue( value );
}



void LightModel::setTwoSided( const TwoSidedValueType& value )
{
	getFieldRW<FTwoSidedType>(getFTwoSided())->setValue( value );
}



void LightModel::eraseTwoSided()
{
	getFieldRW<FTwoSidedType>(getFTwoSided())->eraseValue();
}


const bool LightModel::hasTwoSided() const
{
	return getFieldRO<FTwoSidedType>(getFTwoSided())->hasValue();
}



// Ambient
const bool LightModel::getAmbient( AmbientValueType& value ) const
{
	return getFieldRO<FAmbientType>(getFAmbient())->getValue( value );
}



void LightModel::setAmbient( const AmbientValueType& value )
{
	getFieldRW<FAmbientType>(getFAmbient())->setValue( value );
}



void LightModel::eraseAmbient()
{
	getFieldRW<FAmbientType>(getFAmbient())->eraseValue();
}


const bool LightModel::hasAmbient() const
{
	return getFieldRO<FAmbientType>(getFAmbient())->hasValue();
}



// Field name accessor(s)
const std::string LightModel::getFViewer( void )
{
	return "f_viewer";
}



const std::string LightModel::getFModel( void )
{
	return "f_model";
}



const std::string LightModel::getFShadow( void )
{
	return "f_shadow";
}



const std::string LightModel::getFTwoSided( void )
{
	return "f_twoSided";
}



const std::string LightModel::getFAmbient( void )
{
	return "f_ambient";
}



IMPLEMENT_INDEXABLE_CLASS_CPP( , LightModel );



const vgd::basic::RegisterNode<LightModel> LightModel::m_registrationInstance;



} // namespace node

} // namespace vgd

