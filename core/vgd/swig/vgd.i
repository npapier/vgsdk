
%module (directors="1") vgd

%feature("director"); 
%feature("director:except") {
    if ($error != NULL) {
        throw Swig::DirectorMethodException();
    }
}

%exception {
    try { $action }
    catch (Swig::DirectorException &e) 
	{ 
		PyErr_SetString(PyExc_RuntimeError, e.getMessage()); 
	}
}

#define VGD_API
#define VGE_API
//#define VGEGL_API
//#define VGEGL_CLASS_API
#define BOOST_NOEXCEPT
#pragma SWIG nowarn=SWIGWARN_PARSE_NESTED_struct

%include <std_vector.i>
%include <std_string.i>
%include <std_vector.i>
%include <stdint.i>
%include <Shp.i>
%include vgm/vgm.i


%Shp( vgd::basic::NamedObject )
%Shp( vgd::field::IFieldObserver )
%Shp( vgd::node::ClearFrameBuffer )
%Shp( vgd::basic::Object)
%Shp( vgd::field::FieldManager )
%Shp( vgd::node::Node  )
%Shp( vgd::node::Attribute )
%Shp( vgd::node::SingleAttribute )
%Shp( vgd::node::IGroup )
%Shp( vgd::node::IBoundingBox )
%Shp( vgd::node::Group )
%Shp( vgd::field::AbstractField )

%Shp( vgd::node::CoordinateSystem )
%Shp( vgd::node::CullFace )
%Shp( vgd::node::DepthOfField )
%Shp( vgd::node::Displacement )
%Shp( vgd::node::DrawStyle )
%Shp( vgd::node::EngineProperties )
%Shp( vgd::node::FrameBuffer )
%Shp( vgd::node::FrontFace )
%Shp( vgd::node::LightModel )
%Shp( vgd::node::Material )
%Shp( vgd::node::Noise )
%Shp( vgd::node::OutputBuffers )
%Shp( vgd::node::PointStyle )
%Shp( vgd::node::Program )
%Shp( vgd::node::TessellationLevel )
%Shp( vgd::node::TessellationProperties )
%Shp( vgd::node::Uniforms )
%Shp( vgd::node::Callback )
%Shp( vgd::node::MultiAttribute )
%Shp( vgd::node::LayerPlan )
%Shp( vgd::node::Overlay )
%Shp( vgd::node::IShape )
%Shp( vgd::node::GeoMorph )
%Shp( vgd::node::MultiSwitch )
%Shp( vgd::node::OffscreenRendering )
%Shp( vgd::node::Separator )
%Shp( vgd::node::Switch )
%Shp( vgd::node::TransformSeparator )
%Shp( vgd::node::SingleTransformation )
%Shp( vgd::node::GeometricalTransformation )
%Shp( vgd::node::ProjectionTransformation )
%Shp( vgd::node::Camera )
%Shp( vgd::node::MatrixTransform )
%Shp( vgd::node::SurroundScale )
%Shp( vgd::node::Transform )
%Shp( vgd::node::Shape )
%Shp( vgd::node::GeometricalTransformation )
%Shp( vgd::node::Antialiasing )
%Shp( vgd::node::ITransformation )
%Shp( vgd::node::VertexShape )
%Shp( vgd::node::Sphere )
%Shp( vgd::node::Box )
%Shp( vgd::node::Quad )
%Shp( vgd::node::MultipleInstances )

%Shp( vgd::node::ClipPlane )
%Shp( vgd::node::Decal )
%Shp( vgd::node::Light )
%Shp( vgd::node::DirectionalLight )
%Shp( vgd::node::OutputBufferProperty )
%Shp( vgd::node::PointLight )
%Shp( vgd::node::PostProcessing )
%Shp( vgd::node::SpotLight )
%Shp( vgd::node::MultiTransformation )
%Shp( vgd::node::TextureTransformation )
%Shp( vgd::node::TextureMatrixTransform )

