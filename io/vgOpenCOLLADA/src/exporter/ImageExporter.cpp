// VGSDK - Copyright (C) 2010 Nicolas Papier, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgOpenCOLLADA/exporter/ImageExporter.hpp"

#include <COLLADASWImage.h>

#include <sbf/path.hpp>

#include <vgDebug/Global.hpp>
#include <vgd/basic/Image.hpp>


namespace vgOpenCOLLADA
{

namespace exporter
{
	
ImageExporter::ImageExporter( COLLADASW::StreamWriter * streamWriter, collectedMapType collectedMap, std::string filepath, ExportSettings exportSettings ) 
:	COLLADASW::LibraryImages ( streamWriter ),
	m_collectedMap( collectedMap ),
	m_outputFilePath( filepath ),
	m_exportSettings( exportSettings )
{
	std::string	fileName = m_outputFilePath.stem();
	boost::filesystem::path	directory = m_outputFilePath.parent_path();

	m_imageDirectoryName = "/" + fileName + "_images";

	m_imageDirectory = directory.string() + m_imageDirectoryName;
	sbf::path::mkdirs( m_imageDirectory );
}



void ImageExporter::doExport()
{
	vgDebug::get().logDebug("Exporting images");
	openLibrary();

	typedef collectedMapType::right_map::const_iterator right_const_iterator;

	for( right_const_iterator right_iter = m_collectedMap.right.begin(), iend = m_collectedMap.right.end();
		 right_iter != iend; ++right_iter )
	{
		vgd::Shp< vge::technique::CollectedMaterial > collectedMaterial = right_iter->first;
		vgd::Shp< vgd::node::Texture2D > texture = collectedMaterial->getTexture();

		if( texture )
		{
			vgd::Shp< vgd::basic::IImage > loadedImage;
			texture->getImage( loadedImage );

			vgd::basic::Image image( (*loadedImage.get()) );
			
			//Save image.
			std::string imageName = m_imageDirectory + "/" + texture->getName() + ".png";
			image.save( imageName );

			//Save image in COLLADA Image Library
			std::string imageId = texture->getName();
			COLLADASW::Image imageCollada( "." + m_imageDirectoryName + "/" + texture->getName() + ".png",imageId );
			addImage( imageCollada );

			collectedMaterial->setImageId( imageId );
		}
	}

	closeLibrary();
}



} // namespace exporter

} // namespace vgOpenCOLLADA

