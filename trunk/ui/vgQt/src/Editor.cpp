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

#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <set>
#include <sstream>
#include <string>

//#include <boost/container/list.hpp>
#include <boost/foreach.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/tokenizer.hpp>
#include <boost/regex.hpp>

static const int MARGIN_SCRIPT_FOLD_INDEX = 1;

namespace
{
/**
 * @brief	Case insensitive comparison of two string
 *
 * @param	first the first string to compare
 *
 * @param	second the second string to compare
 *
 * @return	true if first < second
 */
const bool compareNoCase(std::string first, std::string second)
{
	std::transform(first.begin(), first.end(), first.begin(), tolower);
	std::transform(second.begin(), second.end(), second.begin(), tolower);

	int i = first.compare(0, second.length(), second);

	return ( (i < 0 ) ? true : false );
}

}

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

	// Use all keywords autocompletion
    QAction* textAction = new QAction(this);
    textAction->setShortcut(QKeySequence(tr("Ctrl+Return") ));
    textAction->setShortcutContext(Qt::WidgetShortcut);
    addAction(textAction);

	QSignalMapper* signalMapper = new QSignalMapper(this);

	// Set a signalmapper to pass an argument
	connect(keywordAction, SIGNAL( triggered() ), signalMapper, SLOT(map()));
	connect(functionAction, SIGNAL( triggered() ), signalMapper, SLOT(map()));
	connect(variableAction, SIGNAL( triggered() ), signalMapper, SLOT(map()));
	connect(action, SIGNAL( triggered() ), signalMapper, SLOT(map()));

	connect(textAction, SIGNAL( triggered() ), signalMapper, SLOT(map()));

 	// 0, 1, 2 and 3 are the values used to check what shortcut it is
	signalMapper->setMapping(keywordAction, 0);
	signalMapper->setMapping(functionAction, 1);
	signalMapper->setMapping(variableAction, 2);
	signalMapper->setMapping(action, 3);
	signalMapper->setMapping(textAction, 4);


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

const std::string Editor::sortDictionnary(const std::string dictionnary, const bool resorted)
{
	std::string retVal("");
	boost::char_separator<char> sep(" ");
    boost::tokenizer<boost::char_separator<char>> tokens(dictionnary, sep);

	if (!resorted)
	{
		return dictionnary;
		/*BOOST_FOREACH(std::string t, tokens)
		{
			retVal += t + " ";
		}*/
	}
	else
	{
		std::set<std::string> tmpValue;

		BOOST_FOREACH(std::string t, tokens)
		{
			tmpValue.insert(t);
		}

		std::set<std::string, const bool(*)(std::string, std::string)> newset(tmpValue.begin(), tmpValue.end(), compareNoCase);

		for (std::set<std::string, const bool(*)(std::string, std::string)>::const_iterator it = newset.begin(); it != newset.end(); ++it)
		{
			retVal += *it + " ";
		}
	}
	return retVal;
}

const std::string Editor::getTextKeywords(const int size)
{
	QString tmptext = getText(textLength());
	std::string text = tmptext.toStdString();
	boost::regex expression("^[0-9 ]+$");
	boost::cmatch matches;

	std::string retVal("");
	boost::char_separator<char> sep(" \n()\t*-+.\\;|/,=");
    boost::tokenizer<boost::char_separator<char>> tokens(text, sep);

	std::set<std::string> tmpValue;

	BOOST_FOREACH(std::string t, tokens)
	{
		if (t.size() >= size && (boost::regex_match(t.c_str(), matches, expression) == false))
		{
			tmpValue.insert(t);
		}
	}

	std::set<std::string, const bool(*)(std::string, std::string)> newset(tmpValue.begin(), tmpValue.end(), compareNoCase);

	for (std::set<std::string, const bool(*)(std::string, std::string)>::const_iterator it = newset.begin(); it != newset.end(); ++it)
	{
		retVal += *it + " ";
	}

	return retVal;
}

void Editor::setGLSLVersion(gle::GLSL_VERSION_LANGUAGE version)
{
	m_version = version;

	m_keywords.clear();
	m_functions.clear();
	m_variables.clear();
	m_allkeywords.clear();

	m_keywords =  sortDictionnary(gle::getGLSLKeywords(m_version), false);
	m_functions = sortDictionnary(gle::getGLSLFunctions(m_version), false);
	m_variables = sortDictionnary(gle::getGLSLVariables(m_version), false);
	m_allkeywords = sortDictionnary(gle::getAllKeywords(m_version), true);
}

void Editor::setGLSLVersionCompatibility(gle::GLSL_VERSION_LANGUAGE version)
{
	m_version = version;

	m_keywords.clear();
	m_functions.clear();
	m_variables.clear();
	m_allkeywords.clear();

	for (int i = 0 ; i <= static_cast<int>(version); ++i)
	{
		m_keywords +=  gle::getGLSLKeywords(static_cast<gle::GLSL_VERSION_LANGUAGE>(i)) + " ";
		m_functions += gle::getGLSLFunctions(static_cast<gle::GLSL_VERSION_LANGUAGE>(i)) + " ";
		m_variables += gle::getGLSLVariables(static_cast<gle::GLSL_VERSION_LANGUAGE>(i)) + " ";
	}

	m_keywords =  sortDictionnary(m_keywords, true);
	m_functions = sortDictionnary(m_functions, true);
	m_variables = sortDictionnary(m_variables, true);
	m_allkeywords = sortDictionnary(m_keywords + m_functions + m_variables, true);
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
	case 4:
		customKeywords = getTextKeywords(2);
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
