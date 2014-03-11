// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_BASIC_OBJECT_HPP
#define _VGD_BASIC_OBJECT_HPP

#include "vgd/vgd.hpp"



namespace vgd
{

namespace basic
{



/**
 * @brief Base class interface for objects.
 */
struct VGD_API Object
{
	/**
	 * @name Constructor/destructor
	 */
	//@{

	/**
	 * @brief Default constructor.
	 */
	Object();

	/**
	 * @brief Virtual destructor.
	 */
	virtual ~Object();
	//@}



	/**
	 * @name RTTI(run-time type identification) facilities.
	 */
	//@{

	/**
	 * @brief Returns the name of the object's class type.
	 */
	const char*	getClassName() const;

	/**
	 * @brief Test if this class is derived from another one.
	 *
	 * @return Returns a valid pointer if this class is derived from the class passed in parameter, otherwise a null 
	 * pointer.
	 */
	template< typename T >
	const T *isAKindOf() const
	{
		return ( dynamic_cast< const T * >( this ) );
	}

	/**
	 * @brief Test if this class has the same type as another one.
	 *
	 * @return Returns true if this class has the same type as the class passed in parameter.
	 */
	template< typename T >
	bool	isA() const
	{
#ifdef _MSC_VER
		int	retVal = (typeid(*this) == typeid(T));

		return ( retVal != 0 );
#else
		return ( typeid(*this) == typeid(T) );
#endif
	}

	//@}



	/**
	 * @name Accessor methods
	 */
	//@{

	/**
	 * @brief Gets the user data.
	 * 
	 * @remarks Destruction of user data is not done in vgsdk.
	 */
	void*	getUserData() const		{ return ( m_pUserData ); }

	/**
	 * @brief Sets the user data.
	 * 
	 * @remarks Destruction of user data is not done in vgsdk.
	 */
	void	setUserData( void *pUserData )	{ m_pUserData = pUserData; }
	//@}



private:
	/**
	 * @name Data
	 */
	//@{
	
	/**
	* @brief Pointer on user data.
	*/
	void *m_pUserData;
	//@}
};



} // namespace basic

} // namespace vgd

#endif //#ifndef _VGD_BASIC_OBJECT_HPP
