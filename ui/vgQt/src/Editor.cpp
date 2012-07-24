// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller, Alexandre Di Pino
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller
// Author Alexandre Di Pino

#include "vgQt/Editor.hpp"

#include <QDebug>
#include <QAction>
#include <QSignalMapper>

#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <list>

static const int MARGIN_SCRIPT_FOLD_INDEX = 1;

Editor::Editor(QWidget* parent) :
    ScintillaEdit(parent),
	m_version(static_cast<gle::GLSL_VERSION_LANGUAGE>(static_cast<int>(gle::MAX_VERSION_LANGUAGE) - 1))
{
    styleClearAll();
    setMarginWidthN(0,25); // par défaut la marge 0 est le nombre de ligne
    autoCSetIgnoreCase(true);

    connect(this, SIGNAL(marginClicked(int,int,int)), this, SLOT(onMarginClicked(int,int,int)));
    connect(this, SIGNAL(charAdded(int)), this, SLOT(colourise()));
    connect(this, SIGNAL(charAdded(int)), this, SLOT(showSuggestions()));

	// Defined the variable autocompletion shortcut
    QAction* keywordAction = new QAction(this);
    keywordAction->setShortcut(QKeySequence(tr("Ctrl+Shift+K") ));
    keywordAction->setShortcutContext(Qt::WidgetShortcut);
    addAction(keywordAction);

	// Defined the function autocompletion shortcut
    QAction* functionAction = new QAction(this);
    functionAction->setShortcut(QKeySequence(tr("Ctrl+Shift+F") ));
    functionAction->setShortcutContext(Qt::WidgetShortcut);
    addAction(functionAction);

	// Defined the builtin variable autocompletion shortcut
    QAction* variableAction = new QAction(this);
    variableAction->setShortcut(QKeySequence(tr("Ctrl+Shift+V") ));
    variableAction->setShortcutContext(Qt::WidgetShortcut);
    addAction(variableAction);

	// Use all keywords autocompletion
    QAction* action = new QAction(this);
    action->setShortcut(QKeySequence(tr("Ctrl+Space") ));
    action->setShortcutContext(Qt::WidgetShortcut);
    addAction(action);

	QSignalMapper* signalMapper = new QSignalMapper(this);

	// Set a signalmapper to pass an argument
	connect(keywordAction, SIGNAL( triggered() ), signalMapper, SLOT(map()));
	connect(functionAction, SIGNAL( triggered() ), signalMapper, SLOT(map()));
	connect(variableAction, SIGNAL( triggered() ), signalMapper, SLOT(map()));
	connect(action, SIGNAL( triggered() ), signalMapper, SLOT(map()));

 	// 0, 1, 2 and 3 are the values used to check what shortcut it is
	signalMapper->setMapping(keywordAction, 0);
	signalMapper->setMapping(functionAction, 1);
	signalMapper->setMapping(variableAction, 2);
	signalMapper->setMapping(action, 3);

	// Connect to the signal function
	connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(showSuggestionsForced(int)) );
}

