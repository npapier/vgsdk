// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_FIELD_VECTOR_H
#define _VGD_FIELD_VECTOR_H

#include "vgd/vgd.hpp"

#include <vgm/Vector.hpp>

#include "vgd/field/TSingleField.hpp"
#include "vgd/field/TMultiField.hpp"
#include "vgd/field/TSingleAssociativeField.hpp"
#include "vgd/field/TPairAssociativeField.hpp"



namespace vgd
{
	
namespace field
{



/**
 * @name Typedefs for fields containing elements of vgm::Vec<T,N> type.
 */
//@{
typedef TSingleField< vgm::Vec2f >	SFVec2f;
typedef TSingleField< vgm::Vec3f >	SFVec3f;
typedef TSingleField< vgm::Vec4f >	SFVec4f;
typedef TSingleField< vgm::Vec2d >	SFVec2d;
typedef TSingleField< vgm::Vec3d >	SFVec3d;
typedef TSingleField< vgm::Vec4d >	SFVec4d;
typedef TSingleField< vgm::Vec2i >	SFVec2i;
typedef TSingleField< vgm::Vec3i >	SFVec3i;
typedef TSingleField< vgm::Vec4i >	SFVec4i;

typedef TMultiField< vgm::Vec2f >		MFVec2f;
typedef TMultiField< vgm::Vec3f >		MFVec3f;
typedef TMultiField< vgm::Vec4f >		MFVec4f;
typedef TMultiField< vgm::Vec2d >		MFVec2d;
typedef TMultiField< vgm::Vec3d >		MFVec3d;
typedef TMultiField< vgm::Vec4d >		MFVec4d;
typedef TMultiField< vgm::Vec2i >		MFVec2i;
typedef TMultiField< vgm::Vec3i >		MFVec3i;
typedef TMultiField< vgm::Vec4i >		MFVec4i;

typedef TSingleAssociativeField< vgm::Vec2f >	SAFVec2f;
typedef TSingleAssociativeField< vgm::Vec3f >	SAFVec3f;
typedef TSingleAssociativeField< vgm::Vec4f >	SAFVec4f;
typedef TSingleAssociativeField< vgm::Vec2d >	SAFVec2d;
typedef TSingleAssociativeField< vgm::Vec3d >	SAFVec3d;
typedef TSingleAssociativeField< vgm::Vec4d >	SAFVec4d;
typedef TSingleAssociativeField< vgm::Vec2i >	SAFVec2i;
typedef TSingleAssociativeField< vgm::Vec3i >	SAFVec3i;
typedef TSingleAssociativeField< vgm::Vec4i >	SAFVec4i;

// typedef TPairAssociativeField< vgm::Vec2f >	PAFVec2f;
// typedef TPairAssociativeField< vgm::Vec3f >	PAFVec3f;
// typedef TPairAssociativeField< vgm::Vec4f >	PAFVec4f;
// typedef TPairAssociativeField< vgm::Vec2d >	PAFVec2d;
// typedef TPairAssociativeField< vgm::Vec3d >	PAFVec3d;
// typedef TPairAssociativeField< vgm::Vec4d >	PAFVec4d;
// typedef TPairAssociativeField< vgm::Vec2i >	PAFVec2i;
// typedef TPairAssociativeField< vgm::Vec3i >	PAFVec3i;
// typedef TPairAssociativeField< vgm::Vec4i >	PAFVec4i;
//@}



} // namespace field

} // namespace vgd

#endif //#ifndef _VGD_FIELD_VECTOR_H