%Shp( vgd::node::IDragger )
%Shp( vgd::node::Dragger )
%Shp( vgd::node::TransformDragger )
%Shp( vgd::node::Scale1Dragger )
%Shp( vgd::node::NullDragger )
%Shp( vgd::node::TexGen )
%Shp( vgd::node::Texture )
%Shp( vgd::node::TexGenEyeLinear )
%Shp( vgd::node::Texture1D )
%Shp( vgd::node::Texture2D )
%Shp( vgd::node::WireShape )
%Shp( vgd::node::WireQuad )
%Shp( vgd::node::WireBox )
%Shp( vgd::node::Grid )
%Shp( vgd::node::Kit )
%Shp( vgd::node::TriSet )
%Shp( vgd::node::Fluid )
%Shp( vgd::basic::IImage )
%Shp( vgd::basic::Image )

%feature ("flatnested");

%{

#include "vgd/vgd.hpp"
#include "vge/vge.hpp"
//#include "vgeGL/vgeGL.hpp"

#include "vgd/visitor/helpers.hpp"
//#include "vgeGL/itf/IUnderlay.hpp"
// #include <vge/technique/Technique.hpp>
// #include <vgeGL/technique/Technique.hpp>
#include "vgd/field/EditorRO.hpp"
#include "vgd/basic/IImage.hpp"
#include "vgd/basic/Image.hpp"
#include "vgd/event/Listener.hpp"
#include "vgd/event/DeviceManager.hpp"
#include "vgd/field/Enum.hpp"
#include "vgd/field/AbstractField.hpp"
#include "vgd/basic/ClassRegistry.hpp"
#include "vgd/basic/RegisterNode.hpp"
#include "vgd/basic/IndexableClass.hpp"
#include "vgd/basic/Object.hpp"
#include "vgd/field/FieldManager.hpp"

#include "vgd/node/Enum.hpp"
#include "vgd/node/Primitive.hpp"
#include "vgd/node/Node.hpp"
#include "vgd/node/Group.hpp"
#include "vgd/node/IBoundingBox.hpp"
#include "vgd/node/Attribute.hpp"
#include "vgd/node/SingleAttribute.hpp"
#include "vgd/node/Program.hpp"
#include "vgd/node/Kit.hpp"
#include "vgd/node/IDragger.hpp"
#include "vgd/node/Dragger.hpp"
#include "vgd/node/NullDragger.hpp"
#include "vgd/node/TransformDragger.hpp"
#include "vgd/node/Scale1Dragger.hpp"

#include "vgd/node/CoordinateSystem.hpp"
#include "vgd/node/CullFace.hpp"
#include "vgd/node/DepthOfField.hpp"
#include "vgd/node/Displacement.hpp"
#include "vgd/node/DrawStyle.hpp"
#include "vgd/node/EngineProperties.hpp"
#include "vgd/node/FrameBuffer.hpp"
#include "vgd/node/FrontFace.hpp"
#include "vgd/node/LightModel.hpp"
#include "vgd/node/Light.hpp"
#include "vgd/node/Material.hpp"
#include "vgd/node/Noise.hpp"
#include "vgd/node/OutputBuffers.hpp"
#include "vgd/node/PointStyle.hpp"
#include "vgd/node/Program.hpp"
#include "vgd/node/TessellationLevel.hpp"
#include "vgd/node/TessellationProperties.hpp"
#include "vgd/node/Uniforms.hpp"
// #include "vgd/node/Callback.hpp"

#include "vgd/node/MultiAttribute.hpp"
#include "vgd/node/TexGen.hpp"
#include "vgd/node/Texture.hpp"
#include "vgd/node/LayerPlan.hpp"
#include "vgd/node/Overlay.hpp"
#include "vgd/node/ClipPlane.hpp"
#include "vgd/node/Decal.hpp"
#include "vgd/node/Light.hpp" 
#include "vgd/node/DirectionalLight.hpp" 
#include "vgd/node/OutputBufferProperty.hpp" 
#include "vgd/node/PointLight.hpp" 
#include "vgd/node/PostProcessing.hpp" 
#include "vgd/node/SpotLight.hpp" 
#include "vgd/node/TexGenEyeLinear.hpp" 
#include "vgd/node/Texture1D.hpp" 
#include "vgd/node/Texture2D.hpp" 
#include "vgd/node/MultiTransformation.hpp" 
#include "vgd/node/TextureTransformation.hpp" 
#include "vgd/node/TextureMatrixTransform.hpp" 

#include "vgd/node/GeoMorph.hpp"
#include "vgd/node/MultiSwitch.hpp"
#include "vgd/node/OffscreenRendering.hpp"
#include "vgd/node/Separator.hpp"
#include "vgd/node/Switch.hpp"
#include "vgd/node/TransformSeparator.hpp"

#include "vgd/node/ITransformation.hpp"
#include "vgd/node/IShape.hpp"
#include "vgd/node/Shape.hpp"
#include "vgd/node/VertexShape.hpp"
#include "vgd/node/MultipleInstances.hpp"
#include "vgd/node/Quad.hpp"
#include "vgd/node/Sphere.hpp"
#include "vgd/node/WireShape.hpp"
#include "vgd/node/WireQuad.hpp"
#include "vgd/node/WireBox.hpp"
#include "vgd/node/Fluid.hpp"
#include "vgd/node/TriSet.hpp"
#include "vgd/node/Grid.hpp"
#include "vgd/node/Box.hpp"
#include "vgd/node/SingleTransformation.hpp"
#include "vgd/node/GeometricalTransformation.hpp"
#include "vgd/node/ProjectionTransformation.hpp"
#include "vgd/node/Camera.hpp"

#include "vgd/node/MatrixTransform.hpp"
#include "vgd/node/SurroundScale.hpp"
#include "vgd/node/Transform.hpp"
#include "vgd/node/Antialiasing.hpp"
#include "vgd/node/ClearFrameBuffer.hpp"
//#include "boost/smart_ptr/shared_ptr.hpp"
//#include "boost/smart_ptr/enable_shared_from_this.hpp"
//#include "boost/enable_shared_from_this.hpp"
#include "vgd/EnableShpFromThis.hpp"

%}

