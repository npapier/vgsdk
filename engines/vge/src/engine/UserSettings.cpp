// VGSDK - Copyright (C) 2010, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#include "vge/engine/UserSettings.hpp"

#include <algorithm>
#include <string>

#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/algorithm/string/trim.hpp>

#include <sbf/path.hpp>

#include <vgDebug/convenience.hpp>
#include <vgd/field/Enum.hpp>
#include <vgd/node/LightModel.hpp>

#include "vge/engine/SceneManager.hpp"



namespace vge
{

namespace engine
{



template< typename EnumType >
const EnumType getTreeAttributeAsEnum( const boost::property_tree::ptree & ptree, const std::string & attrName )
{
	const std::string attrStr = ptree.get< std::string >( attrName, std::string() );

	return EnumType().fromString(attrStr);
}



UserSettings::UserSettings()
:	m_level( -1 )
{
	loadLevels();
}



UserSettings::UserSettings( const UserSettings & other )
:	m_level( other.m_level ),
	m_card( other.m_card )
{
	loadLevels();
}



UserSettings::UserSettings( const vge::engine::SceneManager & sm )
:	m_level( -1 )
{
	loadLevels();
	setLevel( sm );
}



void UserSettings::apply( vge::engine::SceneManager & sm ) const
{
	namespace bpt = boost::property_tree;

	// Skips when no level has been set.
	if( m_level == -1 )
	{
		return;
	}


	// Skips when no light model node has been found.
	vgd::Shp< vgd::node::LightModel >	lightModel = sm.findFirstByType< vgd::node::LightModel >();
	
	if( !lightModel )
	{
		return;
	}


	// Moves to the right sub-tree.
	bpt::ptree::const_iterator	i = m_levels.begin();
	std::advance( i, m_level );

	assert( i != m_levels.end() );

	// Gathers definitions from selected level and apply them.
	using namespace vgd::node;

	const LightModel::ShadowValueType			shadow( getTreeAttributeAsEnum< LightModel::ShadowValueType >(i->second, "shadow") );
	const LightModel::ShadowQualityValueType	shadowQuality( getTreeAttributeAsEnum< LightModel::ShadowQualityValueType >(i->second, "shadowQuality") );
	const LightModel::ShadowMapTypeValueType	shadowMapType( getTreeAttributeAsEnum< LightModel::ShadowMapTypeValueType >(i->second, "shadowMapType") );

	if( shadow.isValid() )			lightModel->setShadow( shadow );
	if( shadowQuality.isValid() )	lightModel->setShadowQuality( shadowQuality );
	if( shadowMapType.isValid() )	lightModel->setShadowMapType( shadowMapType );
}



const std::string UserSettings::getName( const unsigned int level ) const
{
	namespace bpt = boost::property_tree;

	bpt::ptree::const_iterator	i = m_levels.begin();
	
	// Moves to the appropriate node and if one, gets the description.
	std::advance( i, level );
	if( i != m_levels.end() )
	{
		return i->first;
	}
	else
	{
		return std::string();
	}
}



const std::string UserSettings::getDescription( const unsigned int level ) const
{
	namespace bpt = boost::property_tree;

	bpt::ptree::const_iterator	i = m_levels.begin();
	
	// Moves to the appropriate node and if one, gets the description.
	std::advance( i, level );
	if( i != m_levels.end() )
	{
		return i->second.get<std::string>( "description", std::string() );
	}
	else
	{
		return std::string();
	}
}



const std::string UserSettings::getGraphicCard() const
{
	return m_card;
}



const int UserSettings::getLevel() const
{
	return m_level;
}



const int UserSettings::getLevelCount() const
{
	return m_levels.size();
}



void UserSettings::loadLevels()
{
	namespace bfs = boost::filesystem;
	namespace bpt = boost::property_tree;
	
	// Gets the path of the detail level definitions.
	const bfs::path	path = sbf::path::get(sbf::path::Share) / "user-settings.ini";

	try
	{
		// Loads the detail level defitions.
		bpt::ini_parser::read_ini( path.file_string(), m_levels );

		// Walks through levels to collect graphic cards.
		for( bpt::ptree::iterator i = m_levels.begin(); i != m_levels.end(); ++i )
		{
			std::string	cardNames = i->second.get<std::string>( "cards", std::string() );

			while( ! cardNames.empty() )
			{
				const std::string::size_type	comaIndex	= cardNames.find( ',' );
				const std::string				card		= boost::algorithm::trim_copy( cardNames.substr(0, comaIndex) );
				
				m_cards[ card ] = i;
				cardNames = (comaIndex == std::string::npos) ? std::string() : cardNames.substr(comaIndex+1);
			}
		}
	}
	catch( bpt::ini_parser::ini_parser_error & )
	{
		vgLogError2( "Error while reading detail level definitions file %s", path.native_file_string().c_str() );
	}
}



void UserSettings::setGraphicCard( const std::string & card )
{
	CardContainer::iterator found = m_cards.find(card);

	if( found != m_cards.end() )
	{
		m_level = std::distance( m_levels.begin(), found->second );
		m_card  = card;
	}
}



void UserSettings::setLevel( const int level )
{
	if( level >= -1 && level < static_cast< int >(m_levels.size()) )
	{
		m_level = level;
		m_card.clear();
	}
}



void UserSettings::setLevel( const vge::engine::SceneManager & sm )
{
	// Gathers the light model node.
	vgd::Shp< vgd::node::LightModel >	lightModel = sm.findFirstByType< vgd::node::LightModel >();
	
	if( !lightModel )
	{
		setLevel( -1 );
		return;
	}


	// Gathers node settings.
	using vgd::node::LightModel;

	LightModel::ShadowValueType			nodeShadow;
	LightModel::ShadowQualityValueType	nodeShadowQuality;
	LightModel::ShadowMapTypeValueType	nodeShadowMapType;

	lightModel->getShadow( nodeShadow );
	lightModel->getShadowQuality( nodeShadowQuality );
	nodeShadowMapType = lightModel->getShadowMapType();

	
	// Walks through levels.
	namespace bpt = boost::property_tree;

	for( bpt::ptree::const_iterator	i = m_levels.begin(); i != m_levels.end(); ++i )
	{
		// Gathers current level settings.
		const LightModel::ShadowValueType			levelShadow( getTreeAttributeAsEnum< LightModel::ShadowValueType >(i->second, "shadow") );
		const LightModel::ShadowQualityValueType	levelShadowQuality( getTreeAttributeAsEnum< LightModel::ShadowQualityValueType >(i->second, "shadowQuality") );
		const LightModel::ShadowMapTypeValueType	levelShadowMapType( getTreeAttributeAsEnum< LightModel::ShadowMapTypeValueType >(i->second, "shadowMapType") );


		// Tests if the current level matches the light model settings.
		bool	matches = true;

		if( levelShadow.isValid() )			matches = matches && levelShadow == nodeShadow ;
		if( levelShadowQuality.isValid() )	matches = matches && levelShadowQuality == nodeShadowQuality;
		if( levelShadowMapType.isValid() )	matches = matches && levelShadowMapType == nodeShadowMapType;


		// If the current level is matching, assignes it.
		if( matches )
		{
			bpt::ptree::const_iterator	begin = m_levels.begin();

			setLevel( std::distance(begin, i) );
			break;
		}
	}
}



const UserSettings & UserSettings::operator=( const UserSettings & other )
{
	if( &other != this )
	{
		m_level = other.m_level;
		m_card  = other.m_card;
	}

	return *this;
}



} // namespace engine

} // namespace vge
