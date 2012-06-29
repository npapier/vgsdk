// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#include "vgQt/ResolutionDialog.hpp"

#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>

namespace vgQt
{


ResolutionDialog::ResolutionDialog( QMainWindow* widget )
    : QDialog(widget),
      m_widget(widget->centralWidget()),
      m_resetButton(new QPushButton("Undo")),
      m_applyButton(new QPushButton("Apply")),
      m_resolutions(new QComboBox()),
      m_oldResolution	( m_widget->width(), m_widget->height() ),
      m_newResolution	( m_widget->width(), m_widget->height() )

{
    QVBoxLayout* layout = new QVBoxLayout();
    QLabel* label = new QLabel("Select, in the list bellow, a resolution to apply, \nor specify your own.");
    m_resolutions->addItem(resolutionToString(m_widget->width(), m_widget->height()));
    m_resolutions->addItem("1024x768");
    m_resolutions->addItem("800x600");
    m_resolutions->addItem("720x576");
    m_resolutions->addItem("640x480");
    m_resolutions->setEditable(true);
    QPushButton* closeButton = new QPushButton("Close");

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(m_resetButton);
    buttonLayout->addWidget(m_applyButton);
    buttonLayout->addWidget(closeButton);

    layout->addWidget(label);
    layout->addWidget(m_resolutions);
    layout->addLayout(buttonLayout);

    setLayout(layout);

    connect(m_resetButton, SIGNAL(clicked()), this, SLOT(resetClicked()));
    connect(m_applyButton, SIGNAL(clicked()), this, SLOT(applyClicked()));
    connect(m_resolutions, SIGNAL(currentIndexChanged(QString)), this, SLOT(resolutionChanged(QString)));
    connect(m_resolutions, SIGNAL(editTextChanged(QString)), this, SLOT(resolutionChanged(QString)));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
}

void ResolutionDialog::applyResolution( const int width, const int height )
{
	int mainWindowWidth = ((QWidget*) m_widget->parent())->width();
	int mainWindowHeight = ((QWidget*) m_widget->parent())->height();
	
	((QWidget*) m_widget->parent())->resize( mainWindowWidth - m_widget->width() + width, mainWindowHeight - m_widget->height() + height );
}


void ResolutionDialog::resetClicked()
{
	applyResolution(m_oldResolution.first, m_oldResolution.second);
}

void ResolutionDialog::applyClicked()
{
    if( m_newResolution.first != m_widget->width() || m_newResolution.second != m_widget->height() )
    {
        applyResolution( m_newResolution.first, m_newResolution.second );
    }
}

void ResolutionDialog::resolutionChanged(QString text)
{
    const bool parsed = resolutionFromString( text, m_newResolution.first, m_newResolution.second );

    m_applyButton->setDisabled(!parsed);
}

const bool ResolutionDialog::resolutionFromString( QString text, int &width, int &height )
{
    QRegExp rx("^\\s*(\\d+)\\s*x\\s*(\\d+)\\s*$");
    int pos = rx.indexIn(text);
    if(pos > -1)
    {
        width = rx.cap(1).toInt();
        height = rx.cap(2).toInt();
        return true;
    }
    return false;
}

const QString ResolutionDialog::resolutionToString( const int width, const int height )
{
    return QString::number(width) + "x" + QString::number(height);
}

} // namespace vgQt
