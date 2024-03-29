// VGSDK - Copyright (C) 2004-2006, Guillaume Brocker & Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGD_EVENT_SOURCE_HPP
#define _VGD_EVENT_SOURCE_HPP

#include <set>
#include "vgd/vgd.hpp"

namespace vgd
{
	template<class T> struct Shp;	

	namespace event
	{
		struct Event;
		struct Listener;
	}
}



namespace vgd
{

namespace event
{
	
/**
 * @brief	Defines the abstract class for event sources.
 * 
 * @todo	Improve the listener reference by using smart or weak pointers.
 */
struct VGD_API Source
{
	/**
	 * @brief	Destructor.
	 */
	virtual ~Source();
	
	/**
	 * @brief	Attaches the specified event listener to the source.
	 * 
	 * @param	listener	a pointer to the event listener to attach
	 */
	void attachEventListener( Listener *listener );
	
	/**
	 * @brief	Detaches the specified listener from the source.
	 *
	 * @param	listener	a pointer to the event listener to detach
	 */
	void detachEventListener( Listener *listener );
	
protected:
	
	/**
	 * @brief	Constructor.
	 * 
	 * @remark	The constructor is in the protected scope to prevent from using
	 * 			this class without specialization.
	 */
	Source();

	/**
	 * @briefs	Fires the specified event to all attached listeners.
	 * 
	 * @param	event	a shared pointer to the event to fire
	 */
	void fireEvent( vgd::Shp<vgd::event::Event> event );
	
private:

	/**
	 * @brief	Defines the container type for attached listeners.
	 */
	typedef std::set<Listener*> ListenerContainer;
	
	/**
	 * @brief	Contains all attached listeners.
	 */
	ListenerContainer	listeners;	 	
};



} // namespace event

} // namespace vgd

#endif // _VGD_EVENT_SOURCE_HPP
