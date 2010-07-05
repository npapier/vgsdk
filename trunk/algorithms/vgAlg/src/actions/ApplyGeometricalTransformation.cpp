// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson


#include "vgAlg/actions/ApplyGeometricalTransformation.hpp"

#include <vgAlg/actions/SelectedNode.hpp>

#include <vge/technique/ApplyGeometricalTransformations.hpp>
#include <vgeGL/engine/Engine.hpp>

#include <vgDebug/convenience.hpp>

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
	vgeGL::engine::Engine* engine = new vgeGL::engine::Engine();
	NodeCollectorExtended<> collector( true, false, NodeCollectorExtended<>::IGNORE_KIT );
	m_root->traverse( collector );
	technique.apply( engine, collector.getTraverseElements() );

	vgAlg::actions::SelectedNode::getSelectedNodeObject()->setAction( vgAlg::actions::REFRESH );
}



} // namespace actions

} // namespace vgAlg
