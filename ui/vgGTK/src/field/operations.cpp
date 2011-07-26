// VGSDK - Copyright (C) 2008, 2009, 2010, 2011, Guillaume Brocker and Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#include "vgGTK/field/operations.hpp"

#include <string>
#include <vgBase/Type.hpp>
#include <vgd/field/Enum.hpp>
#include <vgd/field/TMultiField.hpp>
#include <vgd/field/TOptionalField.hpp>
#include <vgd/field/TSingleField.hpp>
#include <vgm/Matrix.hpp>

#include "vgGTK/field/MultiFieldEditor.hpp"
#include "vgGTK/field/MultiFieldEditor2.hpp"
#include "vgGTK/field/OptionalFieldEditor.hpp"
#include "vgGTK/field/SingleFieldEditor.hpp"
#include "vgGTK/field/adapter/MFNumberAdapter.hpp"
#include "vgGTK/field/adapter/MFPrimitiveAdapter.hpp"
#include "vgGTK/field/adapter/MFVectorAdapter.hpp"
#include "vgGTK/field/widget/Bool.hpp"
#include "vgGTK/field/widget/Enum.hpp"
#include "vgGTK/field/widget/Number.hpp"
#include "vgGTK/field/widget/MatrixR.hpp"
#include "vgGTK/field/widget/Rectangle.hpp"
#include "vgGTK/field/widget/String.hpp"
#include "vgGTK/field/widget/Vector.hpp"



