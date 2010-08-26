// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGIO_LOADERREGISTRY_HPP
#define _VGIO_LOADERREGISTRY_HPP


#include "vgio/vgio.hpp"

#include <list>
#include <map>

#include <vgio/ILoader.hpp>
#include <vgd/Shp.hpp>


namespace vgio
{

/**
 * @brief	Reference all actions drawable in a menu.
 */
struct VGIO_API LoaderRegistry
{
	/**
	* @brief	Get the instance of SelectedNode.
	*/
	static vgd::Shp< LoaderRegistry > getLoaderRegistry();	
	
	~LoaderRegistry();

	/**
	 * @brief	Get the list of all loaders referenced.
	 *
	 * @return	the loader map.
	 */
	std::map< std::string, vgd::Shp< vgio::ILoader > > getLoaderMap() const;

	/**
	 * @brief	Add an action to the current list.
	 *
	 * @param action	the loader to add.
	 *
	 * @param type		the type of loader.
	 */
	void addLoader( vgd::Shp< vgio::ILoader > action, std::string type);

	/**
	 * @brief	Get a loader by its type.
	 *
	 * @param	type Loader type to return.
	 */
	vgd::Shp< vgio::ILoader > getLoader( std::string type );


private:
	
	LoaderRegistry();

	std::map< std::string, vgd::Shp< vgio::ILoader > >	 m_loaderMap; ///< the map of loader
};



/**
 * @brief Register a loader in LoaderRegistry.
 */
template< typename loaderType >
struct RegisterLoader
{
	/**
	 * @brief Constructor to register a loader.
	 */	
	RegisterLoader( std::string type )
	{
		// Register the new action in ActionsRegistry.
 		vgd::Shp< loaderType > loader( new loaderType() );
		
		LoaderRegistry::getLoaderRegistry()->addLoader( loader, type );
	}
};


/**
 * @brief Meta helpers.
 */
#define META_LOADER_HPP( loaderType )	\
static const vgio::RegisterLoader< loaderType > m_registrationInstance;

#define META_LOADER_CPP( loaderType, type )	\
const vgio::RegisterLoader< loaderType > loaderType::m_registrationInstance( type );


} // namespace vgio

#endif //#ifndef _VGIO_LOADERREGISTRY_HPP
