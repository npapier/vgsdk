// VGSDK - Copyright (C) 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_ANTIALIASING_HPP
#define _VGD_NODE_ANTIALIASING_HPP

#include "vgd/field/Enum.hpp"
#include "vgd/node/SingleAttribute.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Built-in antialiasing support
 *
 * Antialiasing (AA) is the process of smoothing edges so they dont appear jagged. The technique currently supported is FXAA version 1 designed by Timothy Lottes of NVIDIA. FXAA is short for Fast Approximate Anti-Aliasing. Below is a description of FXAA in much more detail from Timothy Lottes. FXAA was designed to be a fast post-process shader based anti-aliasing method which can improve image quality when an application cannot afford to use hardware anti-aliasing methods like MSAA or CSAA. FXAA is not designed to replace MSAA/CSAA or any other hardware AA method, but rather just offer another option. FXAA is an interesting option for a game which is using deferred rendering and doesn't have MSAA support,  or for a notebook which cannot run 4xMSAA fast enough in a specific game. But for games which have native MSAA support on higher-end machines, the 4xMSAA option will have higher quality. As a post-process filter running without multiple samples per pixel, FXAA has some limitations as to what quality it can reach. FXAA can improve the quality along edges, but it does not do a good job on near horizontal or near vertical edges. Since FXAA runs without MSAA, it also attempts to find areas of the image which might cause jittering in motion and  reduces the contrast to reduce the jittering in motion (compared to no-AA). This effect can look like a softening of the image. FXAA does not mix with MSAA/CSAA. FXAA is designed to find edges on no-AA images,  and the MSAA gradient steps confuse the FXAA filter. That being said some developers like DICE with Battlefield3 on Windows,  decided to offer an FXAA option even with MSAA turned on, and this can increase quality on things like trees and bushes which  use a technique called "alpha test" which doesn't mix as well with MSAA. 
 *
 * New fields defined by this node :
 * - SFEnum \c technique = (FXAA1)<br>
 *   The antialiasing technique to be used.<br>
 *<br>
 *
 * @ingroup g_nodes
 * @ingroup g_singleAttributeNodes
 * @ingroup g_frameBufferNodes
 */
struct VGD_API Antialiasing : public vgd::node::SingleAttribute
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
	static vgd::Shp< Antialiasing > create( const std::string nodeName = "NoName" );

	/**
	 * @brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values and
	 * sets the \c multiAttributeIndex of the multi-attribute.
	 *
	 * @param index		zero-based index of the multi-attribute
	 */
	static vgd::Shp< Antialiasing > create( const std::string nodeName, const uint8 index );
	
	/**
	 *@brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values (optionals fields too).
	 */
	static vgd::Shp< Antialiasing > createWhole( const std::string nodeName = "DefaultWhole" );

	//@}



	/**
	 * @name Accessors to field technique
	 */
	//@{

	/**
	 * @brief Definition of symbolic values
	 */
	enum  
	{
		FXAA1 = 257,	///< Fast Approximate Anti-Aliasing (FXAA) version 1
		NONE = 256,	///< No antialiasing
		DEFAULT_TECHNIQUE = FXAA1	///< Fast Approximate Anti-Aliasing (FXAA) version 1
	};

	/**
	 * @brief Type definition of a container for the previous symbolic values
	 */
	struct TechniqueValueType : public vgd::field::Enum
	{
		TechniqueValueType()
		{}

		TechniqueValueType( const int v )
		: vgd::field::Enum(v)
		{}

		TechniqueValueType( const TechniqueValueType& o )
		: vgd::field::Enum(o)
		{}

		TechniqueValueType( const vgd::field::Enum& o )
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

			retVal.push_back( "NONE" );
			retVal.push_back( "FXAA1" );

			return retVal;
		}
	};

	/**
	 * @brief Type definition of the field named \c technique
	 */
	typedef vgd::field::TSingleField< vgd::field::Enum > FTechniqueType;


	/**
	 * @brief Gets the value of field named \c technique.
	 */
	const TechniqueValueType getTechnique() const;

	/**
	 * @brief Sets the value of field named \c technique.
	 */
	void setTechnique( const TechniqueValueType value );

	//@}



	/**
	 * @name Field name accessors
	 */
	//@{

	/**
	 * @brief Returns the name of field \c technique.
	 *
	 * @return the name of field \c technique.
	 */
	static const std::string getFTechnique( void );

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
	Antialiasing( const std::string nodeName );

public:
	IMPLEMENT_INDEXABLE_CLASS_HPP( , Antialiasing );
private:
	static const vgd::basic::RegisterNode<Antialiasing> m_registrationInstance;
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_ANTIALIASING_HPP