void Editor::setLanguage( Language language)
{
    switch(language)
    {
    case(CPP):
        setLexerLanguage("cpp");
        setStyleBits(5);

        setProperty("fold", "1");

        setMarginMaskN( MARGIN_SCRIPT_FOLD_INDEX, SC_MASK_FOLDERS);
        setMarginWidthN( MARGIN_SCRIPT_FOLD_INDEX, 20);
        setMarginSensitiveN( MARGIN_SCRIPT_FOLD_INDEX, true);
        markerDefine( SC_MARKNUM_FOLDER, SC_MARK_PLUS);
        markerDefine( SC_MARKNUM_FOLDEROPEN, SC_MARK_MINUS);
        markerDefine( SC_MARKNUM_FOLDEREND, SC_MARK_EMPTY);
        markerDefine( SC_MARKNUM_FOLDERMIDTAIL, SC_MARK_EMPTY);
        markerDefine( SC_MARKNUM_FOLDEROPENMID, SC_MARK_EMPTY);
        markerDefine( SC_MARKNUM_FOLDERSUB, SC_MARK_EMPTY);
        markerDefine( SC_MARKNUM_FOLDERTAIL, SC_MARK_EMPTY);
        setFoldFlags(16);

        customKeywords = "and and_eq asm auto bitand bitor bool break" \
                " case catch char class compl const const_cast continue" \
                " default delete do double dynamic_cast else enum explicit export extern false float for" \
                " friend goto if inline int long mutable namespace new not not_eq" \
                " operator or or_eq private protected public" \
                " register reinterpret_cast return short signed sizeof static static_cast struct switch" \
                " template this throw true try typedef typeid typename union unsigned using" \
                " virtual void volatile wchar_t while xor xor_eq";

        //setKeyWords(0, customKeywords.c_str());

        styleSetFore(1, 0x007f00); // multiline comment 
        styleSetFore(2, 0x007f00); // comment inline
        styleSetFore(4, 0xff9900); // number
        styleSetFore(5, 0xff0000); // keyword
        styleSetBold(5, true);
        styleSetFore(6, 0x007f00); // string
        styleSetFore(9, 0xff0000); // preprocessor
        styleSetFore(10, 0x1d0ccf); // operator
        styleSetFore(19, 0x0000ff); // global class

        break;


    case(PYTHON):
        setLexerLanguage("python");
        setStyleBits(5);

        setProperty("fold", "1");

        setMarginMaskN( MARGIN_SCRIPT_FOLD_INDEX, SC_MASK_FOLDERS);
        setMarginWidthN( MARGIN_SCRIPT_FOLD_INDEX, 20);
        setMarginSensitiveN( MARGIN_SCRIPT_FOLD_INDEX, true);
        markerDefine( SC_MARKNUM_FOLDER, SC_MARK_PLUS);
        markerDefine( SC_MARKNUM_FOLDEROPEN, SC_MARK_MINUS);
        markerDefine( SC_MARKNUM_FOLDEREND, SC_MARK_EMPTY);
        markerDefine( SC_MARKNUM_FOLDERMIDTAIL, SC_MARK_EMPTY);
        markerDefine( SC_MARKNUM_FOLDEROPENMID, SC_MARK_EMPTY);
        markerDefine( SC_MARKNUM_FOLDERSUB, SC_MARK_EMPTY);
        markerDefine( SC_MARKNUM_FOLDERTAIL, SC_MARK_EMPTY);
        setFoldFlags(16);

        customKeywords = "and as assert break class continue def del elif else except exec" \
                " False finally for from global if import in is lambda None nonlocal" \
                " not or pass print raise return True try while with yield";
       // setKeyWords(0, customKeywords.c_str());

        styleSetFore(0, 0x808080);
        styleSetFore(1, 0x007F00);
        styleSetFore(2, 0x7F7F00);
        styleSetFore(3, 0x7F007F);
        styleSetFore(4, 0x7F007F);
        styleSetFore(5, 0x7F0000);
        styleSetBold(5, true);
        styleSetFore(6, 0x00007F);
        styleSetFore(7, 0x00007F);
        styleSetFore(8, 0xFF0000);
        styleSetFore(9, 0x7F7F00);
        styleSetFore(10, 0x1d0ccf);
        styleSetFore(12, 0x7F7F7F);
        styleSetFore(13, 0x000000);
        styleSetFore(14, 0x907040);
        styleSetFore(15, 0x005080);
        styleSetFore(34, 0xFF0000);
        styleSetFore(35, 0x0000FF);

        break;
    case(GLSL):
        setLexerLanguage("cpp");
        setStyleBits(5);

		setGLSLVersion(m_version);

		styleSetFore(1, 0x007f00); // multiline comment 
        styleSetFore(2, 0x007f00); // comment inline
        styleSetFore(4, 0xff9900); // number
        styleSetFore(5, 0xff0000);
        styleSetBold(5, false);
        styleSetFore(6, 0x007f00); // string
        styleSetFore(9, 0xff0000); // preprocessor
        styleSetFore(10, 0x1d0ccf); // operator
        styleSetFore(19, 0x0000ff); // global class

        break;
    }
}

