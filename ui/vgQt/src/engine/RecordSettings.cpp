// VGSDK - Copyright (C) 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgQt/engine/RecordSettings.hpp"

#include <QGroupBox>
#include <QVBoxLayout>

#include <vgUI/Canvas.hpp>
#include <vgUI/event/CaptureEventProcessor.hpp>


namespace vgQt
{

namespace engine
{


RecordSettings::RecordSettings()
{
	QGroupBox * captureGroupBox = new QGroupBox(tr("Maximum number of captures per second"));
	QVBoxLayout * captureVbox = new QVBoxLayout;
	m_captureFPS = new QLineEdit();
	captureGroupBox->setLayout( captureVbox );
	captureVbox->addWidget( m_captureFPS );

	m_color = new QCheckBox("Record c&olor buffer");
	m_depth = new QCheckBox("Record &depth buffer");
	m_camera = new QCheckBox("Record c&amera parameters");

	m_shortcutkey = new QTextEdit();
	m_activate = new QCheckBox("Activate shortcut keys");

	addWidget(captureGroupBox);

	addWidget(m_color);
	addWidget(m_depth);
	addWidget(m_camera);

	addWidget(m_shortcutkey);

	addWidget(m_activate);

	// addStretch(); @todo

	connect(m_captureFPS, SIGNAL(textChanged(const QString &)), (RecordSettings*) this, SLOT(onCaptureFPS()));
	//connect(m_color, SIGNAL(clicked()), (RecordSettings*) this, SLOT(onColor()));
	//connect(m_depth, SIGNAL(clicked()), (RecordSettings*) this, SLOT(onDepth()));
	//connect(m_camera, SIGNAL(clicked()), (RecordSettings*) this, SLOT(onCamera()));

	connect(m_activate, SIGNAL(clicked()), (RecordSettings*) this, SLOT(onActivate()));
}


void RecordSettings::setCanvas( vgUI::Canvas * canvas )
{
	m_canvas = canvas;

	// Initializes GUI
	if ( m_canvas )
	{
		using vgUI::event::CaptureEventProcessor;

		// Retrieving capture event processor
		const int index = m_canvas->findEventProcessor< CaptureEventProcessor >();
		if ( index != m_canvas->getNumEventProcessors() )
		{
			// Capture event processor found
			m_captureEventProcessor = m_canvas->getEventProcessor< CaptureEventProcessor >(index);
			m_activate->setChecked( true );
		}
		else
		{
			// No capture event processor found

			// Create a new one and 
			m_captureEventProcessor.reset( new CaptureEventProcessor(m_canvas) );

			m_activate->setChecked( false );
		}

		// Configure GUI
		QString captureFPS;
		captureFPS.setNum( m_canvas->getMaxNumberOfCapturesPerSecond() );
		m_captureFPS->setText( captureFPS );

		m_color->setChecked( true );
		m_color->setDisabled( true );

		m_depth->setChecked( false );
		m_depth->setDisabled( true );

		m_camera->setChecked( true );
		m_camera->setDisabled( true );

		m_shortcutkey->setText("Press 'S' key to take a screenshot.\nPress 'Space' to start/stop recording.");
		m_shortcutkey->setDisabled( true );
		m_shortcutkey->setReadOnly(true);
	}
}


void RecordSettings::onCaptureFPS()
{
	QString str = m_captureFPS->text();
	const uint captureFPS = str.toInt();
	m_canvas->setMaxNumberOfCapturesPerSecond( captureFPS );
}


void RecordSettings::onActivate()
{
	const bool desiredState = m_activate->isChecked();

	// Retrieving capture event processor
	const int indexEP = m_canvas->findEventProcessor( m_captureEventProcessor );
	const bool isEPFound = (indexEP != m_canvas->getNumEventProcessors());
	if ( desiredState )
	{
		// Install capture event processor
		if ( !isEPFound )
		{
			// install it in the canvas
			m_canvas->insertEventProcessor( m_captureEventProcessor );
		}
		// else nothing to do
	}
	else
	{
		// Uninstall capture event processor
		if ( isEPFound )
		{
			// Removes capture event processor
			m_canvas->removeEventProcessor( indexEP );

			// Stops video capture
			m_canvas->setVideoCapture(false);
		}
		// else nothing to do
	}
}


} // namespace engine

} // namespace vgQt
