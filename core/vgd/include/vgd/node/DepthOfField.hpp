// VGSDK - Copyright (C) 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_DEPTHOFFIELD_HPP
#define _VGD_NODE_DEPTHOFFIELD_HPP

#include "vgd/field/Enum.hpp"
#include "vgd/field/Float.hpp"
#include "vgd/field/Int.hpp"
#include "vgd/node/SingleAttribute.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Built-in post-processing effect depth of field
 *
 * Real camera lenses, due to their physical properties, blurs parts of a scene at certain depths, while maintaining sharpness in others areas. This built-in post-processing effect simulates a thin lens camera 
 *
 * New fields defined by this node :
 * - SFFloat \c focusToFar = (1.f)<br>
 *   Sets the distance from focus to far. Must be greater than zero.<br>
 *<br>
 * - SFFloat \c farMaximumBlurriness = (0.5f)<br>
 *   Sets the maximum blurriness for object(s) in [focus, far]. 0 means no blur at all. 1 means maximum blurriness.<br>
 *<br>
 * - SFFloat \c focus = (0.f)<br>
 *   Sets the focal distance. Objects on the focal plane (i.e. at focus distance) are in perfect focus.<br>
 *<br>
 * - SFInt \c sampling = (8)<br>
 *   Sets the number of samples (must be 1, 2, 3, 4, 5, 6, 7 or 8).<br>
 *<br>
 * - SFFloat \c focusToNear = (1.f)<br>
 *   Sets the distance from focus to near. Must be greater than zero.<br>
 *<br>
 * - SFFloat \c nearMaximumBlurriness = (0.5f)<br>
 *   Sets the maximum blurriness for object(s) in [near, focus]. 0 means no blur at all. 1 means maximum blurriness.<br>
 *<br>
 * - SFEnum \c cameraModel = (THIN_LENS)<br>
 *   Sets the camera model.<br>
 *<br>
 *
 * @ingroup g_nodes
 * @ingroup g_singleAttributeNodes
 * @ingroup g_frameBufferNodes
 */
struct VGD_API DepthOfField : public vgd::node::SingleAttribute
{
	/**
	 * @name Factories
	 */
	//@{

	/**
	 * @brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values
	 */
	static vgd::Shp< DepthOfField > create( const std::string nodeName = "NoName" );

	/**
	 * @brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values and
	 * sets the \c multiAttributeIndex of the multi-attribute.
	 *
	 * @param index		zero-based index of the multi-attribute
	 */
	static vgd::Shp< DepthOfField > create( const std::string nodeName, const uint8 index );
	
	/**
	 *@brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values (optionals fields too).
	 */
	static vgd::Shp< DepthOfField > createWhole( const std::string nodeName = "DefaultWhole" );

	//@}



	/**
	 * @name Accessors to field focusToFar
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c focusToFar.
	 */
	typedef float FocusToFarValueType;

	/**
	 * @brief The default value of field named \c focusToFar.
	 */
	static const FocusToFarValueType DEFAULT_FOCUSTOFAR;

	/**
	 * @brief Type definition of the field named \c focusToFar
	 */
	typedef vgd::field::TSingleField< FocusToFarValueType > FFocusToFarType;


	/**
	 * @brief Gets the value of field named \c focusToFar.
	 */
	const FocusToFarValueType getFocusToFar() const;

	/**
	 * @brief Sets the value of field named \c focusToFar.
	 */
	void setFocusToFar( const FocusToFarValueType value );

	//@}



	/**
	 * @name Accessors to field farMaximumBlurriness
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c farMaximumBlurriness.
	 */
	typedef float FarMaximumBlurrinessValueType;

	/**
	 * @brief The default value of field named \c farMaximumBlurriness.
	 */
	static const FarMaximumBlurrinessValueType DEFAULT_FARMAXIMUMBLURRINESS;

	/**
	 * @brief Type definition of the field named \c farMaximumBlurriness
	 */
	typedef vgd::field::TSingleField< FarMaximumBlurrinessValueType > FFarMaximumBlurrinessType;


	/**
	 * @brief Gets the value of field named \c farMaximumBlurriness.
	 */
	const FarMaximumBlurrinessValueType getFarMaximumBlurriness() const;

	/**
	 * @brief Sets the value of field named \c farMaximumBlurriness.
	 */
	void setFarMaximumBlurriness( const FarMaximumBlurrinessValueType value );

	//@}



	/**
	 * @name Accessors to field focus
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c focus.
	 */
	typedef float FocusValueType;

	/**
	 * @brief The default value of field named \c focus.
	 */
	static const FocusValueType DEFAULT_FOCUS;

	/**
	 * @brief Type definition of the field named \c focus
	 */
	typedef vgd::field::TSingleField< FocusValueType > FFocusType;


	/**
	 * @brief Gets the value of field named \c focus.
	 */
	const FocusValueType getFocus() const;

	/**
	 * @brief Sets the value of field named \c focus.
	 */
	void setFocus( const FocusValueType value );

	//@}



	/**
	 * @name Accessors to field sampling
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c sampling.
	 */
	typedef int SamplingValueType;

	/**
	 * @brief The default value of field named \c sampling.
	 */
	static const SamplingValueType DEFAULT_SAMPLING;

	/**
	 * @brief Type definition of the field named \c sampling
	 */
	typedef vgd::field::TSingleField< SamplingValueType > FSamplingType;


