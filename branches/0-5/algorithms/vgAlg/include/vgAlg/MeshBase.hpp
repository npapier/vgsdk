// VGSDK - Copyright (C) 2004, Sylvain Thery.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Sylvain Thery
// Author Nicolas Papier
// 23-12-2004 : Integration of MeshBase and MeshTopology from Sylvain Thery was done.

#ifndef _VGALG_MESHBASE_HPP
#define _VGALG_MESHBASE_HPP

#include <vector>
#include <vgd/node/TriSet.hpp>
#include <vgm/Vector.hpp>

#include "vgAlg/vgAlg.hpp"


namespace vgAlg
{


struct VGALG_API MeshBase 
{
protected:
	/**
	* Table of points
	*/
	std::vector<vgm::Vec3f> m_VvPoints;

	/**
	* Table of edges
	*/
	std::vector<int32> m_VlEdges;

	/**
	* Table of neighbours
	*/
	std::vector<int32> m_VlNeighbours;

	/**
	* Number of points
	*/
	int32 m_lNbPoints;

	/**
	* Number of triangles
	*/
	int32 m_lNbTriangles;
	
	/**
	* Index of next edge to insert
	*/
	int32 m_lNextEdge;

	/**
	* structure for axis aligned bounding box
	*/
	typedef struct
	{
		float m_fMaxX;
		float m_fMaxY;
		float m_fMaxZ;
		
		float m_fMinX;
		float m_fMinY;
		float m_fMinZ;
		
		float m_fWidthX;
		float m_fWidthY;
		float m_fWidthZ;
	} BB;
	
	/**
	 * the bounding box
	 */
	BB m_BB;
	
public:

	/**
	* Default constructor
	* do nothing
	*/
	MeshBase();	

	/**
	* Constructor
	* @param pTriSet TriSet used to initialize the MeshBase.
	* 
	* @todo remove copy of data to improve speed.
	*/
	MeshBase( vgd::Shp< vgd::node::TriSet > pTriSet );	

	/**
	* Constructor
	* @param pVertexShape VertexShape used to initialize the MeshBase.
	* 
	* @todo remove copy of data to improve speed.
	*/
	MeshBase( vgd::Shp< vgd::node::VertexShape > pVertexShape );	
	
	/**
	* Destructor
	* do nothing
	*/
	virtual ~MeshBase();

	/**
	* compute the bounding box
	*/
	void computeBB();
		
	/**
	* accessor to table of edges
	*/
	std::vector<int32>& getEdges() { return m_VlEdges; }

	/**
	* accessor to table of neighbours
	*/
	std::vector<int32>& getNeighbours() { return m_VlEdges; }
	
	
	/**
	* accessor to number of triangles
	*/	
	int32 getNbTriangles()  { return m_lNbTriangles;} const

	/**
	* accessor to number of points
	*/	
	int32 getNbPoints()  { return m_VvPoints.size();} const
	int32 getNumPoints()  { return m_VvPoints.size();} const
	
	/**
	* accessor to table of points
	*/
	std::vector<vgm::Vec3f>& getPoints() { return m_VvPoints; }


	/**
	* accessor to points
	* @param _lIndex index of point
	* @return vgm::Vec3f&
	*/
	vgm::Vec3f& getPoint(int32 _lIndex) { return m_VvPoints[_lIndex];} 

	/**
	* modificator off points
	* @param _lIndex index of point
	* @param _pos the position of point
	*/
	void setPoint(int32 _lIndex, const vgm::Vec3f& _pos) { m_VvPoints[_lIndex] = _pos;}


	/**
	* accessor to edges
	* @param _lIndex index of edge
	* @return int32
	*/
	int32 getEdge(int32 _lIndex) { return m_VlEdges[_lIndex];} const

	/**
	* accessor to points from edge index
	* @param _lIndex index of edge
	* @return vgm::Vec3f&
	*/
	vgm::Vec3f& getPointEdge(int32 _lIndex) { return m_VvPoints[m_VlEdges[_lIndex]];} const

	
 	/**
	* accessor to neighbours
	* @param _lIndex index of neighbour
	* @return vgm::Vec3f&
	*/
	int32 getNeighbour(int32 _lIndex) { return m_VlNeighbours[_lIndex];} const

	/**
	* modificator of edges
	* @param _lIndex index of edge
	* @param _lVal value
	*/
	void setEdge(int32 _lIndex, int32 _lVal) { m_VlEdges[_lIndex] = _lVal;}

	/**
	* modificator of neighbours
	* @param _lIndex index of edge
	* @param _lVal value
	*/
	void setNeighbour(int32 _lIndex, int32 _lVal) { m_VlNeighbours[_lIndex] = _lVal;}

	/**
	* accessor to the location of next edge (eq of number of edge)
	*/
	int32 getNextEdge() { return m_lNextEdge;}
	
	/**
	* accessor to the BB
	*/
	const BB& getBB() const;
	
	/**
	* load a a mesh from file
	* @param _cName the name of file to read
	*/
	bool loadTrian(const char* _cName);
	
	/**
	* save a a mesh into a file
	* @param _cName the name of file to write
	*/
	bool saveTrian(const char* _cName) const;
	
	/**
	* get the next edge of triangle
	* @param _lEdge current edge
	*/
	int32 A1(const int32 _lEdge) const;
	
	/**
	* get the previous edge of triangle
	* @param _lEdge current edge
	*/
	int32 A11(const int32 _lEdge) const;
	
	/**
	* get the neighbour of an edge
	* @param _lEdge the edge
	*/
	int32 A2(const int32 _lEdge) const;

	/**
	* add a face to the mesh, with no neighbours (-1 affected)
	* @param _lV1 first vertex index
	* @param _lV2 second vertex index
	* @param _lV3 third vertex index
	*/
	int32 addFace(int32 _lV1, int32 _lV2, int32 _lV3);
	
	/**
	* add a face to the mesh with neighbour
	* @param _lV1 first vertex index
	* @param _lV2 second vertex index
	* @param _lV3 third vertex index
	* @param _lN1 first edge neighbour
	* @param _lN2 second edge neighbour
	* @param _lN3 third edge neighbour
	:q*/	
	int32 addFace(int32 _lV1, int32 _lV2, int32 _lV3, int32 _lN1, int32 _lN2, int32 _lN3);

	/**
	* add a point in the mesh
	*
	* @param _vPoint the point to add
	*/
	int32 addPoint(vgm::Vec3f _vPoint);


	/**
	* add a edge in the mesh (DANGEROUS, USE CAREFOULY)
	*
	* @param _lVertex the vertex corresponding to the edge to add
	*/
	void addEdge(int32 _lVertex);


	/**
	* append a mesh after this
	* @param _mbGrowMesh mesh to append
	*/
	void append(MeshBase& _mbGrowMesh);
	
	/**
	* compute the volume !!
	* @return float the volume !!
	*/
	float computeVolume() const;

	float computeSignedVolume() const;
};

} // namespace vgAlg

#endif //#ifndef _VGALG_MESHBASE_HPP
