// VGSDK - Copyright (C) 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#include "vgQt/actions/alg/ExportOpenAssetImport.hpp"

#include <QApplication>
#include <QFileDialog>


namespace vgQt
{
namespace actions
{
namespace alg
{


const boost::filesystem::path ExportOpenAssetImport::getPath()
{
	// Creates the name filters.
	QString	nameFilters;
	for( Formats::const_iterator format = m_formats.begin(); format != m_formats.end(); ++format )
	{
		nameFilters += QString("%1 (*%2);;").arg( format->name.c_str(), format->extension.c_str() );
	}

	// Prompts the user for a file path and type.
	const QString filePath = QFileDialog::getSaveFileName( 
		QApplication::activeWindow(),
		"Export object", 
		QString(),
		nameFilters );

	// Returns the file path if one has been soecified, or simply an empty one otherwise.
	return filePath.isEmpty() ? boost::filesystem::path() : boost::filesystem::path( filePath.toStdString() );
}


} // namespace alg
} // namespace actions
} // namespace vgQt
