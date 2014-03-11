// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier
// Author Bryan Schuller

#include <vgBase/Type.hpp>
#include <vgd/field/Enum.hpp>
#include <vgd/field/TMultiField.hpp>
#include <vgd/field/TOptionalField.hpp>
#include <vgd/field/TSingleField.hpp>
#include <vgm/Matrix.hpp>

#include "vgQt/field/operations.hpp"
#include "vgQt/field/FieldEditor.hpp"
#include "vgQt/field/SingleFieldEditor.hpp"
#include "vgQt/field/OptionalFieldEditor.hpp"
#include "vgQt/field/MultiFieldEditor.hpp"

#include "vgQt/field/adapter/MFNumberAdapter.hpp"
#include "vgQt/field/adapter/MFVectorAdapter.hpp"

#include "vgQt/field/widget/Bool.hpp"
#include "vgQt/field/widget/Enum.hpp"
#include "vgQt/field/widget/SpecializedNumber.hpp"
#include "vgQt/field/widget/String.hpp"
#include "vgQt/field/widget/SpecializedRectangle.hpp"
#include "vgQt/field/widget/SpecializedVector.hpp"
#include "vgQt/field/widget/MatrixR.hpp"

namespace vgQt
{

namespace field
{



FieldEditor* createEditor( const vgd::Shp< vgd::field::FieldManager > fieldManager, const QString fieldName )
{
	const std::string		fieldNameStr	= fieldName.toStdString();
	const std::type_info &	fieldType		= fieldManager->getFieldType(fieldNameStr);

    FieldEditor*		editor	= createEditor( fieldType );
	
	if( editor )
	{
		editor->setField( fieldManager, fieldName );
	}
	
	return editor;
}


FieldEditor* createEditor( const std::type_info & fieldType )
{
    FieldEditor* result = 0;

// TSingleField
    // Bool
	if ( fieldType == typeid(vgd::field::TSingleField< bool >) )
        result = new SingleFieldEditor< widget::Bool >();
    // Enum
	else if ( fieldType == typeid(vgd::field::TSingleField< vgd::field::Enum >) )
        result = new SingleFieldEditor< widget::Enum >();
    // Number
	else if ( fieldType == typeid(vgd::field::TSingleField< int8 >) )
        result = new SingleFieldEditor< widget::SpecializedNumber< int8 > >();
	else if ( fieldType == typeid(vgd::field::TSingleField< uint8 >) )
        result = new SingleFieldEditor< widget::SpecializedNumber< uint8 > >();
	else if ( fieldType == typeid(vgd::field::TSingleField< int16 >) )
        result = new SingleFieldEditor< widget::SpecializedNumber< int16 > >();
	else if ( fieldType == typeid(vgd::field::TSingleField< uint16 >) )
        result = new SingleFieldEditor< widget::SpecializedNumber< uint16 > >();
	else if ( fieldType == typeid(vgd::field::TSingleField< int32 >) )
        result = new SingleFieldEditor< widget::SpecializedNumber< int32 > >();
	else if ( fieldType == typeid(vgd::field::TSingleField< uint32 >) )
        result = new SingleFieldEditor< widget::SpecializedNumber< uint32 > >();
	else if ( fieldType == typeid(vgd::field::TSingleField< int >) )
        result = new SingleFieldEditor< widget::SpecializedNumber< int > >();
	else if ( fieldType == typeid(vgd::field::TSingleField< uint >) )
        result = new SingleFieldEditor< widget::SpecializedNumber< uint > >();
	else if ( fieldType == typeid(vgd::field::TSingleField< float >) )
        result = new SingleFieldEditor< widget::SpecializedNumber< float > >();
	else if ( fieldType == typeid(vgd::field::TSingleField< double >) )
        result = new SingleFieldEditor< widget::SpecializedNumber< double > >();
    // String
	else if ( fieldType == typeid(vgd::field::TSingleField< std::string >) )
        result = new SingleFieldEditor< widget::String >();
    // Rectangle
	else if ( fieldType == typeid(vgd::field::TSingleField< vgm::Rectangle2i >) )
        result = new SingleFieldEditor< widget::SpecializedRectangle< int32 > >();
	else if ( fieldType == typeid(vgd::field::TSingleField< vgm::Rectangle2f >) )
        result = new SingleFieldEditor< widget::SpecializedRectangle< float > >();
	else if ( fieldType == typeid(vgd::field::TSingleField< vgm::Rectangle2d >) )
        result = new SingleFieldEditor< widget::SpecializedRectangle< double > >();
    // Vector
	else if ( fieldType == typeid(vgd::field::TSingleField< vgm::Vec2i >) )
        result = new SingleFieldEditor< widget::SpecializedVector<int32, 2> >();
	else if ( fieldType == typeid(vgd::field::TSingleField< vgm::Vec3i >) )
        result = new SingleFieldEditor< widget::SpecializedVector<int32, 3> >();
	else if ( fieldType == typeid(vgd::field::TSingleField< vgm::Vec4i >) )
        result = new SingleFieldEditor< widget::SpecializedVector<int32, 4> >();
	else if ( fieldType == typeid(vgd::field::TSingleField< vgm::Vec5i >) )
        result = new SingleFieldEditor< widget::SpecializedVector<int32, 5> >();
	else if ( fieldType == typeid(vgd::field::TSingleField< vgm::Vec2f >) )
        result = new SingleFieldEditor< widget::SpecializedVector<float, 2> >();
	else if ( fieldType == typeid(vgd::field::TSingleField< vgm::Vec3f >) )
        result = new SingleFieldEditor< widget::SpecializedVector<float, 3> >();
	else if ( fieldType == typeid(vgd::field::TSingleField< vgm::Vec4f >) )
        result = new SingleFieldEditor< widget::SpecializedVector<float, 4> >();
	else if ( fieldType == typeid(vgd::field::TSingleField< vgm::Vec5f >) )
        result = new SingleFieldEditor< widget::SpecializedVector<float, 5> >();
	else if ( fieldType == typeid(vgd::field::TSingleField< vgm::Vec2d >) )
        result = new SingleFieldEditor< widget::SpecializedVector<double, 2> >();
	else if ( fieldType == typeid(vgd::field::TSingleField< vgm::Vec3d >) )
        result = new SingleFieldEditor< widget::SpecializedVector<double, 3> >();
	else if ( fieldType == typeid(vgd::field::TSingleField< vgm::Vec4d >) )
        result = new SingleFieldEditor< widget::SpecializedVector<double, 4> >();
	else if ( fieldType == typeid(vgd::field::TSingleField< vgm::Vec5d >) )
        result = new SingleFieldEditor< widget::SpecializedVector<double, 5> >();
    // MatrixR
	else if ( fieldType == typeid(vgd::field::TSingleField< vgm::MatrixR >) )
        result = new SingleFieldEditor< widget::MatrixR >();
// TOptionalField
    // Bool
    else if	( fieldType == typeid(vgd::field::TOptionalField< bool >) )
        result = new OptionalFieldEditor< widget::Bool >();
    // Enum
    else if	( fieldType == typeid(vgd::field::TOptionalField< vgd::field::Enum > ) )
        result = new OptionalFieldEditor< widget::Enum >();
    // Number
    else if	( fieldType == typeid(vgd::field::TOptionalField< float >) )
        result = new OptionalFieldEditor< widget::SpecializedNumber< float > >();
    // String
	else if	( fieldType == typeid(vgd::field::TOptionalField< std::string >) )
        result = new OptionalFieldEditor< widget::String >();
    // Rectangle
	else if	( fieldType == typeid(vgd::field::TOptionalField< vgm::Rectangle< int32 > >) )
        result = new OptionalFieldEditor< widget::SpecializedRectangle< int32 > >();
    // Vector
	else if	( fieldType == typeid(vgd::field::TOptionalField< vgm::Vec2f >) )
        result = new OptionalFieldEditor< widget::SpecializedVector<float, 2> >();
	else if	( fieldType == typeid(vgd::field::TOptionalField< vgm::Vec3f >) )
        result = new OptionalFieldEditor< widget::SpecializedVector<float, 3> >();
	else if	( fieldType == typeid(vgd::field::TOptionalField< vgm::Vec4f >) )
        result = new OptionalFieldEditor< widget::SpecializedVector<float, 4> >();
	else if	( fieldType == typeid(vgd::field::TOptionalField< vgm::Vec2i >) )
        result = new OptionalFieldEditor< widget::SpecializedVector<int32, 2> >();
	else if	( fieldType == typeid(vgd::field::TOptionalField< vgm::Vec3i >) )
        result = new OptionalFieldEditor< widget::SpecializedVector<int32, 3> >();
	else if	( fieldType == typeid(vgd::field::TOptionalField< vgm::Vec4i >) )
        result = new OptionalFieldEditor< widget::SpecializedVector<int32, 4> >();
// TMultiField
    // Vector
	else if	( fieldType == typeid(vgd::field::TMultiField< vgm::Vec2f >) )
        result = new MultiFieldEditor< adapter::MFVectorAdapter< vgm::Vec2f > >();
	else if	( fieldType == typeid(vgd::field::TMultiField< vgm::Vec3f >) )
        result = new MultiFieldEditor< adapter::MFVectorAdapter< vgm::Vec3f > >();
	else if	( fieldType == typeid(vgd::field::TMultiField< vgm::Vec4f >) )
        result = new MultiFieldEditor< adapter::MFVectorAdapter< vgm::Vec4f > >();
	else if	( fieldType == typeid(vgd::field::TMultiField< vgm::Vec5f >) )
        result = new MultiFieldEditor< adapter::MFVectorAdapter< vgm::Vec5f > >();
    // Number
    else if	( fieldType == typeid(vgd::field::TMultiField< uint >)	)
        result = new MultiFieldEditor< adapter::MFNumberAdapter< uint32 > >();
    else if	( fieldType == typeid(vgd::field::TMultiField< int >)	)
       result = new MultiFieldEditor< adapter::MFNumberAdapter< int > >();
    /*
    else if	( fieldType == typeid(vgd::field::TMultiField< vgd::node::Primitive >)	)
        result = new MultiFieldEditor2< adapter::MFPrimitiveAdapter >();
    */
    return result;
}



} // namespace field

} // namespace vgQt
