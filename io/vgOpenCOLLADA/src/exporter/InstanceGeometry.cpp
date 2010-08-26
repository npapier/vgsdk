// VGSDK - Copyright (C) 2010 Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgOpenCOLLADA/exporter/InstanceGeometry.hpp"


namespace vgOpenCOLLADA
{

namespace exporter
{

InstanceGeometry::InstanceGeometry( COLLADASW::StreamWriter * streamWriter )
:	COLLADASW::InstanceGeometry ( streamWriter ),
	m_matrixCounter( 0 )
{
}



void InstanceGeometry::addMultipleInstanceMatrix( vgm::MatrixR matrix )
{
	double n[4][4];
	std::stringstream ss;

	ss << "<matrix>";
	for (size_t iRow = 0 ;iRow < 4 ; iRow++) 
	{
		for (size_t iCol = 0; iCol < 4; iCol++) 
		{
			ss <<  matrix[iCol][iRow] << " ";
		}
	}

	ss << "</matrix>" << std::endl;

	m_multipleInstancesText += ss.str();
	m_matrixCounter++;
}



void InstanceGeometry::createMultipleInstances()
{
	m_extraTechnique.addExtraTechniqueTextblock( "profile_vgsdk", m_multipleInstancesText );
	
	m_extraTechnique.addExtraTechniques( mSW );
}


} // namespace exporter

} // namespace vgOpenCOLLADA
