// VGSDK - Copyright (C) 2010 Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGOPENCOLLADA_EXPORTER_INSTANCEGEOMETRY_HPP
#define _VGOPENCOLLADA_EXPORTER_INSTANCEGEOMETRY_HPP

#include <COLLADASWInstanceGeometry.h>
#include <COLLADASWExtraTechnique.h>

#include <vgm/Matrix.hpp>


namespace vgOpenCOLLADA
{

namespace exporter
{

/**
 * @brief	COLLADA instance geometry.
 *			Adds vgSDK MultiInstances support.
 */
struct InstanceGeometry : public COLLADASW::InstanceGeometry
{

	InstanceGeometry( COLLADASW::StreamWriter * streamWriter );

	void addMultipleInstanceMatrix( vgm::MatrixR matrix );
	void createMultipleInstances();

private:
	COLLADASW::BaseExtraTechnique	m_extraTechnique;
	int								m_matrixCounter;
	std::string						m_multipleInstancesText;

};

} // namespace exporter

} // namespace vgOpenCOLLADA

#endif // _VGOPENCOLLADA_EXPORTER_INSTANCEGEOMETRY_HPP