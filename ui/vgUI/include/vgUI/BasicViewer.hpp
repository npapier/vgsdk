// VGSDK - Copyright (C) 2004, 2007, 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGUI_BASICVIEWER_HPP
#define _VGUI_BASICVIEWER_HPP

#include <vgd/node/Camera.hpp>
#include <vgd/node/Group.hpp>
#include <vgd/node/MatrixTransform.hpp>

#include "vgUI/Canvas.hpp"



namespace vgUI
{

/**
 * @brief A basic viewer for displaying vgsdk graphics.
 *
 * This class provides some methods to :
 *
 * - set the camera type that will be used by the viewer (see Accessors in the camera section).
 * - adjust the camera position and frustum to be able to view the entire scene (see viewAll method).
 * - adjust camera when window is resized (see resize() method).
 * - manage default lights
 *
 * @remarks Camera behavior (mainly viewAll and resize methods ) can be overridden if the default behavior does'nt meet
 * your needs.
 *
 * The scene graph is divided in two parts. First child of the root is a group node, named \c SETUP, that contains some
 * useful nodes to initialize the scene like :
 * \li the camera node named \c CAMERA
 * \li the optional default light group named \c LIGHTS
 * \li the optional frame buffer clearing node named \c CLEAR
 * \li the view transformation named \c VIEW_TRANSFORM.
 *
 * The second child of the root is a group node, named \c SCENE that must contains the real scene (mesh, material...).
 *
 * @ingroup g_vgWXGroup
 *
 * @todo More documentation on SETUP nodes and more generic.
 * @todo populateSetupGroup( Full | Light).
 */
struct VGUI_API BasicViewer : public Canvas
{
	/**
	 * @name Constructors
	 */
	//@{
	/**
	 * @brief	Constructs a BasicViewer with its own OpenGL context.
	 */
	BasicViewer();

	/**
	 * @brief	Constructs a BasicViewer with its own OpenGL context, but that share OpenGL objects with another(s) Canvas.
	 *
	 * @param	sharedCanvas	a pointer to a canvas that will share OpenGL resources
	 */
	BasicViewer( Canvas * sharedCanvas );
	//@}


	/**
	 * @name Camera Accessors
	 */
	//@{
	/**
	 * @brief The different type of camera type.
	 */
	enum CameraType {

		CAMERA_PERSPECTIVE,
		CAMERA_ORTHOGRAPHIC,

		CAMERA_DEFAULT = CAMERA_PERSPECTIVE
	};

	/**
	 * @brief Sets the desired camera type.
	 *
	 * @param typeOfCamera		the type of the camera. Could be CAMERA_PERSPECTIVE, CAMERA_OTHOGRAPHIC or CAMERA_DEFAULT.
	 */
	void setCameraType( const CameraType typeOfCamera );

	/**
	 * @brief Returns the current camera type used.
	 *
	 * @return the camera type.
	 */
	const CameraType getCameraType() const;

	/**
	 * @brief Returns the camera node.
	 *
	 * @return the camera node.
	 */
	vgd::Shp< vgd::node::Camera > getCamera();

	/**
	 * @brief Camera position hints
	 */
	enum CameraDistanceHints
	{
		CLOSE,
		CENTER,
		//FAR,
		CAMERA_DISTANCE_HINTS_DEFAULT = CENTER
	};

	/**
	 * @brief Changes the camera position and frustum to view the entire scene.
	 */
	virtual void viewAll( const CameraDistanceHints cameraDistance = CAMERA_DISTANCE_HINTS_DEFAULT );
	//@}


	/**
	 * @name Other Accessors
	 */
	//@{
	/**
	 * @brief Returns the setup node.
	 *
	 * @return the setup node.
	 */
	vgd::Shp< vgd::node::Group > getSetup();

	/**
	 * @brief Returns the view transformation node.
	 *
	 * @return the view transformation node.
	 */
	vgd::Shp< vgd::node::MatrixTransform > getViewTransformation();

