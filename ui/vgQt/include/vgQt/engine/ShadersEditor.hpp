// VGSDK - Copyright (C) 2012, Alexandre Di Pino
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Alexandre Di Pino

#ifndef _VGQT_ENGINE_SHADERSEDITOR_HPP_
#define _VGQT_ENGINE_SHADERSEDITOR_HPP_


#include "vgQt/vgQt.hpp"
#include "vgQt/TextEditorMainWindow.hpp"

#include <glo/GLSLProgram.hpp>
#include <vgeGL/engine/Engine.hpp>
#include <vgUI/Canvas.hpp>
#include <gle/GLSLLanguage.hpp>

#include <QComboBox>
#include <QDockWidget>
#include <QGroupBox>
#include <QPlainTextEdit>
#include <QListWidget>
#include <QMainWindow>
#include <QRadioButton>


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


class VGQT_API ShadersEditor : public vgQt::TextEditorMainWindow
{

Q_OBJECT

public:

	/**
	 * @brief Constructor
	 */
	ShadersEditor(QWidget *parent);

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
	 * @brief Set the canvas to get GLSL information.
	 *
	 * @param	canvas the canva who contain the current engine.
	 */
	void setCanvas(vgUI::Canvas* canvas);

public Q_SLOTS:

	/**
	 * @brief Use this Q_SLOTS to set text in the text editor area depends on a QListWidgetItem
	 *
	 * @param item	the QListWidgetItem who refer the shader.
	 */
	void selectItemInShaderList(QListWidgetItem *item);

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
	void compile(	int notificationType, int position, int length, int linesAdded,
					const QByteArray &text, int line, int foldNow, int foldPrev);

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
	 * @brief Use this Q_SLOTS to change the widget visibility
	 */
	void changeVisibility();

protected:

	 bool event(QEvent * e);

private:

	//GUI element
	QDockWidget*	m_upDock;							//>> Up right dock
	QDockWidget*	m_bottomDock;						//>> Bottom right dock

	QPlainTextEdit*	m_editorLog;						//>> Editor log widget

	QGroupBox*		m_mode;								//>> Group box contain core and compatibility button
	QRadioButton*	m_core;								//>> Choose the core api
	QRadioButton*	m_compatibility;					//>> Choose the compatibility api

	QListWidget*	m_shaderList;						//>> ShaderList Widget
	QComboBox*		m_versionList;						//>> ComboBox contain all OpenGL version

	vgUI::Canvas*					m_canvas;			//>> The current canvas
	vgd::Shp<vgeGL::engine::Engine>	m_engine;			//>> The 3d engine

	typedef std::vector<int> KeysContainer;
	typedef std::back_insert_iterator< KeysContainer >	KeysBackInserter;

	int								m_currentProgram;	//>> The current program on the text editor
	glo::GLSLProgram::ShaderType	m_itemType;			//>> The type of shader on the text editor
	glo::GLSLProgram*				m_managerSaved;		//>> The current GLSLProgram
	int								m_currentShader;	//>> The current shader on the text editor
};



} // namespace engine

} // namespace vgQt

#endif // _VGQT_ENGINE_SHADERSEDITOR_HPP_
