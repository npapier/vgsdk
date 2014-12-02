//// VGSDK - Copyright (C) 2004, 2006, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_EVENT_EVENTPROCESSOR_HPP
//#define _VGEGLBASE_EVENT_EVENTPROCESSOR_HPP
//
//#include "vgeGLBase/vgeGLBase.hpp"
//#include "vgeGLBase/engine/SceneManager.hpp"
//#include "vgeGLBase/event/IEventProcessor.hpp"
//
//
//
//
//namespace vgeGLBase
//{
//
//namespace event
//{
//
///**
// * @brief Event processor with a reference on the scene manager.
// */
//struct VGEGLBASE_API EventProcessor : public IEventProcessor
//{
//	/**
//	 * @name Constructor
//	 */
//	//@{
//	
//	/**
//	 * @brief Constructor.
//	 * 
//	 * @param sceneManager	the linked scene manager.
//	 * 
//	 * @pre sceneManager != 0
//	 */
//	EventProcessor( ::vgeGLBase::engine::SceneManager *sceneManager );
//	
//	//@}
//
//
//
//	/**
//	 * @brief Search the first instance of typeOfEventProcessorToSearch class in event processor container of the 
//	 * scene manager.
//	 * 
//	 * @remarks Searching occurs only on the preceding event processors.
//	 * 
//	 * @return a shared pointer on the searched object or an empty shared pointer if it was not found.
//	 * 
//	 * @todo move this method to vgeGLBase::engine::SceneManager ?
//	 */
//	template < typename typeOfEventProcessorToSearch >
//	vgd::Shp< typeOfEventProcessorToSearch > findPreviousEventProcessor()
//	{
//		vgd::Shp< typeOfEventProcessorToSearch > retVal;
//
//		const int32 myIndex = getSceneManager()->findEventProcessor( this );
//		const int32 index	= getSceneManager()->template findEventProcessor< typeOfEventProcessorToSearch >();
//
//		if (	( index != getSceneManager()->getNumEventProcessors() )	&&	// found an event processor 
//																			// that fit the constraint
//				( index < myIndex )		)									// found the event processor before me
//		{
//			retVal = getSceneManager()->template getEventProcessor< typeOfEventProcessorToSearch >( index );
//		}
//	
//		return retVal;
//	}
//
//
//protected:
//
//	/**
//	 * @brief Returns the reference on the linked scene manager.
//	 * 
//	 * @return the reference on the linked scene manager.
//	 */
//	::vgeGLBase::engine::SceneManager *getSceneManager() const { return m_sceneManager; }
//
//private:
//	/**
//	 * @brief The reference on the scene manager.
//	 */
//	::vgeGLBase::engine::SceneManager *m_sceneManager;
//};
//
//
//} // namespace event
//
//} // namespace vgeGLBase
//
//#endif //#ifndef _VGEGLBASE_EVENT_EVENTPROCESSOR_HPP
//