void Editor::setGLSLVersion(gle::GLSL_VERSION_LANGUAGE version)
{
	m_version = version;
	std::list< std::string > vKeywords = gle::getGLSLKeywords(m_version);
	std::list< std::string > fKeywords = gle::getGLSLFunctions(m_version);
	std::list< std::string > bKeywords = gle::getGLSLVariables(m_version);
	std::list<std::string > allKeywords = gle::getAllKeywords(m_version);

	m_keywords.clear();
	m_functions.clear();
	m_variables.clear();
	m_allkeywords.clear();

	typedef std::list< std::string >::const_iterator KeywordsIterator;

	for ( KeywordsIterator it = vKeywords.begin(); it != vKeywords.end(); ++it)
	{
		m_keywords += *it + " ";
	}

	for ( KeywordsIterator it = fKeywords.begin(); it != fKeywords.end(); ++it)
	{
		m_functions += *it + " ";
	}

	for ( KeywordsIterator it = bKeywords.begin(); it != bKeywords.end(); ++it)
	{
		m_variables += *it + " ";
	}

	for ( KeywordsIterator it = allKeywords.begin(); it != allKeywords.end(); ++it)
	{
		m_allkeywords += *it + " ";
	}
   // setKeyWords(0, customKeywords.c_str());
}

const gle::GLSL_VERSION_LANGUAGE Editor::getGLSLVersion() const
{
	return m_version;
}

void Editor::onMarginClicked(int position, int modifiers, int margin)
{
    Q_UNUSED(modifiers);
    switch(margin)
    {
        case MARGIN_SCRIPT_FOLD_INDEX:
            const int line = lineFromPosition(position);
            toggleFold(line);
            break;
    }
}

void Editor::colourise()
{
    ScintillaEdit::colourise(0, -1);
}

void Editor::showSuggestions()
{
    int pos = currentPos();
    int lengthEntered = pos - wordStartPosition(pos, true);
    if (lengthEntered > 0)
    {
        autoCShow(lengthEntered, customKeywords.c_str());
    }
}

void Editor::showSuggestionsForced(int i)
{
    int pos = currentPos();
    int lengthEntered = pos - wordStartPosition(pos, true);
	
	switch(i)
	{
	case 0:
		customKeywords = m_keywords;
		break;
	case 1:
		customKeywords = m_functions;
		break;
	case 2:
		customKeywords = m_variables;
		break;
	case 3:
		customKeywords = m_allkeywords;
		break;
	}

	autoCShow(lengthEntered, customKeywords.c_str());
}

/*
#define SCE_C_DEFAULT 0
#define SCE_C_COMMENT 1
#define SCE_C_COMMENTLINE 2
#define SCE_C_COMMENTDOC 3
#define SCE_C_NUMBER 4
#define SCE_C_WORD 5
#define SCE_C_STRING 6
#define SCE_C_CHARACTER 7
#define SCE_C_UUID 8
#define SCE_C_PREPROCESSOR 9
#define SCE_C_OPERATOR 10
#define SCE_C_IDENTIFIER 11
#define SCE_C_STRINGEOL 12
#define SCE_C_VERBATIM 13
#define SCE_C_REGEX 14
#define SCE_C_COMMENTLINEDOC 15
#define SCE_C_WORD2 16
#define SCE_C_COMMENTDOCKEYWORD 17
#define SCE_C_COMMENTDOCKEYWORDERROR 18
#define SCE_C_GLOBALCLASS 19
#define SCE_C_STRINGRAW 20
#define SCE_C_TRIPLEVERBATIM 21
#define SCE_C_HASHQUOTEDSTRING 22
*/