%nspace vge::technique::Technique::PassIsolationMask;

namespace vgd
{

namespace field
{
	enum EditingMode {
		RW		= -1,
		NONE	= 0,
		RO		= 1
	};
	
	enum Event
	{
		DESTROY, 
		UPDATE 
	};
}
}


%inline %{
typedef unsigned int uint32;
typedef unsigned char uint8;
%} 

%ignore DEFAULT_CLEARCOLOR;

%ignore vgd::node::Group::m_registrationInstance;
%ignore vgd::node::SurroundScale::m_registrationInstance;
%ignore vgd::node::CoordinateSystem::m_registrationInstance;
%ignore vgd::node::Transform::m_registrationInstance;
%ignore vgd::node::Box::m_registrationInstance;
%ignore vgd::node::Callback::computeBoundingBox(struct vgm::MatrixR const &);
%ignore vgd::node::Callback::isBoundingBoxValid(void) const;
%ignore vgd::node::Callback::invalidateBoundingBox(bool);
%ignore vgd::node::Callback::getstructIndex(void);
%ignore vgd::node::Callback::setToDefaults(void);
%ignore vgd::node::Callback::setOptionalsToDefaults(void);

%ignore vgd::node::Antialiasing::DEFAULT_QUALITYPRESET;

%ignore vgd::node::DepthOfField::DEFAULT_FOCUS;
%ignore vgd::node::DepthOfField::DEFAULT_FOCUSTOFAR;
%ignore vgd::node::DepthOfField::DEFAULT_FOCUSTONEAR;
%ignore vgd::node::DepthOfField::DEFAULT_FARMAXIMUMBLURRINESS;
%ignore vgd::node::DepthOfField::DEFAULT_NEARMAXIMUMBLURRINESS;
%ignore vgd::node::DepthOfField::DEFAULT_SAMPLING;
%ignore vgd::node::DrawStyle::DEFAULT_NORMALLENGTH;
%ignore vgd::node::DrawStyle::DEFAULT_TANGENTLENGTH;
%ignore vgd::node::DrawStyle::DEFAULT_SHOWORIENTATION;
%ignore vgd::node::EngineProperties::DEFAULT_MAXANISOTROPY;
%ignore vgd::node::EngineProperties::DEFAULT_OPENGLDEBUGOUTPUT;
%ignore vgd::node::EngineProperties::DEFAULT_OPENGLDIRECTSTATEACCESS;
%ignore vgd::node::LightModel::DEFAULT_SAMPLINGSIZE;
%ignore vgd::node::LightModel::DEFAULT_ILLUMINATIONINSHADOW;
%ignore vgd::node::LightModel::DEFAULT_BUMPMAPPING;
%ignore vgd::node::LightModel::DEFAULT_OPTION1;
%ignore vgd::node::LightModel::DEFAULT_OPTION2;
%ignore vgd::node::LightModel::DEFAULT_IGNOREPOSTPROCESSING;
%ignore vgd::node::LightModel::DEFAULT_TWOSIDED;
%ignore vgd::node::Material::DEFAULT_OPACITY;
%ignore vgd::node::Material::DEFAULT_SHININESS;
%ignore vgd::node::Noise::DEFAULT_CHANNELSSEPARATED;
%ignore vgd::node::Noise::DEFAULT_USETEXTURELESSRANDOM;
%ignore vgd::node::Noise::DEFAULT_FREQUENCY;
%ignore vgd::node::PointStyle::DEFAULT_SIZE;
%ignore vgd::node::PointStyle::DEFAULT_SMOOTH;
%ignore vgd::node::PointStyle::DEFAULT_POINTSPRITE;
%ignore vgd::node::Program::DEFAULT_VERTEXUSE;
%ignore vgd::node::Program::DEFAULT_TESSELLATIONUSE;
%ignore vgd::node::Program::DEFAULT_GEOMETRYUSE;
%ignore vgd::node::Program::DEFAULT_FRAGMENTUSE;
%ignore vgd::node::TessellationProperties::DEFAULT_PHONGBIAS;
%ignore vgd::node::TessellationProperties::DEFAULT_PIXELSPEREDGE;
%ignore vgd::node::LayerPlan::DEFAULT_ALPHASCALE;
%ignore vgd::node::Separator::DEFAULT_FULLSEPARATION;
%ignore vgd::node::Separator::DEFAULT_TESSELLATIONLEVELSEPARATION;
%ignore vgd::node::Separator::DEFAULT_DISPLACEMENTSEPARATION;
%ignore vgd::node::Camera::DEFAULT_FOVY;
%ignore vgd::node::Camera::DEFAULT_EYESEPARATION;
%ignore vgd::node::Camera::DEFAULT_IMAGESHIFT;
%ignore vgd::node::Camera::DEFAULT_RIGHTEYE;
%ignore vgd::node::Camera::DEFAULT_ASPECT;
%ignore vgd::node::Camera::DEFAULT_ZNEAR;
%ignore vgd::node::Camera::DEFAULT_ZFAR;
%ignore vgd::node::LightModel::DEFAULT_SHADOWPOLYGONOFFSET;
%ignore vgd::node::LightModel::DEFAULT_AMBIENT;
%ignore vgd::node::Material::DEFAULT_AMBIENT;
%ignore vgd::node::Material::DEFAULT_DIFFUSE;
%ignore vgd::node::Material::DEFAULT_SPECULAR;
%ignore vgd::node::Material::DEFAULT_EMISSION;
%ignore vgd::node::Noise::DEFAULT_FACTORS;
%ignore vgd::node::Noise::DEFAULT_RANDOMTEXTURESCALEFACTORS;
%ignore vgd::node::PointStyle::DEFAULT_DISTANCEATTENUATION;
%ignore vgd::node::TessellationProperties::DEFAULT_RANGE;
%ignore vgd::node::Callback::m_registrationInstance;