	/**
	 * @brief Returns scene group node.
	 */
	vgd::Shp< vgd::node::Group > getScene();

	/**
	 * @brief Returns scene group node.
	 */
	const vgd::Shp< vgd::node::Group > getScene() const;
	//@}
	
	
	/**
	 * @name	Optional Nodes Control
	 */
	//@{
	enum OptionalNodeType
	{
		CLEAR_FRAME_BUFFER,	///< ClearFrameBuffer optional node
		DRAW_STYLE,			///< DrawStyle optional node
		LIGHT_MODEL,		///< LightModel optional node
		LIGHTS				///< Group optional node containing default lights
	};
	
	/**
	 * @brief	Creates the given optional node, if it does not already exist.
	 * 
	 * @param	type	an optional node type
	 * 
	 * @return	a shared pointer to the create node
	 * 
	 * @see		destroyOptionalNode
	 * @see		getOptionalNode
	 */
	vgd::Shp< vgd::node::Node > createOptionalNode( const OptionalNodeType type );
	
	/**
	 * @brief	Destroyes the the option node of the given type, if any exists.
	 * 
	 * @param	type	an optional node type
	 * 
	 * @see		createOptionalNode
	 * @see		getOptionalNode
	 */
	void destroyOptionalNode( const OptionalNodeType type );
	
	/**
	 * @brief	Retrieves an optional node for the given type, if any exists.
	 * 
	 * @param	type	an optional node type
	 * 
	 * @return	a share pointer to the found optional node, empty if none exists
	 * 
	 * @see		createOptionalNode
	 * @see		destroyOptionalNode
	 */
	vgd::Shp< vgd::node::Node > getOptionalNode( const OptionalNodeType type );
	
	/**
	 * @brief	Retrieves an optional node for the given type, if any exists.
	 * 
	 * @param	type	an optional node type
	 * 
	 * @return	a share pointer to the found optional node, empty if none exists
	 * 
	 * @see		createOptionalNode
	 * @see		destroyOptionalNode
	 */
	template< typename NodeType >
	vgd::Shp< NodeType > getOptionalNodeAs( const OptionalNodeType type )
	{
		vgd::Shp< vgd::node::Node >	node = getOptionalNode( type );
		
		return node ? vgd::dynamic_pointer_cast<NodeType>(node) : vgd::Shp<NodeType>();
	}
	//@}


	/**
	 * @name Rendering methods
	 */
	//@{
	void resize( const vgm::Vec2i size );
	//@}



protected:
	/**
	 * @brief Compute bounding box.
	 *
	 * @param pCollectorExt	node collector.
	 * @param box		computed bounding box value.
	 * @param center	computed center of \c box
	 * @param max		the maximum of width, height and depth of the box.
	 */
	void computeBoundingBox(	vge::visitor::NodeCollectorExtended<> *pCollectorExt,
								vgm::Box3f& box, vgm::Vec3f& center,
								float& max );

	/**
	 * @brief Compute bounding box starting on the group node named SCENE.
	 *
	 * @param box		computed bounding box value.
	 * @param center	computed center of \c box
	 * @param max		the maximum of width, height and depth of the box.
	 */
	void computeSceneBoundingBox(	vgm::Box3f& box, vgm::Vec3f& center,
									float& max );



private:

	/**
	 * @brief Computes a value used to set the camera position in the scene
	 */
	const float compute( const CameraDistanceHints cameraDistance );

	vgd::Shp< vgd::node::Group > 			m_setup;			///< A reference on the setup group node.
	vgd::Shp< vgd::node::Camera >			m_camera;			///< A reference on the camera.
	vgd::Shp< vgd::node::MatrixTransform >	m_viewTransform;	///< A reference on the view transformation.
	vgd::Shp< vgd::node::Group >			m_scene;			///< A reference on the scene group node.
	CameraType								m_cameraType;		///< The camera type that should be used.
};



} // namespace vgWX

#endif // #ifndef _VGUI_BASICVIEWER_HPP
