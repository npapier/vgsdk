// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_FIELD_ABSTRACTFIELD_H
#define _VGD_FIELD_ABSTRACTFIELD_H

#include "vgd/vgd.hpp"

#include <list>

#include "vgd/basic/NamedObject.hpp"
#include "vgd/field/Types.hpp"



namespace vgd
{

namespace field
{

struct IFieldObserver;

/**
 * @brief Abstract class for all single-value fields and multiple-valued fields.
 *
 * This class could be observed by zero to several IFieldObserver(typically FieldManager),
 * for automatic invalidation of flags(like render flag).
 * 
 * @remarks Implements DP subject/observer(this class is a subject, observer is 
 * IFieldObserver).
 * 
 * @remarks Not DefaultConstructible and
 * @todo ??????????????????????Assignable ????????????????????????????????????????????????
 *
 * @todo Serialize.
 */
struct VGD_API AbstractField : public vgd::basic::NamedObject
{
	/**
	 * @name Constructor/destructor.
	 */
	//@{
	
	/**
	 * @brief Default constructor.
	 * 
	 * @param strFieldName		: name of field.
	 */
	AbstractField( const std::string& strFieldName );

	/**
	 * @brief Virtual destructor.
	 */
	virtual ~AbstractField( void );
	//@}



	/** 
	 * @name Design pattern Observer methods.
	 */
	//@{
	
	/**
	 * @brief Returns observers list.
	 * 
	 * @return list of observers.
	 */
	std::list< IFieldObserver* >&			getObservers( void )		{ return ( m_listObservers ); }

	/**
	 * @brief Returns observers list.
	 * 
	 * @return list of observers.
	 */
	const std::list< IFieldObserver* >&	getObservers( void ) const	{ return ( m_listObservers ); }

	/**
	 * @brief Check if pFieldObserver is already in observers list.
	 * 
	 * @return true if founded, false otherwise.
	 */
	bool	findObserver( IFieldObserver* pFieldObserver ) const;

	/**
	 * @brief Attach a new observer.
	 * 
	 * @remarks Throw an assert if pObserver already an observer of this field.
	 */
	void	attach( IFieldObserver* pObserver );

	/**
	 * @brief Detach an observer.
	 * 
	 * @remarks Throw an assert if pObserver is not an observer of this field.
	 */
	void	detach( IFieldObserver* pObserver );

	/**
	 * @brief Detach all observers.
	 */
	void	detach( void );

	/**
	 * @brief Send a notification of an event to all observers.
	 */
	void	sendNotify( const Event& ) const;

	/**
	 * @brief Receive a notification.
	 *
	 * @todo Receive a notification.
	 * @todo Complete code if event is receive(for example if FieldContainer
	 * is destroyed).
	 */
	//void	receiveNotify( const Event& );

	/**
	 * @brief Test if the number of observers is not zero.
	 * 
	 * @return true if this subject is observed by at least one object.
	 */
	bool	isSubject( void ) const;
	//@}



	/** 
	 * @name Editing methods.
	 */
	//@{

    /**
	 * @brief Mark this field to be currently edit in read only mode.
	 * 
     * @todo  mutex for being MT-safe.
     */
    bool startEditingRO( void ) const;

    /**
	 * @brief Mark this field to be currently edit in read-write mode.
	 * 
     * @todo  mutex for being MT-safe.
     */
    bool startEditingRW( void ) const;

    /**
	 * @brief Mark this field to be currently not edit.
	 * 
     * @todo  mutex for being MT-safe.
     */
    bool finishEditing( void ) const;

    /**
	 * @brief Returns editing state of this field.
	 *
	 * @return true if this field is currently edit in the mode passed in argument.
	 *
     * @todo  mutex for being MT-safe.
     */
	bool isSameEditingMode( const EditingMode mode ) const;
	//@}



	/**
	 * @name Field actions.
	 */
	//@{
	
	/**
	 * @todo Field actions(dump, serialize...).
	 */
	/**
	 *
	 */
    //virtual void dump( std::stringstream& _rStreamDump, const int32 _i32Offset, const TDumpMode _tDumpMode )=0;
	//@}



protected:
	/**
	 * @brief Checks if editing mode is compatible with a read-only access.
	 */
	bool checkRO( void ) const
	{
		return ( !isSameEditingMode(NONE) );
	}

	/**
	 * @brief Checks if editing mode is compatible with a read-write access.
	 */
	bool checkRW( void ) const
	{
		return ( isSameEditingMode(RW) );
	}



private:
	/**
	 * @name Private data.
	 */
	//@{
	
	/**
	 * @brief List of observers.
	 */
	typedef std::list< IFieldObserver* >	TListObserver;
	TListObserver									m_listObservers;

	/**
	 * @brief Pseudo mutex.
	 * 
	 * @todo add a real mutex for MThreaded support.
	 */
	mutable EditingMode							m_editingMode;
	
	//@}
};



} // namespace field

} // namespace vgd

#endif //#ifndef _VGD_FIELD_ABSTRACTFIELD_H
