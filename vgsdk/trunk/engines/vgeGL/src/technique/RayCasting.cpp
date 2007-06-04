// VGSDK - Copyright (C) 2004, 2007, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/technique/RayCasting.hpp"

#include <GL/glu.h>

#include <vgd/node/Camera.hpp>
#include <vgd/node/DrawStyle.hpp>
#include <vgd/node/FrontFace.hpp>
#include <vgd/node/Group.hpp>
#include <vgd/node/Kit.hpp>
#include <vgd/node/Shape.hpp>
#include <vge/engine/Engine.hpp>
#include <vge/pass/ForEach.hpp>
#include <vge/service/Painter.hpp>

#include "vgeGL/engine/Engine.hpp"



namespace vgeGL
{

namespace technique
{



RayCasting::RayCasting() 
:	m_x					(	-1	),
	m_y					(	-1	),
	m_pSelectBuffer		(	0	)
	//m_oglViewport[4]
	//m_matrixProjection[16];
	//m_matrixModelview[16];
	//m_pNodes
	//m_pHits
	//m_iterNearestHit
	//m_iterFarthestHit
{}



RayCasting::~RayCasting()
{
	destroy();
}



void RayCasting::destroy()
{
	if ( m_pSelectBuffer != 0 )
	{
		delete[] m_pSelectBuffer;
		m_pSelectBuffer = 0;
	}
	
	m_pNodes.reset();
	m_pHits.reset();
}



void RayCasting::apply(	vgeGL::engine::Engine * engine, vge::visitor::TraverseElementVector* traverseElements,
						const int32 x, const int32 y )
{
	// store x and y.
	m_x = x;
	m_y = y;

	if ( m_pSelectBuffer == 0 )
	{
		m_pSelectBuffer = new GLuint[m_selectBufferSize];
	}
	memset( m_pSelectBuffer, m_selectBufferSize, sizeof(GLuint) );

	//
	glSelectBuffer( m_selectBufferSize, m_pSelectBuffer );
	glRenderMode( GL_SELECT );

	apply( engine, traverseElements );
}



const uint32 RayCasting::getHitsSize() const
{
	uint32 size;
	
	if ( m_pHits.get() != 0 )
	{
		size = static_cast<uint32>(m_pHits->size());
	}
	else
	{
		size = 0;
	}
	
	return size;
}



const vgd::Shp< vgeGL::basic::HitList > RayCasting::getHits() const
{
	assert( getHitsSize() != 0 );
	
	return m_pHits;
}



const vgeGL::basic::Hit& RayCasting::getNearestHit() const
{
	assert( getHitsSize() != 0 );
	
	return ( *m_iterNearestHit );
}



const vgeGL::basic::Hit& RayCasting::getFarthestHit() const
{
	assert( getHitsSize() != 0 );
		
	return ( *m_iterFarthestHit );
}



vgd::node::Node* RayCasting::getNearestHitNode() const
{
	const vgeGL::basic::Hit& hit( getNearestHit() );
	
	vgd::node::Node *pNode;
	if ( hit.stackNode().size() >= 1 )
	{
		pNode = *(hit.stackNode().begin());
	}
	else
	{
		pNode = 0;
	}
	
	return pNode;
}



void RayCasting::apply(	vgeGL::engine::Engine * engine, vge::visitor::TraverseElementVector* traverseElements )
{
	vgd::Shp< vge::service::Service > paint = vge::service::Painter::create();

	prepareEval( engine, traverseElements );
	engine->resetEval();

	// First pass : draw all shape.
	// @todo Creates a Pass class
	beginPass();

	engine->resetMatrices();
	
	engine->pushStateStack();			
	glPushAttrib( GL_ALL_ATTRIB_BITS );

	engine->disregard();
	
	engine->regardIfIsAKindOf<vgd::node::SingleTransformation>();
	engine->regardIfIsA<vgd::node::DrawStyle>();
	engine->regardIfIsA<vgd::node::FrontFace>();
	
	engine->regardIfIsAKindOf<vgd::node::Group>();
	engine->regardIfIsAKindOf<vgd::node::Kit>();
	engine->regardIfIsAKindOf<vgd::node::Shape>();

	// Init.
	bool	cameraAlreadyTraversed = false;

	// Init. database.
	m_pNodes = vgd::Shp< vgd::node::PNodeVector >( new vgd::node::PNodeVector );
	m_pNodes->reserve( traverseElements->size()/2 );											// heuristic FIXME is the good one ?

	// Init. opengl stack name.
	GLuint currentGLName = 0;
	glInitNames();
	glPushName( currentGLName );

	vge::visitor::TraverseElementVector::const_iterator i, iEnd;
	for(	i = traverseElements->begin(), iEnd = traverseElements->end();
			i != iEnd;
			++i )
	{
		if ( (i->first)->isA< vgd::node::Camera >() )
		{
			if ( i->second )
			{
				// preTraverse
				engine->evaluate( paint, i->first, i->second );
			}
			else
			{
				// postTraverse
				assert( !cameraAlreadyTraversed && "Multiple camera node not supported." );			// FIXME
				cameraAlreadyTraversed = true;
				
				engine->evaluate( paint, i->first, i->second );
				
				// getting some OpenGL informations : step 1
				glGetIntegerv( GL_VIEWPORT, m_oglViewport );										// FIXME
				
				// compute pick matrix
				vgm::MatrixR pickMatrix;
				vgm::Rectangle2i viewport(	m_oglViewport[0], m_oglViewport[1],
											m_oglViewport[2], m_oglViewport[3] );
	
				pickMatrix.setPick(	static_cast<float>(m_x), static_cast<float>(m_oglViewport[3] - m_y),
									1., 1., viewport );
				
				// update engine
				vgm::MatrixR& current( engine->getProjectionMatrix().getTop() );
				
				current = current * pickMatrix;

				// Update OpenGL.
				glMatrixMode( GL_PROJECTION );
				glLoadMatrixf( reinterpret_cast<const float*>( current.getValue() ) );
				
				// getting some OpenGL informations : step 2
				glGetDoublev( GL_PROJECTION_MATRIX, m_matrixProjection );									// FIXME
				glGetDoublev( GL_MODELVIEW_MATRIX,  m_matrixModelview );									// FIXME
			}
		}
		else if ( (i->first)->isAKindOf< vgd::node::Kit >() )					// @todo Kit similar to Shape
		{
			if ( i->second )
			{
				// preTraverse
				assert( cameraAlreadyTraversed && "Kit before the Camera !" );

				glLoadName( currentGLName );	
				glPushName( currentGLName );
				++currentGLName;
				m_pNodes->push_back( i->first );
			
				engine->evaluate( paint, i->first, i->second );
			}
			else
			{
				engine->evaluate( paint, i->first, i->second );
				
				glPopName();
			}
		}
		else if ( (i->first)->isAKindOf< vgd::node::Shape >() )
		{
			if ( i->second )
			{
				assert( cameraAlreadyTraversed && "Shape before the Camera !" );
	
				glLoadName( currentGLName );
				++currentGLName;
				m_pNodes->push_back( i->first );
			
				// this is a shape, draw it.
				engine->evaluate( paint, i->first, i->second );
			}
			else
			{
				engine->evaluate( paint, i->first, i->second );
			}
		}
		else
		{
			engine->evaluate( paint, i->first, i->second );
		}
	}

	glPopAttrib();
	engine->popStateStack();

	endPass();

	//
	glFlush();

	GLuint gluintHitsSize = glRenderMode( GL_RENDER );

	fillHits( gluintHitsSize );

	//
	engine->regard();

	finishEval();

	// Release memory.
	m_pNodes.reset();
}



void RayCasting::fillHits( const uint32 gluintHitsSize )
{
	assert( m_pSelectBuffer != 0 );
	assert( m_pNodes.get() != 0 );
	
	// Reset hit list.
	m_pHits = vgd::Shp< vgeGL::basic::HitList >( new vgeGL::basic::HitList );

	// Search the picking node in hits database
	GLuint gluintZMin				= ~0;
	GLuint gluintZMinForNearest		= ~0;
	GLuint gluintZMax				= 0;
	GLuint gluintZMaxForFarthest	= 0;
	int32  i32PickingName			= -1;

	double dX, dY, dZ;

	// Explore opengl hits database.
	GLuint *ptr = static_cast<GLuint*>( m_pSelectBuffer );

	for(	uint32 ui32I=0;
			ui32I < gluintHitsSize;
			++ui32I )
	{
		// nb of hits.
		GLuint uintNumNames = *ptr;
		ptr++;

		// Construct class Hit for the current hit.
		vgeGL::basic::Hit hit;

		// min
		gluintZMin		= *ptr;
		float fDepth	= static_cast<float>(gluintZMin);
		fDepth			/= 4294967295; // pow(2.f, 32) - 1.f;

		hit.minDepthValue() = fDepth;

		gluUnProject(	m_x, m_oglViewport[3]- m_y, fDepth,
						m_matrixModelview, m_matrixProjection, m_oglViewport,
						&dX, &dY, &dZ );															// FIXME
		
		hit.nearestVertex() = vgm::Vec3f(	static_cast<float>(dX),
											static_cast<float>(dY),
											static_cast<float>(dZ) );
		++ptr;

		// max
		gluintZMax		= *ptr;
		fDepth			= static_cast<float>(gluintZMax);
		fDepth			/= 4294967295; // pow(2.f, 32) - 1.f;

		hit.maxDepthValue() = fDepth;

		gluUnProject(	m_x, m_oglViewport[3]- m_y, fDepth,
						m_matrixModelview, m_matrixProjection, m_oglViewport,
						&dX, &dY, &dZ );															// FIXME

		hit.farthestVertex() = vgm::Vec3f(	static_cast<float>(dX),
											static_cast<float>(dY),
											static_cast<float>(dZ) );
		++ptr;
		
		// name
		for(	uint32 ui32J=0;
				ui32J<uintNumNames;
				++ui32J )
		{
			i32PickingName	= *ptr;
			hit.stackName().push_back( i32PickingName );
			hit.stackNode().push_back( searchNodeFromPickingName( i32PickingName ) );
			++ptr;
		}

		// Add a new hit to the hit list.
		m_pHits->push_front( hit );

		// Test if current hit is a nearest candidate.
		if ( gluintZMin < gluintZMinForNearest )
		{
			gluintZMinForNearest	= gluintZMin;
			m_iterNearestHit		= m_pHits->begin();
		}

		// Test if current hit is a farthest candidate.
		if ( gluintZMax > gluintZMaxForFarthest )
		{
			gluintZMaxForFarthest	= gluintZMax;
			m_iterFarthestHit		= m_pHits->begin();
		}
	}
}



vgd::node::Node* RayCasting::searchNodeFromPickingName( const uint32 pickingName ) const
{
	assert( pickingName < m_pNodes->size() );
	
	return ( (*m_pNodes)[pickingName] );
}



const uint32 RayCasting::m_selectBufferSize = 4 * 1024;
// @todo FIXME ?????
//    /**
//     * Sets the ray for source to destination in world-space(along which to pick)
//	 *
//     * @param vec3fRaySource : starting point for ray.
//     * @param vec3fRayDestination : ray is cast to this point(but not stop at this point).
//     */
//    VGL_API void    start( const SbVec3f vec3fRaySource, const SbVec3f vec3fRayDestination );;
//void CPicking::start( const SbVec3f vec3fRaySource, const SbVec3f vec3fRayDestination )
//{
//    // store value
//    glGetIntegerv( GL_VIEWPORT, m_oglViewPort ); // FIXME OPTME
//
//    start( m_oglViewPort[2]/2, m_oglViewPort[3]/2 );
//
//    glLoadIdentity();
//	
//	// the ray segment from source to destination.
//	SbVec3f vec3fSegmentRay		= vec3fRayDestination - vec3fRaySource;
//
//	SbVec3f vec3fDirectionRay	= vec3fSegmentRay;
//	vec3fDirectionRay.normalize();
//
//	vgl::Vec3f vec3fDirectionRayTmp( vec3fDirectionRay[0], vec3fDirectionRay[1], vec3fDirectionRay[2] );
//
//	// Ray is not a "null segment".
//	assert( vec3fSegmentRay.length() > 0 );
//
//	// Set position and orientation of camera.
//	if (	!vec3fDirectionRayTmp.isColinear( vgl::Vec3f(0.f, 1.f, 0.f) )
//		)
//	{
//		gluLookAt(	vec3fRaySource[0], vec3fRaySource[1], vec3fRaySource[2],
//					vec3fRayDestination[0], vec3fRayDestination[1], vec3fRayDestination[2],
//					0.f, 1.f, 0.f );
//	}
//	else
//	{
//		gluLookAt(	vec3fRaySource[0], vec3fRaySource[1], vec3fRaySource[2],
//					vec3fRayDestination[0], vec3fRayDestination[1], vec3fRayDestination[2],
//					1.f, 0.f, 0.f );
//	}
//
//    // FIXME OPTME
//    glGetDoublev( GL_MODELVIEW_MATRIX,  m_matrixModelview );
//}



} // namespace technique

} // namespace vgeGL
