// VGSDK - Copyright (C) 2008, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#include "vgGTK/field/operations.hpp"

#include <string>
#include <vgd/field/TMultiField.hpp>
#include <vgd/field/TSingleField.hpp>
#include <vgm/Matrix.hpp>

#include "vgGTK/field/MultiFieldEditor.hpp"
#include "vgGTK/field/MultiFieldEditor2.hpp"
#include "vgGTK/field/SingleFieldEditor.hpp"
#include "vgGTK/field/adapter/MFNumberAdapter.hpp"
#include "vgGTK/field/adapter/MFPrimitiveAdapter.hpp"
#include "vgGTK/field/adapter/MFVectorAdapter.hpp"
#include "vgGTK/field/widget/Bool.hpp"
#include "vgGTK/field/widget/Number.hpp"
#include "vgGTK/field/widget/MatrixR.hpp"
#include "vgGTK/field/widget/String.hpp"
#include "vgGTK/field/widget/Vector.hpp"



namespace vgGTK
{

namespace field
{



vgd::Shp< Editor > createEditor( const vgd::Shp< vgd::field::FieldManager > fieldManager, const std::string & fieldName )
{
	const std::type_info	& fieldType	= fieldManager->getFieldType(fieldName);
	vgd::Shp< Editor >		editor		= createEditor( fieldType );
	
	if( editor )
	{
		editor->setField( fieldManager, fieldName );
	}
	
	return editor;
}



vgd::Shp< Editor > createEditor( const std::type_info & fieldType )
{
	vgd::Shp< Editor >	result;
	
	if		( fieldType == typeid(vgd::field::TSingleField< std::string >)	)	result.reset( new SingleFieldEditor< widget::String >()				);
	else if	( fieldType == typeid(vgd::field::TSingleField< bool >)			)	result.reset( new SingleFieldEditor< widget::Bool >()				);
	else if	( fieldType == typeid(vgd::field::TSingleField< int >)			)	result.reset( new SingleFieldEditor< widget::Number< int > >()		);
	else if	( fieldType == typeid(vgd::field::TSingleField< float >)		)	result.reset( new SingleFieldEditor< widget::Number< float > >()	);
	else if	( fieldType == typeid(vgd::field::TSingleField< vgm::MatrixR >)	)	result.reset( new SingleFieldEditor< widget::MatrixR >()			);
	
	else if	( fieldType == typeid(vgd::field::TMultiField< vgm::Vec3f >)	)			result.reset( new MultiFieldEditor2< adapter::MFVectorAdapter< vgm::Vec3f > >()		);
	else if	( fieldType == typeid(vgd::field::TMultiField< unsigned long >)	)			result.reset( new MultiFieldEditor2< adapter::MFNumberAdapter< unsigned long > >()	);
	else if	( fieldType == typeid(vgd::field::TMultiField< vgd::node::Primitive >)	)	result.reset( new MultiFieldEditor2< adapter::MFPrimitiveAdapter >()				);
	
	return result;
}



} // namespace field

} // namespace vgGTK
