// VGSDK - Copyright (C) 2006, 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGCOLLADA_READER_HPP
#define _VGCOLLADA_READER_HPP

#include <dae.h>
#include <dom/domTypes.h>
#include <map>
#include <string>
#include <vgd/Shp.hpp>
#include <vgd/node/Primitive.hpp>

#include "vgCollada/vgCollada.hpp"

class domGeometry;
class domMesh;

namespace vgCollada
{
	struct domSourceAdapter;
}

namespace vgd
{
	namespace node
	{
		struct Group;
		struct VertexShape;
	}
}



namespace vgCollada
{



/**
 * @brief The collada reader frontend.
 */
struct Reader
{
	/**
	 * @brief Loads a collada file.
	 * 
	 * @param fileURI	file Uniform Resource Identifier
	 * 
	 * @return true if loading has been successful, false otherwise.
	 */
	VGCOLLADA_API const bool load( const std::string& fileURI );

	/**
	 * @brief Returns the root of the collada file.
	 */
	VGCOLLADA_API vgd::Shp< vgd::node::Group > getRoot() const;



protected:

	vgd::Shp< DAE >					m_dae;	///< The standard interface to the COLLADA runtime database
	vgd::Shp< vgd::node::Group >	m_root;	///< The scene graph root of the collada file

private:

	vgd::Shp< vgd::node::VertexShape > processGeometry( domGeometry * geometry );
	void fillVertexShape( domMesh *, vgd::Shp< vgd::node::VertexShape > );
//?????
	typedef std::map< xsID, vgd::Shp<domSourceAdapter> > SourceMap;
//typedef std::map< xsID ? or ? daeElement *, domSourceReader > SourceMap;

template< typename T >
void processSinglePPrimitive(	T * group, SourceMap& sources,
									const vgd::node::Primitive& primitive,
									vgd::Shp< vgd::node::VertexShape > vertexShape );


};



} // namespace vgCollada

#endif // _VGCOLLADA_READER_HPP
