// VGSDK - Copyright (C) 2004, 2006, 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#ifndef _VGD_FIELD_FIELDMANAGER_HPP
#define _VGD_FIELD_FIELDMANAGER_HPP

#include <map>

#include "vgd/Shp.hpp"
#include "vgd/field/AbstractField.hpp"
#include "vgd/field/DirtyFlag.hpp"
#include "vgd/field/EditorRO.hpp"
#include "vgd/field/EditorRW.hpp"
#include "vgd/field/IFieldObserver.hpp"
#include "vgd/field/detail/FieldsToDirtyFlags.hpp"

namespace vgd
{
	//template<class T> struct Shp;	///< @todo FIXME

	namespace field
	{
		struct DirtyFlag;
	}
}



namespace vgd
{

namespace field
{



/**
 *
 * @brief Class that manage fields, dirty flags and the links between fields and dirty flags.
 *
 * The FieldManager class is a base class for all classes that contain fields (like node and derived class for example).
 *
 * Used to have a central point for field management(enumeration, serialization, lock/unlock, dirty/validate).
 *
 * @remarks \b DefaultConstructible
 *
 * @todo Iterators on dirty flags, fields.
 * @todo Improve UpdateField and UpdateFrom().
 * @todo Concept \b Assignable.
 */
struct VGD_API FieldManager : public IFieldObserver
{
	/**
	 * @name Constructor, copy and assignement
	 */
	//@{

	/**
	 * @brief Default constructor.
	 */
	FieldManager();

	/**
	 * @brief Copy constructor.
	 */
	FieldManager( const FieldManager& rSrc );

	/**
	 * @brief Assignement operator.
	 */
	FieldManager& operator= ( const FieldManager& );

	/**
	 * @brief Destructor.
	 */
	virtual ~FieldManager();

	//@}



	/**
	 * @name Field accessor methods
	 */
	//@{

	/**
	 * @brief Returns the specified field in read-only access mode.
	 *
	 * @pre isField(strFieldName) must returned true
	 *
	 * @return An editor that you can use like a C++ pointer on the field.
	 */
	template< typename T >
	EditorRO<T> getFieldRO( const std::string strFieldName ) const
	{
		EditorRO<T> fieldRO( getField<T>(strFieldName).get() );
		return fieldRO;
	}

	/**
	 * @brief Returns the specified field in read-write access mode.
	 *
	 * @return An editor that you can use like a C++ pointer on the field.
	 *
	 * @remark If the desired field does'nt exist, it is automatically created.
	 */
	template< typename T >
	EditorRW<T> getFieldRW( const std::string strFieldName )
	{
		EditorRW<T> fieldRW( getField<T>(strFieldName).get() );
		return fieldRW;
	}

	/**
	 * @brief Tests if the specified field exist.
	 *
	 * @return Returns true if the specified field exist, false otherwise.
	 */
	const bool isField( const std::string strFieldName ) const;

	/**
	 * brief Tests if the specified field exist and has the desired type.
	 *
	 * @return Returns true if the specified field exist and has the desired type, false otherwise.
	 */
	template< typename fieldType >
	const bool isFieldKindOf( const std::string strFieldName ) const
	{
		// Finds the field
		const MapField::const_iterator iField = m_fields.find( strFieldName );

		if ( iField != m_fields.end() )
		{
			// The field named with the desired name has been found
			const vgd::Shp< fieldType > field = vgd::dynamic_pointer_cast< fieldType >( iField->second );

			return field != 0;
		}
		else
		{
			// The field named with the desired name has NOT been found
			return false;
		}
	}

	/**
	 * @brief Used by getFieldType()
	 */
	struct NotFound {};

	/**
	 * @brief Returns the type of a specified field.
	 *
	 * @return If the field exists, returns a type_info on the field, otherwise  returns a type_info on class \c NotFound
	 */
	const std::type_info& getFieldType( const std::string strFieldName ) const;

	/**
	 * @brief	Retrieves all field names and store them using the given output iterator.
	 *
	 * @remark	The output iterator's value type must be @c std::string.
	 *
	 * @param	output	an STL compliant output iterator
	 */
	template< typename OutputIterator >
	void getFieldNames( OutputIterator & output ) const
	{
		MapField::const_iterator	i;
		for( i = m_fields.begin(); i != m_fields.end(); ++i )
		{
			*output++ = i->first;
		}
	}
	//@}



	/**
	 * @name Dirty flag accessor methods
	 */
	//@{

	/**
	 * @brief Returns specified dirty flag.
	 *
	 * @param	strDirtyFlagName	name of the dirty flag.
	 *
	 * @return A reference to the desired dirty flag or 0 if a flag with the strDirtyFlagName is not founded.
	 */
	DirtyFlag*			getDirtyFlag( const std::string strDirtyFlagName );

