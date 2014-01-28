// VGSDK - Copyright (C) 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_DISPLACEMENT_HPP
#define _VGD_NODE_DISPLACEMENT_HPP

#include "vgd/field/Enum.hpp"
#include "vgd/field/String.hpp"
#include "vgd/field/Vec4f.hpp"
#include "vgd/node/SingleAttribute.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Control displacement of vertices
 *
 * Vertices displacement is available at vertex shader level or/and at tessellation evaluation shader level. To combine several displacements, you have to compute each displacement and mixes them as you like in a custom displacement function (see customDisplacementVS and customDisplacementTES). CUSTOM displacement function has to modify the variable, named position, containing a copy of the current vertex given initially by variable mgl_Vertex. Type of position is vec4 (idem for the read-only variable mgl_Vertex). 
 *
 * New fields defined by this node :
 * - SFString \c declarationsVS = std::string()<br>
 *   Append this field to the vertex shader declarations section. Use case: to define function used by displacementVS field<br>
 *<br>
 * - SFString \c displacementVS = std::string()<br>
 *   Example : position += uDisplacementParameter4f0.x * vec4(normal,0);<br>
 *<br>
 * - SFString \c declarationsTES = std::string()<br>
 *   Append this field to the tessellation shader declarations section. Use case: to define function used by displacementTES field<br>
 *<br>
 * - SFString \c displacementTES = std::string()<br>
 *   Example : position += uDisplacementParameter4f0.y * vec4(ecNormal,0);<br>
 *<br>
 * - OFVec4f \c [parameter4f0] = vgm::Vec4f(0.f, 0.f, 0.f, 0.f)<br>
 *<br>
 * - OFVec4f \c [parameter4f1] = vgm::Vec4f(0.f, 0.f, 0.f, 0.f)<br>
 *<br>
 * - OFPredefinedDisplacementValueType \c [displacementFunctionVS] = (NONE)<br>
 *<br>
 * - OFPredefinedDisplacementValueType \c [displacementFunctionTES] = (NONE)<br>
 *<br>
 *
 * @ingroup g_nodes
 * @ingroup g_singleAttributeNodes
 * @ingroup g_propertiesNodes
 * @ingroup g_shapeModifierNodes
 */
struct VGD_API Displacement : public vgd::node::SingleAttribute
{
	/**
	 * @brief Definition of symbolic values
	 */
	enum PredefinedDisplacement 
	{
		NONE = 272,	///< No displacement add to the shader
		ALONG_NORMAL = 273,	///< Moves vertices along their normals based on among coming from parameter4f0.x (for VS) and from parameter4f0.y for (TES).
		CUSTOM = 274,	///< Uses custom displacement using fields declarationsVS and displacementVS for vertex shader (resp. declarationsTES/displacementTES for tessellation evaluation shader)
		DEFAULT_PREDEFINEDDISPLACEMENT = NONE	///< No displacement add to the shader
	};

	/**
	 * @brief Type definition of a container for the previous symbolic values
	 */
	struct PredefinedDisplacementValueType : public vgd::field::Enum
	{
		PredefinedDisplacementValueType()
		{}

		PredefinedDisplacementValueType( const int v )
		: vgd::field::Enum(v)
		{}

		PredefinedDisplacementValueType( const PredefinedDisplacementValueType& o )
		: vgd::field::Enum(o)
		{}

		PredefinedDisplacementValueType( const vgd::field::Enum& o )
		: vgd::field::Enum(o)
		{}

		const std::vector< int > values() const
		{
			std::vector< int > retVal;

			retVal.push_back( 272 );
			retVal.push_back( 273 );
			retVal.push_back( 274 );

			return retVal;
		}

