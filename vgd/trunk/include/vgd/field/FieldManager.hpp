// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_FIELD_FIELDMANAGER_H
#define _VGD_FIELD_FIELDMANAGER_H

#include "vgd/vgd.hpp"

#include <typeinfo>

#include "vgd/Shp.hpp"
#include "vgd/field/AbstractField.hpp"
#include "vgd/field/EditorRO.hpp"
#include "vgd/field/EditorRW.hpp"
#include "vgd/field/IFieldObserver.hpp"
#include "vgd/field/detail/FieldsToDirtyFlags.hpp"


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
	 * @name Constructor/Copy/Assignement.
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
	~FieldManager();
	//@}



	/**
	 * @name Field accessor methods.
	 */
	//@{

	/**
	 * @brief Returns the specified field in read-only access mode.
	 *
	 * @pre A field with strFieldName must exist(check with assert).
	 * 
	 * @return A Editor that you can use like a C++ pointer on the field.
	 */
	template< typename T >
	EditorRO<T> getFieldRO( const std::string strFieldName ) const
	{
		EditorRO<T> fieldRO( getField<T>(strFieldName).get() );
		return ( fieldRO );
	}

	/**
	 * @brief Returns the specified field in read-write access mode.
	 *
	 * @return A Editor that you can use like a C++ pointer on the field.
	 * 
	 * @remark If the desired field does'nt exist, it is automatically created.
	 */
	template< typename T >
	EditorRW<T> getFieldRW( const std::string strFieldName )
	{
		EditorRW<T> fieldRW( getField<T>(strFieldName).get() );
		return ( fieldRW );
	}
	
	/**
	 * @brief Returns if the specified field exist.
	 * 
	 * @return true if the specified field exist, false otherwise.
	 */
	bool		isField( const std::string strFieldName ) const;
	
	/**
	 * @brief Test the type of the specified field.
	 * 
	 * @return true if the specified field exist and has the desired type, false otherwise.
	 */
	template< typename fieldType >
	bool		isField( const std::string strFieldName ) const
	{
		MapField::const_iterator iField;
		iField = m_fields.find( strFieldName );
		
		if ( iField != m_fields.end() )
		{
			// strFieldName is founded
			if ( dynamic_cast< fieldType >(iField->second.get()) )
			{
				return ( true );
			}
			else
			{
				return ( false );
			}
		}
		else
		{
			// strFieldName is not founded
			return ( false );
		}
	}

	/**
	 * @brief Use by getFieldType.
	 */
	struct NotFound
	{
	};

	/**
	 * @brief Returns the type of a specified field.
	 *
	 * @pre A field with strFieldName must exist(check with assert).
	 * 
	 * @return The type of the specified field if sucessful, otherwise a type_info on class \c NotFound (if the field 
	 * named strFieldName is not founded).
	 */
	const type_info& getFieldType( const std::string strFieldName ) const
	{
		MapField::const_iterator iField;
		iField = m_fields.find( strFieldName );
	
		if ( iField != m_fields.end() )
		{
			// Found
			return ( typeid( *(iField->second.get()) ) );
		}
		else
		{
			// Not found
			return ( typeid( NotFound ) );
		}
	}
	//@}



	/**
	 * @name Dirty flag accessor methods.
	 */
	//@{

	/**
	 * @brief Returns specified dirty flag.
	 * 
	 * @param	strDirtyFlagName	: name of the dirty flag.
	 * 
	 * @return A reference to the desired dirty flag or 0 if a flag with the strDirtyFlagName is not founded.
	 */
	DirtyFlag*			getDirtyFlag( const std::string strDirtyFlagName );

	/**
	 * @brief Returns specified dirty flag.
	 * 
	 * @param	strDirtyFlagName	: name of the dirty flag.
	 * 
	 * @return A reference to the desired dirty flag or 0 if a flag with the strDirtyFlagName is not founded.
	 */
	const DirtyFlag*	getDirtyFlag( const std::string strDirtyFlagName ) const;

	/**
	 * @brief Dirty flag accessor.
	 * 
	 * @return a pair with a begin iterator(the first element of the pair) and a end iterator(the second element of the pair).
	 */
	/*d::pair< MapDirtyFlag::const_iterator, MapDirtyFlag::const_iterator >	
		getDirtyFlagsIterators( void ) const;*/
			
	/**
	 * @brief Dirty flag accessor.
	 * 
	 * @return a pair with a begin iterator(the first element of the pair) and a end iterator(the second element of the pair).
	 */
	/*d::pair< MapDirtyFlag::iterator, MapDirtyFlag::iterator >	
		getDirtyFlagsIterators( void );*/

	//@}
	
	
	