namespace vgGTK
{

namespace field
{



vgd::Shp< FieldEditor > createEditor( const vgd::Shp< vgd::field::FieldManager > fieldManager, const std::string & fieldName )
{
	const std::type_info	& fieldType	= fieldManager->getFieldType(fieldName);
	vgd::Shp< FieldEditor >		editor	= createEditor( fieldType );
	
	if( editor )
	{
		editor->setField( fieldManager, fieldName );
	}
	
	return editor;
}



vgd::Shp< FieldEditor > createEditor( const std::type_info & fieldType )
{
	vgd::Shp< FieldEditor > result;

	// TSingleField
	if ( fieldType == typeid(vgd::field::TSingleField< bool >) )
		result.reset( new SingleFieldEditor< widget::Bool >() );

	else if ( fieldType == typeid(vgd::field::TSingleField< vgd::field::Enum >) )
		result.reset( new SingleFieldEditor< widget::Enum >() );

// Obsolated by the user of Gtk::SpinButton in widget::Number
//
//	else if ( fieldType == typeid(vgd::field::TSingleField< int8 >) )
//		result.reset( new SingleFieldEditor< widget::Int8Number >() );
//	else if ( fieldType == typeid(vgd::field::TSingleField< uint8 >) )
//		result.reset( new SingleFieldEditor< widget::UInt8Number >() );

	else if ( fieldType == typeid(vgd::field::TSingleField< int8 >) )
		result.reset( new SingleFieldEditor< widget::Number< int8 > >() );
	else if ( fieldType == typeid(vgd::field::TSingleField< uint8 >) )
		result.reset( new SingleFieldEditor< widget::Number< uint8 > >() );
	else if ( fieldType == typeid(vgd::field::TSingleField< int16 >) )
		result.reset( new SingleFieldEditor< widget::Number< int16 > >() );
	else if ( fieldType == typeid(vgd::field::TSingleField< uint16 >) )
		result.reset( new SingleFieldEditor< widget::Number< uint16 > >() );
	else if ( fieldType == typeid(vgd::field::TSingleField< int32 >) )
		result.reset( new SingleFieldEditor< widget::Number< int32 > >() );
	else if ( fieldType == typeid(vgd::field::TSingleField< uint32 >) )
		result.reset( new SingleFieldEditor< widget::Number< uint32 > >() );
	else if ( fieldType == typeid(vgd::field::TSingleField< int >) )
		result.reset( new SingleFieldEditor< widget::Number< int > >() );
	else if ( fieldType == typeid(vgd::field::TSingleField< uint >) )
		result.reset( new SingleFieldEditor< widget::Number< uint > >() );

	else if ( fieldType == typeid(vgd::field::TSingleField< float >) )
		result.reset( new SingleFieldEditor< widget::Number< float > >() );
	else if ( fieldType == typeid(vgd::field::TSingleField< double >) )
		result.reset( new SingleFieldEditor< widget::Number< double > >() );

	else if ( fieldType == typeid(vgd::field::TSingleField< std::string >) )
		result.reset( new SingleFieldEditor< widget::String >() );

	// @todo Box3f and XfBox3f

	else if ( fieldType == typeid(vgd::field::TSingleField< vgm::Rectangle2i >) )
		result.reset( new SingleFieldEditor< widget::Rectangle< int32 > >() );
	else if ( fieldType == typeid(vgd::field::TSingleField< vgm::Rectangle2f >) )
		result.reset( new SingleFieldEditor< widget::Rectangle< float > >() );
	else if ( fieldType == typeid(vgd::field::TSingleField< vgm::Rectangle2d >) )
		result.reset( new SingleFieldEditor< widget::Rectangle< double > >() );

	else if ( fieldType == typeid(vgd::field::TSingleField< vgm::Vec2i >) )
		result.reset( new SingleFieldEditor< widget::Vector<int32, 2> >() );
	else if ( fieldType == typeid(vgd::field::TSingleField< vgm::Vec3i >) )
		result.reset( new SingleFieldEditor< widget::Vector<int32, 3> >() );
	else if ( fieldType == typeid(vgd::field::TSingleField< vgm::Vec4i >) )
		result.reset( new SingleFieldEditor< widget::Vector<int32, 4> >() );
	else if ( fieldType == typeid(vgd::field::TSingleField< vgm::Vec2f >) )
		result.reset( new SingleFieldEditor< widget::Vector<float, 2> >() );
	else if ( fieldType == typeid(vgd::field::TSingleField< vgm::Vec3f >) )
		result.reset( new SingleFieldEditor< widget::Vector<float, 3> >() );
	else if ( fieldType == typeid(vgd::field::TSingleField< vgm::Vec4f >) )
		result.reset( new SingleFieldEditor< widget::Vector<float, 4> >() );
	else if ( fieldType == typeid(vgd::field::TSingleField< vgm::Vec2d >) )
		result.reset( new SingleFieldEditor< widget::Vector<double, 2> >() );
	else if ( fieldType == typeid(vgd::field::TSingleField< vgm::Vec3d >) )
		result.reset( new SingleFieldEditor< widget::Vector<double, 3> >() );
	else if ( fieldType == typeid(vgd::field::TSingleField< vgm::Vec4d >) )
		result.reset( new SingleFieldEditor< widget::Vector<double, 4> >() );

	// @todo Plane, Rotation
	else if ( fieldType == typeid(vgd::field::TSingleField< vgm::MatrixR >) )
		result.reset( new SingleFieldEditor< widget::MatrixR >() );

	// @todo vgd types : vgd::Shp< vgd::basic::IImage >, vgd::Shp< vgd::node::Group >,  vgd::Shp< vgd::node::Node >



	// TOptionalField
// @todo
	else if	( fieldType == typeid(vgd::field::TOptionalField< std::string >) )
		result.reset( new OptionalFieldEditor< widget::String >() );
	else if	( fieldType == typeid(vgd::field::TOptionalField< bool >) )
		result.reset( new OptionalFieldEditor< widget::Bool >() );
	else if	( fieldType == typeid(vgd::field::TOptionalField< float >) )
		result.reset( new OptionalFieldEditor< widget::Number< float > >() );
	else if	( fieldType == typeid(vgd::field::TOptionalField< vgd::field::Enum > ) )
		result.reset( new OptionalFieldEditor< widget::Enum >() );
	// @todo MatrixR
	else if	( fieldType == typeid(vgd::field::TOptionalField< vgm::Rectangle< int32 > >) )
		result.reset( new OptionalFieldEditor< widget::Rectangle< int32 > >() );
	else if	( fieldType == typeid(vgd::field::TOptionalField< vgm::Vec2f >) )
		result.reset( new OptionalFieldEditor< widget::Vector<float, 2> >() );
	else if	( fieldType == typeid(vgd::field::TOptionalField< vgm::Vec3f >) )
		result.reset( new OptionalFieldEditor< widget::Vector<float, 3> >() );
	else if	( fieldType == typeid(vgd::field::TOptionalField< vgm::Vec4f >) )
		result.reset( new OptionalFieldEditor< widget::Vector<float, 4> >() );
	else if	( fieldType == typeid(vgd::field::TOptionalField< vgm::Vec2i >) )
		result.reset( new OptionalFieldEditor< widget::Vector<int32, 2> >() );
	else if	( fieldType == typeid(vgd::field::TOptionalField< vgm::Vec3i >) )
		result.reset( new OptionalFieldEditor< widget::Vector<int32, 3> >() );
	else if	( fieldType == typeid(vgd::field::TOptionalField< vgm::Vec4i >) )
		result.reset( new OptionalFieldEditor< widget::Vector<int32, 4> >());



	// TMultiField
	else if	( fieldType == typeid(vgd::field::TMultiField< vgm::Vec3f >) )
		result.reset( new MultiFieldEditor2< adapter::MFVectorAdapter< vgm::Vec3f > >() );
	else if	( fieldType == typeid(vgd::field::TMultiField< vgm::Vec4f >) )
		result.reset( new MultiFieldEditor2< adapter::MFVectorAdapter< vgm::Vec4f > >()		);
	else if	( fieldType == typeid(vgd::field::TMultiField< vgm::Vec5f >) )
		result.reset( new MultiFieldEditor2< adapter::MFVectorAdapter< vgm::Vec5f > >()		);
	else if	( fieldType == typeid(vgd::field::TMultiField< uint >)	)				result.reset( new MultiFieldEditor2< adapter::MFNumberAdapter< uint32 > >()	);
	else if	( fieldType == typeid(vgd::field::TMultiField< int >)	)				result.reset( new MultiFieldEditor2< adapter::MFNumberAdapter< int > >()	);
	else if	( fieldType == typeid(vgd::field::TMultiField< vgd::node::Primitive >)	)	result.reset( new MultiFieldEditor2< adapter::MFPrimitiveAdapter >()				);
	
	return result;
}




} // namespace field

} // namespace vgGTK
