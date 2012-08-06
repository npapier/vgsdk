// VGSDK - Copyright (C) 2012, Alexandre Di Pino
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Alexandre Di Pino

#ifndef _VGQT_TEXTEDITOR_HPP_
#define _VGQT_TEXTEDITOR_HPP_

#include "vgQt/vgQt.hpp"
#include "vgQt/Editor.hpp"

#include <QHBoxLayout>
#include <QLineEdit>
#include <QMainWindow>
#include <QMenu>
#include <QPushButton>
#include <QWidget>


namespace vgQt
{


class VGQT_API TextEditor : public QMainWindow
{

Q_OBJECT

public:

	/**
	 * @brief Constructor
	 */
	TextEditor(const std::string& title, QWidget *parent = 0);

	/**
	 * @brief Create the find and replace menu (open with Ctrl + F).
	 */
	void createFindAndReplaceMenu();

	/**
	 * @brief Create the Goto line menu (open with Ctrl + G).
	 */
	void createGoToLineMenu();

public Q_SLOTS:

	/**
	 * @brief Use this Q_SLOTS when you need the window on top.
	 */
	void onTop( bool );

	/**
	 * @brief Use this Q_SLOTS to open the find and replace menu
	 */
	void findAndReplaceMenu();

	/**
	 * @brief Use this Q_SLOTS to find a word in the editor
	 *
	 * @param text	the text to find
	 */
	void findWithMenu(const QString &text);

	/**
	 * @brief Use this Q_SLOTS to go to the next selection
	 */
	void setNextSelection(bool check);

	/**
	 * @brief Use this Q_SLOTS to replace all selected word by an other.
	 */
	void replaceAllSelected(bool check);

	/**
	 * @brief Use this Q_SLOTS to replace the current
	 */
	void replaceCurrent(bool check);

	/**
	 * @brief Use this Q_SLOTS to go at the specified line
	 */
	void gotoLine(const QString & lineNumber);

	/**
	 * @brief Use this Q_SLOTS to open the Goto line menu
	 */
	void goToMenu();

protected:

	//GUI ELEMENT
	QWidget*		m_findMenu;
	QLineEdit*		m_findText;
	QLineEdit*		m_replaceText;
	QPushButton*	m_findAction;
	QPushButton*	m_replaceAction;
	QPushButton*	m_replaceAllAction;

	QAction*		m_menuStayTop;

	QWidget*		m_goToMenu;
	QLineEdit*		m_line;

	QMenu*			m_file;
	QMenu*			m_edit;

	Editor*			m_textEditor;

	bool			m_newText;
};


}

#endif // _VGQT_TEXTEDITOR_HPP_