	/**
	 * @brief Returns specified dirty flag.
	 *
	 * @param	strDirtyFlagName	name of the dirty flag.
	 *
	 * @return A reference to the desired dirty flag or 0 if a flag with the strDirtyFlagName is not founded.
	 */
	const DirtyFlag*	getDirtyFlag( const std::string strDirtyFlagName ) const;

	/**
	 * @brief	Retrieves all dirty flags names and store them using the given output iterator.
	 *
	 * @remark	The output iterator's value type must be @c std::string.
	 *
	 * @param	output	an STL compliant output iterator
	 */
	template< typename OutputIterator >
	void getDirtyFlagNames( OutputIterator & output ) const
	{
		for(	MapDirtyFlag::const_iterator i = m_dirtyFlags.begin();
				i != m_dirtyFlags.end(); 
				++i )
		{
			*output++ = i->first;
		}
	}

	//@}



protected:
	/**
	 * @name Various typedefs
	 */
	//@{

	/**
	 * @brief Typedef for the field container.
	 *
	 * string					: name of field.
	 * vgd::Shp<AbstractField>	: reference to the field.
	 */
	typedef std::map< std::string, vgd::Shp<AbstractField>	>	MapField;

	/**
	 * @brief Typedef for the dirty flag container.
	 *
	 * key of map		name of DirtyFlag
	 * value of map		the dirty flag
	 */
	typedef std::map< std::string, DirtyFlag >					MapDirtyFlag;

	//@}



	/**
	 * @name Field accessor methods
	 */
	//@{

///@todo FIXME
//	/**
//	 * brief Returns field iterators.
//	 *
//	 * return a pair with a begin iterator(the first element of the pair) and
//	 * the end iterator(the second element of the pair).
//	 *
//	 * todo not MT-safe(see getFieldRO()...)
//	 */
//	std::pair< MapField::const_iterator, MapField::const_iterator > getFieldIterators( void ) const;
//
//	/**
//	 * brief Returns field iterators.
//	 *
//	 * return a pair with a begin iterator(the first element of the pair) and
//	 * the end iterator(the second element of the pair).
//	 *
//	 * todo not MT-safe(see getFieldRO()...)
//	 */
//	std::pair< MapField::iterator, MapField::iterator > getFieldIterators( void );

	//@}



	/**
	 * @name Field management methods
	 *
	 * @todo clearField()
	 * @todo cloneField()
	 */
	//@{

	/**
	 * @brief Add a new field.
	 *
	 * @pre Name of field must be unique in a field manager.
	 *
	 * @param pField		reference on the field to add.
	 *
	 * @remarks After calling this method, the field passed in parameter is owned by the FieldManager.
	 * So it is automatically deleted.
	 *
	 * @remarks This instance of FieldManager is attach to the field(as an IFieldObserver).
	 */
	const bool	addField( AbstractField* pField );

	/**
	 * @brief Remove a field.
	 *
	 * @pre Field must be in field manager.
	 *
	 * @param strFieldName	name of field.
	 */
	const bool	removeField( const std::string strFieldName );

	//@}



	/**
	 * @name Implementation of IFieldObserver
	 */
	//@{

	/**
	 * @todo Replace Event by a c++ class ?
	 */
 	virtual void	updateField( const AbstractField& rField, const Event event );

	/**
	 * @brief Dirty all flag link to strFieldName.
	 */
	void			updateFrom( const std::string strFieldName );
	//@}



	/**
	 * @name Manage links between fields and dirty flags
	 */
	//@{

	/**
	 * @brief Add a link between a field and a dirty flag.
	 *
	 * @pre	strFieldName must be a field name
	 * @pre	strFirtyFlagName must be a dirty flag name.
	 *
	 * @param strFieldName		name of field.
	 * @param strDirtyFlagName	name of dirty flag.
	 *
	 * @return true if link is successfully added, false otherwise.
	 */
	const bool link( const std::string strFieldName, const std::string strDirtyFlagName );

	/**
	 * @brief Add links between all fields currently in the fieldManager and a dirty flag.
	 *
	 * @pre		strFirtyFlagName must be a dirty flag name.
	 *
	 * @param 	strDirtyFlagName	name of dirty flag.
	 *
	 * @return true if all links have been successfully added, false otherwise.
	 */
	const bool link( const std::string strDirtyFlagName );

