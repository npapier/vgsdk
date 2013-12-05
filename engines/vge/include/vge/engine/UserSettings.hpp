// VGSDK - Copyright (C) 2010, 2011, 2013, Guillaume Brocker, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#ifndef _VGE_ENGINE_USERSETTINGS_HPP_
#define _VGE_ENGINE_USERSETTINGS_HPP_

#include <map>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <vgd/Shp.hpp>

#include "vge/vge.hpp"



namespace vge
{

namespace engine
{



struct SceneManager;



/**
 * @brief	Allows to configure a scene using several levels.
 */
struct VGE_API UserSettings
{
	/**
	 * @brief	Default constructor
	 *
	 * Using this constructor, the details level will be left unsed.
	 */
	UserSettings();

	/**
	 * @brief	Constructor
	 *
	 * @param	sm a scene manager used to initial the level
	 *
	 * Initializes the user settings level according to the configuration of the given scene manager.
	 */
	UserSettings( const vge::engine::SceneManager & sm );

	/**
	 * @brief	Constructor
	 *
	 * @param	sm a scene manager used to initial the level
	 *
	 * Initializes the user settings level according to the configuration of the given scene manager.
	 */
	UserSettings( const vgd::Shp< const vge::engine::SceneManager > sm );


	/**
	 * @name	Scene manager configuration
	 */
	//{@
	/**
	 * @brief	Apply the settings on the given scene manager.
	 *
	 * @param	sm	a scene manager to reconfigure
	 *
	 * @return	a reference to the user settings instance
	 */
	const UserSettings & apply( vge::engine::SceneManager & ) const;

	/**
	 * @brief	Apply the settings on the given scene manager.
	 *
	 * @param	sm	a scene manager to reconfigure
	 *
	 * @return	a reference to the user settings instance
	 */
	const UserSettings & apply( vgd::Shp< vge::engine::SceneManager > ) const;
	//@}


	/**
	 * @name	Properties retrieval
	 */
	//@{
	/**
	 * @brief	Retrieves the description of a given level.
	 *
	 * @return	a string, empty if no description or if the level is invalid
	 */
	const std::string getDescription( const unsigned int level ) const;

	/**
	 * @brief	Retrieves the selected graphic card.
	 *
	 * @return	 a string, empty if no card is selected
	 */
	const std::string getGraphicCard() const;

	/**
	 * @brief	Retrieves the current detail level.
	 *
	 * @return	The current level or a negative value if none.
	 */
	const int getLevel() const;

	/**
	 * @brief	Retrieves the count of available detail levels.
	 */
	const int getLevelCount() const;

	/**
	 * @brief	Retrieves the name of the given level.
	 *
	 * @return	a string, empty if the given level is invalid
	 */
	const std::string getName( const unsigned int level ) const;

	/**
	 * @brief	Retrieves all available graphic cards
	 */
	template< typename Container >
	const Container getGraphicCards() const
	{
		Container	result;

		for( CardContainer::const_iterator i = m_cards.begin(); i != m_cards.end(); ++i )
		{
			result.insert( result.end(), i->first );
		}

		return result;
	}
	//@}


	/**
	 * @name	Detail level assignment
	 */
	//@{
	/**
	 * @brief	Assigns a new detail level
	 *
	 * @remark if level >= getLevelCount() then the greatest level available is used (i.e. getLevelCount()-1).
	 */
	UserSettings & setLevel( const int level );

	/**
	 * @brief	Assigns a new detail level based on the configuration of the given scene manager.
	 *
	 * @param	sm	a scene manager whose configuration will be used to determine the user settings level
	 *
	 * @return	a reference to the user settings instance
	 */
	UserSettings & setLevel( const vge::engine::SceneManager & sm );

	/**
	 * @brief	Assigns a new detail level based on the configuration of the given scene manager.
	 *
	 * @param	sm	a scene manager whose configuration will be used to determine the user settings level
	 *
	 * @return	a reference to the user settings instance
	 */
	UserSettings & setLevel( const vgd::Shp< const vge::engine::SceneManager > sm );

	/**
	 * @brief	Assigns a new detail level to the maximum possible value.
	 *
	 * @return	a reference to the user settings instance
	 */
	UserSettings & setMaxLevel();

	/**
	 * @brief	Assigns a graphic card that will be used to determine the appropriate defailt level
	 *
	 * @param	card	a string containing a card name
	 *
	 * @return	a reference to the user settings instance
	 *
	 * @see		getGraphicCards
	 */
	UserSettings & setGraphicCard( const std::string & card );
	//@}

private:

	typedef std::map< std::string, boost::property_tree::ptree::iterator > CardContainer;

	boost::property_tree::ptree	m_levels;	///< Holds all detail level definitions.
	CardContainer				m_cards;	///< Holds all graphic cards.
	int							m_level;	///< The current level, or negative value if none.
	std::string					m_card;		///< The current graphic card, or empty if none.

	void loadLevels();	///< Helper that load the level definitions.
};



} // namespace engine

} // namespace vge



#endif // _VGE_ENGINE_USERSETTINGS_HPP_
