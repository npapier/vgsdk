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

#include <QWidget>
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QFrame>
#include <QDockWidget>
#include <QMainWindow>
#include <QCheckBox>

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


class VGQT_API ShadersEditor : public QWidget
{
Q_OBJECT

public:
	ShadersEditor(vgUI::Canvas* canvas, QWidget *parent = 0);
	
public Q_SLOTS:

	/**
	 * @brief Use this Q_SLOTS to set text in the text editor aream depens on a QListWidgetItem
	 *
	 * @param item	the QListWidgetItem who refer the shader.
	 *
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

private:

	//GUI element
	vgd::Shp< Editor >			m_textEditor;
	vgd::Shp< QPlainTextEdit >	m_editorLog;
	
	vgd::Shp< QHBoxLayout >		m_layout;
	
	vgd::Shp< QVBoxLayout >		m_rightLayout;
	vgd::Shp< QVBoxLayout >		m_progLayout;
	vgd::Shp< QVBoxLayout >		m_buttonLayout;
	vgd::Shp< QVBoxLayout >		m_logLayout;
	
	vgd::Shp< QPushButton >		m_refresh;
	vgd::Shp< QCheckBox >		m_stayTop;
	vgd::Shp< QListWidget >		m_shaderList;

	vgUI::Canvas*					m_canvas;
	vgd::Shp<vgeGL::engine::Engine>	m_engine;

	eShaderType					m_currentType;
	QListWidgetItem*			m_itemSaved;
	glo::GLSLProgram*			m_managerSaved;
	int							m_shaderSaved;

	bool						m_newText;

	static const std::string	m_stringShaderType[];
};



} // namespace engine

} // namespace vgQt

#endif // _VGQT_ENGINE_SHADERSEDITOR_HPP_