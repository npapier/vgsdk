%module (directors="1") vge
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

#define VGE_API
#define VGD_API

%include <std_vector.i>
%include <std_string.i>
%include <Shp.i>

%include vgd/vgd.i

%Shp( vge::engine::Engine )
%Shp( vgd::node::Group )
%Shp( vgd::node::Node )

%feature ("flatnested");


%{

#include "vge/engine/MultiMatrixStack.hpp"
#include "vgd/basic/TimeDuration.hpp"
#include "vge/engine/Engine.hpp"
#include "vge/engine/SceneManager.hpp"
#include "vge/engine/UserSettings.hpp"

%}


%include "vgd/basic/TimeDuration.hpp"
%include "vge/engine/MultiMatrixStack.hpp"
%include "vge/engine/Engine.hpp"
%include "vge/engine/SceneManager.hpp"
%include "vge/engine/UserSettings.hpp"