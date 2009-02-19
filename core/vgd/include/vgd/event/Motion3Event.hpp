// VGSDK - Copyright (C) 2004-2006, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_EVENT_MOTION3EVENT_HPP
#define _VGD_EVENT_MOTION3EVENT_HPP

#include <vgm/Vector.hpp>
#include <vgm/Rotation.hpp>

#include "vgd/event/Event.hpp"



namespace vgd
{

namespace event
{



/**
 * @brief	Defines the event class for 3d movement notifications.
 */
struct VGD_API Motion3Event : public Event
{
	/**
	 * @brief	Defines the translation vector type.
	 */
	typedef vgm::Vec3f Translation;

	/**
	 * @brief	Defines the rotation type.
	 */
	typedef vgm::Rotation Rotation;

	/**
	 * @brief	Defines the 'canvas size' type.
	 */
	typedef vgm::Vec3f Size;

	/**
	 * @brief	Constructor.
	 * 
	 * @param	source			a pointer to event source
	 * @param	buttonStates		a reference to the button state set
	 * @param	translation			the translation to pass through the event
	 * @param	rotation			the rotation to pass through the event
	 * @param	size				the size of the 'canvas' where Motion3Event occurs
	 */
	Motion3Event( Source *source, const ButtonStateSet& buttonStates, const Translation& translation, const Rotation& rotation, const Size& size );
	
	/**
	 * @brief	Destructor.
	 */
	virtual ~Motion3Event();

	/**
	 * @brief	Retrieves the translation passed through the event.
	 * 
	 * @return	a translation
	 */
	const Translation& getTranslation() const;

	/**
	 * @brief	Retrieves the rotation passed through the event.
	 * 
	 * @return	a rotation
	 */
	const Rotation& getRotation() const;

	/**
	 * @brief	Retrieves the 'canvas size' passed through the event.
	 * 
	 * @return	a size
	 */
	const Size& getSize() const;


	// overridden method
	void accept( vgd::event::EventVisitor& eventVisitor );	


private:

	/**
	 * @brief The translation passed through the event.
	 */
	Translation		m_translation;
	
	/**
	 * @brief The rotation passed through the event.
	 */
	Rotation		m_rotation;
	
	/**
	 * The size passed through the event.
	 */
	Size			m_size;	
};


} // namespace event

} // namespace vgd

#endif // _VGD_EVENT_MOTION3EVENT_HPP
