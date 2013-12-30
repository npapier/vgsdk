// VGSDK - Copyright (C) 2010, 2011, 2012, 2013, Guillaume Brocker, Nicolas Papier.
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
#include <vgd/node/Antialiasing.hpp>
#include <vgd/node/EngineProperties.hpp>
#include <vgd/node/LightModel.hpp>
#include <vgd/node/TessellationLevel.hpp>
#include <vgd/node/TessellationProperties.hpp>

#include "vge/engine/SceneManager.hpp"
#include "vgm/operations.hpp"



namespace vge
{

namespace engine
{



namespace
{

template< typename EnumType >
const EnumType getTreeAttributeAsEnum( const boost::property_tree::ptree & ptree, const std::string & attrName )
{
	const std::string attrStr = ptree.get< std::string >( attrName, std::string() );

	return EnumType().fromString(attrStr);
}

const float getTreeAttributeAsFloat( const boost::property_tree::ptree & ptree, const std::string & attrName )
{
	const float retVal = ptree.get< float >( attrName );
	return retVal;
}

const bool getTreeAttributeAsBool( const boost::property_tree::ptree & ptree, const std::string & attrName )
{
	const bool retVal = ptree.get< bool >( attrName );
	return retVal;
}

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



UserSettings::UserSettings( const vgd::Shp< const vge::engine::SceneManager > sm )
:	m_level( -1 )
{
	loadLevels();
	setLevel( sm );
}



const UserSettings & UserSettings::apply( vge::engine::SceneManager & sm ) const
{
	namespace bpt = boost::property_tree;

	// Skips when no level has been set.
	if( m_level == -1 )
	{
		return *this;
	}

	// Moves to the right sub-tree.
	bpt::ptree::const_iterator i = m_levels.begin();

	if ( static_cast<uint>(m_level) < m_levels.size() )
	{
		std::advance( i, m_level );
	}

	// Gathers definitions from selected level
	using vgd::node::Antialiasing;
	using vgd::node::EngineProperties;
	using vgd::node::LightModel;
	using vgd::node::TessellationLevel;
	using vgd::node::TessellationProperties;


	//	shadow related values
	const LightModel::ShadowValueType				shadow			( getTreeAttributeAsEnum< LightModel::ShadowValueType >(i->second, "shadow")					);
	const LightModel::ShadowFilteringValueType		shadowFiltering	( getTreeAttributeAsEnum< LightModel::ShadowFilteringValueType >(i->second, "shadowFiltering")	);
	const LightModel::ShadowMapSizeValueType		shadowMapSize	( getTreeAttributeAsEnum< LightModel::ShadowMapSizeValueType >(i->second, "shadowMapSize")		);
	const LightModel::ShadowMapTypeValueType		shadowMapType	( getTreeAttributeAsEnum< LightModel::ShadowMapTypeValueType >(i->second, "shadowMapType")		);

	//	maximum anisotropy value
	const EngineProperties::MaxAnisotropyValueType	maxAnisotropy	( getTreeAttributeAsFloat(i->second, "maxAnisotropy") );

	//	antialiasing technique
	const Antialiasing::TechniqueValueType			aaTechnique		( getTreeAttributeAsEnum< Antialiasing::TechniqueValueType >(i->second, "antialiasing")			);

	//	bumpmapping
	const LightModel::BumpMappingValueType			bumpmapping		( getTreeAttributeAsBool(i->second, "bumpmapping") 												);

	//	tessellation
	//	tessellation properties
	const TessellationProperties::TessellationValueType		tessellation				( getTreeAttributeAsEnum< TessellationProperties::TessellationValueType >(i->second, "tessellation")	);
	const float												tessellationRangeMin		( getTreeAttributeAsFloat(i->second, "tessellationRangeMin")											);
	const float												tessellationRangeMax		( getTreeAttributeAsFloat(i->second, "tessellationRangeMax")											);
	const float												tessellationPixelsPerEdge	( getTreeAttributeAsFloat(i->second, "tessellationPixelsPerEdge")										);
	//	tessellation level
	const TessellationLevel::MethodValueType				tessellationMethod			( getTreeAttributeAsEnum< TessellationLevel::MethodValueType >(i->second, "tessellationMethod")			);

	// Retrieves several nodes used to apply user settings to scene graph
	vgd::Shp< Antialiasing >			antialiasing		= sm.findFirstByType< Antialiasing >();
	vgd::Shp< EngineProperties >		engineProperties	= sm.findFirstByType< EngineProperties >();
	vgd::Shp< LightModel >				lightModel			= sm.findFirstByType< LightModel >();
	vgd::Shp< TessellationProperties >	tessProperties		= sm.findFirstByType< TessellationProperties >();
	vgd::Shp< TessellationLevel >		tessLevel			= sm.findFirstByType< TessellationLevel >();

	//	shadow settings and bump mapping
	if ( lightModel )
	{
		if( shadow.isValid() )			lightModel->setShadow( shadow );
		if( shadowFiltering.isValid() )	lightModel->setShadowFiltering( shadowFiltering );
		if( shadowMapSize.isValid() )	lightModel->setShadowMapSize( shadowMapSize );
		if( shadowMapType.isValid() )	lightModel->setShadowMapType( shadowMapType );

		lightModel->setBumpMapping( bumpmapping );
	}
	else
	{
		vgAssert( "No LightModel node in scene graph." );
	}

	//	maximum anisotropy
	if ( engineProperties )
	{
		engineProperties->setMaxAnisotropy( maxAnisotropy );
	}
	else
	{
		vgAssert( "No EngineProperties node in scene graph." );
	}

	//	antialiasing
	if ( antialiasing )
	{
		if ( aaTechnique.isValid() )
		{
			antialiasing->setTechnique( aaTechnique );
		}
	}
	else
	{
		vgAssert( "No Antialiasing node in scene graph." );
	}

	//	tessellation
	if ( tessProperties )
	{
		if ( tessellation.isValid() )		tessProperties->setTessellation( tessellation );
		tessProperties->setRange( vgm::Vec2f(tessellationRangeMin, tessellationRangeMax) );
		tessProperties->setPixelsPerEdge( tessellationPixelsPerEdge );
	}

	if ( tessLevel )
	{
		if ( tessellationMethod.isValid() )		tessLevel->setMethod( tessellationMethod );
	}

	// Job's done.
	return *this;
}



const UserSettings & UserSettings::apply( vgd::Shp< vge::engine::SceneManager > sm ) const
{
	return apply( *(sm.get()) );
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



UserSettings & UserSettings::setGraphicCard( const std::string & card )
{
	CardContainer::iterator found = m_cards.find(card);

	if( found != m_cards.end() )
	{
		m_level = std::distance( m_levels.begin(), found->second );
		m_card  = card;
	}
	return *this;
}



UserSettings & UserSettings::setLevel( const int level )
{
	if( level >= -1 )
	{
		m_level = vgm::clamp(level, -1, static_cast< int >(m_levels.size())-1 );
		m_card.clear();
	}
	return *this;
}



UserSettings & UserSettings::setLevel( const vge::engine::SceneManager & sm )
{
	using vgd::node::Antialiasing;
	using vgd::node::EngineProperties;
	using vgd::node::LightModel;
	using vgd::node::TessellationProperties;
	using vgd::node::TessellationLevel;

	// Retrieves several nodes
	vgd::Shp< Antialiasing >			antialiasing		= sm.findFirstByType< Antialiasing >();
	vgd::Shp< EngineProperties >		engineProperties	= sm.findFirstByType< EngineProperties >();
	vgd::Shp< LightModel >				lightModel			= sm.findFirstByType< LightModel >();
	vgd::Shp< TessellationProperties >	tessProperties		= sm.findFirstByType< TessellationProperties >();
	vgd::Shp< TessellationLevel >		tessLevel			= sm.findFirstByType< TessellationLevel >();

	if( !antialiasing || !engineProperties || !lightModel || !tessProperties || !tessLevel )
	{
		setLevel( -1 );
		return *this;
	}

	// Gathers node settings
	bool isDefined;

	//	shadow and bump mapping related values
	LightModel::ShadowValueType				nodeShadow;
	LightModel::ShadowFilteringValueType	nodeShadowFiltering;
	LightModel::ShadowMapSizeValueType		nodeShadowMapSize;
	LightModel::ShadowMapTypeValueType		nodeShadowMapType;

	isDefined = lightModel->getShadow( nodeShadow );
	isDefined = isDefined && lightModel->getShadowFiltering( nodeShadowFiltering );
	isDefined = isDefined && lightModel->getShadowMapSize( nodeShadowMapSize );
	nodeShadowMapType = lightModel->getShadowMapType();

	//	maximum anisotropy value
	EngineProperties::MaxAnisotropyValueType	nodeMaxAnisotropy;
	isDefined = isDefined && engineProperties->getMaxAnisotropy( nodeMaxAnisotropy );

	//	antialiasing technique
	const Antialiasing::TechniqueValueType	nodeAaTechnique = antialiasing->getTechnique();

	//	bumpmapping
	LightModel::BumpMappingValueType		nodeBumpMapping = lightModel->getBumpMapping();

	//	tessellation
	//	tessellation properties
	TessellationProperties::TessellationValueType nodeTessellation;
	isDefined = tessProperties->getTessellation( nodeTessellation );

	vgm::Vec2f nodeTessellationRange;
	isDefined = isDefined && tessProperties->getRange( nodeTessellationRange );

	float nodeTessellationPixelsPerEdge;
	isDefined = isDefined && tessProperties->getPixelsPerEdge( nodeTessellationPixelsPerEdge );

	//	tessellation level
	TessellationLevel::MethodValueType nodeTessellationMethod = tessLevel->getMethod();

	if (!isDefined)
	{
		return *this;
	}

	// Walks through levels.
	namespace bpt = boost::property_tree;

	for( bpt::ptree::const_iterator	i = m_levels.begin(); i != m_levels.end(); ++i )
	{
		//	shadow and bump mapping related values
		const LightModel::ShadowValueType				levelShadow			( getTreeAttributeAsEnum< LightModel::ShadowValueType >(i->second, "shadow")					);
		const LightModel::ShadowFilteringValueType		levelShadowFiltering( getTreeAttributeAsEnum< LightModel::ShadowFilteringValueType >(i->second, "shadowFiltering")	);
		const LightModel::ShadowMapSizeValueType		levelShadowMapSize	( getTreeAttributeAsEnum< LightModel::ShadowMapSizeValueType >(i->second, "shadowMapSize")		);
		const LightModel::ShadowMapTypeValueType		levelShadowMapType	( getTreeAttributeAsEnum< LightModel::ShadowMapTypeValueType >(i->second, "shadowMapType")		);

		//	maximum anisotropy value
		const EngineProperties::MaxAnisotropyValueType	levelMaxAnisotropy	( getTreeAttributeAsFloat(i->second, "maxAnisotropy") );

		//	antialiasing technique
		const Antialiasing::TechniqueValueType			levelAaTechnique	( getTreeAttributeAsEnum< Antialiasing::TechniqueValueType >(i->second, "antialiasing")	);

		//	bumpmapping
		const LightModel::BumpMappingValueType			levelBumpmapping	( getTreeAttributeAsBool(i->second, "bumpmapping") 												);

		//	tessellation
		//	tessellation properties
		const TessellationProperties::TessellationValueType		levelTessellation				( getTreeAttributeAsEnum< TessellationProperties::TessellationValueType >(i->second, "tessellation")	);
		const float												levelTessellationRangeMin		( getTreeAttributeAsFloat(i->second, "tessellationRangeMin")											);
		const float												levelTessellationRangeMax		( getTreeAttributeAsFloat(i->second, "tessellationRangeMax")											);
		const float												levelTessellationPixelsPerEdge	( getTreeAttributeAsFloat(i->second, "tessellationPixelsPerEdge")										);

		//	tessellation level
		const TessellationLevel::MethodValueType				levelTessellationMethod			( getTreeAttributeAsEnum< TessellationLevel::MethodValueType >(i->second, "tessellationMethod")			);

		// Tests if the current level matches the nodes settings.
		bool	matches = true;

		//	shadow
		if( levelShadow.isValid() )				matches = matches && levelShadow == nodeShadow ;
		if( levelShadowFiltering.isValid() )	matches = matches && levelShadowFiltering == nodeShadowFiltering ;
		if( levelShadowMapSize.isValid() )		matches = matches && levelShadowMapSize == nodeShadowMapSize;
		if( levelShadowMapType.isValid() )		matches = matches && levelShadowMapType == nodeShadowMapType;

		//	maximum anisotropy
		matches = matches && levelMaxAnisotropy == nodeMaxAnisotropy;

		//	antialiasing
		if( levelAaTechnique.isValid() )		matches = matches && levelAaTechnique == nodeAaTechnique;

		//	bump mapping
		matches = matches && levelBumpmapping == nodeBumpMapping;

		//	tessellation
		//	tessellation properties
		if( levelTessellation.isValid() )		matches = matches && levelTessellation == nodeTessellation;
		matches = matches && vgm::Vec2f(levelTessellationRangeMin, levelTessellationRangeMax) == nodeTessellationRange;
		matches = matches && levelTessellationPixelsPerEdge == nodeTessellationPixelsPerEdge;

		//	tessellation level
		if( levelTessellationMethod.isValid() )		matches = matches && levelTessellationMethod == nodeTessellationMethod;

		// If the current level is matching, assignes it.
		if( matches )
		{
			bpt::ptree::const_iterator	begin = m_levels.begin();

			setLevel( std::distance(begin, i) );
			return *this;
		}
	}

	// Job's done.
	setLevel( -1 );
	return *this;
}



UserSettings & UserSettings::setLevel( const vgd::Shp< const vge::engine::SceneManager > sm )
{
	return setLevel( *(sm.get()) );
}



UserSettings & UserSettings::setMaxLevel()
{
	if( m_levels.size() > 0 )
	{
		m_level = m_levels.size() - 1;
	}
	return *this;
}



} // namespace engine

} // namespace vge