protected:
	/**
	 * @name Various typedefs.
	 */
	//@{
	
	/**
	 * @brief Typedef for the field container.
	 * 
	 * string						: name of field.
	 * vgd::Shp<AbstractField>	: reference to the field.
	 */
	typedef std::map< std::string, vgd::Shp<AbstractField>	>	MapField;
	
	//@}
	
	
	
	/**
	 * @name Field accessor methods.
	 * 
	 * @todo Uncomments with methods ?
	 */
	//@{

	/**
	 * @brief Returns field iterators.
	 * 
	 * @return a pair with a begin iterator(the first element of the pair) and 
	 * the end iterator(the second element of the pair).
	 * 
	 * @todo not MT-safe(see getFieldRO()...)
	 */
	/*std::pair< MapField::const_iterator, MapField::const_iterator >
		getFieldIterators( void ) const;*/

	/**
	 * @brief Returns field iterators.
	 * 
	 * @return a pair with a begin iterator(the first element of the pair) and 
	 * the end iterator(the second element of the pair).
	 * 
	 * @todo not MT-safe(see getFieldRO()...)
	 */
	/*std::pair< MapField::iterator, MapField::iterator >
		getFieldIterators( void );*/
			
	//@}

	
	
	/** 
	 * @name Field management methods.
	 */
	//@{

	/**
	 * @brief Add a new field.
	 * 
	 * @pre Name of field must be unique in a field manager.
	 * 
	 * @param pField				: reference on the field to add.
	 * 
	 * @remarks After calling this method, the field passed in parameter is owned
	 * by the FieldManager. So it is automatically deleted.
	 * 
	 * @remarks This instance of FieldManager is attach to the field(as an IFieldObserver).
	 * 
	 */
	bool	addField( AbstractField* pField );

	/**
	 * @brief Remove a field.
	 * 
	 * @pre Field must be in field manager.
	 * 
	 * @param strFieldName		: name of field.
	 */
	bool	removeField( const std::string strFieldName );

	/**
	 * @todo clearField()
	 * @todo cloneField()
	 */
	//@}



	/**
	 * @name Implementation of IFieldObserver.
	 */
	//@{
	
	/**
	 * @todo Replace Event by a c++ class ?
	 */
 	virtual void	updateField( const AbstractField& rField, const Event event );

	/**
	 * @brief Dirty all flag link to strFieldName.
	 */
	void				updateFrom( const std::string strFieldName );
	//@}



	/**
	 * @name Manage links between fields and dirty flags.
	 */
	//@{

	/**
	 * @brief Add a link between a field and a dirty flag.
	 * 
	 * @pre	strFieldName must be a field name
	 * @pre	strFirtyFlagName must be a dirty flag name.
	 * 
	 * @param strFieldName		: name of field.
	 * @param strDirtyFlagName	: name of dirty flag.
	 * 
	 * @return true if link is successfully added, false otherwise.
	 */
	bool link( const std::string strFieldName, const std::string strDirtyFlagName );

	/**
	 * @brief Add links between all fields currently in the fieldManager and a dirty flag.
	 * 
	 * @pre		strFirtyFlagName must be a dirty flag name.
	 * 
	 * @param 	strDirtyFlagName	: name of dirty flag.
	 * 
	 * @return true if all links have been successfully added, false otherwise.
	 */
	bool link( const std::string strDirtyFlagName );

	/**
	 * @brief Remove a link between a field and a dirty flag.
	 * 
	 * @pre	strFieldName must be a field name
	 * @pre	strFirtyFlagName must be a dirty flag name.
	 * 
	 * @param strFieldName		: name of field.
	 * @param strDirtyFlagName	: name of dirty flag.
	 * 
	 * @return true if link is successfully removed, false otherwise.
	 */
	bool unlink( const std::string strFieldName, const std::string strDirtyFlagName );

	/**
	 * @brief Remove all links for a field.
	 * 
	 * @pre	strFieldName must be a field name
	 * @pre	strFirtyFlagName must be a dirty flag name.
	 * 
	 * @param strFieldName		: name of field.
	 * 
	 * @return true if link is successfully removed, false otherwise.
	 */
	bool unlinkField( const std::string strFieldName );

	//@}



	/** 
	 * @name Dirty flag management.
	 */
	//@{

	/**
	 * @brief Add a new dirty flag.
	 *
	 * @param	strFlagName	: name of the flag.
	 * 
	 * @return true if the flag is created, false if an error occurs(a flag already created with the same name).
	 */
	bool	addDirtyFlag( const std::string& strFlagName );

	/**
	 * @brief Remove a dirty flag.
	 * 
	 * @pre	strFirtyFlagName must be a dirty flag name.
	 * 
	 * @param	strFlagName	: name of the flag.
	 * 
	 * @return true if the flag is removed sucessfully, false if an error occurs(no flag with this name).
	 * 
	 * @todo Uncomment this if necessary.
	 * @todo Remove link between field and dirty flag ?
	 */
	// bool	removeDirtyFlag( const std::string& strDirtyFlagName );
	//@}



	/**
	 * @name Checking methods.
	 */
	//@{

	/**
	 * @brief Check if a field with strFieldName is contains in field manager.
	 * 
	 * @param strFieldName	: name of field.
	 */
	bool	checkField( const std::string strFieldName ) const;
	
	/**
	 * @brief Check if a dirty flag with strDirtyFlagName is contains in dirty flag container.
	 * 
	 * @param strDirtyFlagName	: name of dirty flag.
	 */
	bool	checkDirtyFlag( const std::string strDirtyFlagName ) const;
	//@}



