//// VGSDK - Copyright (C) 2013, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_ENGINE_DECALMANAGER_HPP
//#define _VGEGLBASE_ENGINE_DECALMANAGER_HPP
//
//#include "vgeGLBase/basic/Hit.hpp"
//#include <vgm/Box.hpp>
//#include <vgm/Triangle.hpp>
//
//
//namespace vgd
//{
//namespace basic { struct IImage; }
//namespace node { struct Decal; struct VertexShape; struct WireBox; }
//}
//
//
//
//namespace vgeGLBase
//{
//
//namespace engine
//{
//
//struct SceneManager;
//
///**
// * @brief Informations from ray casting used by decal spawning functions
// */
//struct DecalInformations
//{
//	/**
//	 * @name Ray informations
//	 */
//	//@{
//	vgm::Vec3f	raySource;
//	vgm::Vec3f	rayDirection;
//	//@}
//
//	/**
//	 * @name Hit informations
//	 */
//	//@{
//	vgd::node::VertexShape *	hitShape;
//	vgm::TriangleExt			hitABC;
//	vgeGLBase::basic::Hit			hit;
//	//@}
//};
//
//
///**
// * @brief Decal properties
// */
//struct DecalProperties
//{
//	/**
//	 * @brief Default constructor
//	 */
//	DecalProperties()
//	{
//		reset();
//	}
//
//	/**
//	 * @brief Set default values
//	 */
//	void reset()
//	{
//		width		= 0.f;
//		height		= 0.f;
//		farPlane	= 0.f;
//		nearPlane	= 0.f;
//
//		texCoordRotation	 = 0.f;
//		texCoordTranslation.setNull();
//		texCoordScaleFactors.setValue( 1.f, 1.f );
//	}
//
//
//	/**
//	 * @name Size of the decal box
//	 */
//	//@{
//
//	float width;			//@< width of the decal box along the tangent direction
//	float height;			//@< height of the decal box along the binormal direction
//	float farPlane;			//@< distance of the far plane from the hit point (along the inverse normal direction).
//	float nearPlane;		//@< distance of the near plane from the hit point (along the normal direction).
//	//@}
//
//	/**
//	 * @name Transformation applied to texture coordinates
//	 *
//	 * transformedTexCoord = texCoord * -C * R * C * T * S with C = (0.5, 0.5), R(otation), T(ranslation) and S(cale)
//	 */
//	//@{
//	float		texCoordRotation;		//@< rotation applied to texture coordinates
//	vgm::Vec2f	texCoordTranslation;	//@< translation applied to texture coordinates
//	vgm::Vec2f	texCoordScaleFactors;	//@< scale applied to texture coordinates
//	//@}
//};
//
//
//
///**
// * @brief Helpers for decal system
// *
// * @see Game Gems 2, chapter 4.8: Applying Decals to Arbitrary Surfaces, by Eric Lengyel
// */
//struct DecalManager
//{
//	/**
//	 * @brief Cast a ray in the scene owned by sceneManager under the mouse location to compute starting point and direction of the ray to instanciate a decal under the mouse.
//	 *
//	 * @param	outRaySourceW			starting point of the ray (in world space) or invalid
//	 * @param	outRayDirectionW		direction of the ray (in world space) or invalid
//	 */
//	VGEGLBASE_API static const bool spawnDecalPrecomputation(	vgeGLBase::engine::SceneManager * sceneManager, const vgm::Vec2i mouseLocation,
//															vgm::Vec3f& outRaySourceW, vgm::Vec3f& outRayDirectionW );
//
//	/**
//	 * @brief Cast a ray using given source and direction
//	 *
//	 * @param oDecalInfos		All hit informations (i.e. hitShape, hitABC and hit fields) are filled by this method
//	 * @param oDecalModifiers	@todo doc
//	 * @param oDecalBox			@todo doc
//	 *
//	 * @return The shape that have to be used by decal node
//	 *
//	 * @todo vgd::Shp< vgd::node::VertexShape > spawnDecalShape( vgeGLBase::engine::SceneManager * sceneManager, mouseLocation )
//	 */
//	VGEGLBASE_API static vgd::Shp< vgd::node::VertexShape > spawnDecalShape(	vgeGLBase::engine::SceneManager * sceneManager, const vgm::Vec3f& raySourceW, const vgm::Vec3f& rayDirectionW,
//																			DecalInformations& oDecalInfos, DecalProperties& oDecalModifiers, vgm::XfBox3f& oDecalBox );
//
//
//	/**
//	 * @brief Create a decal that project image onto the given surface
//	 *
//	 * @param image			the image to project
//	 * @param decalShape	the surface where image is projected
//	 */
//	static VGEGLBASE_API vgd::Shp< vgd::node::Decal > createDecal( vgd::Shp< vgd::basic::IImage > image, vgd::Shp< vgd::node::VertexShape > decalShape );
//
//
//	/**
//	 * @brief Updates wireBoxShape using the given box
//	 *
//	 * @param box					use the box position/size/orientation to update the wireBoxShape. If box is invalid, then all primitives are removed from wireBoxShape
//	 * @param wireBoxShape			use the box position/size/orientation to update the wireBoxShape
//	 * @param addFrontFaceCross		add a cross in the front face of the box to mark it
//	 */
//	static VGEGLBASE_API void synchronize( const vgm::XfBox3f& box, vgd::Shp< vgd::node::WireBox > wireBoxShape, const bool addFrontFaceCross );
//
//private:
//
//	static vgd::Shp< vgd::node::VertexShape > spawnDecalShape(	const DecalInformations& decalInfos, 
//																DecalProperties& oDecalModifiers, vgm::XfBox3f& oDecalBox );
//};
//
//
//
//} // namespace engine
//
//} // namespace vgeGLBase
//
//#endif //#ifndef _VGEGLBASE_ENGINE_DECALMANAGER_HPP
//