// VGSDK - Copyright (C) 2004, Sylvain Thery.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Sylvain Thery
// Author Nicolas Papier
// 23-12-2004 : Integration of MeshBase and MeshTopology from Sylvain Thery was done.

#ifndef _VGALG_MESHTOPOLOGY_HPP
#define _VGALG_MESHTOPOLOGY_HPP

#include "vgAlg/vgAlg.hpp"
#include "vgAlg/MeshBase.hpp"
//#include <GL/glu.h>
//#ifndef CALLBACK
//#define CALLBACK
//#endif


namespace vgAlg
{


/**
 * @todo Enable Callbak from GLU and derived functionnalities (see closeContour()).
 * @todo Reenable findVertexIndex()
 * 
 */
struct VGALG_API MeshTopology : public MeshBase
{
protected:
	
	/**
	* create the acceleration grid (space subdivision)
	* @param int32 _lWidth subdivision of BB
	* @param std::vector<int32>& _VlIndicesGrid the table of indices of each point in the grid
	* @param std::vector<int32>* _VlGrid the grid
	*/
	void createGrid(int32 _lWidth, std::vector<int32>& _VlIndicesGrid, std::vector<int32>* _VlGrid ) const;


	/**
	* find the first edge which is not yet used
	* @param std::vector<short>& _vectFlag the table of flag to store the CC
	*/
	int32 findFirstEdge(const std::vector<short>& _vectFlag) const;
	
	/**
	* grow a connected component
	* @param int32 _ltri index of initial triangle
	* @param std::vector<short>& _vectFlag table of flag to store the CC
	* @param short _sNum the number affected to CC
	* @return int32 the number of triangle in CC
	*/
	int32 grow( int32 _ltri, std::vector<short>& _vectFlag, short _sNum) const;
	
	
	/**
	* create the new table of points whose are necessary for
	* the new edges table, which is modify to link with the new
	* table of points.
	* @param const std::vector<int32>& _VlEdges the new edges table [IN/OUT]
	* @param std::vector<vgm::Vec3f>& _VvNewPoints the new table [OUT]
	*/
	void supressUnusedPoints(std::vector<int32>& _VlEdges, std::vector<vgm::Vec3f>& _VvNewPoints) const;
	
	/**
	* create a table of meshes from this and a flag table obtain
	* in ConnectedComponents.
	* @param short _sNb number of CC
	* @param std::vector<short>& _vectFlag a table of CC number (one entry per face)
	* @return the table of mesh
	*/
	MeshBase* createCCMeshes(short _sNb,std::vector<short>& _vectFlag)const ;



	/**
	* find the index of 3D vertex (in the table)
	* @param GLdouble* _vertexData the vertex
	* @param std::vector<int32>& _vlContour the table of index 
	* @return the found index
	*/
	//int32 findVertexIndex(GLdouble* _vertexData, std::vector<int32> *_vlContour);


//	void computeTriangleLengthAngles(int32 _lEdge, std::vector<float>& _VfAngle, std::vector<float>& _VfLength);
//
//	void computeTriangleAngles(int32 _lEdge, std::vector<float>& _VfAngle, const std::vector<float>& _Vflength);
//
//    float getMaxEdgeAngle(int32 _lEdge, const std::vector<float>& _VfAngle);
//
//	void swapEdge(int32 _lEdge, std::vector<float>& _VfAngle, std::vector<float>& _VfLength);
//

	//std::vector<int32>* m_VlContour;

public:
	/**
	* default constructor
	*/
	MeshTopology();

	/**
	* Default constructor
	* @param TriSet used to initialize the MeshBase.
	* 
	* @todo remove copy of data to improve speed.
	*/
	MeshTopology( vgd::Shp< vgd::node::TriSet > pTriSet );
	
	/**
	* default destructor
	*(do nothing)
	*/
	~MeshTopology();

	/**
	* compute the "edge neighbours"
	* @param int32 _lWidth the subdivision of BB for acceleration grid
	*/
	bool computeNeighbour(int32 _lWidth);
	
	/**
	* compute the "edge neighbours" from
	* from "face neighbours"
	*/
	bool modifyNeighbour();
	
	/**
	* compute the connected components of the mesh
	* @param int32& _lNbCC the number of CC
	* @return a table of allocated meshes
	*/
	MeshBase* ConnectedComponents(int32& _lNbCC) const;


	/**
	* close a give contour with triangles
	* a contour is a list of index. It can include several closed
	* contour . Each of them is fisnished by a -1, and the last
	* by -1 -1
	* @param std::vector<int32>& _vlContour
	* @param vgm::Vec3f& _VNormal
	*/
	//bool closeContour(std::vector<int32>& _vlContour, vgm::Vec3f& _VNormal);

//   	/**
//	* begin callback for tesselator
//	* @param GLenum _type the type of primitive (GL_TRIANGLES)
//	*/
//	static void beginCB(GLenum _type);
//
//	/**
//	* begin callback for tesselator
//	*/
//	static void endCB();
//
//	/**
//	* begin callback for tesselator
//	* @param void* _vertexData the vertex in GLdouble* format
//	* @param void* _userData
//	*/
//	static void vertexCB(void* _vertexData, void* _userData);
//
//	/**
//	* begin callback for tesselator
//	* @param GLboolean _flag edge flag
//	*/
//	static void edgeflagCB(GLboolean _flag);
//
//	/**
//	* begin callback for tesselator
//	* @param GLenum _errorno
//	*/
//	static void errorCB(GLenum _errorno);


	/**
	* set the contour (use by closeContour)
	* @param std::vector<int32> *_VlContour the contour, a std::vector of index on points
	*/
	//void setContour(std::vector<int32> *_VlContour) {m_VlContour = _VlContour;}

	/**
	* get contour (use by closeContour)
	* @return std::vector<int32>* the contour
	*/
	//std::vector<int32>* getContour() { return m_VlContour;}


	/**
	* compute the topology (neighbours) on a limited range of edges
	* @param int32 _lFirstEdge begin of range to treat
	* @param int32 _lLastEdge end of range to treat
	*/
	void computeLocalTopology(int32 _lFirstEdge, int32 _lLastEdge);


	/**
	* return true if there is no hole in the mesh
	*/
	bool isNumHoleEqualToZero();

	/**
	* compute holes in the mesh
	*
	* @return a std::vector of index
	*
	std::vector<int32> getHoles();
*/
};

} // namespace vgAlg

#endif //#ifndef _VGALG_MESHTOPOLOGY_HPP
