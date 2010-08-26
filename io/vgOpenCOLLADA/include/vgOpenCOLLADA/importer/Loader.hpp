// VGSDK - Copyright (C) 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGOPENCOLLADA_IMPORTER_LOADER_HPP
#define _VGOPENCOLLADA_IMPORTER_LOADER_HPP


#include "vgOpenCOLLADA/vgOpenCOLLADA.hpp"
#include <vgOpenCOLLADA/Settings.hpp>

#include <vgOpenCOLLADA/importer/ErrorHandler.hpp>
#include <vgOpenCOLLADA/importer/ExtraDataMultiInstance.hpp>
#include <vgOpenCOLLADA/importer/ExtraDataBumpMapping.hpp>
#include <vgOpenCOLLADA/importer/Reader.hpp>


#include <string>

#include <vgio/ILoader.hpp>
#include <vgio/LoaderRegistry.hpp>

#include <vgd/node/Group.hpp>
#include <vgd/Shp.hpp>

#include <COLLADAFWRoot.h>
#include <COLLADASaxFWLLoader.h>


namespace vgOpenCOLLADA
{

namespace importer
{

/**
 * @brief The COLLADA file loader.
 */
struct VGOPENCOLLADA_API Loader : public vgio::ILoader
{
	META_LOADER_HPP( vgOpenCOLLADA::importer::Loader )
	
	Loader( vgOpenCOLLADA::Settings settings = vgOpenCOLLADA::Settings() ) throw( std::runtime_error );
	virtual ~Loader() {}

	/**
	 * @brief Create and return the whole scene using the Reader class (sax parser).
	 * 
	 * @return a pair bool/group. true if the scene succefully create. The group representing the whole scene graph.
	 */
	std::pair< bool, vgd::Shp< vgd::node::Group > > load( const std::string filePath, const bool bCCW = false ) throw( std::runtime_error );

	/**
	 * @brief Create and return the whole scene using the Reader class (sax parser) and a file in memory.
	 * 
	 * @return a pair bool/group. true if the scene succefully create. The group representing the whole scene graph.
	 */
	std::pair< bool, vgd::Shp< vgd::node::Group > > load( const std::string filePath, vgd::Shp< std::vector< char > > outBuffer, const bool bCCW = false ) throw( std::runtime_error );

	/**
	 * @brief Create and return the whole scene using the Reader class (sax parser), a file in memory and the list of image already load in memory.
	 * 
	 * @return a pair bool/group. true if the scene succefully create. The group representing the whole scene graph.
	 */
	std::pair< bool, vgd::Shp< vgd::node::Group > > load( const std::string filePath, vgd::Shp< std::vector< char > > outBuffer, std::map< std::string, vgd::Shp< vgd::basic::Image > > imageMap, const bool bCCW = false );
		
	const ExtraDataMultiInstance&	getExtraDataMultiInstance();
	const ExtraDataBumpMapping&		getExtraDataBumpMapping();

	virtual vgd::Shp< vgio::ILoader > clone();

private:
	Reader						m_reader;
	ErrorHandler				m_errorHandler;
	COLLADASaxFWL::Loader		m_saxLoader;
	COLLADAFW::Root				m_root;
	ExtraDataMultiInstance		m_extraDataMultiInstance;
	ExtraDataBumpMapping		m_extraDataBumpMapping;

};



} // namespace importer

} // namespace vgOpenCOLLADA

#endif // _VGOPENCOLLADA_IMPORTER_LOADER_HPP

