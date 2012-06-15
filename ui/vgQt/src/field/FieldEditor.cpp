// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#include "vgQt/field/operations.hpp"

#include "vgQt/field/FieldEditor.hpp"

#include "vgQt/graph/convenience.hpp"

#include <QEvent>

namespace vgQt
{

namespace field
{

FieldEditor::FieldEditor()
{
    m_canvas = 0;
}

FieldEditor::~FieldEditor()
{}

void FieldEditor::setField( vgd::Shp< vgd::field::FieldManager > fieldManager, const QString fieldName )
{
	m_fieldManager	= fieldManager;
	m_fieldName		= fieldName;
	
    refresh();
}

void FieldEditor::initialize(QWidget* parent, vgUI::Canvas * canvas)
{
    m_canvas = canvas;
    QHBoxLayout* layout = new QHBoxLayout();

    layout->addLayout( getLayout() );
    QPushButton* rollbackButton = new QPushButton( "&Revert" );
    layout->addStretch();
    layout->addWidget(rollbackButton);

    connect(getWidget(), SIGNAL(signalChanged()), this, SLOT(onEditorChanged()));
    connect(getWidget(), SIGNAL(signalChanged()), parent, SIGNAL(onChangeSignal()));

    connect(rollbackButton, SIGNAL(pressed()), this, SLOT(onRollback()));

    if( m_fieldManager->isField("f_name") )
    {
        connect(getWidget(), SIGNAL(signalChanged()), this, SLOT(refreshLabel()));
    }

    refreshLabel();
    setLayout( layout );
}

void FieldEditor::refreshLabel()
{
    const std::string	name = vgUI::graph::getFieldAsString(m_fieldManager, "f_name");
    QString title = name.empty() ? "Unamed" : QString(name.c_str());

    Q_EMIT titleChanged(title);
}

void FieldEditor::onEditorChanged()
{
    commit();

    if( m_canvas )
    {
        m_canvas->refresh();
    }
}

void FieldEditor::onRollback()
{
    rollback();

    if( m_canvas )
    {
        m_canvas->refresh();
    }
}

void FieldEditor::updateField( const vgd::field::AbstractField & rField, const vgd::field::Event event )
{
    Q_UNUSED(rField);
    Q_UNUSED(event);
}

} // namespace field

} // namespace vgQt
