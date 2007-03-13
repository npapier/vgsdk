// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Sylvain Thery
// 23-12-2004 : Integration of MeshBase and MeshTopology from Sylvain Thery was done.

#include "vgAlg/MeshBase.hpp"

#include <iostream>
#include <iomanip>
#include <fstream>

#include "vgAlg/MeshBase.hpp"


namespace vgAlg
{


#define MAX(A,B) ((A)>=(B)?(A):(B))
#define MIN(A,B) ((A)<=(B)?(A):(B))


MeshBase::MeshBase()
{
	m_lNbPoints=0;
	m_lNbTriangles=0;
	m_lNextEdge=0;
}


MeshBase::MeshBase( vgd::Shp< vgd::node::TriSet > pTriSet )
{
	vgd::field::EditorRO< vgd::field::MFVec3f >	vertices			= pTriSet->getFVertexRO();
	vgd::field::EditorRO< vgd::field::MFUInt32 >	vertexIndex		= pTriSet->getFVertexIndexRO();
	vgd::field::EditorRO< vgd::field::MFPrimitive >	primitives	= pTriSet->getFPrimitiveRO();
	
	// copy vertices
	m_lNbPoints		= vertices->size();
	m_VvPoints.reserve(m_lNbPoints);
	for (int32 i=0; i<m_lNbPoints; ++i)
	{
		m_VvPoints.push_back( (*vertices)[i] );
	}

	// copy edges
	assert( primitives->size() == 1 );
	const vgd::node::Primitive& prim = (*primitives)[0];
	assert( prim.getType() == vgd::node::Primitive::TRIANGLES );
	assert( prim.getIndex() == 0 );
	assert( prim.getNumIndices() == vertexIndex->size() );
	
	m_lNbTriangles = vertexIndex->size() / 3;
	
	// reserve memory for edges and neighbours
	m_VlEdges.reserve(3*m_lNbTriangles);
	m_VlNeighbours.reserve(3*m_lNbTriangles);

	for (int32 i=0; i<3*m_lNbTriangles; )
	{
		m_VlEdges.push_back( (*vertexIndex)[i++] );
		m_VlEdges.push_back( (*vertexIndex)[i++] );
		m_VlEdges.push_back( (*vertexIndex)[i++] );

		// read the three neighbours of triangle
		m_VlNeighbours.push_back(-1);
		m_VlNeighbours.push_back(-1);
		m_VlNeighbours.push_back(-1);				
	}
	m_lNextEdge = m_VlEdges.size();
}
	

MeshBase::MeshBase( vgd::Shp< vgd::node::VertexShape > pVertexShape )
{
	vgd::field::EditorRO< vgd::field::MFVec3f >	vertices			= pVertexShape->getFVertexRO();
	vgd::field::EditorRO< vgd::field::MFUInt32 >	vertexIndex		= pVertexShape->getFVertexIndexRO();
	vgd::field::EditorRO< vgd::field::MFPrimitive >	primitives	= pVertexShape->getFPrimitiveRO();
	
	// copy vertices
	m_lNbPoints		= vertices->size();
	m_VvPoints.reserve(m_lNbPoints);
	for (int32 i=0; i<m_lNbPoints; ++i)
	{
		m_VvPoints.push_back( (*vertices)[i] );
	}

	// copy edges
	assert( primitives->size() == 1 );
	const vgd::node::Primitive& prim = (*primitives)[0];
	assert( prim.getType() == vgd::node::Primitive::TRIANGLES );
	assert( prim.getIndex() == 0 );
	assert( prim.getNumIndices() == vertexIndex->size() );
	
	m_lNbTriangles = vertexIndex->size() / 3;
	
	// reserve memory for edges and neighbours
	m_VlEdges.reserve(3*m_lNbTriangles);
	m_VlNeighbours.reserve(3*m_lNbTriangles);

	for (int32 i=0; i<3*m_lNbTriangles; )
	{
		m_VlEdges.push_back( (*vertexIndex)[i++] );
		m_VlEdges.push_back( (*vertexIndex)[i++] );
		m_VlEdges.push_back( (*vertexIndex)[i++] );

		// read the three neighbours of triangle
		m_VlNeighbours.push_back(-1);
		m_VlNeighbours.push_back(-1);
		m_VlNeighbours.push_back(-1);				
	}
	m_lNextEdge = m_VlEdges.size();
}


MeshBase::~MeshBase()
{
}


bool MeshBase::loadTrian(const char* _cName)
{
	// open file
	std::ifstream fp(_cName, std::ios::in);
	if (!fp.good())
	{
		std::cerr << "MeshBase::loadTrian: Unable to open file " << std::endl;
		return false;
	}

	// read nb of points
	int32 lNbPoints;
	fp >> lNbPoints;
	m_VvPoints.reserve(lNbPoints);
	
	// read points
	for (int32 i=0; i<lNbPoints; i++)
	{
		float x,y,z;
		fp >> x;
		fp >> y;
		fp >> z;
		m_VvPoints.push_back(vgm::Vec3f(x,y,z));
	}

	// read nb of faces
	fp >> m_lNbTriangles;
	
	// reserve memory for edges and neighbours
	m_VlEdges.reserve(3*m_lNbTriangles);
	m_VlNeighbours.reserve(3*m_lNbTriangles);
	// read indices of faces
	for (int32 i=0; i<m_lNbTriangles; i++)
	{
		// read the three edges of triangle
		int32 lEdge;
		fp >> lEdge;
		m_VlEdges.push_back(lEdge);
		fp >> lEdge;
		m_VlEdges.push_back(lEdge);
		fp >> lEdge;
		m_VlEdges.push_back(lEdge);
		// read the three neighbours of triangle
		int32 lNeighbour;
		fp >> lNeighbour;
		m_VlNeighbours.push_back(lNeighbour);
		fp >> lNeighbour;
		m_VlNeighbours.push_back(lNeighbour);
		fp >> lNeighbour;
		m_VlNeighbours.push_back(lNeighbour);
	}
	m_lNextEdge = m_VlEdges.size();
	
	//close file
	fp.close();
	std::cout << m_lNbTriangles<<" triangles"<< std::endl;

	return true;
}


bool MeshBase::saveTrian(const char* _cName) const
{
	// open file
	std::ofstream fs(_cName, std::ios::out);
	if (!fs)
	{
		std::cerr << "MeshBase::saveTrian: Unable to open file " << std::endl;
		return false;
	}

	int32 lNbPoints = m_VvPoints.size();
	// write nb of points
	fs << lNbPoints << std::endl;
	
	// write points
	for (int32 i=0; i<lNbPoints; i++)
	{
		const vgm::Vec3f& P = m_VvPoints[i];
		fs << P[0]<< " ";
		fs << P[1]<< " ";
		fs << P[2]<< std::endl;
	}

	// write nb of faces
	fs << m_lNbTriangles << std::endl;
	// write indices of faces
	int32 j=0;
	for (int32 i=0; i<m_lNbTriangles; i++)
	{

		// write the three edges of triangle
		fs << m_VlEdges[j]<< " ";
		fs << m_VlEdges[j+1]<< " ";
		fs << m_VlEdges[j+2]<< "  ";
		// write the three neighbours of triangle
		fs << m_VlNeighbours[j]<< " ";
		fs << m_VlNeighbours[j+1]<< " ";
		fs << m_VlNeighbours[j+2]<< std::endl;
		j+=3;
	}
	
	//close file
	fs.close();
	return true;
}



int32 MeshBase::A1(int32 _lEdge) const
{
	if ((_lEdge%3) <2)
		return _lEdge+1;
	return _lEdge - 2;
}


int32 MeshBase::A11(int32 _lEdge) const
{
	if ((_lEdge%3) >0)
		return _lEdge-1;
	return _lEdge +2;
}


int32 MeshBase::A2(const int32 _lEdge) const
{
  return m_VlNeighbours[_lEdge];
}


int32 MeshBase::addFace(int32 _lV1, int32 _lV2, int32 _lV3)
{
	int32 lFirst = m_lNextEdge;                      // keep index of first edge of new triangle

	m_VlEdges.push_back(_lV1);
	m_VlEdges.push_back(_lV2);                      // insert the three edges
	m_VlEdges.push_back(_lV3);
	m_lNextEdge += 3;                                       // update the pos of next edge

	m_VlNeighbours.push_back(-1);
	m_VlNeighbours.push_back(-1);       // update the neighbour vector with no neighbour
	m_VlNeighbours.push_back(-1);

	m_lNbTriangles++;                                       // update the number of triangles

	return lFirst;
}


int32 MeshBase::addFace(int32 _lV1, int32 _lV2, int32 _lV3, int32 _lN1, int32 _lN2, int32 _lN3)
{
	int32 lFirst = m_lNextEdge;			// keep index of first edge of new triangle

	m_VlEdges.push_back(_lV1);
	m_VlEdges.push_back(_lV2);			// insert the three edges
	m_VlEdges.push_back(_lV3);

	m_VlNeighbours.push_back(_lN1);
	m_VlNeighbours.push_back(_lN2);		// update the neighbours
	m_VlNeighbours.push_back(_lN3);

	if (_lN1 < m_lNextEdge)
		m_VlNeighbours[_lN1] = m_lNextEdge;

	if (_lN2 < m_lNextEdge)
		m_VlNeighbours[_lN2] = m_lNextEdge+1;

	if (_lN3 < m_lNextEdge)
		m_VlNeighbours[_lN3] = m_lNextEdge+2;

	m_lNextEdge += 3;					// update position of next edge
	m_lNbTriangles++;					// update the number of triangles

	return lFirst;
}


int32 MeshBase::addPoint(vgm::Vec3f _vPoint)
{
	m_VvPoints.push_back(_vPoint);
	m_lNbPoints++;
	return m_lNbPoints;
}


void MeshBase::addEdge(int32 _lVertex)
{
	m_VlEdges.push_back(_lVertex);		// add vertex index
	m_lNextEdge++;						// update the pos of next edge
	m_VlNeighbours.push_back(-1);		// no neighbour

	if ( (m_lNextEdge%3) == 0 )			// last vertex of triangle
	{
		m_lNbTriangles++;
	}
}


float MeshBase::computeVolume() const
{
	float fTotalVolume=0.;
	int32 nb = m_lNbTriangles*3;
	int32 j=0;
	while (j<nb)
	{
		vgm::Vec3f  u = m_VvPoints[m_VlEdges[j++]];
		vgm::Vec3f  v = m_VvPoints[m_VlEdges[j++]];
		vgm::Vec3f  w = m_VvPoints[m_VlEdges[j++]];
		float fTetraVol = (u.dot((v.cross(w))))/6.f;
		fTotalVolume += fTetraVol;
	}
	return fabs(fTotalVolume);
}


void MeshBase::append(MeshBase& _mbGrowMesh)
{
	int32 lShiftEdge = m_lNextEdge;
	int32 lShiftPoints = m_VvPoints.size();
	
	//add points   
	std::vector<vgm::Vec3f>& VvNewPoints = (std::vector<vgm::Vec3f>&) _mbGrowMesh.getPoints();
	m_VvPoints.insert(m_VvPoints.end(),VvNewPoints.begin(),VvNewPoints.end());
	m_lNbPoints = m_VvPoints.size();
	
	//add edges
	std::vector<int32>& VlNewEdges = _mbGrowMesh.getEdges();
	std::vector<int32>& VlNewNeigh = _mbGrowMesh.getNeighbours();
	std::vector<int32>::const_iterator itEdges = VlNewEdges.begin();
	std::vector<int32>::const_iterator itNeigh = VlNewNeigh.begin();
	while (itEdges != VlNewEdges.end())
	{
		m_VlEdges.push_back(*itEdges + lShiftPoints);
		itEdges++;
		m_VlNeighbours.push_back(*itNeigh + lShiftEdge);
		itNeigh++;
	}
	m_lNextEdge = m_VlEdges.size();
	m_lNbTriangles = m_lNextEdge/3;
}


void MeshBase::computeBB()
{
	int32 lNbPoints = m_VvPoints.size();
	
	m_BB.m_fMaxX = m_VvPoints[0][0];
	m_BB.m_fMaxY = m_VvPoints[0][1];
	m_BB.m_fMaxZ = m_VvPoints[0][2];
	m_BB.m_fMinX = m_BB.m_fMaxX;
	m_BB.m_fMinY = m_BB.m_fMaxY;
	m_BB.m_fMinZ = m_BB.m_fMaxZ;
	
	for (int32 i=1; i<lNbPoints; i++)
	{
		float x = m_VvPoints[i][0];
		float y = m_VvPoints[i][1];
		float z = m_VvPoints[i][2];
		
		if ( x > m_BB.m_fMaxX)
			m_BB.m_fMaxX = x;
		if ( y > m_BB.m_fMaxY)
			m_BB.m_fMaxY = y;
		if ( z > m_BB.m_fMaxZ)
			m_BB.m_fMaxZ = z;

		if ( x < m_BB.m_fMinX)
			m_BB.m_fMinX = x;
		if ( y < m_BB.m_fMinY)
			m_BB.m_fMinY = y;
		if ( z < m_BB.m_fMinZ)
			m_BB.m_fMinZ = z;
	}

	m_BB.m_fWidthX = m_BB.m_fMaxX - m_BB.m_fMinX;
	m_BB.m_fWidthY = m_BB.m_fMaxY - m_BB.m_fMinY;
	m_BB.m_fWidthZ = m_BB.m_fMaxZ - m_BB.m_fMinZ;
}


const MeshBase::BB& MeshBase::getBB() const
{
	return m_BB;
}


float MeshBase::computeSignedVolume() const
{
	float fTotalVolume=0.;
	int32 nb = m_lNbTriangles*3;
	int32 j=0;
	while (j<nb)
	{
		vgm::Vec3f  u = m_VvPoints[m_VlEdges[j++]];
		vgm::Vec3f  v = m_VvPoints[m_VlEdges[j++]];
		vgm::Vec3f  w = m_VvPoints[m_VlEdges[j++]];
		float fTetraVol = (u.dot((v.cross(w))))/6.f;
		fTotalVolume += fTetraVol;
	}
	return fTotalVolume;
}

#undef MAX
#undef MIN

} // namespace vgAlg
