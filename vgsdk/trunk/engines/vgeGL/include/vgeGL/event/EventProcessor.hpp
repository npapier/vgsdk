// VGSDK - Copyright (C) 2004, 2006, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_EVENT_EVENTPROCESSOR_H
#define _VGEGL_EVENT_EVENTPROCESSOR_H

#include "vgeGL/vgeGL.hpp"
#include "vgeGL/engine/SceneManager.hpp"
#include "vgeGL/event/IEventProcessor.hpp"




namespace vgeGL
{

namespace event
{

/**
 * @brief Event processor with a reference on the scene manager.
 */
struct VGEGL_API EventProcessor : public IEventProcessor
{
	/**
	 * @name Constructor
	 */
	//@{
	
	/**
	 * @brief Constructor.
	 * 
	 * @param sceneManager	the linked scene manager.
	 * 
	 * @pre sceneManager != 0
	 */
	EventProcessor( ::vgeGL::engine::SceneManager *sceneManager );
	
	//@}



	/**
	 * @brief Search the first instance of typeOfEventProcessorToSearch class in event processor container of the 
	 * scene manager.
	 * 
	 * @remarks Searching occurs only on the preceding event processors.
	 * 
	 * @return a shared pointer on the searched object or an empty shared pointer if it was not found.
	 * 
	 * @todo move this method to vgeGL::engine::SceneManager ?
	 */
	template < typename typeOfEventProcessorToSearch >
	vgd::Shp< typeOfEventProcessorToSearch > findPreviousEventProcessor()
	{
		vgd::Shp< typeOfEventProcessorToSearch > retVal;

		const int32 myIndex = getSceneManager()->findEventProcessor( this );
		const int32 index	= getSceneManager()->template findEventProcessor< typeOfEventProcessorToSearch >();

		if (	( index != getSceneManager()->getNumEventProcessors() )	&&	// found an event processor 
																			// that fit the constraint
				( index < myIndex )		)									// found the event processor before me
		{
			retVal = getSceneManager()->template getEventProcessor< typeOfEventProcessorToSearch >( index );
		}
	
		return retVal;
	}


protected:

	/**
	 * @brief Returns the reference on the linked scene manager.
	 * 
	 * @return the reference on the linked scene manager.
	 */
	::vgeGL::engine::SceneManager *getSceneManager() const { return m_sceneManager; }

private:
	/**
	 * @brief The reference on the scene manager.
	 */
	::vgeGL::engine::SceneManager *m_sceneManager;
};


} // namespace event

} // namespace vgeGL

#endif //#ifndef _VGEGL_EVENT_EVENTPROCESSOR_H