	/**
	 * @brief Remove a link between a field and a dirty flag.
	 *
	 * @pre	strFieldName must be a field name
	 * @pre	strFirtyFlagName must be a dirty flag name.
	 *
	 * @param strFieldName		name of field.
	 * @param strDirtyFlagName	name of dirty flag.
	 *
	 * @return true if link is successfully removed, false otherwise.
	 */
	const bool unlink( const std::string strFieldName, const std::string strDirtyFlagName );

	/**
	 * @brief Remove all links for a field.
	 *
	 * @pre	strFieldName must be a field name
	 * @pre	strFirtyFlagName must be a dirty flag name.
	 *
	 * @param strFieldName	name of field.
	 *
	 * @return true if link is successfully removed, false otherwise.
	 */
	const bool unlinkField( const std::string strFieldName );

	//@}



	/**
	 * @name Dirty flag management
	 */
	//@{

	/**
	 * @brief Add a new dirty flag.
	 *
	 * @param	strFlagName		name of the flag.
	 *
	 * @return true if the flag is created, false if an error occurs(a flag already created with the same name).
	 */
	const bool	addDirtyFlag( const std::string& strFlagName );

///@todo FIXME
//	/**
//	 * brief Remove a dirty flag.
//	 *
//	 * pre	strFirtyFlagName must be a dirty flag name.
//	 *
//	 * param	strFlagName		name of the flag.
//	 *
//	 * return true if the flag is removed sucessfully, false if an error occurs(no flag with this name).
//	 *
//	 * todo Uncomment this if necessary.
//	 * todo Remove link between field and dirty flag ?
//	 */
//	bool	removeDirtyFlag( const std::string& strDirtyFlagName );
	//@}



	/**
	 * @name Checking methods
	 */
	//@{

	/**
	 * @brief Checks if the field manager contains a field with the given name.
	 *
	 * @param strFieldName		name of field.
	 *
	 * @return true if the field manager contains a field with the given name, false otherwise.
	 */
	const bool	checkField( const std::string strFieldName ) const;

	/**
	 * @brief Checks if the field manager contains a dirty flag with the given name.
	 *
	 * @param strDirtyFlagName		name of dirty flag.
	 *
	 * @return true if the field manager contains a dirty flag with the given name, false otherwise.
	 */
	const bool	checkDirtyFlag( const std::string strDirtyFlagName ) const;

	//@}


	/**
	 * @brief Lock field access to the current thread.
	 *
	 * Similar to what is done with vgd::node::Node.
	 */

	static void lockFieldAccess();


private:

	/**
	 * @brief Returns the specified field.
	 *
	 * @pre A field with strFieldName must exist (checked with assert).
	 *
	 * @return A shared pointer to the desired field if sucessful or  a shared pointer with a
	 * null reference(if the field named strFieldName is not founded).
	 */
	template < typename T >
	const vgd::Shp< T > getField( const std::string strFieldName ) const
	{
		ensureFieldAccess(strFieldName);
		MapField::const_iterator iField = m_fields.find( strFieldName );

		if ( iField != m_fields.end() )
		{
			// Found
			return vgd::dynamic_pointer_cast< T >( iField->second );
		}
		else
		{
			// Not found
			assert( false );
			return vgd::Shp<T>( static_cast<T*>(0) );
		}
	}

	/**
	 * @brief Returns specified field.
	 *
	 * @pre A field with strFieldName must exist(checked with assert).
	 *
	 * @return A shared pointer to the desired field if sucessful (it is created if not founded) or a shared pointer
	 * with a null reference (if the field named strFieldName is not founded and creation of a new desired field fails).
	 */
	template < typename T >
	vgd::Shp< T > getField( const std::string strFieldName )
	{
		ensureFieldAccess(strFieldName);
		MapField::iterator iField = m_fields.find( strFieldName );

		if ( iField != m_fields.end() )
		{
			// Found
			return vgd::dynamic_pointer_cast< T >( iField->second );
		}
		else
		{
			// Not found
			const bool bRetVal = addField( new T(strFieldName) );

			if ( bRetVal )
			{
				// Warning recusive call.
				return getField<T>( strFieldName );
			}
			else
			{
				return vgd::Shp<T>( static_cast<T*>(0) );
			}
		}
	}

	void destroy();

	void copy( const FieldManager& rSrc );

	/**
	 * @brief Check that the current thread is the thread that has
	 * been locked for field access through the lockFieldAccess
	 * method.
	*/
	const bool ensureFieldAccess(const std::string& strFieldName) const;


	/**
	 * @name Data
	 */
	//@{
	MapField						m_fields;

	detail::FieldsToDirtyFlags		m_fieldsToDirtyFlags;

	MapDirtyFlag					m_dirtyFlags;
	//@}
};



} // namespace field

} // namespace vgd

#endif //#ifndef _VGD_FIELD_FIELDMANAGER_HPP
