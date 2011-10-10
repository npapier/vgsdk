// VGSDK - Copyright (C) 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_CAMERA_HPP
#define _VGD_NODE_CAMERA_HPP

#include "vgd/field/Bool.hpp"
#include "vgd/field/Enum.hpp"
#include "vgd/field/Float.hpp"
#include "vgd/field/MatrixR.hpp"
#include "vgd/field/Rectangle2i.hpp"
#include "vgd/node/GeometricalTransformation.hpp"
#include "vgd/node/ProjectionTransformation.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Camera node used to set the projection matrix, viewport and scissor box. Camera position and orientation could be specified too.
 *
 * Sets up the rendering mode (monoscopic and 3D stereoscopic) using \c mode field. In stereoscopic mode, \c projectionRight (resp. \c projectionLeft) and \c lookAtRight (resp. \c lookAtLeft) specifies the right (resp. left) eye. Sets up the \c projection with an user defined matrix for the viewing frustum (into the world coordinate system). Sets up the camera position and orientation with 4x4 matrix from \c lookAt field. Note that some matrices (such as singular ones) may result in errors in bounding boxes, picking, and lighting. 
 *
 * New fields defined by this node :
 * - OFRectangle2i \c [viewport] = vgm::Rectangle2i(0, 0, 1600, 1200)<br>
 *   Determines the viewport.<br>
 *<br>
 * - SFMatrixR \c projectionLeft = vgm::MatrixR(vgm::MatrixR::getIdentity())<br>
 *   Determines the projection matrix for monoscopic rendering or for the left eye if stereo is enabled.<br>
 *<br>
 * - OFFloat \c [zFar] = 3996.f<br>
 *   Farest visible z for the camera<br>
 *<br>
 * - SFMatrixR \c lookAtLeft = vgm::MatrixR(vgm::MatrixR::getIdentity())<br>
 *   Determines the 3D geometric transformation as a 4x4 matrix applied to camera for monoscopic rendering or for the left eye if stereo is enabled.\n Note that this transformation is applied to engine like any GeometricalTransformation node with composeTransformation field sets to false.\n By default, the camera is situated at the origin, points down the negative z-axis, and has an up-vector of (0, 1, 0).<br>
 *<br>
 * - SFMatrixR \c lookAtRight = vgm::MatrixR(vgm::MatrixR::getIdentity())<br>
 *   Determines the 3D geometric transformation as a 4x4 matrix applied to camera for the right eye (used only if stereo is enabled).\n Note that this transformation is applied to engine like any GeometricalTransformation node with composeTransformation field sets to false.\n By default, the camera is situated at the origin, points down the negative z-axis, and has an up-vector of (0, 1, 0).<br>
 *<br>
 * - SFMatrixR \c projectionRight = vgm::MatrixR(vgm::MatrixR::getIdentity())<br>
 *   Determines the projection matrix for the right eye (used only if stereo is enabled).<br>
 *<br>
 * - OFRectangle2i \c [scissor] = empty<br>
 *   Determines the scissor box. It is automatically enabled if this field is defined, otherwise it is disabled. The default value is empty, i.e. scissor test is disabled.<br>
 *<br>
 * - SFEnum \c mode = MONOSCOPIC<br>
 *   Specifies the camera mode (monoscopic or stereoscopic mode).\n When you normally look at objects, your two eyes see slightly different images (because they are located at different viewpoints).\n Stereoscopic rendering is a technique for creating the illusion of depth in an image for the viewer. Two images are computed (one for each eye) and presented to the viewer using anaglyph (red/cyan) or quad buffer stereo (todo). The brain combined these images to given the perception of depth.<br>
 *<br>
 * - OFFloat \c [aspect] = 1<br>
 *   Aspect ratio of the camera<br>
 *<br>
 * - SFBool \c rightEye = true<br>
 *   Sets to true to enabled the right eye in stereoscopic mode. Setting this field to false is helpful for debugging.<br>
 *<br>
 * - SFFloat \c eyeSeparation = 0.f<br>
 *   Sets the distance between the left and right eye.<br>
 *<br>
 * - SFFloat \c imageShift = 0.f<br>
 *   Sets the additional horizontal shift between the left and right image. This value must be between 0 and 100. 0 means no shift at all. 100 corresponds to a shift of 1/8 of the drawing surface.<br>
 *<br>
 * - OFFloat \c [zNear] = 0.01f<br>
 *   Nearest visible z for the camera.<br>
 *<br>
 * - SFFloat \c fovy = 45.f<br>
 *   Field of view angle for the Y direction for the camera. In the case of a perspective camera.<br>
 *<br>
 *
 * @ingroup g_nodes
 * @ingroup g_singleAttributeNodes
 * @ingroup g_transformationNodes
 */
