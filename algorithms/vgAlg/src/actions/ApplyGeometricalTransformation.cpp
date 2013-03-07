// VGSDK - Copyright (C) 2010, 2013, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson


#include "vgAlg/actions/ApplyGeometricalTransformation.hpp"

#include <vgAlg/actions/SelectedNode.hpp>

#include <vge/technique/ApplyGeometricalTransformations.hpp>
#include <vge/engine/Engine.hpp>



namespace vgAlg
{

namespace actions
{



ApplyGeometricalTransformation::ApplyGeometricalTransformation()
{

}



void ApplyGeometricalTransformation::execute()
{
	using vge::visitor::NodeCollectorExtended;
	vge::technique::ApplyGeometricalTransformations technique;
	vge::engine::Engine* engine = new vge::engine::Engine();
	NodeCollectorExtended<> collector( true, false, NodeCollectorExtended<>::IGNORE_KIT );
	m_root->traverse( collector );
	technique.setParameters( engine, collector.getTraverseElements() );
	technique.apply( engine, collector.getTraverseElements() );

	vgAlg::actions::SelectedNode::getSelectedNodeObject()->setAction( REFRESH );
}



} // namespace actions

} // namespace vgAlg
