// VGSDK - Copyright (C) 2004, 2007, 2011, 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/technique/RayCasting.hpp"

#include <vgd/node/Camera.hpp>
#include <vgd/node/ClearFrameBuffer.hpp>
#include <vgd/node/DrawStyle.hpp>
#include <vgd/node/GeometricalTransformation.hpp>
#include <vgd/node/Group.hpp>
#include <vgd/node/Kit.hpp>
#include <vgd/node/Shape.hpp>
#include <vge/engine/Engine.hpp>
#include <vge/service/Painter.hpp>

#include "vgeGL/engine/Engine.hpp"
#include "vgeGL/technique/helpers.hpp"



namespace vgeGL
{

namespace technique
{



RayCasting::RayCasting() 
:	m_x					(	-1	),
	m_y					(	-1	),
	m_raySourceW		( vgm::Vec3f::getInvalid() ),
	m_rayDirectionW		( vgm::Vec3f::getInvalid() ),
	m_pSelectBuffer		(	0	)
	//m_modelview
	//m_projection
	//m_viewport
	//m_shapes
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

	m_shapes.clear();
	m_pHits.reset();
}



void RayCasting::apply(	vgeGL::engine::Engine * engine, vge::visitor::TraverseElementVector* traverseElements,
						const int32 x, const int32 y )
{
	// store parameters
	m_x = x;
	m_y = y;

	m_raySourceW.setInvalid();
	m_rayDirectionW.setInvalid();

	//
	apply( engine, traverseElements );
}


void RayCasting::apply(	vgeGL::engine::Engine * engine, vge::visitor::TraverseElementVector* traverseElements,
						const vgm::Vec3f raySource, const vgm::Vec3f rayDirection )
{
	// store parameters
	m_x = 0;
	m_y = 0;

	m_raySourceW	= raySource;
	m_rayDirectionW	= rayDirection;

	//
	apply( engine, traverseElements );
}



const uint32 RayCasting::getHitsSize() const
{
	uint32 size;

	if ( m_pHits.get() )
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
	vgAssert( getHitsSize() > 0 );

	return m_pHits;
}



const vgeGL::basic::Hit& RayCasting::getNearestHit() const
{
	vgAssert( getHitsSize() > 0 );

	return ( *m_iterNearestHit );
}



const vgeGL::basic::Hit& RayCasting::getFarthestHit() const
{
	vgAssert( getHitsSize() > 0 );

	return ( *m_iterFarthestHit );
}



vgd::node::Node* RayCasting::getNearestHitNode() const
{
	vgd::node::Node *pNode;

	if ( getHitsSize() > 0 )
	{
		const vgeGL::basic::Hit& hit( getNearestHit() );

		if ( hit.stackNode().size() >= 1 )
		{
			pNode = *(hit.stackNode().begin());
		}
		else
		{
			vgAssertN( false, "The nearest hit have an empty node stack." ); 
			pNode = 0;
		}
	}
	else
	{
		pNode = 0;
	}

	return pNode;
}



void RayCasting::apply( vgeGL::engine::Engine * engine, vge::visitor::TraverseElementVector* traverseElements )
{
	//
	if ( m_pSelectBuffer == 0 )
	{
		m_pSelectBuffer = new GLuint[m_selectBufferSize];
	}
	memset( m_pSelectBuffer, m_selectBufferSize, sizeof(GLuint) );

	//
	glSelectBuffer( m_selectBufferSize, m_pSelectBuffer );
	glRenderMode( GL_SELECT );

	//
	vgd::Shp< vge::service::Service > paint = vge::service::Painter::create();

	prepareEval( engine, traverseElements );

	// First pass : draw all shape.

	// Makes a backup of GLSL activation state
	using vgeGL::engine::Engine;
	vgd::Shp< Engine::GLSLActivationState > glslActivationState = engine->getGLSLActivationState();
	engine->sethCurrentProgram();

	// Saves texture mapping state and disables it
	const bool isTextureMappingEnabledBak = engine->isTextureMappingEnabled();
	engine->setTextureMappingEnabled(false);

	setPassDescription("RayCasting::apply()");
	beginPass();

	engine->disregard();

	engine->regardIfIsAKindOf<vgd::node::SingleTransformation>();
	//engine->regardIfIsAKindOf<vgd::node::CoordinateSystem>();
	engine->regardIfIsAKindOf<vgd::node::ClearFrameBuffer>();
	engine->regardIfIsA<vgd::node::DrawStyle>();

	engine->regardIfIsAKindOf<vgd::node::Group>();
	engine->regardIfIsAKindOf<vgd::node::Kit>();
	engine->regardIfIsAKindOf<vgd::node::Shape>();

	// Init.
	bool cameraAlreadyTraversed = false;

	// Init. database.
	m_shapes.reserve( traverseElements->size()/2 );
	m_shapes.clear();

	// Init. opengl stack name.
	GLuint currentGLName = 0;
	glInitNames();
	glPushName( currentGLName );

	vge::visitor::TraverseElementVector::const_iterator i, iEnd;
	for(	i = traverseElements->begin(), iEnd = traverseElements->end();
			i != iEnd;
			++i )
	{
		// CAMERA
		using vgd::node::Camera;

		if ( (i->first)->isA< Camera >() )
		{
			Camera * incomingCamera = dynamic_cast< Camera *>( i->first);

			if ( i->second )
			{
				// preTraverse
				vgd::Shp< Camera >	camera;
				vgm::MatrixR		cameraLookAt;
				const vgm::MatrixR& identity = vgm::MatrixR::getIdentity();

				if ( m_raySourceW.isValid() )
				{
					// Setup Camera using m_raySourceW and m_rayDirectionW
					vgAssert( m_rayDirectionW.isValid() );

					// compute pick matrix
					m_x = incomingCamera->getViewport()[2]/2;
					m_y = incomingCamera->getViewport()[3]/2;

					vgm::MatrixR pickMatrix;
					pickMatrix.setPick( static_cast<float>(m_x), static_cast<float>(m_y), 1.f, 1.f, incomingCamera->getViewport() );

					camera = setupRenderFromCamera(
						m_raySourceW, m_rayDirectionW, identity,
						"RAYCASTING.camera", incomingCamera->getProjectionLeft() * pickMatrix, incomingCamera->getViewport(),
						identity, identity, cameraLookAt /* not used*/ );

					//
					engine->evaluate( paint, camera );

					// Disabling TransformDragger (a side effect of the following method call).
					engine->disregardIfIsAKindOf<vgd::node::GeometricalTransformation>();
				}
				else
				{
					// Setup Camera

					// compute pick matrix
					vgm::MatrixR pickMatrix;
					pickMatrix.setPick(	static_cast<float>(m_x), static_cast<float>(m_y), 1.f, 1.f, incomingCamera->getViewport() );

					camera = setupRenderFromCamera(
						vgm::Vec3f::getNull(), vgm::Vec3f(0.f, 0.f, -1.f), incomingCamera->getLookAt().getInverse() /* ??? */,
						"RAYCASTING.camera", incomingCamera->getProjectionLeft() * pickMatrix, incomingCamera->getViewport(),
						identity, identity, cameraLookAt /* not used*/ );

					//
					engine->evaluate( paint, camera );
				}
			}
			else
			{
				// postTraverse
				vgAssertN( !cameraAlreadyTraversed, "Multiple camera node not supported." );
				cameraAlreadyTraversed = true;

				// getting some OpenGL informations
				m_modelview = engine->getGeometricalMatrix().getTop();
				m_projection = engine->getProjectionMatrix().getTop();
				m_viewport.setValue( engine->getViewport() );
			}
		}
		// CLEARFRAMEBUFFER
		else if ( (i->first)->isAKindOf< vgd::node::ClearFrameBuffer >() )
		{
			engine->regardIfIsAKindOf<vgd::node::SingleTransformation>();
			engine->evaluate( paint, *i );
		}
		// KIT
		else if ( (i->first)->isAKindOf< vgd::node::Kit >() )					// @todo Kit similar to Shape
		{
			if ( i->second )
			{
				// preTraverse
				vgAssertN( cameraAlreadyTraversed, "Kit before the Camera !" );

				glLoadName( currentGLName );
				glPushName( currentGLName );
				++currentGLName;

				const vgm::MatrixR& geometricalMatrix = engine->getGeometricalMatrix().getTop();
				m_shapes.push_back( ShapeInformations(i->first, geometricalMatrix) );

				engine->evaluate( paint, *i );
			}
			else
			{
				engine->evaluate( paint, *i );
				
				glPopName();
			}
		}
		// SHAPE
		else if ( (i->first)->isAKindOf< vgd::node::Shape >() )
		{
			if ( i->second )
			{
				vgAssertN( cameraAlreadyTraversed, "Shape before the Camera !" );

				glLoadName( currentGLName );
				++currentGLName;

				const vgm::MatrixR& geometricalMatrix = engine->getGeometricalMatrix().getTop();
				m_shapes.push_back( ShapeInformations( i->first, geometricalMatrix ) );

				// this is a shape, draw it.
				engine->evaluate( paint, *i );
			}
			else
			{
				engine->evaluate( paint, *i );
			}
		}
		// OTHERS
		else
		{
			engine->evaluate( paint, *i );
		}
	}

	endPass();

	//
	glFlush();

	GLuint gluintHitsSize = glRenderMode( GL_RENDER );

	fillHits( gluintHitsSize );

	//
	finishEval();

	// Restores texture mapping state
	engine->setTextureMappingEnabled( isTextureMappingEnabledBak );

	// Restores GLSL activation state
	engine->setGLSLActivationState( glslActivationState );

	// Release memory.
	m_shapes.clear();
}



void RayCasting::fillHits( const uint32 gluintHitsSize )
{
	vgAssert( m_pSelectBuffer != 0 );

	// Reset hit list.
	m_pHits = vgd::Shp< vgeGL::basic::HitList >( new vgeGL::basic::HitList );

	// Search the picking node in hits database
	GLuint gluintZMin				= ~0;
	GLuint gluintZMinForNearest		= ~0;
	GLuint gluintZMax				= 0;
	GLuint gluintZMaxForFarthest	= 0;
	int32  i32PickingName			= -1;

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

		vgm::MatrixR::unProject(	m_x, m_viewport[3]- m_y, fDepth,
									m_modelview, m_projection, m_viewport,
									hit.nearestVertex() );

		++ptr;

		// max
		gluintZMax		= *ptr;
		fDepth			= static_cast<float>(gluintZMax);
		fDepth			/= 4294967295; // pow(2.f, 32) - 1.f;

		hit.maxDepthValue() = fDepth;

		vgm::MatrixR::unProject(	m_x, m_viewport[3]- m_y, fDepth,
									m_modelview, m_projection, m_viewport,
									hit.farthestVertex() );

		++ptr;

		// name
		for(	uint32 ui32J=0;
				ui32J<uintNumNames;
				++ui32J )
		{
			i32PickingName	= *ptr;

			if ( ui32J == 0 )
			{
				using vgm::MatrixR;

				// min in object space
				const MatrixR& modelviewO = m_shapes[i32PickingName].modelview;

				MatrixR::unProject(	m_x, m_viewport[3]- m_y, hit.minDepthValue(),
									modelviewO, m_projection, m_viewport,
									hit.nearestVertexO() );

				// min in scene space
				const MatrixR& modelviewS = glEngine()->getSceneGeometricalMatrix();

				MatrixR::unProject(	m_x, m_viewport[3]- m_y, hit.minDepthValue(),
									modelviewS, m_projection, m_viewport,
									hit.nearestVertexS() );
			}

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
	vgAssert( pickingName < m_shapes.size() );

	return m_shapes[pickingName].shape;
}



const uint32 RayCasting::m_selectBufferSize = 4 * 1024;



} // namespace technique

} // namespace vgeGL
