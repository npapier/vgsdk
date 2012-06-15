// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#include "vgQt/AboutDialog.hpp"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>

namespace vgQt
{

AboutDialog::AboutDialog( QWidget* parent )
    :QDialog( parent ),
      m_title( new QLabel() ),
      m_comment( new QLabel() ),
      m_copyright( new QLabel() ),
      m_website( new QLabel() )
{
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(m_title);
    layout->addWidget(m_comment);
    layout->addWidget(m_copyright);
    layout->addWidget(m_website);

    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    QPushButton* buttonCredits = new QPushButton("Credits");
    QPushButton* buttonLicense = new QPushButton("License");
    QPushButton* buttonClose = new QPushButton("Close");
    buttonsLayout->addWidget(buttonCredits);
    buttonsLayout->addWidget(buttonLicense);
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(buttonClose);
    layout->addLayout(buttonsLayout);

    setLayout(layout);

    connect(buttonClose, SIGNAL(clicked()), this, SLOT(close()));
    connect(buttonCredits, SIGNAL(clicked()), this, SLOT(onCredits()));
    connect(buttonLicense, SIGNAL(clicked()), this, SLOT(onLicence()));

    // design
    m_title->setAlignment(Qt::AlignCenter);
    m_title->setTextFormat(Qt::RichText);
    m_comment->setAlignment(Qt::AlignCenter);
    m_website->setAlignment(Qt::AlignCenter);
    m_website->setOpenExternalLinks(true);
    m_copyright->setTextFormat(Qt::RichText);
    m_copyright->setAlignment(Qt::AlignCenter);
}

void AboutDialog::set_authors( QList< QString > authors )
{
    m_authors = authors;
}

void AboutDialog::set_title( QString title )
{
    m_title->setText("<h1>" + title + "</h1>");
}


void AboutDialog::set_comments( QString comment )
{
    m_comment->setText(comment);
}

void AboutDialog::set_copyright ( QString copyright )
{
    m_copyright->setText("<span style='font-size:7pt;'>" + copyright + "</span>");
}

void AboutDialog::set_license ( QString licence )
{
    m_licence = licence;
}

void AboutDialog::set_website ( QString website )
{
    m_website->setText("<a href=\"" + website + "\">" + website + "</a>");
}

void AboutDialog::onCredits()
{
    QString credits = QString("Written by:\n");
    Q_FOREACH(QString author, m_authors)
    {
        credits.append( author + "\n" );
    }

    QMessageBox::about( this, "Written by", credits );
}

void AboutDialog::onLicence()
{
    QMessageBox::about( this, "License", m_licence );
}

} // namespace vgQt
