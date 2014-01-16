// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#if _MSC_VER <= 1600

#include "vgQt/node/ColladaSettings.hpp"

#include <QPushButton>

namespace vgQt
{

namespace node
{

ColladaSettings::ColladaSettings()
{
    m_geometryFrame = new QGroupBox("Geometry settings");
    m_textureFrame = new QGroupBox("Texture settings");
    m_miscFrame = new QGroupBox("Other settings");

    m_geometryVBox = new QVBoxLayout();
    m_geometryHBox1 = new QHBoxLayout();
    m_applyGeometricalTransformation = new QCheckBox("Apply geometrical transformation");
    m_triangulate = new QCheckBox("Triangulate");
    m_invertPrimitiveOrientation = new QCheckBox("Invert primitives orientation");
    m_geometryHBox1->addWidget(m_applyGeometricalTransformation, 0, Qt::AlignCenter);
    m_geometryHBox1->addWidget(m_triangulate, 0, Qt::AlignCenter);
    m_geometryHBox2 = new QHBoxLayout();
    m_geometryHBox2->addWidget(m_invertPrimitiveOrientation, 0, Qt::AlignCenter);
    m_geometryVBox->addLayout(m_geometryHBox1);
    m_geometryVBox->addLayout(m_geometryHBox2);
    m_geometryFrame->setLayout(m_geometryVBox);


    m_textureVBox = new QVBoxLayout();
    m_textureHBox1 = new QHBoxLayout();
    m_textureHBox2 = new QHBoxLayout();
    m_textureSizeLabel = new QLabel("Maximum texture Size:");
    m_textureSize = new QSpinBox();
    m_textureSize->setRange( 1, 32768 );
    m_textureSize->setValue( 8192 );
    m_reflective = new QCheckBox("Reflective");
    m_bump = new QCheckBox("Bump");
    m_specular = new QCheckBox("Specular");
    m_textureHBox1->addWidget(m_textureSizeLabel, 0, Qt::AlignCenter);
    m_textureHBox1->addWidget(m_textureSize, 0, Qt::AlignCenter);
    m_textureHBox2->addWidget(m_reflective, 0, Qt::AlignCenter);
    m_textureHBox2->addWidget(m_bump, 0, Qt::AlignCenter);
    m_textureHBox2->addWidget(m_specular, 0, Qt::AlignCenter);
    m_textureVBox->addLayout(m_textureHBox1);
    m_textureVBox->addLayout(m_textureHBox2);
    m_textureFrame->setLayout(m_textureVBox);

    m_miscHBox = new QHBoxLayout();
    m_exportLevelCombo = new QComboBox();
    m_exportLevelCombo->addItem("Geometry only");
    m_exportLevelCombo->addItem("Material");
    m_exportLevelCombo->addItem("Texture");
    m_exportLevelCombo->setCurrentIndex(2);

    m_encrypt = new QCheckBox("Encrypt");
    m_miscHBox->addWidget(m_exportLevelCombo, 0, Qt::AlignCenter);
    m_miscHBox->addWidget(m_encrypt, 0, Qt::AlignCenter);
    m_miscFrame->setLayout(m_miscHBox);

    addWidget(m_geometryFrame);
    addWidget(m_textureFrame);
    addWidget(m_miscFrame);

    m_reflective->setDisabled(true);
    m_bump->setDisabled(true);
    m_specular->setDisabled(true);

    // Disable
    m_reflective->setDisabled(true);
    m_bump->setDisabled(true);
    m_specular->setDisabled(true);
    m_encrypt->setDisabled(true);
}



vgOpenCOLLADA::Settings ColladaSettings::getSettings()
{
    bool applyGeometricalTransformation = m_applyGeometricalTransformation->isChecked();
    bool triangulate = m_triangulate->isChecked();
    bool invertPrimitiveOrientation = m_invertPrimitiveOrientation->isChecked();
    bool encrypt = m_encrypt->isChecked();
    bool reflective = m_reflective->isChecked();
    bool bump = m_bump->isChecked();
    bool specular = m_specular->isChecked();
    int textureSize = m_textureSize->value();

	vgOpenCOLLADA::LEVEL exportLevel;

    int rowNumber = m_exportLevelCombo->currentIndex();
	switch( rowNumber )
	{
		case 0:
			exportLevel = vgOpenCOLLADA::GEOMETRY;
			break;
		case 1:
			exportLevel = vgOpenCOLLADA::MATERIAL;
			break;
		case 2:
			exportLevel = vgOpenCOLLADA::TEXTURE;
			break;
		default:
			exportLevel = vgOpenCOLLADA::TEXTURE;
			break;
	}

	vgOpenCOLLADA::Settings settings( applyGeometricalTransformation, triangulate, invertPrimitiveOrientation, 
		encrypt, reflective, bump, specular, textureSize, exportLevel );

	return settings;
}



} // namespace node

} // namespace vgQt

#endif // #if _MSC_VER <= 1600