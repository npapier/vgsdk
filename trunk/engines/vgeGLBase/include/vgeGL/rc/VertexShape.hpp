//// VGSDK - Copyright (C) 2011, 2013, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_RC_VERTEXSHAPE_HPP
//#define _VGEGLBASE_RC_VERTEXSHAPE_HPP
//
//#include <glo/ArrayBuffer.hpp>
//#include <glo/ElementArrayBuffer.hpp>
//#include <glo/VertexArrayObject.hpp>
//#include <vector>
//#include <vgm/Vector.hpp>
//
//#include "vge/rc/IResource.hpp"
//#include "vgeGLBase/vgeGLBase.hpp"
//
//
//
//namespace vgeGLBase
//{
//
//namespace rc
//{
//
//
//
///**
// * @brief OpenGL objects associated to VertexShape submitting
// */
//struct VGEGLBASE_API VertexShape : public vge::rc::IResource, public glo::IResource
//{
//	glo::ArrayBuffer					vertex;
//	glo::ArrayBuffer					normal;
//	glo::ArrayBuffer					tangent;
//	glo::ArrayBuffer					color;
//	std::vector< glo::ArrayBuffer >		texCoord;
//	glo::ElementArrayBuffer				vertexIndex;
//
//	glo::VertexArrayObject				vao;
//
//	std::vector< vgm::Vec3f >			drawNormalsVectors;
//	glo::ArrayBuffer					drawNormalsBuffer;
//
//	std::vector< vgm::Vec3f >			drawTangentsVectors;
//	glo::ArrayBuffer					drawTangentsBuffer;
//
//	std::vector< vgm::Vec3f >			drawCentersOfTrianglesVectors;
//	glo::ArrayBuffer					drawCentersOfTrianglesBuffer;
//	std::vector< vgm::Vec3f >			drawRedArrowVectors;
//	glo::ArrayBuffer					drawRedArrowBuffer;
//	std::vector< vgm::Vec3f >			drawGreenArrowVectors;
//	glo::ArrayBuffer					drawGreenArrowBuffer;
//	std::vector< vgm::Vec3f >			drawBlueArrowVectors;
//	glo::ArrayBuffer					drawBlueArrowBuffer;
//};
//
//
//
//} // namespace rc
//
//} // namespace vgeGLBase
//
//#endif //#ifndef _VGEGLBASE_RC_VERTEXSHAPE_HPP
//