// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#ifndef _VGGTK_EVENT_SIGNALHANDLER_HPP_
#define _VGGTK_EVENT_SIGNALHANDLER_HPP_

#include <gtkmm/widget.h>



namespace vgGTK
{

namespace event
{



/**
 * @brief	Provides the abstract implementation for GTK signal handling devices
 * 			with automatic signal callback connection lifetime management.
 */
struct SignalHandler
{

	/**
	 * @brief	Constructor
	 */
	SignalHandler();

	/**
	 * @brief	Destructor
	 */
	virtual ~SignalHandler();


	/**
	 * @name	Signal Connection Managament
	 */
	//@{

	/**
	 * @brief	Tells the signale handler to connect to the given GTK widget.
	 *
	 * Sub-classes must override this method in order to connect signal callbacks and store
	 * connections.
	 *
	 * @param	widget	a pointer to the widget to connect to
	 *
	 * @see		disconnect, store
	 */
	virtual void connect( Gtk::Widget * widget );

	/**
	 * @brief	Tells of the signal handler is connected to any widget.
	 */
	const bool isConnected() const;

	/**
	 * @brief	Disconnects the signal handler for it widget.
	 *
	 * All stored connections will be automatically disconnected.
	 * Sub-classes may override this method in order to
	 * perform additionnal treatements.
	 *
	 * @see	connect, store
	 */
	virtual void disconnect();
	//@}


protected:

	/**
	 * @brief	Stores a given signal callback connection.
	 *
	 * Storing a signal callback connection allows automatic disconnection when
	 * calling disconnect method or when the instance gets destroyed.
	 *
	 * @see	connect, disconnect
	 */
	void store( const ::sigc::connection & connection );


private:

	typedef std::vector< ::sigc::connection > ConnectionContainer;	///< Defines a collection for sigc++ connections.

	::Gtk::Widget		* m_connectedWidget;	///< A pointer to the widget the mouse is connected to (null if none).
	ConnectionContainer	m_connections;			///< Holds all connections of this signal handler

	/**
	 * @brief	Do the effective disconnection treatement.
	 */
	void doDisconnect();

};


} // namespace event

} // namespace vgGTK




#endif /*_VGGTK_EVENT_SIGNALHANDLER_HPP_*/
