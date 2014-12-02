//// VGSDK - Copyright (C) 2009, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_EVENT_TIMEREVENTPROCESSOR_HPP
//#define _VGEGLBASE_EVENT_TIMEREVENTPROCESSOR_HPP
//
//#include <set>
//
//#include "vgeGLBase/event/EventProcessor.hpp"
//
//namespace vgd { namespace event { struct TimerCallback; } }
//
//
//
//namespace vgeGLBase
//{
//
//namespace event
//{
//
//
///**
// * @brief Process incoming timer event by propagating in its timer callbacks.
// * 
// * This is the default event processor in vgsdk used to process event from timer devices.
// *
// * @ingroup g_time
// */
//struct VGEGLBASE_API TimerEventProcessor : public EventProcessor
//{
//	/**
//	 * @brief Constructor
//	 * 
//	 * @param sceneManager	the linked scene manager.
//	 * 
//	 * @pre sceneManager != 0
//	 */
//	TimerEventProcessor( ::vgeGLBase::engine::SceneManager *sceneManager );
//
//	/**
//	 * @name Timer callback management
//	 *
//	 * @todo clear
//	 */
//	//@{
//
//	/**
//	 * @brief	Adds the given timer callback.
//	 *
//	 * @param callback	the callback to add
//	 */
//	void add( vgd::Shp< vgd::event::TimerCallback > callback );
//
//	/**
//	 * @brief	Removes the given timer callback.
//	 *
//	 * @param callback	the callback to remove
//	 */
//	void remove( vgd::Shp< vgd::event::TimerCallback > callback );
//
//	/**
//	 * @brief	Looks for the first callback that matches the given type.
//	 *
//	 * @return	A shared pointer to the found callback, or empty if none.
//	 */
//	template< typename TimerCallbackType >
//	vgd::Shp< TimerCallbackType > find() const
//	{
//		vgd::Shp< TimerCallbackType >	result;
//
//		for( TimerCallbackContainer::const_iterator i = m_callbacks.begin(); i != m_callbacks.end(); ++i )
//		{
//			result = vgd::dynamic_pointer_cast< TimerCallbackType >( *i );
//
//			if( result )
//			{
//				break;
//			}
//		}
//
//		return result;
//	}
//
//	/**
//	 * @brief	Tells if this event processor contains the given timer callback.
//	 *
//	 * @param callback	the callback to search
//	 */
//	const bool has( vgd::Shp< vgd::event::TimerCallback > callback ) const;
//
//	/**
//	 * @brief	Retrieves the number of callback.
//	 *
//	 * @return the number of callback
//	 */
//	const uint count() const;
//
//	//@}
//
//protected:
//	/**
//	 * @name Overridden method
//	 */
//	//@{
//	const bool onEvent( vgd::Shp<vgd::event::Event> event );
//	//@}
//
//	void onTimerEvent( vgd::Shp<vgd::event::TimerEvent> event ); 
//
//private:
//	typedef std::set< vgd::Shp< vgd::event::TimerCallback > >	TimerCallbackContainer;
//
//	TimerCallbackContainer	m_callbacks;	///< Holds all timer callback the event processor is connected to.
//};
//
//
//} // namespace event
//
//} // namespace vgeGLBase
//
//#endif //#ifndef _VGEGLBASE_EVENT_TIMEREVENTPROCESSOR_HPP
//