// VGSDK - Copyright (C) 2013, Guillaume Brocker, Bryan Schuller, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGSDKVIEWERQT_WINDOWLIST_HPP_
#define _VGSDKVIEWERQT_WINDOWLIST_HPP_

#include <vector>
#include <QObject>


namespace vgsdkViewerQt
{


struct MainWindow;


/**
 * @brief	Manages the list of main windows and all associated services.
 */
struct WindowList : public QObject
{
	Q_OBJECT

public:

	/**
	 * @brief	Constructor
	 */
	WindowList();

	/**
	 * @brief	Adds the given window to the list.
	 */
	void add( MainWindow * );

	/**
	 * @brief	Retrieves the current window list counter.
	 *
	 * This counter is incremented every time a window is added to the list.
	 * But it is not decremented when a window is removed.
	 */
	const int counter() const;

	/**
	 * @brief	Removes the given window from the list.
	 */
	void remove( MainWindow * );

public Q_SLOTS:

	/**
	 * @brief	Closes all windows.
	 */
	void closeAll();

private:

	typedef std::vector< MainWindow * > Container;

	int			m_counter;	///< List counter.
	Container	m_windows;	///< The collection of windows.
};


} // vgsdkViewerQt


#endif // _VGSDKVIEWERQT_WINDOWLIST_HPP_