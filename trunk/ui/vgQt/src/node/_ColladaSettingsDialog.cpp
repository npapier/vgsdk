// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#if _MSC_VER <= 1600

#include "vgQt/node/ColladaSettingsDialog.hpp"

#include <QPushButton>

namespace vgQt
{

namespace node
{



ColladaSettingsDialog::ColladaSettingsDialog()
:	QDialog( )
{
    setWindowTitle("Collada Export Settings");

    m_exportCollada = new ColladaSettings();
    setLayout(m_exportCollada);

    QPushButton* oKButton = new QPushButton("OK");
    QPushButton* cancelButton = new QPushButton("Cancel");
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(oKButton);
    buttonLayout->addWidget(cancelButton);
    m_exportCollada->addLayout(buttonLayout);
    QObject::connect(oKButton, SIGNAL(clicked()), this, SLOT(accept()));
    QObject::connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

vgOpenCOLLADA::Settings ColladaSettingsDialog::getSettings()
{
    return m_exportCollada->getSettings();
}



} // namespace node

} // namespace vgQt

#endif // #if _MSC_VER <= 1600