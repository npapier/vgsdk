// VGSDK - Copyright (C) 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_FLUID_HPP
#define _VGD_NODE_FLUID_HPP

#include "vgd/field/Bool.hpp"
#include "vgd/field/Float.hpp"
#include "vgd/field/IImageShp.hpp"
#include "vgd/field/MatrixR.hpp"
#include "vgd/field/NodeWkp.hpp"
#include "vgd/field/String.hpp"
#include "vgd/field/Vec2i.hpp"
#include "vgd/field/Vec4f.hpp"
#include "vgd/field/Vec5f.hpp"
#include "vgd/node/Shape.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Fluid allow the simulation of liquids
 *
 * Liquids are simulated using several height maps (sceneHeightMap computed from \c scene, fluidHeightMap containing height of the fluid). A tessellated quad with displacement mapping is used for the rendering. 
 *
 * New fields defined by this node :
 * - SFFloat \c opacity = (0.6)<br>
 *   todo<br>
 *<br>
 * - MFVec5f \c emittersOrDrainers = vgm::Vec5f(0.f, 0.f, 0.f, 0.f, 0.f)<br>
 *   Specifies the position (x, y, z), and properties (radius and intensity) of each fluid emitter/drainer. Actually, the maximum number of emitters/drainers is 4.<br>
 *<br>
 * - SFVec2i \c heightMapSize = vgm::Vec2i(256, 256)<br>
 *   Specifies the size of the textures used to store scene and fluid height map.<br>
 *<br>
 * - SFNodeWkp \c scene = vgd::node::NodeWkp()<br>
 *   Specifies the root of the scene graph used by the fluid simulation.<br>
 *<br>
 * - SFBool \c requestFeedback = (false)<br>
 *   True to request a feedback in field fluidPositionFeedback during the next rendering. This field is automatically reset to false after the completion of the feedback.<br>
 *<br>
 * - SFVec4f \c gravity = vgm::Vec4f(0.f, -1.f, 0.f, 9.8f)<br>
 *   Specifies the direction of the gravity (the first three components) and the intensity (the last component).<br>
 *<br>
 * - SFString \c simulationPass1 = std::string()<br>
 *   Specifies the second stage of the simulation.<br>
 *<br>
 * - SFString \c simulationPass0 = std::string()<br>
 *   Specifies the first stage of the simulation.<br>
 *<br>
 * - SFFloat \c cellSize = (1.0)<br>
 *   todo<br>
 *<br>
 * - SFMatrixR \c feedbackInformationsBis = vgm::MatrixR(vgm::MatrixR::getIdentity())<br>
 *   todo<br>
 *<br>
 * - SFFloat \c damping = (0.8)<br>
 *   todo<br>
 *<br>
 * - SFFloat \c timeStep = (0.1)<br>
 *   todo<br>
 *<br>
 * - SFFloat \c thickness = (1.0)<br>
 *   fluid thickness factor (only visual)<br>
 *<br>
 * - SFVec5f \c feedbackInformations = vgm::Vec5f(0.f, 0.f, 0.f, 0.f, 0.f)<br>
 *   todo<br>
 *<br>
 * - SFFloat \c css = (1.0)<br>
 *   todo<br>
 *<br>
 * - SFIImageShp \c fluidPositionFeedback = vgd::basic::IImageShp()<br>
 *   todo<br>
 *<br>
 *
 * @ingroup g_nodes
 * @ingroup g_shapeNodes
 * @ingroup g_propertiesNodes
 */
