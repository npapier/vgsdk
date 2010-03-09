// VGSDK - Copyright (C) 2010, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGE_ENGINE_USERSETTINGS_HPP_
#define _VGE_ENGINE_USERSETTINGS_HPP_

#include <map>
#include <string>
#include <boost/property_tree/ptree.hpp>

#include <vge/vge.hpp>



namespace vge
{

namespace engine
{



/**
 * @brief	Allows to configure a scene using several levels.
 */
struct VGE_API UserSettings
{
	/**
	 * @brief	Constructor
	 */
	UserSettings();

	/**
	 * @brief	Retrieves the description of a given level.
	 *
	 * @return	a string, empty if no description or if the level is invalid
	 */
	const std::string getDescription( const unsigned int level ) const;

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

		for( CardsContainer::const_iterator i = m_cards.begin(); i != m_cards.end(); ++i )
		{
			result.insert( result.end(), i->first );
		}

		return result;
	}

	/**
	 * @brief	Assigns a new detail level.
	 */
	void setLevel( const int level );

	/**
	 * @brief	Assigns a graphic card that will be used to determine the appropriate defailt level
	 */
	void setGraphicCard( const std::string & card );

private:

	typedef std::map< std::string, bpt::ptree::iterator > CardsContainer;

	boost::property_tree::ptree	m_levels;	///< Holds all detail level definitions.
	CarsContainer				m_cards;	///< Holds all graphic cards.
	int							m_level;	///< The current level, or negative value if none.

};



} // namespace engine

} // namespace vge



#endif // _VGE_ENGINE_USERSETTINGS_HPP_
