// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGWX_BASICVIEWER_HPP
#define _VGWX_BASICVIEWER_HPP
#include <vgd/node/Camera.hpp>
#include <vgd/node/Group.hpp>
#include <vgd/node/MatrixTransform.hpp>
#include <wx/defs.h>

#include "vgWX/vgWX.hpp"
#include "vgWX/Canvas.hpp"



namespace vgWX
{

/**
 * @brief A basic viewer for displaying vgsdk graphics.
 * 
 * This class provides some methods to :
 * 
 * - set the camera type that will be used by the viewer (see Accessors in the camera section).
 * - adjust the camera position and frustum to be able to view the entire scene (see viewAll method).
 * - adjust camera when window is resized (see resize() method).
 * 
 * @remarks Camera behavior (mainly viewAll and resize methods ) can be overridden if the default behavior does'nt meet 
 * your needs.
 * 
 * The scene graph is divided in two parts. First child of the root is a group node, named \c SETUP, that contains some 
 * useful nodes to initialize the scene like :
 * \li The camera node is named \c CAMERA.
 * \li The view transformation is named \c VIEW_TRANSFORM.
 * 
 * The second child of the root is a group node, named \c SCENE that must contains the real scene (mesh, material...).
 *
 * @ingroup g_vgWXGroup
 * 
 * @todo More documentation on SETUP nodes and more generic.
 * @todo populateSetupGroup( Full | Light).
 */
struct VGWX_API BasicViewer : public Canvas
{
	/**
	 * @name Constructors
	 */
	//@{
	
	/**
	 * @brief Construct a BasicViewer with its own OpenGL context.
	 * 
	 * @param	pParent	A pointer to the parent window.
	 */
	BasicViewer(	wxWindow *parent,
					const wxString& name = _T("BasicViewer"),
					const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
					long style = 0,
					int* gl_attrib = NULL,
					const wxWindowID id = -1 );

	/**
	 * @brief Construct a BasicViewer with its own OpenGL context, but that share OpenGL objects with another(s) Canvas.
	 * 
	 * @param	pParent	A pointer to the parent window.
	 */
	BasicViewer(	wxWindow *parent,
					Canvas *pSharedCanvas,
					const wxString& name = _T("BasicViewer"),
					const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
					long style = 0,
					int* gl_attrib = NULL,
					const wxWindowID id = -1 );
	//@}



	/**
	 * @name Accessors to the camera
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
	void 				setCameraType( const CameraType typeOfCamera );
	
	
	/**
	 * @brief Returns the current camera type used.
	 * 
	 * @return the camera type.
	 */
	const CameraType	getCameraType() const;
	
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

	/**
	 * @brief Returns the setup node.
	 * 
	 * @return the setup node.
	 */
	vgd::Shp< vgd::node::Group >	getSetup();

	/**
	 * @brief Returns the camera node.
	 * 
	 * @return the camera node.
	 */
	vgd::Shp< vgd::node::Camera >	getCamera();
	
	/**
	 * @brief Returns the view transformation node.
	 * 
	 * @return the view transformation node.
	 */
	vgd::Shp< vgd::node::MatrixTransform >	getViewTransformation();
	
	/**
	 * @brief Returns scene group node.
	 */
	vgd::Shp< vgd::node::Group >	getScene();
	
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
	//DECLARE_EVENT_TABLE();

	/**
	 * @brief Computes a value used to set the camera position in the scene
	 */
	const float compute( const CameraDistanceHints cameraDistance );

	/**
	 * @brief A reference on the setup group node.
	 */
	vgd::Shp< vgd::node::Group >				m_setup;
	
	/**
	 * @brief A reference on the camera.
	 */
	vgd::Shp< vgd::node::Camera >				m_camera;

	/**
	 * @brief A reference on the view transformation.
	 */
	vgd::Shp< vgd::node::MatrixTransform >		m_viewTransform;
	
	/**
	 * @brief A reference on the scene group node.
	 */
	vgd::Shp< vgd::node::Group >				m_scene;
	
	



	/**
	 * @brief The camera type that should be used.
	 */
	CameraType									m_cameraType;
};



} // namespace vgWX

#endif // #ifndef _VGWX_BASICVIEWER_HPP
