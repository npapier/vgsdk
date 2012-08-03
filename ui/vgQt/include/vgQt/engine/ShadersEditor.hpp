// VGSDK - Copyright (C) 2012, Alexandre Di Pino
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Alexandre Di Pino

#ifndef _VGQT_ENGINE_SHADERSEDITOR_HPP_
#define _VGQT_ENGINE_SHADERSEDITOR_HPP_


#include "vgQt/vgQt.hpp"
#include "vgQt/Editor.hpp"
#include <glo/GLSLProgram.hpp>
#include <vgeGL/engine/Engine.hpp>
#include <vgUI/Canvas.hpp>
#include <gle/GLSLLanguage.hpp>

#include <QCheckBox>
#include <QComboBox>
#include <QDockWidget>
#include <QFrame>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPlainTextEdit>
#include <QLineEdit>
#include <QListWidget>
#include <QMainWindow>
#include <QMenu>
#include <QPushButton>
#include <QRadioButton>
#include <QSplitter>
#include <QVBoxLayout>
#include <QWidget>


namespace vgUI
{
	struct Canvas;
}


namespace vgQt
{

namespace engine
{


/**
 * @brief enum for Qt QListWidgetItem
 * @remark 1000 is the first id for user defined in Qt
 */
enum eShaderType
{
	VERTEX_SHADER = 1000,
	TESSELATION_CONTROL_SHADER,
	TESSELATION_EVALUATION_SHADER,
	GEOMETRY_SHADER,
	FRAGMENT_SHADER,
	PROGRAM_SHADER,
	NONE,
	DEFAULT_SHADER_TYPE = VERTEX_SHADER
};


class VGQT_API ShadersEditor : public QMainWindow
{
Q_OBJECT

public:

	/**
	 * @brief Constructor
	 */
	ShadersEditor(vgUI::Canvas* canvas, QWidget *parent = 0);

	/**
	 * @brief Check if the shader contain a #version
	 *
	 * @param shader	the current shader.
	 */
	void checkVersionOnShader(const std::string& shader);

	/**
	 * @brief Check if the shader contain error
	 *
	 * @param log	the current shader.
	 */
	void checkErrorLine(const std::string& log);


	/**
	 * @brief Create the find and replace menu (open with Ctrl + F).
	 */
	void createFindAndReplaceMenu();

public Q_SLOTS:

	/**
	 * @brief Use this Q_SLOTS to set text in the text editor aream depens on a QListWidgetItem
	 *
	 * @param item	the QListWidgetItem who refer the shader.
	 */
	void checkText(QListWidgetItem *item);

	/**
	 * @brief Use this Q_SLOTS to refresh the shader manager.
	 */
	void refreshUI();

	/**
	 * @brief Use this Q_SLOTS when you need compile the current edited shader.
	 *
	 * By default, the shader editor compile when you change a letter in the editor.
	 *
	 */
	void compile(int notificationType, int position, int length, int linesAdded,
	              const QByteArray &text, int line, int foldNow, int foldPrev);

	/**
	 * @brief Use this Q_SLOTS when you need the window on top.
	 */
	void onTop( int );

	/**
	 * @brief Use this Q_SLOTS when you change the GLSL version value
	 */
	void versionChanged( int );

	/**
	 * @brief Use this Q_SLOTS when you change the GLSL mode to core
	 */
	void modeCore( bool );

	/**
	 * @brief Use this Q_SLOTS when you change the GLSL mode to compatibility
	 */
	void modeCompatibility( bool );

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

protected:

	 bool event(QEvent * e);

private:

	//GUI element
	QWidget*			m_findMenu;
	QLineEdit*			m_findText;
	QLineEdit*			m_replaceText;
	QPushButton*		m_findAction;
	QPushButton*		m_replaceAction;
	QPushButton*		m_replaceAllAction;

	QMenu*				m_file;
	QMenu*				m_edit;

	QDockWidget*		m_upDock;
	QDockWidget*		m_bottomDock;

	QWidget*			m_upWidget;
	QWidget*			m_bottomWidget;

	Editor*				m_textEditor;
	QPlainTextEdit*		m_editorLog;

	QGroupBox*			m_mode;
	QRadioButton*		m_core;
	QRadioButton*		m_compatibility;

	QCheckBox*			m_stayTop;

	QListWidget*		m_shaderList;
	QComboBox*			m_versionList;

	vgUI::Canvas*					m_canvas;
	vgd::Shp<vgeGL::engine::Engine>	m_engine;

	int								m_currentProgram;
	glo::GLSLProgram::ShaderType	m_itemType;
	glo::GLSLProgram*				m_managerSaved;
	int								m_currentShader;

	bool							m_newText;
};



} // namespace engine

} // namespace vgQt

#endif // _VGQT_ENGINE_SHADERSEDITOR_HPP_