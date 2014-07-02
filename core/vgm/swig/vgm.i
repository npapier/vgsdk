%module (directors="1") vgm
%feature("director"); 

%feature("director:except") {
    if ($error != NULL) {
        throw Swig::DirectorMethodException();
    }
}

%exception {
    try { $action }
    catch (Swig::DirectorException &e) 
	{ PyErr_SetString(PyExc_RuntimeError, e.getMessage()); }
}

#define VGM_API
#define vgDEPRECATED(x) x
#ifdef _DEBUG
		assert( N == 3 );
#endif

//%rename (MatR)						vgm::MatrixR;
%rename (operatorX)					vgm::MatrixR::operator*( const vgm::MatrixR& m1, const vgm::MatrixR& m2 );
%rename (operatorEqRawMat)			vgm::MatrixR::operator=( const RawMatrix m );
%rename (operatorEqMat)				vgm::MatrixR::operator=( const MatrixR& m );
%rename (operatorEqRot)				vgm::MatrixR::operator=( const Rotation& q );
%rename	(operatorBracketMat)		vgm::MatrixR::operator[]( int32 i );
%rename	(operatorBracketMatConst)	vgm::MatrixR::operator[]( const int32 i ) const;
%rename (operatorEqVect)			vgm::Vector::operator=( const Vector& v );
%rename (operatorBacketVect) 		vgm::Vector::operator[]( int32 i );
%rename	(operatorBacketVectConst)   vgm::Vector::operator[]( int32 i ) const;
%rename (operatorBacketRotConst)	vgm::Rotation::operator[]( const uint );
%rename (operatorBacketRotConst)	vgm::Rotation::operator[]( const uint ) const;

%feature ("flatnested");

%{


#include "vgm/Rotation.hpp"
#include "vgm/vgm.hpp"
#include "vgm/operations.hpp"
#include "vgm/Vector.hpp"
#include "vgm/Matrix.hpp"					//Inclure Matrix.hpp sino erreur � la compilation 

%}

%ignore vgm::Vector::cross( const Vector& rV ) const;

// %ignore dot( const vgm::Vector& v ) const;
// %ignore getClosestAxis();
%include "vgm/operations.hpp"
%include "vgm/Vector.hpp"
%include "vgm/Rotation.hpp"
%include "vgm/Matrix.hpp"

// %template (Vec2f)	vgm::Vector< float, 2 >;
%template (Vec3f)	vgm::Vector< float, 3 >;
//%template (Vec4f)	vgm::Vector< float, 4 >;
// %template (Vec5f)	vgm::Vector< float, 5 >;


%extend vgm::Vector< float, 3 > 
{
    float __getitem__(unsigned int i) 
	{
        return (*($self))[i];
    }
}
