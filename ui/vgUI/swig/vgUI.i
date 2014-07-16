%module (directors="1") vgUI
%feature("director"); 
//Pour gérer les exceptions swig
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

#define VGUI_API
#define VGD_API
#define VGE_API
#define VGEGL_API

%include <std_vector.i>
%include <std_string.i>
%include <Shp.i>

// %include vge/vge.i
%include vgd/vgd.i

// %Shp( vge::engine::Engine )
// %Shp( vgd::node::Group )
// %Shp( vgd::node::Node )

// %Shp( vgd::node::SingleAttribute )
// %Shp( vgd::node::ClearFrameBuffer )
// %Shp( vgd::basic::Object)
// %Shp( vgd::field::IFieldObserver )
// %Shp( vgd::field::FieldManager )
// %Shp( vgd::node::Node  )
// %Shp( vgd::node::IGroup )
// %Shp( vgd::node::IBoundingBox )
// %Shp( vgd::node::Group )
// %Shp( vgd::field::AbstractField )

%Shp( vgd::event::Device )
%Shp( vge::engine::Engine )
%Shp( vgd::node::Group )
%Shp( vgd::node::Node )
%Shp( vgUI::python::Context )

%feature ("flatnested");


%{

// #include "vgd/node/Node.hpp"
// #include "vgd/node/IGroup.hpp"
// #include "vgd/node/IBoundingBox.hpp"
// #include "vgd/field/IFieldObserver.hpp"

// #include "vgd/node/Group.hpp"
// #include "vgd/basic/TimeDuration.hpp"
// #include "vge/engine/MultiMatrixStack.hpp"
// #include "vge/engine/Engine.hpp"
// #include "vge/engine/SceneManager.hpp"
#include "vgd/event/Source.hpp"
#include "vgd/event/Device.hpp"
#include "vgd/event/DeviceManager.hpp"
#include "vgeGL/itf/IUnderlay.hpp"
#include "vgeGL/technique/RayCasting.hpp"
#include <vge/engine/MultiMatrixStack.hpp>
#include <vgd/basic/TimeDuration.hpp>
#include <vge/engine/Engine.hpp>
#include <vge/engine/SceneManager.hpp>
#include <vgeGL/engine/SceneManager.hpp>
#include <vgd/event/Source.hpp>
#include <vgUI/Canvas.hpp>

#include <vgUI/BasicViewer.hpp>
#include <vgUI/BasicManipulator.hpp>

#include <vgUI/python/Context.hpp>

%}

// %include "vgd/node/Node.hpp"
// %include "vgd/node/IGroup.hpp"
// %include "vgd/node/IBoundingBox.hpp"
// %include "vgd/field/IFieldObserver.hpp"

// %include "vgd/node/Group.hpp"
// %include "vgd/basic/TimeDuration.hpp"
// %include "vge/engine/MultiMatrixStack.hpp"
// %include "vge/engine/Engine.hpp"

%rename(vgeSceneManager) vge::engine::SceneManager;
%ignore  vgeGL::engine::SceneManager::getRayCastingTechnique;
// %include "vgd/event/DeviceManager.hpp"
// %include "vgeGL/itf/IUnderlay.hpp"
%include "vgeGL/technique/RayCasting.hpp"
%include <vge/engine/MultiMatrixStack.hpp>
%include <vgd/basic/TimeDuration.hpp>
%include <vge/engine/Engine.hpp>
%include <vge/engine/SceneManager.hpp>
%include <vgeGL/engine/SceneManager.hpp>
%include <vgd/event/Source.hpp>
%include <vgUI/Canvas.hpp>
%include <vgUI/BasicViewer.hpp>
%include <vgUI/BasicManipulator.hpp>

%include <vgUI/python/Context.hpp>

%template( getOptionalNodeAsAntialising ) 			vgUI::BasicViewer::getOptionalNodeAs< vgd::node::Antialiasing >;
%template( getOptionalNodeAsClearFrameBuffer ) 		vgUI::BasicViewer::getOptionalNodeAs< vgd::node::ClearFrameBuffer >;
%template( getOptionalNodeAsDrawStyle ) 			vgUI::BasicViewer::getOptionalNodeAs< vgd::node::DrawStyle >;
%template( getOptionalNodeAsEngineProperties ) 		vgUI::BasicViewer::getOptionalNodeAs< vgd::node::EngineProperties >;
%template( getOptionalNodeAsLightModel ) 			vgUI::BasicViewer::getOptionalNodeAs< vgd::node::LightModel >;
%template( getOptionalNodeAsLights ) 				vgUI::BasicViewer::getOptionalNodeAs< vgd::node::Group >;
%template( getOptionalNodeAsTessellation ) 			vgUI::BasicViewer::getOptionalNodeAs< vgd::node::Group >;
%template( getOptionalNodeAsUnderlayContainer ) 	vgUI::BasicViewer::getOptionalNodeAs< vgd::node::LayerPlan >;
%template( getOptionalNodeAsProgram ) 				vgUI::BasicViewer::getOptionalNodeAs< vgd::node::Program >;

%template( createOptionalNodeAsAntialising ) 		vgUI::BasicViewer::createOptionalNodeAs< vgd::node::Antialiasing >;
%template( createOptionalNodeAsClearFrameBuffer ) 	vgUI::BasicViewer::createOptionalNodeAs< vgd::node::ClearFrameBuffer >;
%template( createOptionalNodeAsDrawStyle ) 			vgUI::BasicViewer::createOptionalNodeAs< vgd::node::DrawStyle >;
%template( createOptionalNodeAsEngineProperties ) 	vgUI::BasicViewer::createOptionalNodeAs< vgd::node::EngineProperties >;
%template( createOptionalNodeAsLightModel ) 		vgUI::BasicViewer::createOptionalNodeAs< vgd::node::LightModel >;
%template( createOptionalNodeAsLights ) 			vgUI::BasicViewer::createOptionalNodeAs< vgd::node::Group >;
%template( createOptionalNodeAsTessellation ) 		vgUI::BasicViewer::createOptionalNodeAs< vgd::node::Group >;
%template( createOptionalNodeAsUnderlayContainer ) 	vgUI::BasicViewer::createOptionalNodeAs< vgd::node::LayerPlan >;
%template( createOptionalNodeAsProgram ) 			vgUI::BasicViewer::createOptionalNodeAs< vgd::node::Program >;