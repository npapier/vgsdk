// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGQT_EDITOR_HPP_
#define _VGQT_EDITOR_HPP_

#include <QTextEdit>
#include <ScintillaEdit.h>
#include <string>

class Editor : public ScintillaEdit
{
    Q_OBJECT

public:
    enum Language { CPP, PYTHON, GLSL };

    Editor( QWidget * parent = 0 );
    void setLanguage( Language language);

private:
   std::string customKeywords;

private Q_SLOTS:
    void colourise();
    void onMarginClicked(int position, int modifiers, int margin);
    void showSuggestions();
    void showSuggestionsForced();
};

#endif // _VGQT_EDITOR_HPP_
