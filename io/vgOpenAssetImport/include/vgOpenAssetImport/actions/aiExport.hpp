// VGSDK - Copyright (C) 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGOPENASSETIMPORT_ACTIONS_AIEXPORT_HPP_
#define _VGOPENASSETIMPORT_ACTIONS_AIEXPORT_HPP_

#include <vector>
#include <boost/filesystem/path.hpp>

#include "vgOpenAssetImport/actions/aiAction.hpp"


namespace vgOpenAssetImport
{
namespace actions
{


/**
 * @brief	Base class for exports based on OpenAssetImport
 *
 * This class exports nodes using OpenAssetImport facilities but
 * it has to be to be specialized for a specific widget toolkit, leaving
 * this part to dedicted subclasses.
 */
struct VGOPENASSETIMPORT_API aiExport : public aiAction
{

protected:

	/**
	 * @brief	Defines an export format
	 */
	struct Format
	{
		Format( const std::string & _name, const std::string & _extension, const std::string & _aiId ) : name(_name), extension(_extension), aiId(_aiId)
		{}

		std::string name;
		std::string extension;
		std::string aiId;
	};

	typedef std::vector< Format > Formats;

	static const Formats m_formats;	///< Holds all available export formats.

	/**
	 * @brief	Retrieves the destination path for the export.
	 *
	 * Subclasses must implement this method, for example by prompting an appropriate dialog box to the user.
	 *
	 * @return	a full file path, empty to cancel action.
	 */
	virtual const boost::filesystem::path getPath() = 0;

	/**
	 * @name	Overrides
	 */
	//@{
	const bool aiExecute( const aiScene * scene );
	//@}

private:

	/**
	 * @name	Helpers
	 */
	//@{
	static const Formats createFormats();
	static Formats::const_iterator findFormat( const boost::filesystem::path & path );	///< Retrieves the format using the file extention in the given path.
	//@}
};


} // namespace actions
} // namespace vgOpenAssetImport


#endif // _VGOPENASSETIMPORT_ACTIONS_AIEXPORT_HPP_
