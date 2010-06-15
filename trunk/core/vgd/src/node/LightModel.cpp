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
	addField( new FShadowMapTypeType(getFShadowMapType()) );
	addField( new FIlluminationInShadowType(getFIlluminationInShadow()) );
	addField( new FTwoSidedType(getFTwoSided()) );
	addField( new FSamplingSizeType(getFSamplingSize()) );
	addField( new FIgnorePostProcessingType(getFIgnorePostProcessing()) );
	addField( new FShadowQualityType(getFShadowQuality()) );
	addField( new FViewerType(getFViewer()) );
	addField( new FUseShadowSamplersType(getFUseShadowSamplers()) );
	addField( new FAmbientType(getFAmbient()) );
	addField( new FModelType(getFModel()) );
	addField( new FShadowPolygonOffsetType(getFShadowPolygonOffset()) );
	addField( new FShadowType(getFShadow()) );

	// Sets link(s)

	link( getDFNode() );
}



void LightModel::setToDefaults( void )
{
	SingleAttribute::setToDefaults();
	setShadowMapType( INT32 );
	setIlluminationInShadow( 0.4f );
	setSamplingSize( 1.0 );
	setIgnorePostProcessing( false );
	setShadowPolygonOffset( vgm::Vec2f(4.f, 16.f) );
}



void LightModel::setOptionalsToDefaults()
{
	SingleAttribute::setOptionalsToDefaults();
	setTwoSided( false );
	setShadowQuality( MEDIUM );
	setViewer( AT_INFINITY );
	setUseShadowSamplers( true );
	setAmbient( vgm::Vec4f(0.2f, 0.2f, 0.2f, 0.0f) );
	setModel( STANDARD_PER_VERTEX );
	setShadow( SHADOW_OFF );
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
const LightModel::IlluminationInShadowValueType LightModel::getIlluminationInShadow() const
{
	return getFieldRO<FIlluminationInShadowType>(getFIlluminationInShadow())->getValue();
}



void LightModel::setIlluminationInShadow( const IlluminationInShadowValueType value )
{
	getFieldRW<FIlluminationInShadowType>(getFIlluminationInShadow())->setValue( value );
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



// SamplingSize
const LightModel::SamplingSizeValueType LightModel::getSamplingSize() const
{
	return getFieldRO<FSamplingSizeType>(getFSamplingSize())->getValue();
}



void LightModel::setSamplingSize( const SamplingSizeValueType value )
{
	getFieldRW<FSamplingSizeType>(getFSamplingSize())->setValue( value );
}



// IgnorePostProcessing
const LightModel::IgnorePostProcessingValueType LightModel::getIgnorePostProcessing() const
{
	return getFieldRO<FIgnorePostProcessingType>(getFIgnorePostProcessing())->getValue();
}



void LightModel::setIgnorePostProcessing( const IgnorePostProcessingValueType value )
{
	getFieldRW<FIgnorePostProcessingType>(getFIgnorePostProcessing())->setValue( value );
}



// ShadowQuality
const bool LightModel::getShadowQuality( ShadowQualityValueType& value ) const
{
	return getFieldRO<FShadowQualityType>(getFShadowQuality())->getValue( value );
}



void LightModel::setShadowQuality( const ShadowQualityValueType& value )
{
	getFieldRW<FShadowQualityType>(getFShadowQuality())->setValue( value );
}



void LightModel::eraseShadowQuality()
{
	getFieldRW<FShadowQualityType>(getFShadowQuality())->eraseValue();
}


const bool LightModel::hasShadowQuality() const
{
	return getFieldRO<FShadowQualityType>(getFShadowQuality())->hasValue();
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



// UseShadowSamplers
const bool LightModel::getUseShadowSamplers( UseShadowSamplersValueType& value ) const
{
	return getFieldRO<FUseShadowSamplersType>(getFUseShadowSamplers())->getValue( value );
}



void LightModel::setUseShadowSamplers( const UseShadowSamplersValueType& value )
{
	getFieldRW<FUseShadowSamplersType>(getFUseShadowSamplers())->setValue( value );
}



void LightModel::eraseUseShadowSamplers()
{
	getFieldRW<FUseShadowSamplersType>(getFUseShadowSamplers())->eraseValue();
}


const bool LightModel::hasUseShadowSamplers() const
{
	return getFieldRO<FUseShadowSamplersType>(getFUseShadowSamplers())->hasValue();
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



// Field name accessor(s)
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



const std::string LightModel::getFIgnorePostProcessing( void )
{
	return "f_ignorePostProcessing";
}



const std::string LightModel::getFShadowQuality( void )
{
	return "f_shadowQuality";
}



const std::string LightModel::getFViewer( void )
{
	return "f_viewer";
}



const std::string LightModel::getFUseShadowSamplers( void )
{
	return "f_useShadowSamplers";
}



const std::string LightModel::getFAmbient( void )
{
	return "f_ambient";
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



IMPLEMENT_INDEXABLE_CLASS_CPP( , LightModel );



const vgd::basic::RegisterNode<LightModel> LightModel::m_registrationInstance;



} // namespace node

} // namespace vgd

