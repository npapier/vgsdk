// VGSDK - Copyright (C) 2006, 2007, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGWX_DETAIL_CONTEXTUALMENU_HPP
#define _VGWX_DETAIL_CONTEXTUALMENU_HPP

#include <wx/wx.h>

#include "vgWX/vgWX.hpp"

class wxMenu;

namespace vgd 
{
	template<class T> struct Shp; 
	namespace node { struct VertexShape; }
}

namespace vgWX { struct Canvas; }



namespace vgWX
{

namespace detail
{

/**
 * @brief Identifier used by the default contextual menu.
 * 
 * Don't use the same. Identifier inside [wxID_HIGHEST + 1024,wxID_HIGHEST + 2048] are reserved.
 */
enum {
	// GRAPHWIZ
	wxID_CTX_WRITEGRAPHWIZ  = wxID_HIGHEST + 1024,

	// GLSL
	wxID_CTX_GLSL,
	wxID_CTX_GLSL_ENABLE,

	// VIEWALL
	wxID_CTX_VIEWALL,
	
	// LIGHTING TECHNIQUE
	wxID_CTX_LIGHTING,
	wxID_CTX_LIGHTING_FIXED_PIPELINE,
	wxID_CTX_LIGHTING_PROGRAMMABLE_PIPELINE,

	// DRAWSTYLE
	wxID_CTX_DRAWSTYLE,
	
	wxID_CTX_DRAWSTYLE_NONE,
	wxID_CTX_DRAWSTYLE_POINT,
	wxID_CTX_DRAWSTYLE_FLAT,
	wxID_CTX_DRAWSTYLE_SMOOTH,
	wxID_CTX_DRAWSTYLE_WIREFRAME,
	wxID_CTX_DRAWSTYLE_HIDDEN_LINE,
	wxID_CTX_DRAWSTYLE_FLAT_HIDDEN_LINE,
	wxID_CTX_DRAWSTYLE_SMOOTH_HIDDEN_LINE,
	wxID_CTX_DRAWSTYLE_NEIGHBOUR,

	wxID_CTX_DRAWSTYLE_NORMALLENGTHNEGATIV,
	wxID_CTX_DRAWSTYLE_NORMALLENGTHMINUS8,
	wxID_CTX_DRAWSTYLE_NORMALLENGTHMINUS4,
	wxID_CTX_DRAWSTYLE_NORMALLENGTH0,
	wxID_CTX_DRAWSTYLE_NORMALLENGTH4,
	wxID_CTX_DRAWSTYLE_NORMALLENGTH8,
	wxID_CTX_DRAWSTYLE_NORMALLENGTHPOSITIV,
	
	wxID_CTX_DRAWSTYLE_SHOWORIENTATION,
	
	wxID_CTX_DRAWSTYLE_NO_BOUNDING_BOX,
	wxID_CTX_DRAWSTYLE_OBJECT_SPACE,
	wxID_CTX_DRAWSTYLE_AA_OBJECT_SPACE,
	wxID_CTX_DRAWSTYLE_OBJECT_AND_AA_OBJECT_SPACE,

	
	// LIGHTMODEL
	wxID_CTX_LIGHTMODEL_MODEL,
	
	wxID_CTX_LIGHTMODEL_MODEL_LIGHTING_OFF,
	wxID_CTX_LIGHTMODEL_MODEL_STANDARD_PER_VERTEX,
	wxID_CTX_LIGHTMODEL_MODEL_STANDARD_PER_PIXEL,

	//wxID_CTX_LIGHTMODEL_AMBIENT

	wxID_CTX_LIGHTMODEL_VIEWER,
	
	wxID_CTX_LIGHTMODEL_TWOSIDED,
	
	// ALGORITHMS and IO on shape 
	wxID_CTX_ALGORITHMS_AND_IO,
	
	wxID_CTX_ALGORITHMS,
	wxID_CTX_ALGORITHMS_INVERT_TRIANGLE_ORIENTATION,

	wxID_CTX_IO,	
	wxID_CTX_IO_SAVETRIAN
};



/**
 * @brief Constructs the contextual menu.
 * 
 * @param canvas	the canvas
 * 
 * @todo flags to construct partial menu ?
 */
wxMenu *createContextualMenu( const Canvas * canvas );



/**
 * @brief Constructs the contextual menu for algorithms/io on shape.
 * 
 * @param canvas	the canvas
 * @param shape		the picked shape
 */
wxMenu *createContextualMenu( const Canvas * canvas, vgd::Shp< vgd::node::VertexShape > shape );



/**
 * @brief Processes an event generated by the contextual menu.
 * 
 * @param canvas	the canvas
 * @param event		the event to process
 */
void processContextualMenuEvent( Canvas * canvas, wxCommandEvent& event );



/**
 * @brief Processes an event generated by the contextual menu.
 * 
 * @param canvas	the canvas
 * @param event		the event to process
 * @param shape		the picked shape 
 */
void processContextualMenuEvent( Canvas * canvas, wxCommandEvent& event, vgd::Shp< vgd::node::VertexShape > shape );



} // namespace detail

} // namespace vgWX

#endif // #ifndef _VGWX_DETAIL_CONTEXTUALMENU_HPP