%ignore vgd::node::LayerPlan::DEFAULT_POSITION;
%ignore vgd::node::LayerPlan::DEFAULT_SIZE;
%ignore vgd::node::LayerPlan;
%ignore vgd::node::GeoMorph::DEFAULT_WEIGHTS;
%ignore vgd::node::OffscreenRendering::DEFAULT_ROOT;

%ignore vgd::node::Camera::DEFAULT_PROJECTIONLEFT;
%ignore vgd::node::Camera::DEFAULT_LOOKATLEFT;
%ignore vgd::node::Camera::DEFAULT_PROJECTIONRIGHT;
%ignore vgd::node::Camera::DEFAULT_LOOKATRIGHT;
%ignore vgd::node::Camera::DEFAULT_VIEWPORT;
%ignore vgd::node::Camera::DEFAULT_SCISSOR;

%ignore vgd::node::Displacement::DEFAULT_DECLARATIONSVS;
%ignore vgd::node::Displacement::DEFAULT_DISPLACEMENTVS;
%ignore vgd::node::Displacement::DEFAULT_DECLARATIONSTES;
%ignore vgd::node::Displacement::DEFAULT_DISPLACEMENTTES;
%ignore vgd::node::Program::DEFAULT_VERTEX;
%ignore vgd::node::Program::DEFAULT_TESSELLATIONCONTROL;
%ignore vgd::node::Program::DEFAULT_TESSELLATIONEVALUATION;
%ignore vgd::node::Program::DEFAULT_GEOMETRY;
%ignore vgd::node::Program::DEFAULT_FRAGMENT;
%ignore vgd::node::TessellationLevel::DEFAULT_CUSTOMDECLARATIONS;
%ignore vgd::node::TessellationLevel::DEFAULT_CUSTOMCODE;

