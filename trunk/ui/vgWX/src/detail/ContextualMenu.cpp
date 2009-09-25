// VGSDK - Copyright (C) 2006, 2007, 2008, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgWX/detail/ContextualMenu.hpp"

#include <wx/menu.h>

#include <vgAlg/node/TriSet.hpp>
#include <vgd/node/DrawStyle.hpp>
#include <vgd/node/Kit.hpp>
#include <vgd/node/LightModel.hpp>
#include <vgd/node/TriSet.hpp>
#include <vgd/visitor/helpers.hpp>
#include <vgd/visitor/predicate/ByKindOfType.hpp>
#include <vgeGL/engine/Engine.hpp>
#include <vgeGL/technique/Main.hpp>
//#include <vgeGL/technique/MainGLSL.hpp>
#include <vgTrian/Loader.hpp>

#include "vgWX/BasicViewer.hpp"



namespace vgWX
{

namespace detail
{

namespace
{

vgd::Shp< vgd::node::TriSet > extractTriSet( vgd::Shp< vgd::node::Node > shape )
{
	using vgd::node::Kit;
	using vgd::node::TriSet;

	vgd::Shp< TriSet > triset;

	if ( shape->isAKindOf< Kit >() )
	{
		// Gets root node of kit
		vgd::Shp< Kit > kit = vgd::dynamic_pointer_cast< Kit >( shape );
		vgd::Shp< vgd::node::Group > root = kit->getRoot();

		// Searches first triset node
		vgd::visitor::predicate::ByKindOfType< TriSet > predicate;

		triset = vgd::visitor::findFirst< TriSet >( root, predicate );

//		vgd::Shp< vgd::node::Node > result = root->findFirst( predicate );
//	
//		if ( result != 0 )
//		{
//			triset = vgd::dynamic_pointer_cast< TriSet >( result );
//		}
//		// else nothing to do
	}
	else
	{
		triset = vgd::dynamic_pointer_cast< TriSet >( shape );
	}
	
	return triset;
}

}



wxMenu *createContextualMenu( const Canvas * canvas )
{
	using namespace vgd::node;
	
	wxMenu *ctxMenu = new wxMenu;
	
	bool isDefined;
	wxMenu *subMenu;

	// Write scene graph
	
	ctxMenu->Append( wxID_CTX_WRITEGRAPHWIZ, _T("Write scene graph into sceneGraph.dot") );
	
	ctxMenu->AppendSeparator();

	// GLSL
	subMenu = new wxMenu;

	subMenu->AppendCheckItem( wxID_CTX_GLSL_ENABLE, _T("&GLSL usage enabled"), _T("vgsdk would use the Open(GL) (S)hading (L)anguage") ); 

	subMenu->Check( wxID_CTX_GLSL_ENABLE, canvas->getGLEngine()->isGLSLEnabled() );

	ctxMenu->Append( wxID_CTX_GLSL, _T("GLSL"), subMenu );

	ctxMenu->AppendSeparator();

	// ViewAll
	if ( dynamic_cast< const vgWX::BasicViewer * >( canvas ) )
	{
		ctxMenu->Append( wxID_CTX_VIEWALL, _T("&View all") );
		
		ctxMenu->AppendSeparator();
	}

/*	// Creates lighting menu
	subMenu = new wxMenu;

	subMenu->AppendRadioItem(	wxID_CTX_LIGHTING_FIXED_PIPELINE,
								_T("&Fixed pipeline"), _T("vgsdk would use the fixed OpenGL pipeline") );

	subMenu->AppendRadioItem(	wxID_CTX_LIGHTING_PROGRAMMABLE_PIPELINE,
								_T("&Programmable pipeline"), _T("vgsdk would use the programmable OpenGL pipeline (i.e. glsl)") );
	
	using vgeGL::technique::Main;
	
	const bool isMainTechnique = vgd::dynamic_pointer_cast< Main >( canvas->getPaintTechnique() );
	
	if ( isMainTechnique )
	{
		subMenu->Check( wxID_CTX_LIGHTING_FIXED_PIPELINE, true );
	}
	else
	{
		subMenu->Check( wxID_CTX_LIGHTING_PROGRAMMABLE_PIPELINE, true );
	}

	ctxMenu->Append( wxID_CTX_LIGHTING, _T("Lighting technique"), subMenu );
	
	ctxMenu->AppendSeparator();*/
	
	// DrawStyle
	subMenu = new wxMenu;

	vgd::Shp< DrawStyle > drawStyle( canvas->findFirstByType< DrawStyle >() );
		
	// drawStyle.shape

	subMenu->Append( wxID_CTX_DRAWSTYLE_NONE, _T("N&one"), _T("None"), wxITEM_CHECK );
	subMenu->Append( wxID_CTX_DRAWSTYLE_POINT, _T("&Point"), _T("Point"), wxITEM_CHECK );
	subMenu->Append( wxID_CTX_DRAWSTYLE_FLAT, _T("&Flat"), _T("Flat"), wxITEM_CHECK );
	subMenu->Append( wxID_CTX_DRAWSTYLE_SMOOTH, _T("&Smooth"), _T("Smooth"), wxITEM_CHECK );
	subMenu->Append( wxID_CTX_DRAWSTYLE_WIREFRAME, _T("&Wireframe"), _T("Wireframe"), wxITEM_CHECK );
	subMenu->Append( wxID_CTX_DRAWSTYLE_HIDDEN_LINE, _T("&Hidden line"), _T("Hidden line"), wxITEM_CHECK );
	subMenu->Append( wxID_CTX_DRAWSTYLE_FLAT_HIDDEN_LINE, _T("F&lat hidden line"), _T("Flat hidden line"), wxITEM_CHECK );
	subMenu->Append( wxID_CTX_DRAWSTYLE_SMOOTH_HIDDEN_LINE, _T("S&mooth hidden line"), _T("Smooth hidden line"), wxITEM_CHECK );
	subMenu->Append( wxID_CTX_DRAWSTYLE_NEIGHBOUR, _T("&Neighbour"), _T("Neighbour"), wxITEM_CHECK );

	if ( drawStyle.get() != 0 )
	{
		DrawStyle::ShapeValueType	shapeValue;
		
		isDefined = drawStyle->getShape( shapeValue );
		
		if ( isDefined )
		{
			subMenu->Check( wxID_CTX_DRAWSTYLE_NONE + shapeValue - DrawStyle::NONE, true );
		}
	}

	// drawStyle.normalLength
	subMenu->AppendSeparator();
	
	subMenu->Append( wxID_CTX_DRAWSTYLE_NORMALLENGTHNEGATIV, _T("-x"), _T("-x"), wxITEM_CHECK );	
	subMenu->Append( wxID_CTX_DRAWSTYLE_NORMALLENGTHMINUS8, _T("-8"), _T("-8"), wxITEM_CHECK );
	subMenu->Append( wxID_CTX_DRAWSTYLE_NORMALLENGTHMINUS4, _T("-4"), _T("-4"), wxITEM_CHECK );
	subMenu->Append( wxID_CTX_DRAWSTYLE_NORMALLENGTH0, _T("0"), _T("0"), wxITEM_CHECK );
	subMenu->Append( wxID_CTX_DRAWSTYLE_NORMALLENGTH4, _T("4"), _T("4"), wxITEM_CHECK );
	subMenu->Append( wxID_CTX_DRAWSTYLE_NORMALLENGTH8, _T("8"), _T("8"), wxITEM_CHECK );
	subMenu->Append( wxID_CTX_DRAWSTYLE_NORMALLENGTHPOSITIV, _T("+x"), _T("+x"), wxITEM_CHECK );
	
	if ( drawStyle.get() != 0 )
	{
		DrawStyle::NormalLengthValueType	normalLengthValue;
		
		isDefined = drawStyle->getNormalLength( normalLengthValue );
		
		if ( isDefined )
		{
			if ( normalLengthValue < -8 )
			{
				subMenu->Check( wxID_CTX_DRAWSTYLE_NORMALLENGTHNEGATIV, true );
			}
			else if ( normalLengthValue == -8 )
			{
				subMenu->Check( wxID_CTX_DRAWSTYLE_NORMALLENGTHMINUS8, true );
			}
			else if ( normalLengthValue == -4 )
			{
				subMenu->Check( wxID_CTX_DRAWSTYLE_NORMALLENGTHMINUS4, true );
			}
			else if ( normalLengthValue == 0 )
			{
				subMenu->Check( wxID_CTX_DRAWSTYLE_NORMALLENGTH0, true );
			}
			else if ( normalLengthValue == 4 )
			{
				subMenu->Check( wxID_CTX_DRAWSTYLE_NORMALLENGTH4, true );
			}
			else if ( normalLengthValue == 8 )
			{
				subMenu->Check( wxID_CTX_DRAWSTYLE_NORMALLENGTH8, true );
			}
			else if ( normalLengthValue > 8 )
			{
				subMenu->Check( wxID_CTX_DRAWSTYLE_NORMALLENGTHPOSITIV, true );
			}			
		}
	}

	// drawStyle.showOrientation
	subMenu->AppendSeparator();
	
	subMenu->Append( wxID_CTX_DRAWSTYLE_SHOWORIENTATION, _T("Show orientation"), _T("Show orientation"), wxITEM_CHECK );

	if ( drawStyle.get() != 0 )
	{
		DrawStyle::ShowOrientationValueType	showOrientationValue;
		
		isDefined = drawStyle->getShowOrientation( showOrientationValue );
		
		if ( isDefined )
		{
			subMenu->Check( wxID_CTX_DRAWSTYLE_SHOWORIENTATION, true );
		}
	}

	// drawStyle.boundingBox
	subMenu->AppendSeparator();
	
	subMenu->Append( wxID_CTX_DRAWSTYLE_NO_BOUNDING_BOX, _T("No bounding box"), _T("No bounding box"), wxITEM_CHECK );
	subMenu->Append( wxID_CTX_DRAWSTYLE_OBJECT_SPACE, _T("Object space bounding box"), 
		_T("Object space bounding box"), wxITEM_CHECK );
	subMenu->Append( wxID_CTX_DRAWSTYLE_AA_OBJECT_SPACE, _T("Axis aligned object space bounding box"), 
		_T("Axis aligned object space bounding box"), wxITEM_CHECK );
	subMenu->Append( wxID_CTX_DRAWSTYLE_OBJECT_AND_AA_OBJECT_SPACE, _T("Object and axis aligned object space bounding box"),
		_T("Object and axis aligned object space bounding box"), wxITEM_CHECK );

	if ( drawStyle.get() != 0 )
	{
		DrawStyle::BoundingBoxValueType bbValue;
		
		isDefined = drawStyle->getBoundingBox( bbValue );
		
		if ( isDefined )
		{
			subMenu->Check( wxID_CTX_DRAWSTYLE_NO_BOUNDING_BOX + bbValue - DrawStyle::NO_BOUNDING_BOX, true );
		}
	}
	
	//
	if ( drawStyle != 0 )
	{
		ctxMenu->Append( wxID_CTX_DRAWSTYLE, _T("Drawing style"), subMenu );
	}

	// LightModel
	ctxMenu->AppendSeparator();
	
	subMenu = new wxMenu;
	
	vgd::Shp< LightModel > lightModel ( canvas->findFirstByType< LightModel >() );

	// lightModel.model
	subMenu->Append( wxID_CTX_LIGHTMODEL_MODEL_LIGHTING_OFF, _T("Lighting off"), _T("Lighting off"), wxITEM_CHECK );
	subMenu->Append( wxID_CTX_LIGHTMODEL_MODEL_STANDARD_PER_VERTEX, _T("Standard per vertex"), _T("Standard per vertex"), 
		wxITEM_CHECK );
	subMenu->Append( wxID_CTX_LIGHTMODEL_MODEL_STANDARD_PER_PIXEL, _T("Standard per pixel"), _T("Standard per vertex")
		, wxITEM_CHECK );
		
	if ( lightModel.get() != 0 )
	{
		LightModel::ModelValueType modelValue;
		
		isDefined = lightModel->getModel( modelValue );
		
		if ( isDefined )
		{
			if(modelValue==LightModel::LIGHTING_OFF)
				subMenu->Check( wxID_CTX_LIGHTMODEL_MODEL_LIGHTING_OFF, true );
			else if (modelValue==LightModel::STANDARD_PER_VERTEX)
				subMenu->Check( wxID_CTX_LIGHTMODEL_MODEL_STANDARD_PER_VERTEX, true );
			else if(modelValue==LightModel::STANDARD_PER_PIXEL)
				subMenu->Check( wxID_CTX_LIGHTMODEL_MODEL_STANDARD_PER_PIXEL, true );
			else
				assert( false && "Unknown LightModel.model value." );
		}
	}		
	
	// lightModel.viewer	
	subMenu->AppendSeparator();
	subMenu->Append(wxID_CTX_LIGHTMODEL_VIEWER, _T("Local viewer"), _T("Local viewer"), wxITEM_CHECK );

	if ( lightModel.get() != 0 )
	{
		LightModel::ViewerValueType viewerValue;
		isDefined = lightModel->getViewer( viewerValue );
		
		if ( isDefined )
		{
			subMenu->Check( wxID_CTX_LIGHTMODEL_VIEWER, viewerValue == LightModel::AT_EYE );
		}
	}
	
	// lightModel.twoSided
	subMenu->AppendSeparator();
	subMenu->Append(wxID_CTX_LIGHTMODEL_TWOSIDED, _T("Two sided"), _T("Two sided"), wxITEM_CHECK );
	
	if ( lightModel.get() != 0 )
	{
		LightModel::TwoSidedValueType twosidedValue;
		isDefined = lightModel->getTwoSided( twosidedValue );
		
		if ( isDefined )
		{
			subMenu->Check( wxID_CTX_LIGHTMODEL_TWOSIDED, twosidedValue );
		}
	}

	//
	if ( lightModel != 0 )
	{
		ctxMenu->Append( wxID_CTX_LIGHTMODEL_MODEL, _T("Lighting model"), subMenu );	
	}

	return ctxMenu;
}



wxMenu *createContextualMenu( const Canvas * canvas, vgd::Shp< vgd::node::Node > shape )
{
	wxMenu *ctxMenu = new wxMenu;
	
	// ALGORITHMS & IO
	using vgd::node::TriSet;

	vgd::Shp< TriSet > triset = extractTriSet( shape );

	if ( triset )
	{
		ctxMenu->AppendCheckItem(	wxID_CTX_ALGORITHMS_INVERT_TRIANGLE_ORIENTATION,
									_T("&Invert triangle orientation"),
									_T("Invert triangle orientation of the selected shape.") );

		ctxMenu->AppendCheckItem(	wxID_CTX_IO_SAVETRIAN,
									_T("&Save triset.trian"),
									_T("Save triangle shape into triset.trian file.") );				
	}
	
	return ctxMenu;
}



void processContextualMenuEvent( Canvas * canvas, wxCommandEvent& event )
{
	using namespace vgd::node;

	switch ( event.GetId() )
	{
		// writeGraphviz
		case wxID_CTX_WRITEGRAPHWIZ:
			canvas->writeGraphviz( false );
			break;

		// GLSL
		case wxID_CTX_GLSL_ENABLE:
		{
			const bool isGLSLEnabled = canvas->getGLEngine()->isGLSLEnabled();
			
			canvas->getGLEngine()->setGLSLEnabled( !isGLSLEnabled );
			break;
		}

		// ViewAll
		case wxID_CTX_VIEWALL:
		{
			vgWX::BasicViewer *viewer = dynamic_cast< vgWX::BasicViewer * >( canvas );
			
			if ( viewer != 0 )
			{
				viewer->viewAll();
			}
			break;
		}

		/*// Lighting menu
		case wxID_CTX_LIGHTING_FIXED_PIPELINE:
		{
			using vgeGL::technique::Main;
			
			vgd::Shp< Main > fixed( new Main() );
			canvas->setPaintTechnique( fixed );
			break;
		}

		case wxID_CTX_LIGHTING_PROGRAMMABLE_PIPELINE:
		{
			using vgeGL::technique::MainGLSL;
			
			vgd::Shp< MainGLSL > glsl( new MainGLSL() );
			canvas->setPaintTechnique( glsl );
			break;
		}*/
			
		// DrawStyle
		case wxID_CTX_DRAWSTYLE_NONE:
		case wxID_CTX_DRAWSTYLE_POINT:
		case wxID_CTX_DRAWSTYLE_FLAT:
		case wxID_CTX_DRAWSTYLE_SMOOTH:
		case wxID_CTX_DRAWSTYLE_WIREFRAME:
		case wxID_CTX_DRAWSTYLE_HIDDEN_LINE:
		case wxID_CTX_DRAWSTYLE_FLAT_HIDDEN_LINE:
		case wxID_CTX_DRAWSTYLE_SMOOTH_HIDDEN_LINE:
		case wxID_CTX_DRAWSTYLE_NEIGHBOUR:
		{
			vgd::Shp< DrawStyle >		drawStyle( canvas->findFirstByType< DrawStyle >() );
			
			if ( drawStyle.get() != 0 )
			{
				int32 value;
				value  = event.GetId() - wxID_CTX_DRAWSTYLE_NONE + DrawStyle::NONE;
	
				drawStyle->setShape( static_cast< DrawStyle::ShapeValueType >(value) );
			}
			break;
		}
		
		case wxID_CTX_DRAWSTYLE_NORMALLENGTHNEGATIV:
		case wxID_CTX_DRAWSTYLE_NORMALLENGTHMINUS8:
		case wxID_CTX_DRAWSTYLE_NORMALLENGTHMINUS4:
		case wxID_CTX_DRAWSTYLE_NORMALLENGTH0:
		case wxID_CTX_DRAWSTYLE_NORMALLENGTH4:
		case wxID_CTX_DRAWSTYLE_NORMALLENGTH8:
		case wxID_CTX_DRAWSTYLE_NORMALLENGTHPOSITIV:
		{
			vgd::Shp< DrawStyle >		drawStyle( canvas->findFirstByType< DrawStyle >() );
			
			if ( drawStyle.get() != 0 )
			{
				switch ( event.GetId() )
				{
					case wxID_CTX_DRAWSTYLE_NORMALLENGTHNEGATIV:
						drawStyle->setNormalLength( -15 );
						break;
					case wxID_CTX_DRAWSTYLE_NORMALLENGTHMINUS8:
						drawStyle->setNormalLength( -8 );
						break;
					case wxID_CTX_DRAWSTYLE_NORMALLENGTHMINUS4:
						drawStyle->setNormalLength( -4 );
						break;					
					case wxID_CTX_DRAWSTYLE_NORMALLENGTH0:
						drawStyle->setNormalLength( 0 );
						break;
					case wxID_CTX_DRAWSTYLE_NORMALLENGTH4:
						drawStyle->setNormalLength( 4 );
						break;					
					case wxID_CTX_DRAWSTYLE_NORMALLENGTH8:
						drawStyle->setNormalLength( 8 );
						break;					
					case wxID_CTX_DRAWSTYLE_NORMALLENGTHPOSITIV:
						drawStyle->setNormalLength( 15 );
						break;
					default:
						assert( false && "Unknown case" );
				}
			}
			break;
		}
		
		case wxID_CTX_DRAWSTYLE_SHOWORIENTATION:
		{
			vgd::Shp< DrawStyle >		drawStyle( canvas->findFirstByType< DrawStyle >() );
			
			if ( drawStyle.get() != 0 )
			{
				DrawStyle::ShowOrientationValueType value;
				bool isDefined = drawStyle->getShowOrientation( value );
				
				if ( isDefined )
				{
					drawStyle->setShowOrientation( !value );
				}
				else
				{
					drawStyle->setShowOrientation( true );
				}
			}
			break;
		}
		
		case wxID_CTX_DRAWSTYLE_NO_BOUNDING_BOX:
		case wxID_CTX_DRAWSTYLE_OBJECT_SPACE:
		case wxID_CTX_DRAWSTYLE_AA_OBJECT_SPACE:
		case wxID_CTX_DRAWSTYLE_OBJECT_AND_AA_OBJECT_SPACE:
		{
			vgd::Shp< DrawStyle >		drawStyle( canvas->findFirstByType< DrawStyle >() );
			
			if ( drawStyle.get() != 0 )
			{
				int32 value;
				value  = event.GetId() - wxID_CTX_DRAWSTYLE_NO_BOUNDING_BOX + DrawStyle::NO_BOUNDING_BOX;
	
				drawStyle->setBoundingBox( static_cast< DrawStyle::BoundingBoxValueType >(value) );
			}
			break;
		}


		// LightModel
		
		//
		case wxID_CTX_LIGHTMODEL_MODEL_LIGHTING_OFF:
		{
			vgd::Shp< LightModel >		lightModel( canvas->findFirstByType< LightModel >() );
			
			if ( lightModel.get() != 0 )
			{
				lightModel->setModel( LightModel::LIGHTING_OFF );
			}
			break;
		}

		case wxID_CTX_LIGHTMODEL_MODEL_STANDARD_PER_VERTEX:
		{
			vgd::Shp< LightModel >		lightModel( canvas->findFirstByType< LightModel >() );
			
			if ( lightModel.get() != 0 )
			{
				lightModel->setModel( LightModel::STANDARD_PER_VERTEX );
			}
			break;
		}		
		
		case wxID_CTX_LIGHTMODEL_MODEL_STANDARD_PER_PIXEL:				
		{
			vgd::Shp< LightModel >		lightModel( canvas->findFirstByType< LightModel >() );
			
			if ( lightModel.get() != 0 )
			{
				lightModel->setModel( LightModel::STANDARD_PER_PIXEL );
			}
			break;
		}
		
		//
		case wxID_CTX_LIGHTMODEL_VIEWER:
		{
			vgd::Shp< LightModel >		lightModel( canvas->findFirstByType< LightModel >() );
			
			if ( lightModel.get() != 0 )
			{
				LightModel::ViewerValueType value;
				bool isDefined = lightModel->getViewer( value );
				
				if ( isDefined )
				{
					if ( value == LightModel::AT_INFINITY )
					{
						lightModel->setViewer( LightModel::AT_EYE );
					}
					else
					{
						lightModel->setViewer( LightModel::AT_INFINITY );
					}
				}
				else
				{
					lightModel->setViewer( LightModel::AT_EYE );
				}
			}
			break;
		}

		//
		case wxID_CTX_LIGHTMODEL_TWOSIDED:
		{
			vgd::Shp< LightModel >		lightModel( canvas->findFirstByType< LightModel >() );
			
			if ( lightModel.get() != 0 )
			{
				bool value;
				bool isDefined = lightModel->getTwoSided( value );
				
				if ( isDefined )
				{
					lightModel->setTwoSided( !value );
				}
				else
				{
					lightModel->setTwoSided( true );
				}
			}

			break;
		}
	
		//default:
		// nothing to do
	}

	canvas->refresh();
}



void processContextualMenuEvent( Canvas * canvas, wxCommandEvent& event, vgd::Shp< vgd::node::Node > shape )
{
	using vgd::node::TriSet;

	vgd::Shp< TriSet > triset = extractTriSet( shape );

	switch ( event.GetId() )
	{
		// ALGORITHMS
		case wxID_CTX_ALGORITHMS_INVERT_TRIANGLE_ORIENTATION:
			if ( triset )
			{
				vgAlg::node::invertTriangleOrientation( triset );
				triset->computeNormals();
			}
			break;
		
		// IO
		case wxID_CTX_IO_SAVETRIAN:
			if ( triset )
			{
				vgTrian::Loader ioTrian;
				ioTrian.saveTrian( triset, "triset.trian" );
			}
			break;

		//default:
		// nothing to do
	}

	canvas->refresh();
}



} // namespace detail

} // namespace vgWX
