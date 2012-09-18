// VGSDK - Copyright (C) 2012, Nicolas Papier.
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



vgd::Shp< LightModel > LightModel::create( const std::string nodeName, const uint8 index )
{
	/* Creates a new node */
	vgd::Shp< LightModel > node = LightModel::create(nodeName);

	/* Sets index of multi-attributes */
	node->setMultiAttributeIndex(index);

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
	addField( new FShadowMapSizeType(getFShadowMapSize()) );
	addField( new FShadowFilteringType(getFShadowFiltering()) );
	addField( new FShadowMapTypeType(getFShadowMapType()) );
	addField( new FIlluminationInShadowType(getFIlluminationInShadow()) );
	addField( new FTwoSidedType(getFTwoSided()) );
	addField( new FSamplingSizeType(getFSamplingSize()) );
	addField( new FOption2Type(getFOption2()) );
	addField( new FAmbientType(getFAmbient()) );
	addField( new FViewerType(getFViewer()) );
	addField( new FIgnorePostProcessingType(getFIgnorePostProcessing()) );
	addField( new FModelType(getFModel()) );
	addField( new FShadowPolygonOffsetType(getFShadowPolygonOffset()) );
	addField( new FShadowType(getFShadow()) );
	addField( new FOption0Type(getFOption0()) );
	addField( new FOption1Type(getFOption1()) );

	// Sets link(s)

	link( getDFNode() );
}



void LightModel::setToDefaults( void )
{
	SingleAttribute::setToDefaults();
	setShadowMapType( (INT32) );
	setIlluminationInShadow( (0.4f) );
	setSamplingSize( (1.0) );
	setOption2( (false) );
	setIgnorePostProcessing( (false) );
	setShadowPolygonOffset( vgm::Vec2f(4.f, 16.f) );
	setOption0( (CHOICE0) );
	setOption1( (false) );
}



void LightModel::setOptionalsToDefaults()
{
	SingleAttribute::setOptionalsToDefaults();
	setShadowMapSize( (MEDIUM) );
	setShadowFiltering( (LINEAR) );
	setTwoSided( (false) );
	setAmbient( vgm::Vec4f(0.2f, 0.2f, 0.2f, 0.0f) );
	setViewer( (AT_INFINITY) );
	setModel( (STANDARD_PER_VERTEX) );
	setShadow( (SHADOW_OFF) );
}



// ShadowMapSize

const bool LightModel::getShadowMapSize( ShadowMapSizeValueType& value ) const
{
	return getFieldRO<FShadowMapSizeType>(getFShadowMapSize())->getValue( value );
}



void LightModel::setShadowMapSize( const ShadowMapSizeValueType& value )
{
	getFieldRW<FShadowMapSizeType>(getFShadowMapSize())->setValue( value );
}



void LightModel::eraseShadowMapSize()
{
	getFieldRW<FShadowMapSizeType>(getFShadowMapSize())->eraseValue();
}


const bool LightModel::hasShadowMapSize() const
{
	return getFieldRO<FShadowMapSizeType>(getFShadowMapSize())->hasValue();
}



// ShadowFiltering

const bool LightModel::getShadowFiltering( ShadowFilteringValueType& value ) const
{
	return getFieldRO<FShadowFilteringType>(getFShadowFiltering())->getValue( value );
}



void LightModel::setShadowFiltering( const ShadowFilteringValueType& value )
{
	getFieldRW<FShadowFilteringType>(getFShadowFiltering())->setValue( value );
}



void LightModel::eraseShadowFiltering()
{
	getFieldRW<FShadowFilteringType>(getFShadowFiltering())->eraseValue();
}


const bool LightModel::hasShadowFiltering() const
{
	return getFieldRO<FShadowFilteringType>(getFShadowFiltering())->hasValue();
}



// ShadowMapType

const LightModel::ShadowMapTypeValueType LightModel::getShadowMapType() const
{
	return getFieldRO<FShadowMapTypeType>(getFShadowMapType())->getValue();
}



void LightModel::setShadowMapType( const ShadowMapTypeValueType value )
{
	getFieldRW<FShadowMapTypeType>(getFShadowMapType())->setValue( value );
}



// IlluminationInShadow

const LightModel::IlluminationInShadowValueType LightModel::DEFAULT_ILLUMINATIONINSHADOW = (0.4f);



const LightModel::IlluminationInShadowValueType LightModel::getIlluminationInShadow() const
{
	return getFieldRO<FIlluminationInShadowType>(getFIlluminationInShadow())->getValue();
}



void LightModel::setIlluminationInShadow( const IlluminationInShadowValueType value )
{
	getFieldRW<FIlluminationInShadowType>(getFIlluminationInShadow())->setValue( value );
}