	/**
	 * @brief Gets the value of field named \c sampling.
	 */
	const SamplingValueType getSampling() const;

	/**
	 * @brief Sets the value of field named \c sampling.
	 */
	void setSampling( const SamplingValueType value );

	//@}



	/**
	 * @name Accessors to field focusToNear
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c focusToNear.
	 */
	typedef float FocusToNearValueType;

	/**
	 * @brief The default value of field named \c focusToNear.
	 */
	static const FocusToNearValueType DEFAULT_FOCUSTONEAR;

	/**
	 * @brief Type definition of the field named \c focusToNear
	 */
	typedef vgd::field::TSingleField< FocusToNearValueType > FFocusToNearType;


	/**
	 * @brief Gets the value of field named \c focusToNear.
	 */
	const FocusToNearValueType getFocusToNear() const;

	/**
	 * @brief Sets the value of field named \c focusToNear.
	 */
	void setFocusToNear( const FocusToNearValueType value );

	//@}



	/**
	 * @name Accessors to field nearMaximumBlurriness
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c nearMaximumBlurriness.
	 */
	typedef float NearMaximumBlurrinessValueType;

	/**
	 * @brief The default value of field named \c nearMaximumBlurriness.
	 */
	static const NearMaximumBlurrinessValueType DEFAULT_NEARMAXIMUMBLURRINESS;

	/**
	 * @brief Type definition of the field named \c nearMaximumBlurriness
	 */
	typedef vgd::field::TSingleField< NearMaximumBlurrinessValueType > FNearMaximumBlurrinessType;


	/**
	 * @brief Gets the value of field named \c nearMaximumBlurriness.
	 */
	const NearMaximumBlurrinessValueType getNearMaximumBlurriness() const;

	/**
	 * @brief Sets the value of field named \c nearMaximumBlurriness.
	 */
	void setNearMaximumBlurriness( const NearMaximumBlurrinessValueType value );

	//@}



	/**
	 * @name Accessors to field cameraModel
	 */
	//@{

	/**
	 * @brief Definition of symbolic values
	 */
	enum  
	{
		THIN_LENS = 271,	///< todo
		PINHOLE = 270,	///< todo
		DEFAULT_CAMERAMODEL = THIN_LENS	///< todo
	};

	/**
	 * @brief Type definition of a container for the previous symbolic values
	 */
	struct CameraModelValueType : public vgd::field::Enum
	{
		CameraModelValueType()
		{}

		CameraModelValueType( const int v )
		: vgd::field::Enum(v)
		{}

		CameraModelValueType( const CameraModelValueType& o )
		: vgd::field::Enum(o)
		{}

		CameraModelValueType( const vgd::field::Enum& o )
		: vgd::field::Enum(o)
		{}

		const std::vector< int > values() const
		{
			std::vector< int > retVal;

			retVal.push_back( 270 );
			retVal.push_back( 271 );

			return retVal;
		}

		const std::vector< std::string > strings() const
		{
			std::vector< std::string > retVal;

			retVal.push_back( "PINHOLE" );
			retVal.push_back( "THIN_LENS" );

			return retVal;
		}
	};

	/**
	 * @brief Type definition of the field named \c cameraModel
	 */
	typedef vgd::field::TSingleField< vgd::field::Enum > FCameraModelType;


	/**
	 * @brief Gets the value of field named \c cameraModel.
	 */
	const CameraModelValueType getCameraModel() const;

	/**
	 * @brief Sets the value of field named \c cameraModel.
	 */
	void setCameraModel( const CameraModelValueType value );

	//@}



	/**
	 * @name Field name accessors
	 */
	//@{

	/**
	 * @brief Returns the name of field \c focusToFar.
	 *
	 * @return the name of field \c focusToFar.
	 */
	static const std::string getFFocusToFar( void );

	/**
	 * @brief Returns the name of field \c farMaximumBlurriness.
	 *
	 * @return the name of field \c farMaximumBlurriness.
	 */
	static const std::string getFFarMaximumBlurriness( void );

	/**
	 * @brief Returns the name of field \c focus.
	 *
	 * @return the name of field \c focus.
	 */
	static const std::string getFFocus( void );

	/**
	 * @brief Returns the name of field \c sampling.
	 *
	 * @return the name of field \c sampling.
	 */
	static const std::string getFSampling( void );

	/**
	 * @brief Returns the name of field \c focusToNear.
	 *
	 * @return the name of field \c focusToNear.
	 */
	static const std::string getFFocusToNear( void );

	/**
	 * @brief Returns the name of field \c nearMaximumBlurriness.
	 *
	 * @return the name of field \c nearMaximumBlurriness.
	 */
	static const std::string getFNearMaximumBlurriness( void );

	/**
	 * @brief Returns the name of field \c cameraModel.
	 *
	 * @return the name of field \c cameraModel.
	 */
	static const std::string getFCameraModel( void );

	//@}


	/**
	 * @name Dirty flags enumeration
	 */
	//@{


	//@}



	/**
	 * @name Constructor and initializer methods
	 */
	//@{

	void	setToDefaults( void );

	void	setOptionalsToDefaults();

	//@}

protected:
	/**
	 * @brief Default constructor
	 */
	DepthOfField( const std::string nodeName );

public:
	IMPLEMENT_INDEXABLE_CLASS_HPP( , DepthOfField );
private:
	static const vgd::basic::RegisterNode<DepthOfField> m_registrationInstance;
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_DEPTHOFFIELD_HPP
