// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/TextureCubeMap.hpp"

//#include <Magick++/Image.h> FIXME

#include <vgd/basic/Image.hpp>
#include <vgd/field/DirtyFlag.hpp>
#include <vgd/node/TextureCubeMap.hpp>
#include <vge/rc/Manager.hpp>
#include <vge/service/Painter.hpp>
#include <vgm/Utilities.hpp>

#include "vgeGL/engine/Engine.hpp"
#include "vgeGL/rc/TextureCubeMap.hpp"


namespace vgeGL
{

namespace handler
{

namespace painter
{



META_HANDLER_CPP( TextureCubeMap );



/*const vge::service::List TextureCubeMap::getServices() const
{
	vge::service::List list;
	list.push_back( vgd::Shp<vge::service::Service>( new vge::service::Painter ) );

	return ( list );
}*/



const vge::handler::Handler::TargetVector TextureCubeMap::getTargets() const
{
	vge::handler::Handler::TargetVector targets;

	targets.push_back( vgd::node::TextureCubeMap::getClassIndexStatic() );

	return ( targets );
}



void TextureCubeMap::apply ( vge::engine::Engine* pEngine, vgd::node::Node *pNode )
{
	assert( dynamic_cast< vgeGL::engine::Engine* >(pEngine) != 0 );
	vgeGL::engine::Engine *pGLEngine = static_cast< vgeGL::engine::Engine* >(pEngine);

	assert( dynamic_cast< vgd::node::TextureCubeMap* >(pNode) != 0 );
	vgd::node::TextureCubeMap *pCastedNode = static_cast< vgd::node::TextureCubeMap* >(pNode);

	vge::rc::Manager& rGLManager = pGLEngine->getGLManager();

	// ****** Render ******
	vgd::field::DirtyFlag	*pDF;
	
	vge::rc::IResource 		*pResource;
	vgeGL::rc::TextureCubeMap		*pCastedResource;

	// get dirty flag of node
	pDF = pCastedNode->getDirtyFlag( pCastedNode->getDFNode() );

	// lookup the resource.
	pResource			= rGLManager.getAbstract( pNode );
	pCastedResource	= dynamic_cast< vgeGL::rc::TextureCubeMap* >(pResource);
	
	if (	(pCastedResource==0) &&
			(pResource != 0) )
	{
		// There is a resource, but not of the expected type.
		// Dynamic change of handler ?
		// or node that must be process differently (static, dynamic for VertexShape).
		rGLManager.remove( pNode );

		pResource			= 0;
	}

	assert(	(pResource==0 && pCastedResource==0) ||
				(pResource!=0 && pCastedResource!=0)
				 );

	// What to do ?
	if ( pDF->isDirty() )
	{
		// Node is invalidated.
		if ( pCastedResource != 0 )
		{
			// Founded an associated resource, recycle it
			pCastedResource->release();
		}
		else
		{
			// No resource (this is the first evaluation), create it.
			pCastedResource = new vgeGL::rc::TextureCubeMap();
			rGLManager.add( pNode, pCastedResource );
		}

		// update resource.
		create( pGLEngine, pCastedNode, pCastedResource );
		use( pGLEngine, pCastedNode, pCastedResource );
		
		// validate vertex shape.
		pDF->validate();
	}
	else
	{
		// No change in node..
		if ( pCastedResource != 0 )
		{
			// Founded an associated resource.
			
			// render
			use( pGLEngine, pCastedNode, pCastedResource );
		}
		else
		{
			// No resource, but already validate !!!
			assert( false && "No resource, but already validate !!!" );
		}
	}
}



void TextureCubeMap::unapply ( vge::engine::Engine* engine, vgd::node::Node* pNode )
{
}



void TextureCubeMap::setToDefaults()
{
	Texture::setToDefaults();
}



void TextureCubeMap::create(	vgeGL::engine::Engine *pGLEngine, vgd::node::TextureCubeMap *pNode,
										vgeGL::rc::TextureCubeMap *pResource )
{
	// Create cube map texture.
	if ( !pResource->isEmpty() )
	{
		pResource->release();
	}

	//	Update cube map texture image.
	for(	int32 i = vgd::node::TextureCubeMap::POS_X;
			i <= vgd::node::TextureCubeMap::NEG_Z;
			i++ )
	{
		vgd::Shp< vgd::basic::IImage > shpImage;
		bool isDefined;
		
		isDefined = pNode->getIImages( 
			static_cast<vgd::node::TextureCubeMap::IImagesParameterType>(i),
			shpImage );
		
		if ( isDefined )
		{
			if ( pResource->isEmpty() )
			{
				pResource->generate();
				pResource->bind();
			}
			create( m_cubeMapTarget[i], pGLEngine, shpImage, pResource );
		}
	}
}



void TextureCubeMap::create( GLenum target, vgeGL::engine::Engine *pGLEngine, 
		vgd::Shp< vgd::basic::IImage > shpImage, vgeGL::rc::TextureCubeMap *pResource )
{
	vgd::Shp< vgd::basic::Image > imImage;
	imImage	=	vgd::dynamic_pointer_cast< vgd::basic::Image >( shpImage );

	assert( false );
		
//	if ( imImage != 0 )
//	{
//		Magick::Image& image( imImage->getImagick() );
//		Magick::Image newImage;
//				
//		int32	components	;//= shpImage->components();
//		components	= 4;											// FIXME : optme.
//		
//		int32	width			= shpImage->width();
//		int32	texWidth		= vgm::Utilities::nextPower2( width );
//		int32	height		= shpImage->height();
//		int32	texHeight	= vgm::Utilities::nextPower2( height );
//		
//		assert( width == height && "Width and height must be the same." );
//		
//		GLenum	format	;//= convertMyFormat2GL( shpImage->format() );
//		format	= GL_BGRA;										// FIXME : optme.
//		
//
//		// Copy and convert image to newImage
//		newImage.size( Magick::Geometry(width, height) );
//		newImage.magick("BGRA");
//		//const
//		Magick::PixelPacket *newPixelCache;
//		newPixelCache = newImage.getPixels( 0, 0,
//					width, height );
//					
//		image.write(0,0, width, height, "BGRA", Magick::CharPixel, newPixelCache );
//		
////		/*const */Magick::PixelPacket *pixelCache;
////		pixelCache = image.getPixels( 0, 0,
////					shpImage->width(), shpImage->height() );
//		uint8*	pixels	= reinterpret_cast< uint8* >(newPixelCache);
//		
//		glTexImage2D( target,
//			0,
//			components,
//			texWidth, texHeight,			
//			0,
//			format,
//			GL_UNSIGNED_BYTE,
//			0 );
//	
//		glTexSubImage2D( target,
//				0,				// level
//				0, 0,			// offset
//				width, height,
//				format,
//				GL_UNSIGNED_BYTE,
//				pixels
//				);
//	}
//	else
//	{
//		int32	components	= shpImage->components();
//		int32	width			= shpImage->width();
//		int32	texWidth		= vgm::Utilities::nextPower2( width );
//		int32	height		= shpImage->height();
//		int32	texHeight	= vgm::Utilities::nextPower2( height );
//		GLenum	format	= convertMyFormat2GL( shpImage->format() );
//		uint8*	pixels	= shpImage->pixels();
//
//		glTexImage2D( target,
//				0,
//				components,
//				texWidth, texHeight,
//				0,
//				format,
//				GL_UNSIGNED_BYTE,
//				0
//				);
//			
//
//		glTexSubImage2D( target,
//				0,				// level
//				0, 0,			// offset
//				width, height,
//				format,
//				GL_UNSIGNED_BYTE,
//				pixels
//				);
//		// TexturePainter::paint( pGLEngine, pNode, pResource ); FIXME
//	}
}



void TextureCubeMap::use(	vgeGL::engine::Engine *pGLEngine, vgd::node::TextureCubeMap *pNode,
									vgeGL::rc::TextureCubeMap *pResource  )
{
	// FIXME IIImages ?
	vgd::Shp< vgd::basic::IImage > shpImage;
	bool isDefined;
	
	isDefined = pNode->getIImages( 
		vgd::node::TextureCubeMap::POS_X,
		shpImage );

	pResource->active( GL_TEXTURE0_ARB + pNode->getMultiAttributeIndex() );		

	if ( isDefined )
	{	
		pResource->enable();	
		pResource->bind();

		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP_ARB);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP_ARB);
		glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP_ARB);
		
		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);
		glEnable(GL_TEXTURE_GEN_R);
	}		

	Texture::paint( pGLEngine, pNode, pResource );
	
	// else nothing
	
	