%ignore vgd::node::ClipPlane::DEFAULT_ON;
%ignore vgd::node::Decal::DEFAULT_ALPHATEST;
%ignore vgd::node::Decal::DEFAULT_BLENDING;
%ignore vgd::node::Light::DEFAULT_CASTSHADOW;
%ignore vgd::node::Light::DEFAULT_ON;
%ignore vgd::node::OutputBufferProperty::DEFAULT_CURRENT;
%ignore vgd::node::PostProcessing::DEFAULT_PARAM1F0;
%ignore vgd::node::PostProcessing::DEFAULT_PARAM1F1;
%ignore vgd::node::SpotLight::DEFAULT_CUTOFFANGLE;
%ignore vgd::node::SpotLight::DEFAULT_DROPOFFRATE;
%ignore vgd::node::ClipPlane::DEFAULT_PLANE;
%ignore vgd::node::Decal::DEFAULT_TEXTURE;
%ignore vgd::node::Decal::DEFAULT_SHAPE;
%ignore vgd::node::Light::DEFAULT_AMBIENT;
%ignore vgd::node::Light::DEFAULT_DIFFUSE;
%ignore vgd::node::Light::DEFAULT_SPECULAR;
%ignore vgd::node::DirectionalLight::DEFAULT_DIRECTION;
%ignore vgd::node::OutputBufferProperty::DEFAULT_SIZE;
%ignore vgd::node::OutputBufferProperty::DEFAULT_TEXTURENODE;
%ignore vgd::node::PointLight::DEFAULT_POSITION;
%ignore vgd::node::PostProcessing::DEFAULT_TEXTURE0;
%ignore vgd::node::PostProcessing::DEFAULT_PARAM4F0;
%ignore vgd::node::PostProcessing::DEFAULT_PARAM4F1;
%ignore vgd::node::PostProcessing::DEFAULT_PARAM4X4F0;
%ignore vgd::node::SpotLight::DEFAULT_DIRECTION;
%ignore vgd::node::TexGenEyeLinear::DEFAULT_PARAMETERS;
%ignore vgd::node::OutputBufferProperty::DEFAULT_CUSTOMDECLARATION;
%ignore vgd::node::OutputBufferProperty::DEFAULT_CUSTOMCOMMAND;
%ignore vgd::node::PostProcessing::DEFAULT_CUSTOMFILTERDEFINITION;
%ignore vgd::node::PostProcessing::DEFAULT_CUSTOMFILTERAPPLY;

%ignore vgd::node::TexGen::DEFAULT_ON;
%ignore vgd::node::Texture::DEFAULT_MIPMAP;
%ignore  vgd::node::Texture::DEFAULT_MAXANISOTROPY;
%ignore  vgd::node::Fluid::DEFAULT_CELLSIZE;
%ignore  vgd::node::Fluid::DEFAULT_CSS;
%ignore  vgd::node::Fluid::DEFAULT_TIMESTEP;
%ignore  vgd::node::Fluid::DEFAULT_DAMPING;
%ignore  vgd::node::Fluid::DEFAULT_THICKNESS;
%ignore  vgd::node::Fluid::DEFAULT_OPACITY;
%ignore vgd::node::Fluid::DEFAULT_REQUESTFEEDBACK;
%ignore vgd::node::Texture::DEFAULT_IMAGE;