struct VGD_API Camera : public vgd::node::GeometricalTransformation, public vgd::node::ProjectionTransformation
{
	/**
	 * @brief Definition of symbolic values
	 */
	enum EyeUsagePolicy 
	{
		EYE_LEFT = 256,	///< the left eye
		EYE_RIGHT = 257,	///< the right eye
		EYE_BOTH = 258,	///< the left eye and right eye
		DEFAULT_EYEUSAGEPOLICY = EYE_BOTH	///< the left eye and right eye
	};

	/**
	 * @brief Type definition of a container for the previous symbolic values
	 */
	struct EyeUsagePolicyValueType : public vgd::field::Enum
	{
		EyeUsagePolicyValueType()
		{}

		EyeUsagePolicyValueType( const int v )
		: vgd::field::Enum(v)
		{}

		EyeUsagePolicyValueType( const EyeUsagePolicyValueType& o )
		: vgd::field::Enum(o)
		{}

		EyeUsagePolicyValueType( const vgd::field::Enum& o )
		: vgd::field::Enum(o)
		{}

		const std::vector< int > values() const
		{
			std::vector< int > retVal;

			retVal.push_back( 256 );
			retVal.push_back( 257 );
			retVal.push_back( 258 );

			return retVal;
		}

		const std::vector< std::string > strings() const
		{
			std::vector< std::string > retVal;

			retVal.push_back( "EYE_LEFT" );
			retVal.push_back( "EYE_RIGHT" );
			retVal.push_back( "EYE_BOTH" );

			return retVal;
		}
	};



	/**
	 * @name Factories
	 */
	//@{

	/**
	 * @brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values
	 */
	static vgd::Shp< Camera > create( const std::string nodeName = "NoName" );

	/**
	 * @brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values and
	 * sets the \c multiAttributeIndex of the multi-attribute.
	 *
	 * @param index		zero-based index of the multi-attribute
	 */
	static vgd::Shp< Camera > create( const std::string nodeName, const uint8 index );
	
	/**
	 *@brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values (optionals fields too).
	 */
	static vgd::Shp< Camera > createWhole( const std::string nodeName = "DefaultWhole" );

	//@}



	/**
	 * @name Accessors to field viewport
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c viewport.
	 */
	typedef vgm::Rectangle2i ViewportValueType;

	/**
	 * @brief Type definition of the field named \c viewport
	 */
	typedef vgd::field::TOptionalField< ViewportValueType > FViewportType;


