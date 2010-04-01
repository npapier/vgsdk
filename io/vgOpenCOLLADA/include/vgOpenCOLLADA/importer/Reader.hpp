// VGSDK - Copyright (C) 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGOPENCOLLADA_IMPORTER_READER_HPP
#define _VGOPENCOLLADA_IMPORTER_READER_HPP


#include "vgOpenCOLLADA/vgOpenCOLLADA.hpp"
#include "vgOpenCOLLADA/convenience.hpp"

#include <vgd/Shp.hpp>
#include <vgd/node/Group.hpp>
#include <vgd/node/Switch.hpp>
#include <vgd/node/Texture2D.hpp>
#include <vgd/node/VertexShape.hpp>

#include <COLLADAFWIWriter.h>
#include <COLLADABUURI.h>
#include <COLLADAFWPrerequisites.h>
#include <COLLADAFWFileInfo.h>
#include <COLLADASaxFWLLoader.h>


namespace vgOpenCOLLADA
{

namespace importer
{

/**
 * @brief The COLLADA file reader frontend.
 */
struct VGOPENCOLLADA_API Reader : public COLLADAFW::IWriter
{
	Reader(LOAD_TYPE type);
	virtual ~Reader() {};

	virtual void start() {}
	virtual void cancel(const COLLADAFW::String& errorMessage) {}
	virtual void finish() {}
	
	//Methods being called from the SaxParser

    /** 
	 * Get the global document asset.
	 * 
	 * @return Should return true, if reading succeeded, false otherwise.
	 */
	virtual bool writeGlobalAsset ( const COLLADAFW::FileInfo* asset );

    /** 
	 * Instanciates all node and elements of the scene.
	 * 
	 * @return Should return true, if reading succeeded, false otherwise.
	 */
	virtual bool writeVisualScene ( const COLLADAFW::VisualScene* visualScene );

    /** 
	 * Creates geometry of the scene and store them in m_switchVertexShape.
	 * 
	 * @return Should return true, if reading succeeded, false otherwise.
	 */
	virtual bool writeGeometry ( const COLLADAFW::Geometry* geometry );

    /** 
	 * Creates materials of the scene and store them in m_switchMaterial.
	 * 
	 * @return Should return true, if reading succeeded, false otherwise.
	 */
	virtual bool writeMaterial( const COLLADAFW::Material* material );

    /** 
	 * Creates effects of the scene and store them in the material which instiate it.
	 * 
	 * @return Should return true, if reading succeeded, false otherwise.
	 */
	virtual bool writeEffect( const COLLADAFW::Effect* effect );

    /** 
	 * Loads images of the scene and store them in m_switchTexture.
	 * 
	 * @return Should return true, if reading succeeded, false otherwise.
	 */
	virtual bool writeImage( const COLLADAFW::Image* image );

	//method not used atm.
	virtual bool writeScene ( const COLLADAFW::Scene* scene ) { return true; }
	virtual bool writeLibraryNodes ( const COLLADAFW::LibraryNodes* libraryNodes ) { return true; }
	virtual bool writeCamera( const COLLADAFW::Camera* camera ) { return true; }
	virtual bool writeLight( const COLLADAFW::Light* light ) { return true; }
	virtual bool writeAnimation( const COLLADAFW::Animation* animation ) { return true; }
	virtual bool writeAnimationList( const COLLADAFW::AnimationList* animationList ) { return true; }
	virtual bool writeSkinControllerData( const COLLADAFW::SkinControllerData* skinControllerData ) { return true; }
	virtual bool writeController( const COLLADAFW::Controller* Controller ) { return true; }
    virtual bool writeFormulas( const COLLADAFW::Formulas* formulas ) { return true; }
	virtual bool writeKinematicsScene( const COLLADAFW::KinematicsScene* kinematicsScene ) { return true; }

	/**
	 * @brief Return the whole scene
	 * 
	 * @return a pair bool/group. true if the scene succefully create. The group representing the whole scene graph.
	 */
	std::pair< bool, vgd::Shp< vgd::node::Group > > getScene();

	/**
	* @brief Clones a Texture node
	*
	* @param texture: a texture
	*
	* @return: the cloned texture
	*/
	vgd::Shp< vgd::node::Texture2D > cloneTexture( vgd::Shp< vgd::node::Texture2D > texture );


private:
	COLLADABU::URI									m_inputFile;
	LOAD_TYPE										m_loadType;
	std::pair< bool, vgd::Shp< vgd::node::Group > > m_scene;
	vgd::Shp< vgd::node::Group >					m_group;
	vgd::Shp< vgd::node::Switch >					m_switchMaterial;
	vgd::Shp< vgd::node::Switch >					m_switchTexture;
	vgd::Shp< vgd::node::Switch >					m_switchVertexShape;

};



} // namespace importer

} // namespace vgOpenCOLLADA

#endif // _VGOPENCOLLADA_IMPORTER_READER_HPP