/*	glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_CUBE_MAP_EXT, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP_EXT, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);*/
	
	
	/*glTexGenf(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR );
	glTexGenf(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR );
	glTexGenf(GL_R, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR );	*/
	
	
	
	
	
	/*glTexGeni(	GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR );
	GLfloat plane[] = { 1.0, 1.0, 1.0, 0.0 };
	glTexGenfv(	GL_S, GL_OBJECT_PLANE, plane );
	glEnable(GL_TEXTURE_GEN_S);

	glTexGeni(	GL_T GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR );
	glTexGenfv(	GL_T, GL_OBJECT_PLANE, plane );
	glEnable(GL_TEXTURE_GEN_T);*/
	
	
	//glTexGenf(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR );
	//glTexGenf(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR );	

	//glEnable(GL_TEXTURE_GEN_S);
	//glEnable(GL_TEXTURE_GEN_T);	
	
//	glTexGenfv(GL_S,GL_SPHERE_MAP,0);
//	glTexGenfv(GL_T,GL_SPHERE_MAP,0);
//	glEnable(GL_TEXTURE_GEN_S);
//	glEnable(GL_TEXTURE_GEN_T);
}


GLenum TextureCubeMap::m_cubeMapTarget[] = {
	GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB,
	GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB,
	GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB
};



} // namespace painter

} // namespace handler

} // namespace vgeGL
