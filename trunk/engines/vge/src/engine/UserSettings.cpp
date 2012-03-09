// VGSDK - Copyright (C) 2010, 2011, 2012, Guillaume Brocker, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#include "vge/engine/UserSettings.hpp"

#include <algorithm>
#include <string>

#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/algorithm/string/trim.hpp>

#include <sbf/pkg/Module.hpp>

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
	bpt::ptree::const_iterator i = m_levels.begin();

	if ( m_level < m_levels.size() )
	{
		std::advance( i, m_level );
	}

	// Gathers definitions from selected level and apply them.
	using namespace vgd::node;

	const LightModel::ShadowValueType			shadow			( getTreeAttributeAsEnum< LightModel::ShadowValueType >(i->second, "shadow")					);
	const LightModel::ShadowFilteringValueType	shadowFiltering	( getTreeAttributeAsEnum< LightModel::ShadowFilteringValueType >(i->second, "shadowFiltering")	);
	const LightModel::ShadowMapSizeValueType	shadowMapSize	( getTreeAttributeAsEnum< LightModel::ShadowMapSizeValueType >(i->second, "shadowMapSize")		);
	const LightModel::ShadowMapTypeValueType	shadowMapType	( getTreeAttributeAsEnum< LightModel::ShadowMapTypeValueType >(i->second, "shadowMapType")		);

	if( shadow.isValid() )			lightModel->setShadow( shadow );
	if( shadowFiltering.isValid() )	lightModel->setShadowFiltering( shadowFiltering );
	if( shadowMapSize.isValid() )	lightModel->setShadowMapSize( shadowMapSize );
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
	const bfs::path	path = sbf::pkg::Module::get()->getPath(sbf::pkg::SharePath) / "user-settings.ini";

	try
	{
		// Loads the detail level defitions.
		bpt::ini_parser::read_ini( path.string(), m_levels );

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
		vgLogError( "Error while reading detail level definitions file %s", path.string().c_str() );
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

	LightModel::ShadowValueType				nodeShadow;
	LightModel::ShadowFilteringValueType	nodeShadowFiltering;
	LightModel::ShadowMapSizeValueType		nodeShadowMapSize;
	LightModel::ShadowMapTypeValueType		nodeShadowMapType;

	lightModel->getShadow( nodeShadow );
	lightModel->getShadowFiltering( nodeShadowFiltering );
	lightModel->getShadowMapSize( nodeShadowMapSize );
	nodeShadowMapType = lightModel->getShadowMapType();


	// Walks through levels.
	namespace bpt = boost::property_tree;

	for( bpt::ptree::const_iterator	i = m_levels.begin(); i != m_levels.end(); ++i )
	{
		const LightModel::ShadowValueType			levelShadow				( getTreeAttributeAsEnum< LightModel::ShadowValueType >(i->second, "shadow")					);
		const LightModel::ShadowFilteringValueType	levelShadowFiltering	( getTreeAttributeAsEnum< LightModel::ShadowFilteringValueType >(i->second, "shadowFiltering")	);
		const LightModel::ShadowMapSizeValueType	levelShadowMapSize		( getTreeAttributeAsEnum< LightModel::ShadowMapSizeValueType >(i->second, "shadowMapSize")		);
		const LightModel::ShadowMapTypeValueType	levelShadowMapType		( getTreeAttributeAsEnum< LightModel::ShadowMapTypeValueType >(i->second, "shadowMapType")		);


		// Tests if the current level matches the light model settings.
		bool	matches = true;

		if( levelShadow.isValid() )				matches = matches && levelShadow == nodeShadow ;
		if( levelShadowFiltering.isValid() )	matches = matches && levelShadowFiltering == nodeShadowFiltering ;
		if( levelShadowMapSize.isValid() )		matches = matches && levelShadowMapSize == nodeShadowMapSize;
		if( levelShadowMapType.isValid() )		matches = matches && levelShadowMapType == nodeShadowMapType;


		// If the current level is matching, assignes it.
		if( matches )
		{
			bpt::ptree::const_iterator	begin = m_levels.begin();

			setLevel( std::distance(begin, i) );
			break;
		}
	}
}



} // namespace engine

} // namespace vge