%ignore vgd::node::Texture::DEFAULT_VERTEXFUNCTION;
%ignore vgd::node::Texture::DEFAULT_FRAGMENTFUNCTION;
%ignore vgd::node::Fluid::DEFAULT_SIMULATIONPASS0;
%ignore vgd::node::Fluid::DEFAULT_SIMULATIONPASS1;

%ignore vgd::node::Fluid::DEFAULT_SCENE;
%ignore vgd::node::Fluid::DEFAULT_GRAVITY;
%ignore vgd::node::Fluid::DEFAULT_HEIGHTMAPSIZE;
%ignore vgd::node::Fluid::DEFAULT_FEEDBACKINFORMATIONS;
%ignore vgd::node::Fluid::DEFAULT_FEEDBACKINFORMATIONSBIS;
%ignore vgd::node::Fluid::DEFAULT_FLUIDPOSITIONFEEDBACK;

%ignore vgd::node::TextureMatrixTransform::m_registrationInstance;
%ignore vgd::node::MatrixTransform::m_registrationInstance;
%ignore vgd::node::WireQuad::m_registrationInstance;
%ignore vgd::node::WireBox::m_registrationInstance;
%ignore vgd::node::Grid::m_registrationInstance;
%ignore vgd::node::TriSet::m_registrationInstance;

%ignore vgd::node::NullDragger::m_registrationInstance;
%ignore vgd::node::TransformDragger::m_registrationInstance;
%ignore vgd::node::Scale1Dragger::m_registrationInstance;
%ignore vgd::node::Quad::m_registrationInstance;
%ignore vgd::node::Sphere::m_registrationInstance;
%ignore vgd::node::MultipleInstances::DEFAULT_SHAPE;

%ignore boost::shared_ptr::operator=;
%ignore vgd::node::Material::getColor;
%ignore vgd::node::Material::setColor;
%ignore vgd::node::Material::eraseColor;

%ignore vgd::node::Light::getColor;
%ignore vgd::node::Light::setColor;
%ignore vgd::node::Light::getMatrix;
%ignore vgd::node::Light::setMatrix;
%ignore vgd::node::Light::eraseColor;

%ignore vgd::node::Camera::getMatrix;
%ignore vgd::node::Light::setMatrix;

%rename( TechniqueVge ) vge::technique::Technique;
%rename( FilterValueTypePostProcessing ) vgd::node::PostProcessing::FilterValueType;
%rename( MethodValueTypeGeoMorph ) vgd::node::GeoMorph::MethodValueType;
%rename( ModeValueTypeCamera ) vgd::node::Camera::ModeValueType;
%rename( TechniqueValueTypeVertexShape ) vgd::node::VertexShape::TechniqueValueType;
%rename( ComposeModeValueTypeDisplacement) vgd::node::Displacement::ComposeModeValueType;
%rename( ComposeModeValueTypeUniforms) vgd::node::Uniforms::ComposeModeValueType;

%feature("flatnested") SizeSemanticValueType;
%feature("flatnested") FormatValueType;
%feature("flatnested") TypeValueType;
%feature("flatnested") CommandValueType;;


%include "vgd/visitor/helpers.hpp"
//%include "vgeGL/itf/IUnderlay.hpp"
%include "vgd/event/Listener.hpp"
%include "vgd/event/DeviceManager.hpp"
// %include "vge/technique/Technique.hpp"
// %include "vgeGL/technique/Technique.hpp"

