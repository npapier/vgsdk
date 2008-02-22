// VGSDK - Copyright (C) 2004, Sylvain Thery.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Sylvain Thery
// 23-12-2004 : Integration of MeshBase and MeshTopology from Sylvain Thery was done.

#include "vgAlg/MeshTopology.hpp"

#include <list>
#include <iostream>



namespace vgAlg
{



MeshTopology::MeshTopology() : MeshBase()
{
	//std::cerr << "MeshTopoloy Constructor"<<std::endl;
}


MeshTopology::MeshTopology( vgd::Shp< vgd::node::TriSet > pTriSet ) :
	MeshBase( pTriSet )
{
}


MeshTopology::~MeshTopology()
{
}


bool MeshTopology::modifyNeighbour()
{
	std::vector<int32> VlOldNeighbours(m_VlNeighbours);
	
	for(int32 i=0; i<m_lNextEdge; i++)
	{
		int32 lNeigh = VlOldNeighbours[i];
		if (lNeigh <0)
		{
			m_VlNeighbours[A1(i)]  = -1;
		}
		else
		{
			int32 lEdgePoint = A11(i);

			lNeigh *= 3;
			int32 k=0;
			while ( ( m_VlEdges[lNeigh] != m_VlEdges[lEdgePoint] ) && (k <3) )
			{
				lNeigh++;
				k++;
			}
			if (k>=3)
			{
				std::cerr << "Error in neighbour modification"<<std::endl;
				return false;
			}
			m_VlNeighbours[lEdgePoint] = lNeigh;
		}
	}
	return true;
}


void MeshTopology::createGrid(int32 _lWidth, std::vector<int32>& _VlIndicesGrid, std::vector<int32> *_VlGrid ) const
{
	int32 lWidth2 = _lWidth*_lWidth;
	float fWidth = (float)_lWidth;
	int32 lNbPoints = m_VvPoints.size();

	// find subspace of each point
	for (int32 i=0; i<lNbPoints; i++)
	{
		float x = m_VvPoints[i][0];
		float y = m_VvPoints[i][1];		// get coordinates of point
		float z = m_VvPoints[i][2];
		
		// compute coordinate of subspace in which it is included
		int32 lX =  (int32)((x - m_BB.m_fMinX)*fWidth/m_BB.m_fWidthX);
		if (lX == _lWidth)
			lX--;
		int32 lY = (int32)((y - m_BB.m_fMinY)*fWidth/m_BB.m_fWidthY);
		if (lY == _lWidth)
			lY--;
		int32 lZ =  (int32)((z - m_BB.m_fMinZ)*fWidth/m_BB.m_fWidthZ);
		if (lZ == _lWidth)
			lZ--;
		// compute and store the index of the subspace
		_VlIndicesGrid[i] = lZ*lWidth2 + lY*_lWidth + lX;
	}

	// create the grid	
	for (int32 i=0; i<m_lNextEdge; i++)
	{
		// compute the subspace indices of the two points of edge
		int32 ind1 = _VlIndicesGrid[m_VlEdges[i]];
		int32 ind2 = _VlIndicesGrid[m_VlEdges[A1(i)]];
		
		// store the index of edge in two or one (if same) subspace.
		_VlGrid[ind1].push_back(i);
		if (ind2 != ind1)
			_VlGrid[ind2].push_back(i);
	}
}


bool MeshTopology::computeNeighbour(int32 _lWidth)
{
	int32 lNbPoints = m_VvPoints.size();
	std::vector<int32> VlIndicesGrid(lNbPoints);
	std::vector<int32>* VlGrid = new std::vector<int32>[_lWidth*_lWidth*_lWidth];
	
	computeBB();
	
	createGrid(_lWidth, VlIndicesGrid, VlGrid);
	
	// initialization of all neighbour to -1
	for (int32 i=0; i<m_lNextEdge; i++)
	{
		m_VlNeighbours[i] = -1;
	}
	
	// for each edge
	for (int32 i=0; i<m_lNextEdge; i++)
	{
		if ( m_VlNeighbours[i] == -1) // if not yet computed
		{
			std::vector<int32>& vect = VlGrid[VlIndicesGrid[m_VlEdges[i]]]; //select the subspace including edge
			bool finish=false;
			std::vector<int32>::iterator neigh = vect.begin();
			while ((! finish) && (neigh != vect.end())) // test all edges in the subspace
			{
				if (*neigh > i)		//if neighbour edge after edge (else already treated)
				{
					if ( (m_VlEdges[i] == m_VlEdges[A1(*neigh)]) && (m_VlEdges[A1(i)] == m_VlEdges[*neigh]) )
					{										//test if the two edges share the same points
						m_VlNeighbours[i] = *neigh;
						m_VlNeighbours[*neigh] = i;		// update neighbours
						*neigh = -1;					// tag the edge of subspace as used (-1 never after i)
						finish=true;					// stop the research
					}
				}
				neigh++;	// next  edges in subspace
			}
		}
	}
	delete[] VlGrid;
	return true;
}


MeshBase* MeshTopology::ConnectedComponents(int32& _lNbCC) const
{
	std::vector<short> vecFlag(m_lNbTriangles,-1);
	int32 total =0;
	short sNum=0;
	while (total < m_lNbTriangles)
	{
		int32 ltri =findFirstEdge(vecFlag);
		int32 lWidthCC = grow( ltri, vecFlag, sNum);
//		std::cerr << "CC n °"<<sNum<<" : "<<lWidthCC<<" triangles"<<std::endl;
		total +=  lWidthCC;
		sNum++;
	}
	_lNbCC = sNum;
	return createCCMeshes(sNum,vecFlag);
}


int32 MeshTopology::findFirstEdge(const std::vector<short>& _vectFlag) const
{
	int32 i=0;
	while (i<m_lNbTriangles)
	{
		if (_vectFlag[i] ==-1)
		{
			return i;
		}
		i++;
	}
	std::cerr << "Error findFirstEdge: no free triangle found !!"<<std::endl;
	return -1;
}


int32 MeshTopology::grow( int32 _ltri, std::vector<short>& _vectFlag, short _sNum) const
{
	int32 lEdge = 3*_ltri;
	std::list<int32> listEdge;
	listEdge.push_back(lEdge);
	listEdge.push_back(lEdge+1);	
	listEdge.push_back(lEdge+2);
	int32 lNb = 1;
	_vectFlag[_ltri]=_sNum;

	do
	{
		std::list<int32>::iterator deb=listEdge.begin();
		for (std::list<int32>::iterator it=deb; it != listEdge.end(); it++)
		{
			int32 vois = m_VlNeighbours[*it];	// take the neighbour of edge
			int32 trivois = vois/3;				// and the corresponding triangle
			if ((vois != -1) && (_vectFlag[trivois]==-1)) // if not yet used
			{
				_vectFlag[trivois]=_sNum;			  	// set the number of CC
				lNb++;
				int32 vois1 = A1(vois);			// compute index of the second edge of neighbour
				int32 vois2 = A1(vois1);			// compute index of the third edge of neighbou
				if (A2(vois1)>=0)
				{
					if (_vectFlag[A2(vois1)/3]==-1)
					{
						listEdge.push_front(vois1);		// add the second edge if not marked
					}
				}
				if (A2(vois2)>=0)
				{
					if (_vectFlag[A2(vois2)/3]==-1)
					{
						listEdge.push_front(vois2);		// add the third edge if not marked
					}
				}
			}
		}
		listEdge.erase(deb,listEdge.end());	// remove edges of preceding pass
	} while (!listEdge.empty());
		
	return lNb;
}



void MeshTopology::supressUnusedPoints(std::vector<int32>& _VlEdges, std::vector<vgm::Vec3f>& _VvNewPoints) const
{
	int32 lNbPoints = m_VvPoints.size();
	std::vector<int32> VlFlagPoint(lNbPoints,-1);

	// first select used points
	int32 nb = _VlEdges.size();	
	for(int32 i=0; i<nb ;i++)
	{
		VlFlagPoint[_VlEdges[i]] = 1;
	}
	
	// then create the new table of points
	// and the corresponding table in VlFlagPoint
	int32 j=0;
	for(int32 i=0; i< lNbPoints;i++)
	{
		if (VlFlagPoint[i] >= 0)
		{
			_VvNewPoints.push_back(m_VvPoints[i]);
			VlFlagPoint[i] = j++;
		}
	}
	
	// finally modify edges
	for(int32 i=0; i< nb;i++)
	{
		_VlEdges[i] = VlFlagPoint[_VlEdges[i]];
	}
}

MeshBase* MeshTopology::createCCMeshes(short _sNb, std::vector<short>& _vectFlag) const
{
	MeshBase* newMeshes = new MeshBase[_sNb];
	std::vector<int32>  vlNextEdges(_sNb,0);
	std::vector<int32>  vlCorresp(m_lNextEdge);

	//  create a corresponding table for all meshes
	for(int32 i=0; i<m_lNbTriangles; i++)
	{
		int32 j = i*3;
		int32 next =  vlNextEdges[_vectFlag[i]];
		vlCorresp[j++] = next++;
		vlCorresp[j++] = next++;
		vlCorresp[j++] = next++;
		vlNextEdges[_vectFlag[i]] = next;
		vlNextEdges[_vectFlag[i]]++;
	}
	
	// create the faces of all meshes
	for(int32 i=0; i<m_lNbTriangles; i++)
	{
		int32 j=i*3;
		short num = _vectFlag[i];
		int32 p1 = m_VlEdges[j];
		int32 p2 = m_VlEdges[j+1];
		int32 p3 = m_VlEdges[j+2];
		int32 n1 = vlCorresp[m_VlNeighbours[j]];
		int32 n2 = vlCorresp[m_VlNeighbours[j+1]];
		int32 n3 = vlCorresp[m_VlNeighbours[j+2]];
        newMeshes[num].addFace(p1,p2,p3,n1,n2,n3);
	}

	// create the table of points and modify edges of each new mesh
	for(short i=0;i<_sNb;i++)
	{
		std::vector<int32>& VlEdges = newMeshes[i].getEdges();
		std::vector<vgm::Vec3f>& VvNewPoints =(std::vector<vgm::Vec3f>&) newMeshes[i].getPoints();
		supressUnusedPoints(VlEdges, VvNewPoints);
	}
	
	return newMeshes;
}


	

//void CALLBACK MeshTopology::beginCB(GLenum type)
//{
//	if (type == GL_TRIANGLES)
//	{
//		std::cerr << "glBegin(GL_TRIANGLES)"<<std::endl;
//	}
//	else
//	{
//		std::cerr << "Error: not TRIANGLES"<<std::endl;
//	}
//}
//
//
//	
//void CALLBACK MeshTopology::endCB()
//{
//	std::cerr << "glEnd() CB"<<std::endl;
//}
//
//
//void CALLBACK MeshTopology::vertexCB(void* vertexData, void* userData)
//{
//	MeshTopology *mesh = (MeshTopology*)userData;
//	std::vector<int32> *vlContour = mesh->getContour();
//
//	int32 lVertex = mesh->findVertexIndex((GLdouble*)vertexData, vlContour);
//
//	mesh->addEdge(lVertex);
//}
//
//	
//void CALLBACK MeshTopology::edgeflagCB(GLboolean flag)
//{
//}
//
//
//void CALLBACK MeshTopology::errorCB(GLenum _errno)
//{
//	std::cerr << "ERROR CB  "<< gluErrorString(_errno) << std::endl;
//}


//int32 MeshTopology::findVertexIndex(GLdouble* _vertexData, std::vector<int32> *_vlContour)
//{
//#define EPSILON 0.01
//
//    vgm::Vec3f point(_vertexData[0],_vertexData[1],_vertexData[2]);
//
//	for (std::vector<int32>::iterator it = _vlContour->begin(); it != _vlContour->end(); it++)
//	{
//        vgm::Vec3f v = m_VvPoints[*it] - point;
//        float dist = v.getSqrLength();
//        if (dist < EPSILON)
//        {
//			return *it;
//		}
//	}
//	std::cerr << "findVertexIndex FAILED"<<std::endl;
//	return -1;
//	
//#undef EPSILON
//}


//bool MeshTopology::closeContour(std::vector<int32>& _vlContour, vgm::Vec3f& _VNormal)
//{
//
//	int32 lFirstEdge = getNextEdge();
//
//	GLUtesselator* tesselator = gluNewTess();
//	
//	gluTessCallback(tesselator, GLU_TESS_BEGIN, (void (*)())(MeshTopology::beginCB));
//	gluTessCallback(tesselator, GLU_TESS_END, MeshTopology::endCB);
//	gluTessCallback(tesselator, GLU_TESS_VERTEX_DATA, (void (*)())(MeshTopology::vertexCB));
//	gluTessCallback(tesselator, GLU_TESS_EDGE_FLAG, (void (*)())(MeshTopology::edgeflagCB));
//	gluTessCallback(tesselator, GLU_TESS_ERROR, (void (*)())(MeshTopology::errorCB));
//
//	gluTessProperty(tesselator, GLU_TESS_WINDING_RULE, GLU_TESS_WINDING_NONZERO);
//	gluTessNormal(tesselator, (GLdouble)_VNormal[0], (GLdouble)_VNormal[1], (GLdouble)_VNormal[2]);
//	
//	
//	std::vector<int32>::iterator it = _vlContour.begin();
//	GLdouble *pointsIni = new GLdouble[3*_vlContour.size()];
//	GLdouble *points = pointsIni;
//
//	void *userData = (void*)this;
//
//	setContour(&_vlContour);
//	
//	gluTessBeginPolygon(tesselator, userData);
//
//	do
//	{
//		gluTessBeginContour(tesselator);
//		do
//		{
//			GLdouble *point = points;
//			point[0] = (GLdouble)m_VvPoints[*it][0];
//			point[1] = (GLdouble)m_VvPoints[*it][1];	// get point in GLdouble format
//			point[2] = (GLdouble)m_VvPoints[*it][2];
//			gluTessVertex(tesselator, point,point);
//			points++;points++;points++;
//			it++;
//		} while (*it != -1);
//		gluTessEndContour(tesselator);
//		it++;
//	} while (*it != -1);
//
//	gluTessEndPolygon(tesselator);
//
//	gluDeleteTess(tesselator);
//
//	delete pointsIni;
//
//	int32 lLastEdge = getNextEdge() - 1;
//	computeLocalTopology(lFirstEdge, lLastEdge);
//
//	return true;
//}


void MeshTopology::computeLocalTopology(int32 _lFirstEdge, int32 _lLastEdge)
{
	for (int32 i = _lFirstEdge; i <= _lLastEdge; i++)
	{
		int32 p0 = m_VlEdges[i];			// first point of edge
		int32 p1 = m_VlEdges[A1(i)];		// second point of edge

		if (m_VlNeighbours[i] < 0)		// if neighbour not yet computed
		{
			int32 j = i+1;
			while (j <= _lLastEdge)		// search in all next edges
			{
				int32 q0 = m_VlEdges[j];		// first point of other edge
				int32 q1 = m_VlEdges[A1(j)]; // second point of other edge

				if ((p0==q1)&&(p1==q0))		// same edge ??
				{
					m_VlNeighbours[i] = j;
					m_VlNeighbours[j] = i;	// update the neighbours
					j = _lLastEdge;			// little trick to stop searching
				}

				j++;	
			}
		}
	}
}


bool MeshTopology::isNumHoleEqualToZero()
{
	int32 lNb = getNextEdge(); //A changer en NumEdge
	
	for(int32 i= 0; i<lNb; i++)
	{
		int32 lNeigh = getNeighbour(i);
		if (lNeigh == -1)
		{
			return false;
		}
	}
	return true;
}


/*
void MeshTopology::equilateralisation()
{
	int32 nb = m_VlEdges.size();
	std::vector<float> VfLength(nb,-1.0);
	std::vector<float> VfAngle(nb,-1.0);
	
	for (int32 i = 0; i <= nb; i+=3)
	{
		computeTriangleLengthAngles(i, VfAngle, VfLength);
	}

	
    while (fini)
	{
		for (int32 i = 0; i <= nb; i++)
		{
			

 	}

}




float MeshTopology::getMaxEdgeAngle(int32 _lEdge, const std::vector<float>& _VfAngle)
{
    float fAngle=0.0f;
	int32 lEdge  = _lEdge;
	
	if (_VfAngle[lEdge]	> fAngleMax)
	{
		fAngleMax = _VfAngle[lEdge];
	}

	lEdge = A1(lEdge);
	if (_VfAngle[lEdge]	> fAngleMax)
	{
		fAngleMax = _VfAngle[lEdge];
	}

	lEdge = A1(lEdge);
	if (_VfAngle[lEdge]	> fAngleMax)
	{
		fAngleMax = _VfAngle[lEdge];
	}

	lEdge = A2(_lEdge);
	if (_VfAngle[lEdge]	> fAngleMax)
	{
		fAngleMax = _VfAngle[lEdge];
	}

	lEdge = A1(lEdge);
	if (_VfAngle[lEdge]	> fAngleMax)
	{
		fAngleMax = _VfAngle[lEdge];
	}

	lEdge = A1(lEdge);
	if (_VfAngle[lEdge]	> fAngleMax)
	{
		fAngleMax = _VfAngle[lEdge];
	}

	return fAngleMax;
}


void MeshTopology::swapEdge(int32 _lEdge, std::vector<float>& _VfAngle, std::vector<float>& _VfLength)
{
	int32 lEdgeA = _lEdge;
	int32 lEdgeA1 = A1(lEdgeA);
	int32 lEdgeA2 = A11(lEdgeA);

	int32 lEdgeB = A2(_lEdge);
	int32 lEdgeB1 = A1(lEdgeB);
	int32 lEdgeB2 = A11(lEdgeB);

	// update edges

	setEdge(lEdgeA1, getEdge(lEdgeB2));
	setEdge(lEdgeB1, getEdge(lEdgeA2));

	//update neighbours

	setNeighbour(lEdgeA, getNeighbour(lEdgeB1));
	setNeighbour(lEdgeB, getNeighbour(lEdgeA1));
	setNeighbour(lEdgeA1, lEdgeB1);
	setNeighbour(lEdgeB1, lEdgeA1);

	// update length of edges

	_VfLength[lEdgeA] = _VfLength[lEdgeB1];
	_VfLength[lEdgeB] = _VfLength[lEdgeA1];

	vgm::Vec3f diag = getPointEdge(lEdgeA1) - getPointEdge(lEdgeB1);
	float fNewLength = diag.getLength();
	_VfLength[lEdgeA1] = _VfLength[lEdgeA1];
	_VfLength[lEdgeB1] = _VfLength[lEdgeA1];

 	// update angles

	computeTriangleAngles(lEdgeA, VfAngle, VfLength);
	computeTriangleAngles(lEdgeB, VfAngle, VfLength);
}





void MeshTopology::computeTriangleLengthAngles(int32 _lEdge, std::vector<float>& _VfAngle, std::vector<float>& _VfLength )
{
	int32 lEd = _lEdge;
	int32 lEd1 = A1(lEd);
	int32 lEd2 = A11(lEd);

	vgm::Vec3f P0 = getPointEdge(lEd);
	vgm::Vec3f P1 = getPointEdge(lEd1);
	vgm::Vec3f P2 = getPointEdge(lEd2);

	vgm::Vec3f vEdge0 = P1 - P0;
	vgm::Vec3f vEdge1 = P2 - P1;
	vgm::Vec3f vEdge2 = P0 - P2;

	if (_VfLength[lEd]<0)
	{
       	_VfLength[lEd] = vEdge0.getLength();
		_VfLength[getNeighbour(lEd)] = VfLength[lEd];
	}
	if (_VfLength[lEd1]<0)
	{
       	_VfLength[lEd1] = vEdge1.getLength();
		_VfLength[getNeighbour(lEd1)] = VfLength[lEd1];
	}
	if (_VfLength[lEd2]<0)
	{
       	_VfLength[lEd2] = vEdge2.getLength();
		_VfLength[getNeighbour(lEd2)] = VfLength[lEd2];
	}

	VfAngle[lEd]  = 1.0f + (vEdge0*vEdge2/(VfLength[lEd]*VfLength[lEd2]));	// not really angle but 1 - cos(angle)
	VfAngle[lEd1] = 1.0f + (vEdge1*vEdge0/(VfLength[lEd1]*VfLength[lEd]));	// [0 .. PI] -> [0 .. 2]
	VfAngle[lEd2] = 1.0f + (vEdge2*vEdge1/(VfLength[lEd2]*VfLength[lEd1]));
}


void MeshTopology::computeTriangleAngles(int32 _lEdge, std::vector<float>& _VfAngle, const std::vector<float>& _VfLength )
{
	int32 lEd = _lEdge;
	int32 lEd1 = A1(lEd);
	int32 lEd2 = A11(lEd);

	vgm::Vec3f P0 = getPointEdge(lEd);
	vgm::Vec3f P1 = getPointEdge(lEd1);
	vgm::Vec3f P2 = getPointEdge(lEd2);

	vgm::Vec3f vEdge0 = P1 - P0;
	vgm::Vec3f vEdge1 = P2 - P1;
	vgm::Vec3f vEdge2 = P0 - P2;

	VfAngle[lEd]  = 1.0f + (vEdge0*vEdge2/(VfLength[lEd]*VfLength[lEd2]));	// not really angle but 1 - cos(angle)
	VfAngle[lEd1] = 1.0f + (vEdge1*vEdge0/(VfLength[lEd1]*VfLength[lEd]));	// [0 .. PI] -> [0 .. 2]
	VfAngle[lEd2] = 1.0f + (vEdge2*vEdge1/(VfLength[lEd2]*VfLength[lEd1]));
}

*/

} // namespace vgAlg
