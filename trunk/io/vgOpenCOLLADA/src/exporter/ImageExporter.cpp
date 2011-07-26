// VGSDK - Copyright (C) 2010, 2011, Nicolas Papier, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson
// Author Guillaume Brocker

#include "vgOpenCOLLADA/exporter/ImageExporter.hpp"

#include <COLLADASWImage.h>

#include <sbf/path.hpp>

#include <vgDebug/helpers.hpp>
#include <vgd/basic/Image.hpp>


namespace vgOpenCOLLADA
{

namespace exporter
{
	
ImageExporter::ImageExporter( COLLADASW::StreamWriter * streamWriter, collectedMapType collectedMap, std::string filepath, vgOpenCOLLADA::Settings exportSettings ) 
:	COLLADASW::LibraryImages ( streamWriter ),
	m_collectedMap( collectedMap ),
	m_outputFilePath( filepath ),
	m_exportSettings( exportSettings )
{
	std::string	fileName = m_outputFilePath.stem().string();
	boost::filesystem::path	directory = m_outputFilePath.parent_path();

	m_imageDirectoryName = "/" + fileName + "_images";

	m_imageDirectory = directory.string() + m_imageDirectoryName;
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
			int maxSize = m_exportSettings.getTextureSize();
			bool mustResize = false;
			if( image.width() > maxSize || image.height() > maxSize || image.depth() > maxSize )
			{
				vgm::Vec3i  size( std::min<int>( image.width(), maxSize), std::min<int>( image.height(), maxSize), std::min<int>( image.depth(), maxSize) );
				image.scale( size, vgd::basic::Image::FILTER_SCALE_MITCHELL );
			}

			if( m_exportSettings.getEncrypt() == true )
			{
				//ILGetData to get pointer to the file?
				//encrypt image
			}

			// Creates directory if needed
			sbf::path::mkdirs( m_imageDirectory );

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