%include "vgd/field/EditorRO.hpp"
%include "vgd/basic/IImage.hpp"
%include "vgd/basic/Image.hpp"
%include "vgd/field/Enum.hpp"
%include "vgd/node/Enum.hpp"
%include "vgd/node/Primitive.hpp"
%include "vgd/basic/NamedObject.hpp"
%include "vgd/field/IFieldObserver.hpp"
%include "vgd/field/AbstractField.hpp"
%include "vgd/basic/ClassRegistry.hpp"
%include "vgd/basic/RegisterNode.hpp"
%include "vgd/basic/Object.hpp"
%include "vgd/field/FieldManager.hpp"
%include "vgd/node/Node.hpp"
%include "vgd/node/IGroup.hpp"
%include "vgd/node/IBoundingBox.hpp"
%include "vgd/node/IShape.hpp"
%include "vgd/node/Group.hpp"
%include "vgd/node/Attribute.hpp"
%include "vgd/node/SingleAttribute.hpp"
%include "vgd/node/Program.hpp"
%include "vgd/node/Kit.hpp"
%include "vgd/node/IDragger.hpp"
%include "vgd/node/Dragger.hpp"
%include "vgd/node/NullDragger.hpp"
%include "vgd/node/TransformDragger.hpp"
%include "vgd/node/Scale1Dragger.hpp"
//Herite de singleAttribute
%include "vgd/node/CoordinateSystem.hpp"
%include "vgd/node/CullFace.hpp"
%include "vgd/node/DepthOfField.hpp"
%include "vgd/node/Displacement.hpp"
%include "vgd/node/DrawStyle.hpp"
%include "vgd/node/EngineProperties.hpp"
%include "vgd/node/FrameBuffer.hpp"
%include "vgd/node/FrontFace.hpp"
%include "vgd/node/LightModel.hpp"
%include "vgd/node/Light.hpp"
%include "vgd/node/Material.hpp"
%include "vgd/node/Noise.hpp"
%include "vgd/node/OutputBuffers.hpp"
%include "vgd/node/PointStyle.hpp"
%include "vgd/node/Program.hpp"
%include "vgd/node/TessellationLevel.hpp"
%include "vgd/node/TessellationProperties.hpp"
%include "vgd/node/Uniforms.hpp"
// %include "vgd/node/Callback.hpp"


%include "vgd/node/MultiAttribute.hpp"
%include "vgd/node/TexGen.hpp"
%include "vgd/node/Texture.hpp"
%include "vgd/node/LayerPlan.hpp"
%include "vgd/node/Overlay.hpp"
%include "vgd/node/ClipPlane.hpp"
%include "vgd/node/Decal.hpp"
%include "vgd/node/Light.hpp" 
%include "vgd/node/DirectionalLight.hpp" 
%include "vgd/node/OutputBufferProperty.hpp" 
%include "vgd/node/PointLight.hpp" 
%include "vgd/node/PostProcessing.hpp" 
%include "vgd/node/SpotLight.hpp" 
%include "vgd/node/TexGenEyeLinear.hpp" 
%include "vgd/node/Texture1D.hpp" 
%include "vgd/node/Texture2D.hpp" 
%include "vgd/node/MultiTransformation.hpp" 
%include "vgd/node/TextureTransformation.hpp" 
%include "vgd/node/TextureMatrixTransform.hpp" 
  
%include "vgd/node/GeoMorph.hpp"
%include "vgd/node/MultiSwitch.hpp"
%include "vgd/node/OffscreenRendering.hpp"
%include "vgd/node/Separator.hpp"
%include "vgd/node/Switch.hpp"
%include "vgd/node/TransformSeparator.hpp"

%include "vgd/node/SingleTransformation.hpp"
%include "vgd/node/GeometricalTransformation.hpp"
%include "vgd/node/ProjectionTransformation.hpp"
%include "vgd/node/Camera.hpp"

%include "vgd/node/MatrixTransform.hpp"
%include "vgd/node/SurroundScale.hpp"
%include "vgd/node/Transform.hpp"

%include "vgd/node/ITransformation.hpp"
%include "vgd/node/Shape.hpp"
%include "vgd/node/VertexShape.hpp"
%include "vgd/node/Quad.hpp"
%include "vgd/node/Sphere.hpp"
%include "vgd/node/WireShape.hpp"
%include "vgd/node/WireQuad.hpp"
%include "vgd/node/WireBox.hpp"
%include "vgd/node/Grid.hpp"
%include "vgd/node/TriSet.hpp"
%include "vgd/node/MultipleInstances.hpp"

%include "vgd/node/Box.hpp"
%include "vgd/node/Antialiasing.hpp"
%include "vgd/node/ClearFrameBuffer.hpp"
%include "vgd/node/Fluid.hpp"

//%include "boost/smart_ptr/shared_ptr.hpp"
//%include "boost/smart_ptr/enable_shared_from_this.hpp"
//%include <boost/shared_ptr.hpp>
//%include "boost/enable_shared_from_this.hpp"
%include "vgd/EnableShpFromThis.hpp"

