// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson


#include "vgGTK/ActionsRegistry.hpp"

#include <vgAlg/actions/SelectedNode.hpp>

#include <vgUI/actions/ApplyGeometricalTransformation.hpp>
#include <vgUI/actions/CopyNode.hpp>
#include <vgUI/actions/CutNode.hpp>
#include <vgUI/actions/ExpandSubTree.hpp>
#include <vgGTK/actions/ui/ExportNodeUI.hpp>
#include <vgUI/actions/GetNodeInTree.hpp>
#include <vgUI/actions/HideAllExceptSelectedNode.hpp>
#include <vgUI/actions/HideAllNode.hpp>
#include <vgUI/actions/HideNode.hpp>
#include <vgUI/actions/InvertNormalOrientation.hpp>
#include <vgUI/actions/InvertTriangleOrientation.hpp>
#include <vgUI/actions/NextNode.hpp>
#include <vgUI/actions/PasteNode.hpp>
#include <vgUI/actions/PreviousNode.hpp>
#include <vgGTK/actions/ui/RemoveNodeUI.hpp>
#include <vgUI/actions/SetOptionalToDefault.hpp>
#include <vgUI/actions/SetToDefault.hpp>
#include <vgUI/actions/ShowAllHiddenNode.hpp>
#include <vgUI/actions/ShowNode.hpp>

namespace vgGTK
{


ActionsRegistry::ActionsRegistry( )
{
	using namespace vgUI::actions;
	//@todo auto generate list from files.
	m_actionList.push_back( vgd::makeShp( new ApplyGeometricalTransformation() ) );
	m_actionList.push_back( vgd::makeShp( new CopyNode() ) );
	m_actionList.push_back( vgd::makeShp( new CutNode() ) );
	m_actionList.push_back( vgd::makeShp( new ExpandSubTree() ) );
	m_actionList.push_back( vgd::makeShp( new vgGTK::actions::ui::ExportNodeUI() ) );
	m_actionList.push_back( vgd::makeShp( new GetNodeInTree() ) );
	m_actionList.push_back( vgd::makeShp( new HideAllExceptSelectedNode() ) );
	m_actionList.push_back( vgd::makeShp( new HideAllNode() ) );
	m_actionList.push_back( vgd::makeShp( new HideNode() ) );
	m_actionList.push_back( vgd::makeShp( new InvertNormalOrientation() ) );
	m_actionList.push_back( vgd::makeShp( new InvertTriangleOrientation() ) );
	m_actionList.push_back( vgd::makeShp( new NextNode() ) );
	m_actionList.push_back( vgd::makeShp( new PasteNode() ) );
	m_actionList.push_back( vgd::makeShp( new PreviousNode() ) );
	m_actionList.push_back( vgd::makeShp( new vgGTK::actions::ui::RemoveNodeUI() ) );
	m_actionList.push_back( vgd::makeShp( new SetOptionalToDefault() ) );
	m_actionList.push_back( vgd::makeShp( new SetToDefault() ) );
	m_actionList.push_back( vgd::makeShp( new ShowAllHiddenNode() ) );
}



ActionsRegistry::~ActionsRegistry( )
{
	m_actionList.clear();
	m_hiddenNodeMap.clear();
}



std::list< vgd::Shp< vgUI::actions::IActionUI > > ActionsRegistry::getActionList() const
{
	return m_actionList;
}



void ActionsRegistry::addAction( vgd::Shp< vgUI::actions::IActionUI > action)
{
	m_actionList.push_back( action );
}



vgd::Shp< vgUI::actions::IActionUI > ActionsRegistry::getAction( std::string id )
{
	vgd::Shp< vgUI::actions::IActionUI > retVal;
	std::list< vgd::Shp< vgUI::actions::IActionUI > >::iterator it = m_actionList.begin();
	for( it; it != m_actionList.end(); it++ )
	{
		if( (*it)->getId() == id )
		{
			retVal = (*it);
			return retVal;
		}
	}
	
	return retVal;
}



std::list< vgd::Shp< vgUI::actions::IActionUI > > ActionsRegistry::getHiddenNodeActionList()
{
	std::list< vgd::Shp< vgUI::actions::IActionUI > > hiddenNodeActionList;

	vgd::Shp< std::list< vgd::Shp< vgAlg::actions::HiddenNode > > > hiddenNodes = vgAlg::actions::SelectedNode::getSelectedNodeObject()->getHiddenNodeList();

	std::list< vgd::Shp < vgAlg::actions::HiddenNode > >::iterator it = hiddenNodes->begin();
	for( it; it != hiddenNodes->end(); it++ )
	{
		if( m_hiddenNodeMap.count( (*it) ) == 0 )
		{
			vgd::Shp< vgUI::actions::IActionUI > action = vgd::makeShp( new vgUI::actions::ShowNode( (*it) ) );
			hiddenNodeActionList.push_back( action );
			m_hiddenNodeMap[ (*it) ] = action;
		}
	}

	return hiddenNodeActionList;
}



} // namespace vgGTK
