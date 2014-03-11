// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#include "vgQt/actions/alg/EncryptFileAction.hpp"

#include <vgAlg/actions/Encrypt.hpp>

#include <fstream>
#include <QFileDialog>
#include <QInputDialog>
#include <QObject>

namespace vgQt
{

namespace actions
{

namespace alg
{


EncryptFileAction::EncryptFileAction()
{}



EncryptFileAction::~EncryptFileAction()
{}


void EncryptFileAction::execute()
{
    QString originalFile = QFileDialog::getOpenFileName(0,
        QObject::tr("File to encrypt"), "", QObject::tr("All supported file (*.DAE *.trian2 *.png *.jpg);;COLLADA file (*.DAE);;Trian2 file (*.trian2);;Image file (*.png *.jpg)"));
    if (originalFile == "")
        return;

    QString encryptedFile = QFileDialog::getSaveFileName(0, QObject::tr("Save encrypted file as.."),
                                "",
                                QObject::tr("COLLADA Encrypted file (*.dae.crypt);;Trian2 Encrypted file (*.trian2.crypt);;Jpg Encrypted file (*.jpg.crypt);;PNG Encrypted file (*.png.crypt)"));
    if(encryptedFile == "")
        return;

    bool ok;
    QString key = QInputDialog::getText(0, QObject::tr("Set encryption key"),
                                              QObject::tr("Key:"), QLineEdit::Normal,
                                        "vgsdkViewerGTK", &ok);

    if(!ok)
        return;

    std::ifstream inFile;
    inFile.open( originalFile.toStdString().c_str(), std::ifstream::in | std::ifstream::binary );
    inFile.seekg (0, std::ios::end);
    int length = inFile.tellg();
    inFile.seekg (0, std::ios::beg);

    vgd::Shp< std::vector<char> > inBuffer( new std::vector<char> );
    inBuffer->resize( length );
    inFile.read( &(*inBuffer)[0], length );

    vgd::Shp< std::vector<char> > outBuffer( new std::vector<char> );
    vgAlg::actions::Encrypt encrypt;

    encrypt.setInitialize( key.toStdString(), inBuffer, outBuffer );
    encrypt.execute();

    std::ofstream outFile( encryptedFile.toStdString().c_str(), std::ios::trunc | std::ios::binary );
    for( unsigned int i = 0; i < outBuffer->size(); ++i )
    {
        outFile << (*outBuffer)[i];
    }
    outFile.close();
    inFile.close();
}


} // namespace alg

} // namespace actions

} // namespace vgQt