		const std::vector< std::string > strings() const
		{
			std::vector< std::string > retVal;

			retVal.push_back( "NONE" );
			retVal.push_back( "ALONG_NORMAL" );
			retVal.push_back( "CUSTOM" );

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
	static vgd::Shp< Displacement > create( const std::string nodeName = "NoName" );

	/**
	 * @brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values and
	 * sets the \c multiAttributeIndex of the multi-attribute.
	 *
	 * @param index		zero-based index of the multi-attribute
	 */
	static vgd::Shp< Displacement > create( const std::string nodeName, const uint8 index );
	
	/**
	 *@brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values (optionals fields too).
	 */
	static vgd::Shp< Displacement > createWhole( const std::string nodeName = "DefaultWhole" );

	//@}



	/**
	 * @name Accessors to field declarationsVS
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c declarationsVS.
	 */
	typedef std::string DeclarationsVSValueType;

	/**
	 * @brief The default value of field named \c declarationsVS.
	 */
	static const DeclarationsVSValueType DEFAULT_DECLARATIONSVS;

	/**
	 * @brief Type definition of the field named \c declarationsVS
	 */
	typedef vgd::field::TSingleField< DeclarationsVSValueType > FDeclarationsVSType;


	/**
	 * @brief Gets the value of field named \c declarationsVS.
	 */
	const DeclarationsVSValueType getDeclarationsVS() const;

	/**
	 * @brief Sets the value of field named \c declarationsVS.
	 */
	void setDeclarationsVS( const DeclarationsVSValueType value );

	//@}



	/**
	 * @name Accessors to field displacementVS
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c displacementVS.
	 */
	typedef std::string DisplacementVSValueType;

	/**
	 * @brief The default value of field named \c displacementVS.
	 */
	static const DisplacementVSValueType DEFAULT_DISPLACEMENTVS;

	/**
	 * @brief Type definition of the field named \c displacementVS
	 */
	typedef vgd::field::TSingleField< DisplacementVSValueType > FDisplacementVSType;


	/**
	 * @brief Gets the value of field named \c displacementVS.
	 */
	const DisplacementVSValueType getDisplacementVS() const;

	/**
	 * @brief Sets the value of field named \c displacementVS.
	 */
	void setDisplacementVS( const DisplacementVSValueType value );

	//@}



	/**
	 * @name Accessors to field declarationsTES
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c declarationsTES.
	 */
	typedef std::string DeclarationsTESValueType;

	/**
	 * @brief The default value of field named \c declarationsTES.
	 */
	static const DeclarationsTESValueType DEFAULT_DECLARATIONSTES;

	/**
	 * @brief Type definition of the field named \c declarationsTES
	 */
	typedef vgd::field::TSingleField< DeclarationsTESValueType > FDeclarationsTESType;


	/**
	 * @brief Gets the value of field named \c declarationsTES.
	 */
	const DeclarationsTESValueType getDeclarationsTES() const;

	/**
	 * @brief Sets the value of field named \c declarationsTES.
	 */
	void setDeclarationsTES( const DeclarationsTESValueType value );

	//@}



	/**
	 * @name Accessors to field displacementTES
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c displacementTES.
	 */
	typedef std::string DisplacementTESValueType;

	/**
	 * @brief The default value of field named \c displacementTES.
	 */
	static const DisplacementTESValueType DEFAULT_DISPLACEMENTTES;

	/**
	 * @brief Type definition of the field named \c displacementTES
	 */
	typedef vgd::field::TSingleField< DisplacementTESValueType > FDisplacementTESType;


	/**
	 * @brief Gets the value of field named \c displacementTES.
	 */
	const DisplacementTESValueType getDisplacementTES() const;

	/**
	 * @brief Sets the value of field named \c displacementTES.
	 */
	void setDisplacementTES( const DisplacementTESValueType value );

	//@}



	/**
	 * @name Accessors to field parameter4f0
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c parameter4f0.
	 */
	typedef vgm::Vec4f Parameter4f0ValueType;

	/**
	 * @brief The default value of field named \c parameter4f0.
	 */
	static const Parameter4f0ValueType DEFAULT_PARAMETER4F0;

	/**
	 * @brief Type definition of the field named \c parameter4f0
	 */
	typedef vgd::field::TOptionalField< Parameter4f0ValueType > FParameter4f0Type;


	/**
	 * @brief Gets the value of field named \c parameter4f0.
	 */
	const bool getParameter4f0( Parameter4f0ValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c parameter4f0.
 	 */
	void setParameter4f0( const Parameter4f0ValueType& value );

	/**
	 * @brief Erases the field named \c parameter4f0.
	 */
	void eraseParameter4f0();

	/**
	 * @brief Tests if the value of field named \c parameter4f0 has been initialized.
	 */
	const bool hasParameter4f0() const;
	//@}



	/**
	 * @name Accessors to field parameter4f1
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c parameter4f1.
	 */
	typedef vgm::Vec4f Parameter4f1ValueType;

	/**
	 * @brief The default value of field named \c parameter4f1.
	 */
	static const Parameter4f1ValueType DEFAULT_PARAMETER4F1;

	/**
	 * @brief Type definition of the field named \c parameter4f1
	 */
	typedef vgd::field::TOptionalField< Parameter4f1ValueType > FParameter4f1Type;


	/**
	 * @brief Gets the value of field named \c parameter4f1.
	 */
	const bool getParameter4f1( Parameter4f1ValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c parameter4f1.
 	 */
	void setParameter4f1( const Parameter4f1ValueType& value );

	/**
	 * @brief Erases the field named \c parameter4f1.
	 */
	void eraseParameter4f1();

	/**
	 * @brief Tests if the value of field named \c parameter4f1 has been initialized.
	 */
	const bool hasParameter4f1() const;
	//@}



	/**
	 * @name Accessors to field displacementFunctionVS
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c displacementFunctionVS.
	 */
	typedef PredefinedDisplacementValueType DisplacementFunctionVSValueType;

	/**
	 * @brief Type definition of the field named \c displacementFunctionVS
	 */
	typedef vgd::field::TOptionalField< vgd::field::Enum > FDisplacementFunctionVSType;


	/**
	 * @brief Gets the value of field named \c displacementFunctionVS.
	 */
	const bool getDisplacementFunctionVS( DisplacementFunctionVSValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c displacementFunctionVS.
 	 */
	void setDisplacementFunctionVS( const DisplacementFunctionVSValueType& value );

	/**
	 * @brief Erases the field named \c displacementFunctionVS.
	 */
	void eraseDisplacementFunctionVS();

	/**
	 * @brief Tests if the value of field named \c displacementFunctionVS has been initialized.
	 */
	const bool hasDisplacementFunctionVS() const;
	//@}



	/**
	 * @name Accessors to field displacementFunctionTES
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c displacementFunctionTES.
	 */
	typedef PredefinedDisplacementValueType DisplacementFunctionTESValueType;

	/**
	 * @brief Type definition of the field named \c displacementFunctionTES
	 */
	typedef vgd::field::TOptionalField< vgd::field::Enum > FDisplacementFunctionTESType;


	/**
	 * @brief Gets the value of field named \c displacementFunctionTES.
	 */
	const bool getDisplacementFunctionTES( DisplacementFunctionTESValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c displacementFunctionTES.
 	 */
	void setDisplacementFunctionTES( const DisplacementFunctionTESValueType& value );

	/**
	 * @brief Erases the field named \c displacementFunctionTES.
	 */
	void eraseDisplacementFunctionTES();

	/**
	 * @brief Tests if the value of field named \c displacementFunctionTES has been initialized.
	 */
	const bool hasDisplacementFunctionTES() const;
	//@}



	/**
	 * @name Field name accessors
	 */
	//@{

	/**
	 * @brief Returns the name of field \c declarationsVS.
	 *
	 * @return the name of field \c declarationsVS.
	 */
	static const std::string getFDeclarationsVS( void );

	/**
	 * @brief Returns the name of field \c displacementVS.
	 *
	 * @return the name of field \c displacementVS.
	 */
	static const std::string getFDisplacementVS( void );

	/**
	 * @brief Returns the name of field \c declarationsTES.
	 *
	 * @return the name of field \c declarationsTES.
	 */
	static const std::string getFDeclarationsTES( void );

	/**
	 * @brief Returns the name of field \c displacementTES.
	 *
	 * @return the name of field \c displacementTES.
	 */
	static const std::string getFDisplacementTES( void );

	/**
	 * @brief Returns the name of field \c parameter4f0.
	 *
	 * @return the name of field \c parameter4f0.
	 */
	static const std::string getFParameter4f0( void );

	/**
	 * @brief Returns the name of field \c parameter4f1.
	 *
	 * @return the name of field \c parameter4f1.
	 */
	static const std::string getFParameter4f1( void );

	/**
	 * @brief Returns the name of field \c displacementFunctionVS.
	 *
	 * @return the name of field \c displacementFunctionVS.
	 */
	static const std::string getFDisplacementFunctionVS( void );

	/**
	 * @brief Returns the name of field \c displacementFunctionTES.
	 *
	 * @return the name of field \c displacementFunctionTES.
	 */
	static const std::string getFDisplacementFunctionTES( void );

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
	Displacement( const std::string nodeName );

public:
	IMPLEMENT_INDEXABLE_CLASS_HPP( , Displacement );
private:
	static const vgd::basic::RegisterNode<Displacement> m_registrationInstance;
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_DISPLACEMENT_HPP
