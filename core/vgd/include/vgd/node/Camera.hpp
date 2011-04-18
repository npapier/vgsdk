// VGSDK - Copyright (C) 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_CAMERA_HPP
#define _VGD_NODE_CAMERA_HPP

#include "vgd/field/Enum.hpp"
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
 * - SFMatrixR \c projectionLeft = vgm::MatrixR(vgm::MatrixR::getIdentity())<br>
 *   Determines the projection matrix for monoscopic rendering or for the left eye if stereo is enabled.<br>
 *<br>
 * - SFMatrixR \c lookAtLeft = vgm::MatrixR(vgm::MatrixR::getIdentity())<br>
 *   Determines the 3D geometric transformation as a 4x4 matrix applied to camera for monoscopic rendering or for the left eye if stereo is enabled.\nNote that this transformation is applied to engine like any GeometricalTransformation node with composeTransformation field sets to false.\nBy default, the camera is situated at the origin, points down the negative z-axis, and has an up-vector of (0, 1, 0).<br>
 *<br>
 * - SFMatrixR \c lookAtRight = vgm::MatrixR(vgm::MatrixR::getIdentity())<br>
 *   Determines the 3D geometric transformation as a 4x4 matrix applied to camera for the right eye (used only if stereo is enabled).\nNote that this transformation is applied to engine like any GeometricalTransformation node with composeTransformation field sets to false.\nBy default, the camera is situated at the origin, points down the negative z-axis, and has an up-vector of (0, 1, 0).<br>
 *<br>
 * - SFMatrixR \c projectionRight = vgm::MatrixR(vgm::MatrixR::getIdentity())<br>
 *   Determines the projection matrix for the right eye (used only if stereo is enabled).<br>
 *<br>
 * - OFRectangle2i \c [scissor] = empty<br>
 *   Determines the scissor box. It is automatically enabled if this field is defined, otherwise it is disabled. The default value is empty, i.e. scissor test is disabled.<br>
 *<br>
 * - SFEnum \c mode = MONOSCOPIC<br>
 *   Specifies the camera mode (monoscopic or stereoscopic mode).\nWhen you normally look at objects, your two eyes see slightly different images (because they are located at different viewpoints).\nStereoscopic rendering is a technique for creating the illusion of depth in an image for the viewer. Two images are computed (one for each eye) and presented to the viewer using anaglyph (red/cyan) or quad buffer stereo (todo). The brain combined these images to given the perception of depth.<br>
 *<br>
 * - OFRectangle2i \c [viewport] = vgm::Rectangle2i(0, 0, 1600, 1200)<br>
 *   Determines the viewport.<br>
 *<br>
 *
 * @ingroup g_nodes
 * @ingroup g_singleAttributeNodes
 * @ingroup g_transformationNodes
 */
struct VGD_API Camera : public vgd::node::GeometricalTransformation, public vgd::node::ProjectionTransformation
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
		MONOSCOPIC = 256,	///< Non stereoscopic rendering. \c projectionLeft, \c lookAtLeft, \c viewport and \c scissor fields are used to define the camera.
		ANAGLYPH = 257,	///< Stereoscopic rendering using red/cyan anaglyph. All fields are used to define the camera.
		DEFAULT_MODE = MONOSCOPIC	///< Non stereoscopic rendering. \c projectionLeft, \c lookAtLeft, \c viewport and \c scissor fields are used to define the camera.
	};

	/**
	 * @brief Type definition of the value contained by field named \c mode.
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

			retVal.push_back( 256 );
			retVal.push_back( 257 );

			return retVal;
		}

		const std::vector< std::string > strings() const
		{
			std::vector< std::string > retVal;

			retVal.push_back( "MONOSCOPIC" );
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
	 * @name Field name accessors
	 */
	//@{

	/**
	 * @brief Returns the name of field \c projectionLeft.
	 *
	 * @return the name of field \c projectionLeft.
	 */
	static const std::string getFProjectionLeft( void );

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
	 * @brief Returns the name of field \c viewport.
	 *
	 * @return the name of field \c viewport.
	 */
	static const std::string getFViewport( void );

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
	 * @return vertex transformed
	 *
	 * @pre hasViewport()
	 */
	const vgm::Vec3f applyViewport( const vgm::Vec3f& vertex );
	//@}



	/**
	 * @name Helpers
	 */
	//@{

	typedef LookAtLeftValueType LookAtValueType;

	/**
	 * @brief Gets the value of field named \c lookAtLeft.
	 */
	const LookAtValueType getLookAt() const;

	/**
	 * @brief Sets the value of field named \c lookAtLeft.
	 */
	void setLookAt( const LookAtValueType value );



	typedef ProjectionLeftValueType ProjectionValueType;

	/**
	 * @brief Gets the value of field named \c projectionLeft.
	 */
	const ProjectionValueType getProjection() const;

	/**
	 * @brief Sets the value of field named \c projectionLeft.
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
