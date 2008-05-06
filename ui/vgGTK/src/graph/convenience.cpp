// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#include "vgGTK/graph/convenience.hpp"

#include <sstream>

#include <vgd/field/Bool.hpp>
#include <vgd/field/Integer.hpp>
#include <vgd/field/Float.hpp>
#include <vgd/field/Matrix.hpp>
#include <vgd/field/String.hpp>
#include <vgd/field/Vector.hpp>

#include <vgio/operators.hpp>




namespace vgGTK
{

namespace graph
{



const std::string getFieldAsString( const vgd::Shp< vgd::field::FieldManager > fieldManager, const std::string & fieldName )
{
	std::ostringstream	os;

	// Ensures that the field exists.
	if( fieldManager->isField(fieldName) == false )
	{
		os << "Missing field!";
	}
	else
	{
		// Retrieves the field type information
		const std::type_info	& fieldType = fieldManager->getFieldType( fieldName );


		// For the found field type, now we will get a RO editor and perform the serialization to a string.
		using namespace vgd::field;

		typedef vgd::node::Material::FColorType		PAFMaterialColor;
		typedef vgd::node::Material::FShininessType	PAFMaterialShininess;

		if		( fieldType == typeid(SFBool)	)	os << fieldManager->getFieldRO< SFBool    >( fieldName );
		else if	( fieldType == typeid(SFInt8)	)	os << fieldManager->getFieldRO< SFInt8    >( fieldName );
		else if	( fieldType == typeid(SFUInt8)	)	os << fieldManager->getFieldRO< SFUInt8   >( fieldName );
		else if	( fieldType == typeid(SFInt16)	)	os << fieldManager->getFieldRO< SFInt16   >( fieldName );
		else if	( fieldType == typeid(SFUInt16)	)	os << fieldManager->getFieldRO< SFUInt16  >( fieldName );
		else if	( fieldType == typeid(SFInt32)	)	os << fieldManager->getFieldRO< SFInt32   >( fieldName );
		else if	( fieldType == typeid(SFUInt32)	)	os << fieldManager->getFieldRO< SFUInt32  >( fieldName );
		else if	( fieldType == typeid(SFFloat)	)	os << fieldManager->getFieldRO< SFFloat   >( fieldName );
		else if	( fieldType == typeid(SFDouble)	)	os << fieldManager->getFieldRO< SFDouble  >( fieldName );
		else if	( fieldType == typeid(SFString)	)	os << fieldManager->getFieldRO< SFString  >( fieldName );
		else if ( fieldType == typeid(SFVec3f)	)	os << fieldManager->getFieldRO< SFVec3f   >( fieldName );
		else if ( fieldType == typeid(SFVec4f)	)	os << fieldManager->getFieldRO< SFVec4f   >( fieldName );
		else if	( fieldType == typeid(SFMatrixR))	os << fieldManager->getFieldRO< SFMatrixR >( fieldName );
		else if	( fieldType == typeid(MFBool)	)	os << fieldManager->getFieldRO< MFBool    >( fieldName );
		else if	( fieldType == typeid(MFInt8)	)	os << fieldManager->getFieldRO< MFInt8    >( fieldName );
		else if	( fieldType == typeid(MFUInt8)	)	os << fieldManager->getFieldRO< MFUInt8   >( fieldName );
		else if	( fieldType == typeid(MFInt16)	)	os << fieldManager->getFieldRO< MFInt16   >( fieldName );
		else if	( fieldType == typeid(MFUInt16)	)	os << fieldManager->getFieldRO< MFUInt16  >( fieldName );
		else if	( fieldType == typeid(MFInt32)	)	os << fieldManager->getFieldRO< MFInt32   >( fieldName );
		else if	( fieldType == typeid(MFUInt32)	)	os << fieldManager->getFieldRO< MFUInt32  >( fieldName );
		else if	( fieldType == typeid(MFFloat)	)	os << fieldManager->getFieldRO< MFFloat   >( fieldName );
		else if	( fieldType == typeid(MFDouble)	)	os << fieldManager->getFieldRO< MFDouble  >( fieldName );
		else if	( fieldType == typeid(MFString)	)	os << fieldManager->getFieldRO< MFString  >( fieldName );
		else if ( fieldType == typeid(MFVec3f)	)	os << fieldManager->getFieldRO< MFVec3f   >( fieldName );
		else if ( fieldType == typeid(MFVec4f)	)	os << fieldManager->getFieldRO< MFVec4f   >( fieldName );
		else if	( fieldType == typeid(MFMatrixR))	os << fieldManager->getFieldRO< MFMatrixR >( fieldName );
		else if	( fieldType == typeid(PAFMaterialColor))		os << fieldManager->getFieldRO< PAFMaterialColor     >( fieldName );
		else if	( fieldType == typeid(PAFMaterialShininess))	os << fieldManager->getFieldRO< PAFMaterialShininess >( fieldName );
		else										os << "Unknown field type!";
	}

	return os.str();
}



} // namespace graph

} // namespace vgGTK
