// VGSDK - Copyright (C) 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGOPENCOLLADA_IMPORTER_LOADER_HPP
#define _VGOPENCOLLADA_IMPORTER_LOADER_HPP


#include "vgOpenCOLLADA/vgOpenCOLLADA.hpp"
#include "vgOpenCOLLADA/convenience.hpp"

#include "vgOpenCOLLADA/importer/Reader.hpp"
#include "vgOpenCOLLADA/importer/ErrorHandler.hpp"

#include <string>

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
struct VGOPENCOLLADA_API Loader
{
	Loader(LOAD_TYPE type) throw(std::runtime_error);
	virtual ~Loader() {};

	/**
	 * @brief Create and return the whole scene using the Reader class (sax parser).
	 * 
	 * @return a pair bool/group. true if the scene succefully create. The group representing the whole scene graph.
	 */
	std::pair< bool, vgd::Shp< vgd::node::Group > > load(const std::string filePath) throw(std::runtime_error);

private:
	Reader m_reader;
	ErrorHandler m_errorHandler;
	COLLADASaxFWL::Loader m_saxLoader;
	COLLADAFW::Root m_root;

};



} // namespace importer

} // namespace vgOpenCOLLADA

#endif // _VGOPENCOLLADA_IMPORTER_LOADER_HPP

