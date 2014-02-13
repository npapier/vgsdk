// VGSDK - Copyright (C) 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#include "vgOpenAssetImport/actions/aiExport.hpp"

#include <assimp/IOSystem.hpp>
#include <assimp/Exporter.hpp>

#include <vgDebug/helpers.hpp>


namespace vgOpenAssetImport
{
namespace actions
{


const aiExport::Formats aiExport::m_formats( createFormats() );


const bool aiExport::aiExecute( const aiScene * scene )
{
	// Retrieves the file path.
	const boost::filesystem::path path = getPath();

	// If there is a file path, we can export.
	if( !path.empty() )
	{
		Assimp::Exporter		exporter;
		Formats::const_iterator format = findFormat( path );

		vgAssertN( format != m_formats.end(), "Export format must be specified." );
		exporter.Export( scene, format->aiId, path.string().c_str(), 0u );
		// We should do some error checking !
	}

	return false; // We never need to refresh the scene.
}


const aiExport::Formats aiExport::createFormats()
{
	aiExport::Formats formats;

	formats.push_back( Format("OpenCollada", ".dae", "collada") );
	formats.push_back( Format("Wavefromt OBJ", ".obj", "obj") );
	formats.push_back( Format("STereoLithography", ".stl", "stl") );
	formats.push_back( Format("Polygon File Format", ".ply", "ply") );
	
	return formats;
}


aiExport::Formats::const_iterator aiExport::findFormat( const boost::filesystem::path & path )
{
	const std::string		extension = path.extension().string();
	Formats::const_iterator format;
	for( format = m_formats.begin(); format != m_formats.end(); ++format )
	{
		if( format->extension == extension )
		{
			break;
		}
	}
	return format;
}


} // namespace actions
} // vgOpenAssetImport