private:

	void destroy();

	void copy( const FieldManager& rSrc );
	
	/**
	 * @brief Returns the specified field.
	 *
	 * @pre A field with strFieldName must exist(check with assert).
	 * 
	 * @return A shared pointer to the desired field if sucessful or
	 * a shared pointer with a null reference(if the field named strFieldName is
	 * not founded).
	 */
	template < typename T >
	const vgd::Shp< T > getField( const std::string strFieldName ) const
	{
		MapField::const_iterator iField;
		iField = m_fields.find( strFieldName );
	
		if ( iField != m_fields.end() )
		{
			// Found
			return ( vgd::dynamic_pointer_cast< T >( iField->second ) );
		}
		else
		{
			// Not found
			assert( false );
			return ( vgd::Shp<T>( static_cast<T*>(0) ) );
		}
	}

	/**
	 * @brief Returns specified field.
	 *
	 * @pre A field with strFieldName must exist(check with assert).
	 * 
	 * @return A shared pointer to the desired field if sucessful (it is created if not founded) or
	 * a shared pointer with a null reference(if the field named strFieldName is 
	 * not founded and creation of a new desired field fails).
	 */
	template < typename T >
	vgd::Shp< T > getField( const std::string strFieldName )
	{
		MapField::iterator iField;
		iField = m_fields.find( strFieldName );
	
		if ( iField != m_fields.end() )
		{
			// Found
			return ( vgd::dynamic_pointer_cast< T >( iField->second ) );
		}
		else
		{
			// Not found
			bool bRetVal;
			bRetVal = addField( new T(strFieldName) );
			
			if ( bRetVal )
			{
				// Warning recusive call.
				return ( getField<T>( strFieldName ) );
			}
			else
			{
				return ( vgd::Shp<T>( static_cast<T*>(0) ) );
			}
		}
	}


	
	/**
	 * @name Data.
	 */
	//@{
	MapField							m_fields;

	detail::FieldsToDirtyFlags	m_fieldsToDirtyFlags;

	MapDirtyFlag					m_dirtyFlags;
	//@}
};



} // namespace field

} // namespace vgd

#endif //#ifndef _VGD_FIELD_FIELDMANAGER_H