// TwoSided

const LightModel::TwoSidedValueType LightModel::DEFAULT_TWOSIDED = (false);



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



// SamplingSize

const LightModel::SamplingSizeValueType LightModel::DEFAULT_SAMPLINGSIZE = (1.0);



const LightModel::SamplingSizeValueType LightModel::getSamplingSize() const
{
	return getFieldRO<FSamplingSizeType>(getFSamplingSize())->getValue();
}



void LightModel::setSamplingSize( const SamplingSizeValueType value )
{
	getFieldRW<FSamplingSizeType>(getFSamplingSize())->setValue( value );
}



// Option2

const LightModel::Option2ValueType LightModel::DEFAULT_OPTION2 = (false);



const LightModel::Option2ValueType LightModel::getOption2() const
{
	return getFieldRO<FOption2Type>(getFOption2())->getValue();
}



void LightModel::setOption2( const Option2ValueType value )
{
	getFieldRW<FOption2Type>(getFOption2())->setValue( value );
}



// Ambient

const LightModel::AmbientValueType LightModel::DEFAULT_AMBIENT = vgm::Vec4f(0.2f, 0.2f, 0.2f, 0.0f);



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



// IgnorePostProcessing

const LightModel::IgnorePostProcessingValueType LightModel::DEFAULT_IGNOREPOSTPROCESSING = (false);



const LightModel::IgnorePostProcessingValueType LightModel::getIgnorePostProcessing() const
{
	return getFieldRO<FIgnorePostProcessingType>(getFIgnorePostProcessing())->getValue();
}



void LightModel::setIgnorePostProcessing( const IgnorePostProcessingValueType value )
{
	getFieldRW<FIgnorePostProcessingType>(getFIgnorePostProcessing())->setValue( value );
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



// ShadowPolygonOffset

const LightModel::ShadowPolygonOffsetValueType LightModel::DEFAULT_SHADOWPOLYGONOFFSET = vgm::Vec2f(4.f, 16.f);



const LightModel::ShadowPolygonOffsetValueType LightModel::getShadowPolygonOffset() const
{
	return getFieldRO<FShadowPolygonOffsetType>(getFShadowPolygonOffset())->getValue();
}



void LightModel::setShadowPolygonOffset( const ShadowPolygonOffsetValueType value )
{
	getFieldRW<FShadowPolygonOffsetType>(getFShadowPolygonOffset())->setValue( value );
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



// Option0

const LightModel::Option0ValueType LightModel::getOption0() const
{
	return getFieldRO<FOption0Type>(getFOption0())->getValue();
}



void LightModel::setOption0( const Option0ValueType value )
{
	getFieldRW<FOption0Type>(getFOption0())->setValue( value );
}



// Option1

const LightModel::Option1ValueType LightModel::DEFAULT_OPTION1 = (false);



const LightModel::Option1ValueType LightModel::getOption1() const
{
	return getFieldRO<FOption1Type>(getFOption1())->getValue();
}



void LightModel::setOption1( const Option1ValueType value )
{
	getFieldRW<FOption1Type>(getFOption1())->setValue( value );
}



// Field name accessor(s)
const std::string LightModel::getFShadowMapSize( void )
{
	return "f_shadowMapSize";
}



const std::string LightModel::getFShadowFiltering( void )
{
	return "f_shadowFiltering";
}



const std::string LightModel::getFShadowMapType( void )
{
	return "f_shadowMapType";
}



const std::string LightModel::getFIlluminationInShadow( void )
{
	return "f_illuminationInShadow";
}



const std::string LightModel::getFTwoSided( void )
{
	return "f_twoSided";
}



const std::string LightModel::getFSamplingSize( void )
{
	return "f_samplingSize";
}



const std::string LightModel::getFOption2( void )
{
	return "f_option2";
}



const std::string LightModel::getFAmbient( void )
{
	return "f_ambient";
}



const std::string LightModel::getFViewer( void )
{
	return "f_viewer";
}



const std::string LightModel::getFIgnorePostProcessing( void )
{
	return "f_ignorePostProcessing";
}



const std::string LightModel::getFModel( void )
{
	return "f_model";
}



const std::string LightModel::getFShadowPolygonOffset( void )
{
	return "f_shadowPolygonOffset";
}



const std::string LightModel::getFShadow( void )
{
	return "f_shadow";
}



const std::string LightModel::getFOption0( void )
{
	return "f_option0";
}



const std::string LightModel::getFOption1( void )
{
	return "f_option1";
}



IMPLEMENT_INDEXABLE_CLASS_CPP( , LightModel );



const vgd::basic::RegisterNode<LightModel> LightModel::m_registrationInstance;



} // namespace node

} // namespace vgd