%template( EditorROVertexShapeFNormalType ) vgd::field::EditorRO< vgd::node::VertexShape::FNormalType >;
%template( EditorROVertexShapeFColorType ) vgd::field::EditorRO< vgd::node::VertexShape::FColorType >;
%template( registryGroup )	vgd::basic::ClassRegistry<struct vgd::node::Group>;
%template( registrationInstanceGoup )	vgd::basic::RegisterNode<struct vgd::node::Group>;
//%template( NodeBoostShpFromThis) boost::enable_shared_from_this< vgd::node::Node >;
//%template( NodeBoostShpFromThis) boost::enable_shared_from_this< vgd::node::Node >;
%template( NodeshpFromThis ) vgd::EnableShpFromThis<vgd::node::Node>;
%template( findFirstByNameVertexShape ) vgd::visitor::findFirstByName< vgd::node::VertexShape >;
%template( setUniformVec4f ) vgd::node::Uniforms::setUniform<vgm::Vec4f>;


/*
%{

typedef vgd::node::CullFace::ModeValueType ModeValueType;
typedef vgd::node::DepthOfField::CameraModelValueType CameraModelValueType;
typedef vgd::node::Displacement::PredefinedDisplacementValueType PredefinedDisplacementValueType;
// typedef vgd::node::Displacement::ComposeModeValueType ComposeModeValueType;

typedef vgd::node::DrawStyle::ShapeValueType ShapeValueType;
typedef vgd::node::DrawStyle::BoundingBoxValueType BoundingBoxValueType;
typedef vgd::node::FrontFace::OrientationValueType OrientationValueType;
typedef vgd::node::LightModel::ViewerValueType ViewerValueType;
typedef vgd::node::LightModel::ShadowValueType ShadowValueType;
typedef vgd::node::LightModel::ModelValueType ModelValueType;
typedef vgd::node::LightModel::ShadowMapSizeValueType ShadowMapSizeValueType;
typedef vgd::node::LightModel::ShadowFilteringValueType ShadowFilteringValueType;
typedef vgd::node::LightModel::Option0ValueType Option0ValueType;
typedef vgd::node::TessellationLevel::MethodValueType MethodValueType;
typedef vgd::node::TessellationLevel::ComposeModeValueType ComposeModeValueType;
typedef vgd::node::Texture::WrapSelectorValueType WrapSelectorValueType;
typedef vgd::node::Texture::FilterValueType FilterValueType;
typedef vgd::node::Texture::FilteringValueType FilteringValueType;
typedef vgd::node::Texture::UsageValueType UsageValueType;
typedef vgd::node::Texture::InternalFormatValueType InternalFormatValueType;
typedef vgd::node::Texture::WrappingValueType WrappingValueType;

typedef vgd::node::OutputBufferProperty::SizeSemanticValueType SizeSemanticValueType;
typedef vgd::node::OutputBufferProperty::FormatValueType FormatValueType;
typedef vgd::node::OutputBufferProperty::TypeValueType TypeValueType;
typedef vgd::node::OutputBufferProperty::CommandValueType CommandValueType;

typedef vgd::node::PostProcessing::FilterValueType FilterValueType;
typedef vgd::node::PostProcessing::Input0ValueType Input0ValueType;
typedef vgd::node::PostProcessing::Input0SamplingValueType Input0SamplingValueType;
typedef vgd::node::PostProcessing::Input1ValueType Input1ValueType;
typedef vgd::node::PostProcessing::Input2ValueType Input2ValueType;
typedef vgd::node::PostProcessing::OutputValueType OutputValueType;

// typedef vgd::node::GeoMorph::MethodValueType MethodValueType;
typedef vgd::node::Camera::EyeUsagePolicyValueType EyeUsagePolicyValueType;
// typedef vgd::node::Camera::ModeValueTypeCamera ModeValueTypeCamera;

typedef vgd::node::VertexShape::BoundingBoxUpdatePolicyValueType BoundingBoxUpdatePolicyValueType;
typedef vgd::node::VertexShape::DeformableHintValueType DeformableHintValueType;
// typedef vgd::node::VertexShape::TechniqueValueType TechniqueValueType;

%}
*/