	/**
	 * @brief Gets the value of field named \c viewport.
	 */
	const bool getViewport( ViewportValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c viewport.
 	 */
	void setViewport( const ViewportValueType& value );

	/**
	 * @brief Erases the field named \c viewport.
	 */
	void eraseViewport();

	/**
	 * @brief Tests if the value of field named \c viewport has been initialized.
	 */
	const bool hasViewport() const;
	//@}



	/**
	 * @name Accessors to field projectionLeft
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c projectionLeft.
	 */
	typedef vgm::MatrixR ProjectionLeftValueType;

	/**
	 * @brief Type definition of the field named \c projectionLeft
	 */
	typedef vgd::field::TSingleField< ProjectionLeftValueType > FProjectionLeftType;


	/**
	 * @brief Gets the value of field named \c projectionLeft.
	 */
	const ProjectionLeftValueType getProjectionLeft() const;

	/**
	 * @brief Sets the value of field named \c projectionLeft.
	 */
	void setProjectionLeft( const ProjectionLeftValueType value );

	//@}



	/**
	 * @name Accessors to field zFar
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c zFar.
	 */
	typedef float ZFarValueType;

	/**
	 * @brief Type definition of the field named \c zFar
	 */
	typedef vgd::field::TOptionalField< ZFarValueType > FZFarType;


	/**
	 * @brief Gets the value of field named \c zFar.
	 */
	const bool getZFar( ZFarValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c zFar.
 	 */
	void setZFar( const ZFarValueType& value );

	/**
	 * @brief Erases the field named \c zFar.
	 */
	void eraseZFar();

	/**
	 * @brief Tests if the value of field named \c zFar has been initialized.
	 */
	const bool hasZFar() const;
	//@}



	/**
	 * @name Accessors to field lookAtLeft
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c lookAtLeft.
	 */
	typedef vgm::MatrixR LookAtLeftValueType;

	/**
	 * @brief Type definition of the field named \c lookAtLeft
	 */
	typedef vgd::field::TSingleField< LookAtLeftValueType > FLookAtLeftType;


	/**
	 * @brief Gets the value of field named \c lookAtLeft.
	 */
	const LookAtLeftValueType getLookAtLeft() const;

	/**
	 * @brief Sets the value of field named \c lookAtLeft.
	 */
	void setLookAtLeft( const LookAtLeftValueType value );

	//@}



	/**
	 * @name Accessors to field lookAtRight
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c lookAtRight.
	 */
	typedef vgm::MatrixR LookAtRightValueType;

	/**
	 * @brief Type definition of the field named \c lookAtRight
	 */
	typedef vgd::field::TSingleField< LookAtRightValueType > FLookAtRightType;


	/**
	 * @brief Gets the value of field named \c lookAtRight.
	 */
	const LookAtRightValueType getLookAtRight() const;

	/**
	 * @brief Sets the value of field named \c lookAtRight.
	 */
	void setLookAtRight( const LookAtRightValueType value );

	//@}



	/**
	 * @name Accessors to field projectionRight
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c projectionRight.
	 */
	typedef vgm::MatrixR ProjectionRightValueType;

	/**
	 * @brief Type definition of the field named \c projectionRight
	 */
	typedef vgd::field::TSingleField< ProjectionRightValueType > FProjectionRightType;


	/**
	 * @brief Gets the value of field named \c projectionRight.
	 */
	const ProjectionRightValueType getProjectionRight() const;

	/**
	 * @brief Sets the value of field named \c projectionRight.
	 */
	void setProjectionRight( const ProjectionRightValueType value );

	//@}



	/**
	 * @name Accessors to field scissor
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c scissor.
	 */
	typedef vgm::Rectangle2i ScissorValueType;

	/**
	 * @brief Type definition of the field named \c scissor
	 */
	typedef vgd::field::TOptionalField< ScissorValueType > FScissorType;


	/**
	 * @brief Gets the value of field named \c scissor.
	 */
	const bool getScissor( ScissorValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c scissor.
 	 */
	void setScissor( const ScissorValueType& value );

	/**
	 * @brief Erases the field named \c scissor.
	 */
	void eraseScissor();

	/**
	 * @brief Tests if the value of field named \c scissor has been initialized.
	 */
	const bool hasScissor() const;
	//@}



	/**
	 * @name Accessors to field mode
	 */
	//@{

	/**
	 * @brief Definition of symbolic values
	 */
	enum  
	{
		MONOSCOPIC = 259,	///< Non stereoscopic rendering. Scene is viewed for the one eye located at \c lookAtLeft and projected with \c projectionLeft along eye direction on near plane. \c viewport and \c scissor fields are used to define the camera too.
		ANAGLYPH = 261,	///< @todo Stereoscopic rendering using red/cyan anaglyph. All fields are used to define the camera.
		QUAD_BUFFER = 260,	///< Stereoscopic rendering using quad buffer (i.e. active stereo using shutter glasses, or passive stereo using polarized projectors and glasses). Scene is viewer for left and right eyes. All fields are used to define the camera.
		DEFAULT_MODE = MONOSCOPIC	///< Non stereoscopic rendering. Scene is viewed for the one eye located at \c lookAtLeft and projected with \c projectionLeft along eye direction on near plane. \c viewport and \c scissor fields are used to define the camera too.
	};

	/**
	 * @brief Type definition of a container for the previous symbolic values
	 */
	struct ModeValueType : public vgd::field::Enum
	{
		ModeValueType()
		{}

		ModeValueType( const int v )
		: vgd::field::Enum(v)
		{}

		ModeValueType( const ModeValueType& o )
		: vgd::field::Enum(o)
		{}

		ModeValueType( const vgd::field::Enum& o )
		: vgd::field::Enum(o)
		{}

		const std::vector< int > values() const
		{
			std::vector< int > retVal;

			retVal.push_back( 259 );
			retVal.push_back( 260 );
			retVal.push_back( 261 );

			return retVal;
		}

		const std::vector< std::string > strings() const
		{
			std::vector< std::string > retVal;

			retVal.push_back( "MONOSCOPIC" );
			retVal.push_back( "QUAD_BUFFER" );
			retVal.push_back( "ANAGLYPH" );

			return retVal;
		}
	};

	/**
	 * @brief Type definition of the field named \c mode
	 */
	typedef vgd::field::TSingleField< vgd::field::Enum > FModeType;


	/**
	 * @brief Gets the value of field named \c mode.
	 */
	const ModeValueType getMode() const;

	/**
	 * @brief Sets the value of field named \c mode.
	 */
	void setMode( const ModeValueType value );

	//@}



	/**
	 * @name Accessors to field aspect
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c aspect.
	 */
	typedef float AspectValueType;

	/**
	 * @brief Type definition of the field named \c aspect
	 */
	typedef vgd::field::TOptionalField< AspectValueType > FAspectType;


	/**
	 * @brief Gets the value of field named \c aspect.
	 */
	const bool getAspect( AspectValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c aspect.
 	 */
	void setAspect( const AspectValueType& value );

	/**
	 * @brief Erases the field named \c aspect.
	 */
	void eraseAspect();

	/**
	 * @brief Tests if the value of field named \c aspect has been initialized.
	 */
	const bool hasAspect() const;
	//@}



	/**
	 * @name Accessors to field rightEye
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c rightEye.
	 */
	typedef bool RightEyeValueType;

	/**
	 * @brief Type definition of the field named \c rightEye
	 */
	typedef vgd::field::TSingleField< RightEyeValueType > FRightEyeType;


	/**
	 * @brief Gets the value of field named \c rightEye.
	 */
	const RightEyeValueType getRightEye() const;

	/**
	 * @brief Sets the value of field named \c rightEye.
	 */
	void setRightEye( const RightEyeValueType value );

	//@}



	/**
	 * @name Accessors to field eyeSeparation
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c eyeSeparation.
	 */
	typedef float EyeSeparationValueType;

	/**
	 * @brief Type definition of the field named \c eyeSeparation
	 */
	typedef vgd::field::TSingleField< EyeSeparationValueType > FEyeSeparationType;


	/**
	 * @brief Gets the value of field named \c eyeSeparation.
	 */
	const EyeSeparationValueType getEyeSeparation() const;

	/**
	 * @brief Sets the value of field named \c eyeSeparation.
	 */
	void setEyeSeparation( const EyeSeparationValueType value );

	//@}



	/**
	 * @name Accessors to field imageShift
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c imageShift.
	 */
	typedef float ImageShiftValueType;

	/**
	 * @brief Type definition of the field named \c imageShift
	 */
	typedef vgd::field::TSingleField< ImageShiftValueType > FImageShiftType;


	/**
	 * @brief Gets the value of field named \c imageShift.
	 */
	const ImageShiftValueType getImageShift() const;

	/**
	 * @brief Sets the value of field named \c imageShift.
	 */
	void setImageShift( const ImageShiftValueType value );

	//@}



	/**
	 * @name Accessors to field zNear
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c zNear.
	 */
	typedef float ZNearValueType;

	/**
	 * @brief Type definition of the field named \c zNear
	 */
	typedef vgd::field::TOptionalField< ZNearValueType > FZNearType;


	/**
	 * @brief Gets the value of field named \c zNear.
	 */
	const bool getZNear( ZNearValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c zNear.
 	 */
	void setZNear( const ZNearValueType& value );

	/**
	 * @brief Erases the field named \c zNear.
	 */
	void eraseZNear();

	/**
	 * @brief Tests if the value of field named \c zNear has been initialized.
	 */
	const bool hasZNear() const;
	//@}



	/**
	 * @name Accessors to field fovy
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c fovy.
	 */
	typedef float FovyValueType;

	/**
	 * @brief Type definition of the field named \c fovy
	 */
	typedef vgd::field::TSingleField< FovyValueType > FFovyType;


	/**
	 * @brief Gets the value of field named \c fovy.
	 */
	const FovyValueType getFovy() const;

	/**
	 * @brief Sets the value of field named \c fovy.
	 */
	void setFovy( const FovyValueType value );

	//@}



	/**
	 * @name Field name accessors
	 */
	//@{

	/**
	 * @brief Returns the name of field \c viewport.
	 *
	 * @return the name of field \c viewport.
	 */
	static const std::string getFViewport( void );

	/**
	 * @brief Returns the name of field \c projectionLeft.
	 *
	 * @return the name of field \c projectionLeft.
	 */
	static const std::string getFProjectionLeft( void );

	/**
	 * @brief Returns the name of field \c zFar.
	 *
	 * @return the name of field \c zFar.
	 */
	static const std::string getFZFar( void );

	/**
	 * @brief Returns the name of field \c lookAtLeft.
	 *
	 * @return the name of field \c lookAtLeft.
	 */
	static const std::string getFLookAtLeft( void );

	/**
	 * @brief Returns the name of field \c lookAtRight.
	 *
	 * @return the name of field \c lookAtRight.
	 */
	static const std::string getFLookAtRight( void );

	/**
	 * @brief Returns the name of field \c projectionRight.
	 *
	 * @return the name of field \c projectionRight.
	 */
	static const std::string getFProjectionRight( void );

	/**
	 * @brief Returns the name of field \c scissor.
	 *
	 * @return the name of field \c scissor.
	 */
	static const std::string getFScissor( void );

	/**
	 * @brief Returns the name of field \c mode.
	 *
	 * @return the name of field \c mode.
	 */
	static const std::string getFMode( void );

	/**
	 * @brief Returns the name of field \c aspect.
	 *
	 * @return the name of field \c aspect.
	 */
	static const std::string getFAspect( void );

	/**
	 * @brief Returns the name of field \c rightEye.
	 *
	 * @return the name of field \c rightEye.
	 */
	static const std::string getFRightEye( void );

	/**
	 * @brief Returns the name of field \c eyeSeparation.
	 *
	 * @return the name of field \c eyeSeparation.
	 */
	static const std::string getFEyeSeparation( void );

	/**
	 * @brief Returns the name of field \c imageShift.
	 *
	 * @return the name of field \c imageShift.
	 */
	static const std::string getFImageShift( void );

	/**
	 * @brief Returns the name of field \c zNear.
	 *
	 * @return the name of field \c zNear.
	 */
	static const std::string getFZNear( void );

	/**
	 * @brief Returns the name of field \c fovy.
	 *
	 * @return the name of field \c fovy.
	 */
	static const std::string getFFovy( void );

	//@}


	/**
	 * @name Dirty flags enumeration
	 */
	//@{


	//@}
	/**
	 * @name High-level methods
	 *
	 * @todo viewAll()
	 */
	//@{

	/**
	 * @brief Apply the viewport transformation (as defined in OpenGL specification) to a vertex.
	 *
	 * @param vertex	vertex to transform
	 * @return the transformed vertex
	 *
	 * @pre hasViewport()
	 */
	const vgm::Vec3f applyViewport( const vgm::Vec3f& vertex );

	/**
	 * @brief Apply the viewport transformation (as defined in OpenGL specification) to a vertex.
	 *
	 * @param viewport	the viewport used to compute the transformation
	 * @param vertex	vertex to transform
	 * @return the transformed vertex
	 */
	static const vgm::Vec3f applyViewport( const vgm::Rectangle2i& viewport, const vgm::Vec3f& vertex );

	//@}


	/**
	 * @name Helpers
	 */
	//@{

	typedef LookAtLeftValueType LookAtValueType;

	/**
	 * @brief Gets the value of field named \c lookAtLeft or \c lookAtRight depending of the given eye usage policy.
	 *
	 * @return	Returns \c lookAtLeft if eyeUsagePolicy is EYE_LEFT.
	 *			Returns \c lookAtRight if eyeUsagePolicy is EYE_RIGHT.
	 *			Returns \c lookAtLeft if eyeUsagePolicy is EYE_BOTH (but in this case, the precondition getLookAtLeft() == getLookAtRight() must be verified).
	 */
	const LookAtValueType getLookAt( const EyeUsagePolicyValueType eyeUsagePolicy = EyeUsagePolicyValueType(EYE_BOTH) ) const;

	/**
	 * @brief Sets the value of field named \c lookAtLeft and \c lookAtRight
	 */
	void setLookAt( const LookAtValueType value );



	typedef ProjectionLeftValueType ProjectionValueType;

	/**
	 * @brief Gets the value of field named \c projectionLeft or \c projectionRight depending of the given eye usage policy.
	 *
	 * @return	Returns \c projectionLeft if eyeUsagePolicy is EYE_LEFT.
	 *			Returns \c projectionRight if eyeUsagePolicy is EYE_RIGHT.
	 *			Returns \c projectionLeft if eyeUsagePolicy is EYE_BOTH (but in this case, the precondition getProjectionLeft() == getProjectionRight() must be verified).
	 */
	const ProjectionValueType getProjection( const EyeUsagePolicyValueType eyeUsagePolicy =  EyeUsagePolicyValueType(EYE_BOTH) ) const;

	/**
	 * @brief Sets the value of field named \c projectionLeft and \c projectionRight
	 *
	 * depends on \c mode field
	 * @todo doc
	 */
	void setProjection( const ProjectionValueType value );

	//@}



	/**
	 * @name Accessors to field matrix
	 * @deprecated
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c Matrix.
	 * @deprecated
	 */
	typedef vgm::MatrixR MatrixValueType;

	/**
	 * @brief Type definition of the field named \c matrix
	 * @deprecated
	 */
	typedef vgd::field::TSingleField< MatrixValueType > FMatrixType;


	/**
	 * @brief Gets the value of field named \c matrix.
	 * @deprecated
	 */
	vgDEPRECATED( const MatrixValueType getMatrix() const );

	/**
	 * @brief Sets the value of field named \c matrix.
	 * @deprecated
	 */
	vgDEPRECATED( void setMatrix( const MatrixValueType value ) );

	//@}



	/**
	 * @name High-level accessors
	 */
	//@{

	/**
	 * @brief Returns the value of field named \c viewport modified (if needed) by taking care of the given eye usage policy, the \c mode field and the \c imageShift field.
	 */
	const bool gethViewport( ViewportValueType& value, const int drawingSurfaceWidth, const EyeUsagePolicyValueType eyeUsagePolicy =  EyeUsagePolicyValueType(EYE_BOTH) ) const;

	/**
	 * brief Sets at once \c lookAtLeft and \c lookAtRight fields for stereoscopic rendering
	 *
	 * The first three parameters defines a 3D geometric transformation applied to monoscopic eye.
	 * The position of monoscopic eye is slightly shift along the X axis using \c eyeSeparation value to define left eye and right eye.
	 *
	 * param lookAtEye		the position of the eye point
	 * param lookAtCenter	the position of the reference point
	 * param lookAtUp		the direction of the up vector
	 * param eyeSeparation	the distance between the two eyes
	 */
	//void sethLookAtLeftAndRight( const vgm::Vec3f lookAtEye, const vgm::Vec3f lookAtCenter, const vgm::Vec3f lookAtUp, const float eyeSeparation );

	/**
	 * @brief Sets the value of the field named \c fovy and recompute the projection matrix using the value of aspect zNear and zFar optional fields if they are presents.
	 * Otherwise, only sets the fovy field.
	 */
	void sethFovy( const FovyValueType fovy);

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
	Camera( const std::string nodeName );

public:
	IMPLEMENT_INDEXABLE_CLASS_HPP( , Camera );
private:
	static const vgd::basic::RegisterNode<Camera> m_registrationInstance;
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_CAMERA_HPP
