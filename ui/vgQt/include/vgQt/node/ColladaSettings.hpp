// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGQT_NODE_COLLADASETTINGS_HPP_
#define _VGQT_NODE_COLLADASETTINGS_HPP_

#include <vgOpenCOLLADA/Settings.hpp>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QCheckBox>
#include <QLabel>
#include <QSpinBox>
#include <QComboBox>

#include "vgQt/vgQt.hpp"

namespace vgQt
{

namespace node
{



/**
 * @brief	A widget that allows to configure collada import/export settings.
 */
struct VGQT_API ColladaSettings : public QVBoxLayout
{
	/**
	 * @brief	Constructor
	 */
	ColladaSettings();

    vgOpenCOLLADA::Settings getSettings();


private:

    QHBoxLayout*				m_geometryHBox1;
    QHBoxLayout*				m_geometryHBox2;
    QVBoxLayout*				m_geometryVBox;

    QHBoxLayout*				m_textureHBox1;
    QHBoxLayout*				m_textureHBox2;
    QVBoxLayout*				m_textureVBox;

    QHBoxLayout*				m_miscHBox;

    QGroupBox*					m_geometryFrame;
    QGroupBox*					m_textureFrame;
    QGroupBox*					m_miscFrame;

    QCheckBox*      			m_applyGeometricalTransformation;
    QCheckBox*              	m_triangulate;
    QCheckBox*              	m_invertPrimitiveOrientation;
    QCheckBox*              	m_encrypt;
    QCheckBox*              	m_reflective;
    QCheckBox*              	m_bump;
    QCheckBox*              	m_specular;

    QSpinBox*   				m_textureSize;

    QComboBox*      			m_exportLevelCombo;

    QLabel* 					m_textureSizeLabel;
};



} // namespace node

} // namespace vgQt


#endif // _VGQT_NODE_COLLADASETTINGS_HPP_
