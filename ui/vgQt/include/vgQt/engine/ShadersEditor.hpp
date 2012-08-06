// VGSDK - Copyright (C) 2012, Alexandre Di Pino
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Alexandre Di Pino

#ifndef _VGQT_ENGINE_SHADERSEDITOR_HPP_
#define _VGQT_ENGINE_SHADERSEDITOR_HPP_


#include "vgQt/vgQt.hpp"
#include "vgQt/TextEditor.hpp"

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


class VGQT_API ShadersEditor : public vgQt::TextEditor
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

protected:

	 bool event(QEvent * e);

private:

	//GUI element
	QDockWidget*	m_upDock;
	QDockWidget*	m_bottomDock;

	QWidget*		m_upWidget;
	QWidget*		m_bottomWidget;

	QPlainTextEdit*	m_editorLog;

	QGroupBox*		m_mode;
	QRadioButton*	m_core;
	QRadioButton*	m_compatibility;

	QListWidget*	m_shaderList;
	QComboBox*		m_versionList;

	vgUI::Canvas*					m_canvas;
	vgd::Shp<vgeGL::engine::Engine>	m_engine;

	int								m_currentProgram;
	glo::GLSLProgram::ShaderType	m_itemType;
	glo::GLSLProgram*				m_managerSaved;
	int								m_currentShader;
};



} // namespace engine

} // namespace vgQt

#endif // _VGQT_ENGINE_SHADERSEDITOR_HPP_