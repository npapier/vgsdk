//// VGSDK - Copyright (C) 2013, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef __USE_VGALG__
//	#pragma message("vgeGL::engine::DecalManager is disabled")
//#else
//
//#include "vgeGL/engine/DecalManager.hpp"
//
//#include <vgAlg/intersect/helpers.hpp>
//#include <vgAlg/vertexShape/operations.hpp>
//#include <vgAlg/vertexShape/texGen.hpp>
//#include <vgd/basic/IImage.hpp>
//#include <vgd/node/Decal.hpp>
//#include <vgd/node/Texture2D.hpp>
//#include <vgd/node/VertexShape.hpp>
//#include <vgd/node/WireBox.hpp>
//#include <vgm/Plane.hpp>
//#include "vgeGL/engine/SceneManager.hpp"
//
//
//
//namespace vgeGL
//{
//
//namespace engine
//{
//
//
//
//const bool DecalManager::spawnDecalPrecomputation(	vgeGL::engine::SceneManager * sceneManager, const vgm::Vec2i mouseLocation,
//													vgm::Vec3f& outRaySourceW, vgm::Vec3f& outRayDirectionW )
//{
//	// Cast ray under the mouse
//	vgm::TriangleExt ABC;
//	vgd::node::VertexShape * hitShape = sceneManager->castRay( mouseLocation[0], mouseLocation[1], ABC /*output*/ );
//
//	if ( hitShape )
//	{
//		// Hit point in world space
//		const vgeGL::basic::Hit	hit			= sceneManager->getNearestHit();
//		const vgm::Vec3f		hitPointW	= hit.nearestVertexS();
//
//		// Compute normal in world space
//		vgm::Vec3f ABCNormalE;
//		hit.modelviewO().multMatrixVec( ABC.getNormal(), ABCNormalE );				// object => eye space
//		vgm::Vec3f ABCNormalW;
//		hit.modelviewS().getInverse().multMatrixVec( ABCNormalE, ABCNormalW );		// eye => world space
//		ABCNormalW.normalize();
//
//		// Cast ray using hitPointW and ABCNormalW (to find a good source of ray casting for the decal).
//		const vgeGL::basic::Hit * hit2 = sceneManager->castRayForHit( hitPointW, ABCNormalW );
//		const float averageLength = (ABC.AB().getLength() + ABC.BC().getLength() + ABC.CA().getLength())/3.f;
//
//		// outputs
//		outRaySourceW = (hit2 != 0) ? (hitPointW + hit2->nearestVertexS())/2.f : hitPointW + ABCNormalW * averageLength;
//		outRayDirectionW = - ABCNormalW;
//
//		return true;
//	}
//	else
//	{
//		outRaySourceW.setInvalid();
//		outRayDirectionW.setInvalid();
//		return false;
//	}
//}
//
//
//vgd::Shp< vgd::node::VertexShape > DecalManager::spawnDecalShape( vgeGL::engine::SceneManager * sceneManager, const vgm::Vec3f& raySourceW, const vgm::Vec3f& rayDirectionW,
//	DecalInformations& oDecalInfos, DecalProperties& oDecalModifiers, vgm::XfBox3f& oDecalBox )
//{
//	vgd::Shp< vgd::node::VertexShape > retVal;
//
//	// Cast ray from raySourceW along rayDirectionW
//	oDecalInfos.hitShape = sceneManager->castRay( raySourceW, rayDirectionW, oDecalInfos.hitABC );
//
//	if ( oDecalInfos.hitShape )
//	{
//		// There is an hit
//		oDecalInfos.hit = sceneManager->getNearestHit();
//		retVal = spawnDecalShape( oDecalInfos, oDecalModifiers, oDecalBox );
//	}
//	else
//	{
//		oDecalBox.setInvalid();
//	}
//
//	return retVal;
//}
//
//
//
//vgd::Shp< vgd::node::Decal > DecalManager::createDecal( vgd::Shp< vgd::basic::IImage > image, vgd::Shp< vgd::node::VertexShape > decalShape )
//{
//	//	Texture
//	using vgd::node::Texture2D;
//	vgd::Shp< Texture2D > decalTexture = Texture2D::create("DECAL.texture");
//	decalTexture->setImage( image );
//	decalTexture->sethDefaults();
//
//	//	Decal
//	using vgd::node::Decal;
//	vgd::Shp< Decal > decal = Decal::create("DECAL", -1);
//	decal->setTexture( decalTexture );
//	decal->setShape( decalShape );
//
//	return decal;
//}
//
//
//void DecalManager::synchronize( const vgm::XfBox3f& box, vgd::Shp< vgd::node::WireBox > wireBoxShape, const bool addFrontFaceCross )
//{
//	if ( box.isValid() )
//	{
//		vgm::Vec3f min, max;
//		box.getBounds( min, max );
//		wireBoxShape->initializeGeometry( vgm::Box3f(min,max) );
//
//		wireBoxShape->transform( box.getTransform() );
//
//		// Add a cross in front face
//		if ( addFrontFaceCross )
//		{
//			vgd::field::EditorRW< vgd::field::MFUInt>		vertexIndex	= wireBoxShape->getVertexIndexRW();
//			vgd::field::EditorRW< vgd::field::MFPrimitive >	primitive	= wireBoxShape->getPrimitiveRW();
//
//			vertexIndex->push_back( 4 );
//			vertexIndex->push_back( 7 );
//			vertexIndex->push_back( 5 );
//
//			(*primitive)[0].addToNumIndices( 3 );
//		}
//	}
//	else
//	{
//		vgd::field::EditorRW< vgd::field::MFPrimitive > primitives = wireBoxShape->getPrimitiveRW();
//		primitives->clear();
//	}
//}
//
//
//vgd::Shp< vgd::node::VertexShape > DecalManager::spawnDecalShape(	const DecalInformations& decalInfos,
//																	DecalProperties& oDecalModifiers, vgm::XfBox3f& oDecalBox )
//{
//	using vgd::node::VertexShape;
//	vgd::Shp< VertexShape > retVal;
//
//	const bool hasTangents = (decalInfos.hitShape->getTangentBinding() == vgd::node::BIND_PER_VERTEX);
//	if ( !hasTangents ) vgLogDebug( "Decal not applied to shape '%s', because its tangents field is empty.", decalInfos.hitShape->getName().c_str() );
//
//	if ( decalInfos.hitShape && hasTangents )
//	{
//		// P(oint) and N(ormal)
//		const vgm::Vec3f P = decalInfos.hit.nearestVertexO();
//		const vgm::Vec3f N = decalInfos.hitABC.getNormal();
//		//vgLogDebug("N=(%f %f %f)", N[0], N[1], N[2] );
//
//		// T(angent) and B(inormal)
//		vgd::field::EditorRO< vgd::field::MFVec3f > tangents = decalInfos.hitShape->getTangentRO();
//		const vgm::Vec3i indices = decalInfos.hitABC.indices();
//		const vgm::Vec3f tA = (*tangents)[indices[0]];
//		const vgm::Vec3f tB = (*tangents)[indices[1]];
//		const vgm::Vec3f tC = (*tangents)[indices[2]];
//		vgm::Vec3f T =	(1.f-decalInfos.hitABC.P()[0]) * tA + (decalInfos.hitABC.P()[0] * tB) +
//						(1.f-decalInfos.hitABC.P()[1]) * tA + (decalInfos.hitABC.P()[1] * tC);
//		T.normalize();
//		tangents.release();
//		//vgLogDebug("T=(%f %f %f)", T[0], T[1], T[2] );
//
//		const vgm::Vec3f B = N.cross(T);
//
//		if ( vgm::equals(oDecalModifiers.width, 0.f) )
//		{
//			// Instantiate decal with uninitialized modifiers, so predefined values are used
//			oDecalModifiers.width		= (decalInfos.hitABC.AB().getLength() + decalInfos.hitABC.BC().getLength() + decalInfos.hitABC.CA().getLength())/3.f * 5.f;
//			oDecalModifiers.height		= oDecalModifiers.width;
//			oDecalModifiers.farPlane	= oDecalModifiers.width;
//			oDecalModifiers.nearPlane	= oDecalModifiers.width;
//		}
//
//		// Generate a triangle mesh for the decal by clipping the hitShape using six boundary planes
//		std::vector< uint32 > outTrianglesIndices1;
//		std::vector< uint32 > outTrianglesIndices2;
//		bool foundTriangles;
//
//		/*//	filter using sphere
//		std::vector< uint32 > outTrianglesIndices1;
//		oDecalSphere.setValue( P, oDecalModifiers.size/2.f );
//		bool foundTriangles = vgAlg::intersect::getTriangles( decalInfos.hitShape, oDecalSphere, outTrianglesIndices );*/
//
//		//	filter using farPlane
//		// far plane <=> back of box
//		//vgLogDebug( "farPlane=%f", oDecalModifiers.farPlane );
//		vgm::Plane farPlane( N, P );
//		farPlane.offset( -oDecalModifiers.farPlane );
//		outTrianglesIndices1.clear();
//		foundTriangles = vgAlg::intersect::getTriangles(	decalInfos.hitShape, outTrianglesIndices2,
//															farPlane,
//															outTrianglesIndices1 );
//
//		//	filter using nearPlane
//		// near plane <=> front of box
//		//vgLogDebug( "nearPlane=%f", oDecalModifiers.nearPlane );
//		vgm::Plane nearPlane( -N, P );
//		nearPlane.offset( -oDecalModifiers.nearPlane );
//		outTrianglesIndices2.clear();
//		foundTriangles = vgAlg::intersect::getTriangles(	decalInfos.hitShape, outTrianglesIndices1,
//															nearPlane,
//															outTrianglesIndices2 );
//
//		//	filter using leftPlane and rightPlane
//		//vgLogDebug( "width=%f", oDecalModifiers.width );
//		vgm::Plane leftPlane( T, P );
//		leftPlane.offset( -oDecalModifiers.width/2.f );
//		outTrianglesIndices1.clear();
//		foundTriangles = vgAlg::intersect::getTriangles(	decalInfos.hitShape, outTrianglesIndices2,
//															leftPlane,
//															outTrianglesIndices1 );
//
//		vgm::Plane rightPlane( -T, P );
//		rightPlane.offset( -oDecalModifiers.width/2.f );
//		outTrianglesIndices2.clear();
//		foundTriangles = vgAlg::intersect::getTriangles(	decalInfos.hitShape, outTrianglesIndices1,
//															rightPlane,
//															outTrianglesIndices2 );
//
//		//	filter using topPlane and bottomPlane
//		//vgLogDebug( "height=%f", oDecalModifiers.height );
//		vgm::Plane topPlane( B, P );
//		topPlane.offset( -oDecalModifiers.height/2.f );
//		outTrianglesIndices1.clear();
//		foundTriangles = vgAlg::intersect::getTriangles(	decalInfos.hitShape, outTrianglesIndices2,
//															topPlane,
//															outTrianglesIndices1 );
//
//		vgm::Plane bottomPlane( -B, P );
//		bottomPlane.offset( -oDecalModifiers.height/2.f );
//		outTrianglesIndices2.clear();
//		foundTriangles = vgAlg::intersect::getTriangles(	decalInfos.hitShape, outTrianglesIndices1,
//															bottomPlane,
//															outTrianglesIndices2 );
//
//		if ( foundTriangles )
//		{
//			// Create sub-mesh
//			retVal = vgAlg::vertexShape::createSubTriSet( decalInfos.hitShape, outTrianglesIndices2 );
//
//			// Updates oDecalBox for visual feedback
//			const vgm::Vec3f minBoxCorner(	-oDecalModifiers.width/2.f,	-oDecalModifiers.height/2.f,	-oDecalModifiers.farPlane);
//			const vgm::Vec3f maxBoxCorner(	oDecalModifiers.width/2.f,	oDecalModifiers.height/2.f,		oDecalModifiers.nearPlane);
//			oDecalBox.setBounds( minBoxCorner, maxBoxCorner );
//
//			//	transformation applied to wirebox
//			vgm::MatrixR orientation = vgm::MatrixR::getIdentity();
//			orientation.setRow( 0, vgm::Vec4f(T) );
//			orientation.setRow( 1, vgm::Vec4f(B) );
//			orientation.setRow( 2, vgm::Vec4f(N) );
//
//			vgm::Vec3f P2;
//			orientation.getInverse().multVecMatrix(P, P2);
//
//			vgm::MatrixR transform = orientation;
//			transform.translate( P2 );
//
//			oDecalBox.setTransform( transform );
//
//			const vgm::Vec4f xAxis = leftPlane.getValue();
//			const vgm::Vec4f yAxis = bottomPlane.getValue();
//			vgAlg::vertexShape::computeTexGenObjectLinear( retVal,
//				xAxis/oDecalModifiers.width,
//				yAxis/oDecalModifiers.height,
//				0 /*texCoordIndex*/);
//
//			vgm::MatrixR texMatrix;
//
//			const vgm::Vec3f	texCoordScaleFactors		( oDecalModifiers.texCoordScaleFactors, 1.f										);
//			const vgm::Vec3f	texCenter					( 0.5f, 0.5f, 0.f																);
//			const vgm::Rotation	texCoordRotation			( vgm::Vec3f(0.f, 0.f, 1.f), vgm::deg2rad(oDecalModifiers.texCoordRotation)		);
//			const vgm::Vec3f	texCoordTranslation			( oDecalModifiers.texCoordTranslation											);
//
//			texMatrix.setScale( texCoordScaleFactors );
//			texMatrix.translate( texCoordTranslation );
//			texMatrix.translate( texCenter );
//			texMatrix.rotate( texCoordRotation );
//			texMatrix.translate( -texCenter );
//
//			retVal->textureTransform( texMatrix, 0 );
//		}
//		else
//		{
//			vgAssertN( false, "Triangle too big..." );
//			oDecalBox.setInvalid();
//		}
//	}
//	else
//	{
//		oDecalBox.setInvalid();
//	}
//
//	return retVal;
//}
//
//
//
//} // namespace engine
//
//} // namespace vgeGL
//
//#endif // #ifndef __USE_VGALG__
//