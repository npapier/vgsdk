// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller, Alexandre Di Pino
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller
// Author Alexandre Di Pino

#ifndef _VGQT_EDITOR_HPP_
#define _VGQT_EDITOR_HPP_

#include <QTextEdit>
#include <ScintillaEdit.h>
#include <string>
#include <gle/GLSLLanguage.hpp>

class Editor : public ScintillaEdit
{
    Q_OBJECT

public:
    enum Language { CPP, PYTHON, GLSL };

	/**
	 * @brief	Constructor
	 */
    Editor( QWidget * parent = 0 );

	/**
	 * @brief	Set Current Language 
	 *
	 * @param	language enum to set the language
	 */
    void setLanguage( Language language);


	const std::string getTextKeywords(const int size);
	/**
	 * @brief	Set the GLSL version to the lexer
	 *
	 * @param	version	the GLSL version
	 */
	void setGLSLVersion(gle::GLSL_VERSION_LANGUAGE version);

	/**
	 * @brief	Set the GLSL version to the lexer (Compatibility mode)
	 *
	 * @param	version	the GLSL version
	 */
	void setGLSLVersionCompatibility(gle::GLSL_VERSION_LANGUAGE version);

	/**
	 * @brief	Get the current GLSL version setted to the lexer
	 *
	 * @return	the GLSL version
	 */
	const gle::GLSL_VERSION_LANGUAGE getGLSLVersion() const;

	/**
	 * @brief	Set a red marker on a line
	 *
	 * @param	line the line number
	 */
	void setLineMarker(int line);

	/**
	 * @brief	Clear all error marker
	 */
	void clearAllUnderligned();

	/**
	 * @brief	Select one or several word
	 *
	 * @param	text the text to find
	 *
	 * @param	seeAll true if select all same word on the text editorm false otherwise
	 */
	void selectText(const std::string& text, const bool seeAll);

	/**
	 * @brief	Set the current selection if you have several same word
	 *
	 * @param	i the current selection
	 */
	void setCurrentSelection(const int i);

	/**
	 * @brief	Get the current selection if you have several same word
	 */
	const int getCurrentSelection();


	/**
	 * @brief	Find a word and return a vector of position
	 *
	 * @param	word the word to find in the editor
	 */
	const std::vector<QPair<int, int>> find(const std::string& word);

private:

	/**
	 * @brief	Sort a simple string by alphabetical order
	 *
	 * @param	dictionnary the dictionnary non sorted
	 */
	const std::string sortDictionnary(const std::string dictionnary/*, const bool resorted*/);

private:
	std::string customKeywords;
	std::string m_keywords;
	std::string m_functions;
	std::string m_variables;
	std::string m_allkeywords;
	int			m_currentSelection;
	gle::GLSL_VERSION_LANGUAGE m_version;

private Q_SLOTS:
    void colourise();
    void onMarginClicked(int position, int modifiers, int margin);
    void showSuggestions();
    void showSuggestionsForced(int i);
	void onDoubleClick(int position, int line);
};

#endif // _VGQT_EDITOR_HPP_