struct VGD_API Fluid : public vgd::node::Shape
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
	static vgd::Shp< Fluid > create( const std::string nodeName = "NoName" );

	/**
	 * @brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values and
	 * sets the \c multiAttributeIndex of the multi-attribute.
	 *
	 * @param index		zero-based index of the multi-attribute
	 */
	static vgd::Shp< Fluid > create( const std::string nodeName, const uint8 index );
	
	/**
	 *@brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values (optionals fields too).
	 */
	static vgd::Shp< Fluid > createWhole( const std::string nodeName = "DefaultWhole" );

	//@}



	/**
	 * @name Accessors to field opacity
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c opacity.
	 */
	typedef float OpacityValueType;

	/**
	 * @brief The default value of field named \c opacity.
	 */
	static const OpacityValueType DEFAULT_OPACITY;

	/**
	 * @brief Type definition of the field named \c opacity
	 */
	typedef vgd::field::TSingleField< OpacityValueType > FOpacityType;


	/**
	 * @brief Gets the value of field named \c opacity.
	 */
	const OpacityValueType getOpacity() const;

	/**
	 * @brief Sets the value of field named \c opacity.
	 */
	void setOpacity( const OpacityValueType value );

	//@}



	/**
	 * @name Accessors to field emittersOrDrainers
	 *
	 * @todo getEmittersOrDrainers( const bool rw = false ) ?
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c emittersOrDrainers.
	 */
	typedef vgm::Vec5f EmittersOrDrainersValueType;

	/**
	 * @brief Type definition of the field named \c emittersOrDrainers
	 */
	typedef vgd::field::TMultiField< EmittersOrDrainersValueType > FEmittersOrDrainersType;


	/**
	 * @brief Gets a read-only editor on the multi field named \c emittersOrDrainers.
	 */
	vgd::field::EditorRO< FEmittersOrDrainersType > getEmittersOrDrainersRO() const;

	/**
	 * @brief Gets a read-write editor on the multi field named \c emittersOrDrainers.
	 */
	vgd::field::EditorRW< FEmittersOrDrainersType > getEmittersOrDrainersRW();

	//@}



	/**
	 * @name Accessors to field heightMapSize
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c heightMapSize.
	 */
	typedef vgm::Vec2i HeightMapSizeValueType;

	/**
	 * @brief The default value of field named \c heightMapSize.
	 */
	static const HeightMapSizeValueType DEFAULT_HEIGHTMAPSIZE;

	/**
	 * @brief Type definition of the field named \c heightMapSize
	 */
	typedef vgd::field::TSingleField< HeightMapSizeValueType > FHeightMapSizeType;


	/**
	 * @brief Gets the value of field named \c heightMapSize.
	 */
	const HeightMapSizeValueType getHeightMapSize() const;

	/**
	 * @brief Sets the value of field named \c heightMapSize.
	 */
	void setHeightMapSize( const HeightMapSizeValueType value );

	//@}



	/**
	 * @name Accessors to field scene
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c scene.
	 */
	typedef vgd::node::NodeWkp SceneValueType;

	/**
	 * @brief The default value of field named \c scene.
	 */
	static const SceneValueType DEFAULT_SCENE;

	/**
	 * @brief Type definition of the field named \c scene
	 */
	typedef vgd::field::TSingleField< SceneValueType > FSceneType;


	/**
	 * @brief Gets the value of field named \c scene.
	 */
	const SceneValueType getScene() const;

	/**
	 * @brief Sets the value of field named \c scene.
	 */
	void setScene( const SceneValueType value );

	//@}



	/**
	 * @name Accessors to field requestFeedback
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c requestFeedback.
	 */
	typedef bool RequestFeedbackValueType;

	/**
	 * @brief The default value of field named \c requestFeedback.
	 */
	static const RequestFeedbackValueType DEFAULT_REQUESTFEEDBACK;

	/**
	 * @brief Type definition of the field named \c requestFeedback
	 */
	typedef vgd::field::TSingleField< RequestFeedbackValueType > FRequestFeedbackType;


	/**
	 * @brief Gets the value of field named \c requestFeedback.
	 */
	const RequestFeedbackValueType getRequestFeedback() const;

	/**
	 * @brief Sets the value of field named \c requestFeedback.
	 */
	void setRequestFeedback( const RequestFeedbackValueType value );

	//@}



	/**
	 * @name Accessors to field gravity
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c gravity.
	 */
	typedef vgm::Vec4f GravityValueType;

	/**
	 * @brief The default value of field named \c gravity.
	 */
	static const GravityValueType DEFAULT_GRAVITY;

	/**
	 * @brief Type definition of the field named \c gravity
	 */
	typedef vgd::field::TSingleField< GravityValueType > FGravityType;


	/**
	 * @brief Gets the value of field named \c gravity.
	 */
	const GravityValueType getGravity() const;

	/**
	 * @brief Sets the value of field named \c gravity.
	 */
	void setGravity( const GravityValueType value );

	//@}



	/**
	 * @name Accessors to field simulationPass1
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c simulationPass1.
	 */
	typedef std::string SimulationPass1ValueType;

	/**
	 * @brief The default value of field named \c simulationPass1.
	 */
	static const SimulationPass1ValueType DEFAULT_SIMULATIONPASS1;

	/**
	 * @brief Type definition of the field named \c simulationPass1
	 */
	typedef vgd::field::TSingleField< SimulationPass1ValueType > FSimulationPass1Type;


	/**
	 * @brief Gets the value of field named \c simulationPass1.
	 */
	const SimulationPass1ValueType getSimulationPass1() const;

	/**
	 * @brief Sets the value of field named \c simulationPass1.
	 */
	void setSimulationPass1( const SimulationPass1ValueType value );

	//@}



	/**
	 * @name Accessors to field simulationPass0
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c simulationPass0.
	 */
	typedef std::string SimulationPass0ValueType;

	/**
	 * @brief The default value of field named \c simulationPass0.
	 */
	static const SimulationPass0ValueType DEFAULT_SIMULATIONPASS0;

	/**
	 * @brief Type definition of the field named \c simulationPass0
	 */
	typedef vgd::field::TSingleField< SimulationPass0ValueType > FSimulationPass0Type;


	/**
	 * @brief Gets the value of field named \c simulationPass0.
	 */
	const SimulationPass0ValueType getSimulationPass0() const;

	/**
	 * @brief Sets the value of field named \c simulationPass0.
	 */
	void setSimulationPass0( const SimulationPass0ValueType value );

	//@}



	/**
	 * @name Accessors to field cellSize
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c cellSize.
	 */
	typedef float CellSizeValueType;

	/**
	 * @brief The default value of field named \c cellSize.
	 */
	static const CellSizeValueType DEFAULT_CELLSIZE;

	/**
	 * @brief Type definition of the field named \c cellSize
	 */
	typedef vgd::field::TSingleField< CellSizeValueType > FCellSizeType;


	/**
	 * @brief Gets the value of field named \c cellSize.
	 */
	const CellSizeValueType getCellSize() const;

	/**
	 * @brief Sets the value of field named \c cellSize.
	 */
	void setCellSize( const CellSizeValueType value );

	//@}



	/**
	 * @name Accessors to field feedbackInformationsBis
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c feedbackInformationsBis.
	 */
	typedef vgm::MatrixR FeedbackInformationsBisValueType;

	/**
	 * @brief The default value of field named \c feedbackInformationsBis.
	 */
	static const FeedbackInformationsBisValueType DEFAULT_FEEDBACKINFORMATIONSBIS;

	/**
	 * @brief Type definition of the field named \c feedbackInformationsBis
	 */
	typedef vgd::field::TSingleField< FeedbackInformationsBisValueType > FFeedbackInformationsBisType;


	/**
	 * @brief Gets the value of field named \c feedbackInformationsBis.
	 */
	const FeedbackInformationsBisValueType getFeedbackInformationsBis() const;

	/**
	 * @brief Sets the value of field named \c feedbackInformationsBis.
	 */
	void setFeedbackInformationsBis( const FeedbackInformationsBisValueType value );

	//@}



	/**
	 * @name Accessors to field damping
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c damping.
	 */
	typedef float DampingValueType;

	/**
	 * @brief The default value of field named \c damping.
	 */
	static const DampingValueType DEFAULT_DAMPING;

	/**
	 * @brief Type definition of the field named \c damping
	 */
	typedef vgd::field::TSingleField< DampingValueType > FDampingType;


	/**
	 * @brief Gets the value of field named \c damping.
	 */
	const DampingValueType getDamping() const;

	/**
	 * @brief Sets the value of field named \c damping.
	 */
	void setDamping( const DampingValueType value );

	//@}



	/**
	 * @name Accessors to field timeStep
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c timeStep.
	 */
	typedef float TimeStepValueType;

	/**
	 * @brief The default value of field named \c timeStep.
	 */
	static const TimeStepValueType DEFAULT_TIMESTEP;

	/**
	 * @brief Type definition of the field named \c timeStep
	 */
	typedef vgd::field::TSingleField< TimeStepValueType > FTimeStepType;


	/**
	 * @brief Gets the value of field named \c timeStep.
	 */
	const TimeStepValueType getTimeStep() const;

	/**
	 * @brief Sets the value of field named \c timeStep.
	 */
	void setTimeStep( const TimeStepValueType value );

	//@}



	/**
	 * @name Accessors to field thickness
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c thickness.
	 */
	typedef float ThicknessValueType;

	/**
	 * @brief The default value of field named \c thickness.
	 */
	static const ThicknessValueType DEFAULT_THICKNESS;

	/**
	 * @brief Type definition of the field named \c thickness
	 */
	typedef vgd::field::TSingleField< ThicknessValueType > FThicknessType;


	/**
	 * @brief Gets the value of field named \c thickness.
	 */
	const ThicknessValueType getThickness() const;

	/**
	 * @brief Sets the value of field named \c thickness.
	 */
	void setThickness( const ThicknessValueType value );

	//@}



	/**
	 * @name Accessors to field feedbackInformations
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c feedbackInformations.
	 */
	typedef vgm::Vec5f FeedbackInformationsValueType;

	/**
	 * @brief The default value of field named \c feedbackInformations.
	 */
	static const FeedbackInformationsValueType DEFAULT_FEEDBACKINFORMATIONS;

	/**
	 * @brief Type definition of the field named \c feedbackInformations
	 */
	typedef vgd::field::TSingleField< FeedbackInformationsValueType > FFeedbackInformationsType;


	/**
	 * @brief Gets the value of field named \c feedbackInformations.
	 */
	const FeedbackInformationsValueType getFeedbackInformations() const;

	/**
	 * @brief Sets the value of field named \c feedbackInformations.
	 */
	void setFeedbackInformations( const FeedbackInformationsValueType value );

	//@}



	/**
	 * @name Accessors to field css
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c css.
	 */
	typedef float CssValueType;

	/**
	 * @brief The default value of field named \c css.
	 */
	static const CssValueType DEFAULT_CSS;

	/**
	 * @brief Type definition of the field named \c css
	 */
	typedef vgd::field::TSingleField< CssValueType > FCssType;


	/**
	 * @brief Gets the value of field named \c css.
	 */
	const CssValueType getCss() const;

	/**
	 * @brief Sets the value of field named \c css.
	 */
	void setCss( const CssValueType value );

	//@}



	/**
	 * @name Accessors to field fluidPositionFeedback
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c fluidPositionFeedback.
	 */
	typedef vgd::basic::IImageShp FluidPositionFeedbackValueType;

	/**
	 * @brief The default value of field named \c fluidPositionFeedback.
	 */
	static const FluidPositionFeedbackValueType DEFAULT_FLUIDPOSITIONFEEDBACK;

	/**
	 * @brief Type definition of the field named \c fluidPositionFeedback
	 */
	typedef vgd::field::TSingleField< FluidPositionFeedbackValueType > FFluidPositionFeedbackType;


	/**
	 * @brief Gets the value of field named \c fluidPositionFeedback.
	 */
	const FluidPositionFeedbackValueType getFluidPositionFeedback() const;

	/**
	 * @brief Sets the value of field named \c fluidPositionFeedback.
	 */
	void setFluidPositionFeedback( const FluidPositionFeedbackValueType value );

	//@}



	/**
	 * @name Field name accessors
	 */
	//@{

	/**
	 * @brief Returns the name of field \c opacity.
	 *
	 * @return the name of field \c opacity.
	 */
	static const std::string getFOpacity( void );

	/**
	 * @brief Returns the name of field \c emittersOrDrainers.
	 *
	 * @return the name of field \c emittersOrDrainers.
	 */
	static const std::string getFEmittersOrDrainers( void );

	/**
	 * @brief Returns the name of field \c heightMapSize.
	 *
	 * @return the name of field \c heightMapSize.
	 */
	static const std::string getFHeightMapSize( void );

	/**
	 * @brief Returns the name of field \c scene.
	 *
	 * @return the name of field \c scene.
	 */
	static const std::string getFScene( void );

	/**
	 * @brief Returns the name of field \c requestFeedback.
	 *
	 * @return the name of field \c requestFeedback.
	 */
	static const std::string getFRequestFeedback( void );

	/**
	 * @brief Returns the name of field \c gravity.
	 *
	 * @return the name of field \c gravity.
	 */
	static const std::string getFGravity( void );

	/**
	 * @brief Returns the name of field \c simulationPass1.
	 *
	 * @return the name of field \c simulationPass1.
	 */
	static const std::string getFSimulationPass1( void );

	/**
	 * @brief Returns the name of field \c simulationPass0.
	 *
	 * @return the name of field \c simulationPass0.
	 */
	static const std::string getFSimulationPass0( void );

	/**
	 * @brief Returns the name of field \c cellSize.
	 *
	 * @return the name of field \c cellSize.
	 */
	static const std::string getFCellSize( void );

	/**
	 * @brief Returns the name of field \c feedbackInformationsBis.
	 *
	 * @return the name of field \c feedbackInformationsBis.
	 */
	static const std::string getFFeedbackInformationsBis( void );

	/**
	 * @brief Returns the name of field \c damping.
	 *
	 * @return the name of field \c damping.
	 */
	static const std::string getFDamping( void );

	/**
	 * @brief Returns the name of field \c timeStep.
	 *
	 * @return the name of field \c timeStep.
	 */
	static const std::string getFTimeStep( void );

	/**
	 * @brief Returns the name of field \c thickness.
	 *
	 * @return the name of field \c thickness.
	 */
	static const std::string getFThickness( void );

	/**
	 * @brief Returns the name of field \c feedbackInformations.
	 *
	 * @return the name of field \c feedbackInformations.
	 */
	static const std::string getFFeedbackInformations( void );

	/**
	 * @brief Returns the name of field \c css.
	 *
	 * @return the name of field \c css.
	 */
	static const std::string getFCss( void );

	/**
	 * @brief Returns the name of field \c fluidPositionFeedback.
	 *
	 * @return the name of field \c fluidPositionFeedback.
	 */
	static const std::string getFFluidPositionFeedback( void );

	//@}


	/**
	 * @name Dirty flags enumeration
	 */
	//@{


	//@}



	bool computeBoundingBox( const vgm::MatrixR& transformation );	///< overridden method

	bool isBoundingBoxValid() const;								///< overridden method

	void invalidateBoundingBox( bool bInvalidate = true );			///< overridden method


	/**
	 *@name High-level accessors
	 */
	//@{

	/**
	 * @brief Sets default value for simulationPass0 and simulationPass1 fields.
	 */
	void sethSimulationPassToDefault();
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
	Fluid( const std::string nodeName );

public:
	IMPLEMENT_INDEXABLE_CLASS_HPP( , Fluid );
private:
	static const vgd::basic::RegisterNode<Fluid> m_registrationInstance;
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_FLUID_HPP
