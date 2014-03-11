// VGSDK - Copyright (C) 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGGTK_CONTAINER_HPP_
#define _VGGTK_CONTAINER_HPP_

#include <gtkmm.h>

#include <vgd/Shp.hpp>
#include "vgGTK/vgGTK.hpp"



namespace vgGTK
{



/**
 * @brief Element of Container
 *
 * @pre Must be a Gtk::Widget
 */
struct VGGTK_API ContainerElement
{
	/**
	 * @brief Constructor
	 */
	ContainerElement()
	{}

	/**
	 * @brief Virtual destructor
	 */
	virtual ~ContainerElement() {}


	/**
	 * @brief	Signal emited when the settings changed.
	 */
	sigc::signal< void > & signalChanged() { return m_signalChanged; }

private:

	//
	sigc::signal< void >		m_signalChanged;			///< The signal emited when on setting changes.
};



/**
 * @brief A vertical box widget containing \c ContainerElement
 */
struct VGGTK_API Container : public Gtk::VBox
{
	/**
	 * @brief	Constructor
	 */
	Container();

	/**
	 * @brief
	 */
	void add( vgd::Shp< ContainerElement > element );

	/**
	 * @brief	Signal emited when the settings changed.
	 */
	sigc::signal< void > & signalChanged();

private:

	void onSignalChangedFromContainerElement();
	//
	sigc::signal< void >		m_signalChanged;			///< The signal emited when on setting changes.
};



} // namespace vgGTK



#endif // _VGGTK_CONTAINER_HPP_
