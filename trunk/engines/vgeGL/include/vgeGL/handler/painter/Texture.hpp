// VGSDK - Copyright (C) 2004, 2007, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_HANDLER_PAINTER_TEXTURE_HPP
#define _VGEGL_HANDLER_PAINTER_TEXTURE_HPP

#include <boost/tuple/tuple.hpp>
#include <vgd/basic/IImage.hpp>
#include <vge/handler/painter/MultiAttribute.hpp>

#include "vgeGL/vgeGL.hpp"

namespace glo { struct Texture; }

namespace vgd
{
	namespace field { struct DirtyFlag; }
	namespace node { struct Texture; }
}

namespace vgeGL
{
	namespace engine { struct Engine; }
	namespace rc { struct Texture; }
}



namespace vgeGL
{

namespace handler
{

namespace painter
{


/**
 * @brief Send render commands for the Texture node.
 * 
 * @todo Optimize convertMy*2GL() using a table.
 */
struct VGEGL_API Texture : public vge::handler::painter::MultiAttribute
{
protected:

	struct TexInfo; ///< Forward declaration

public:

	void setToDefaults();

	void paint( vgeGL::engine::Engine*, vgd::node::Texture*, glo::Texture* );

	/**
	 * @brief Sends glTexParameter commands for the Texture node.
	 */
	void paintParams( vgeGL::engine::Engine *pEngine, vgd::node::Texture *pNode, glo::Texture *pResource );

	/**
	 * brief Sends glTexEnv commands for the Texture node.
	 *
	 * Only for non GLSL pipeline (LayerPlan)
	 */
	//void paintEnv( vgeGL::engine::Engine *pEngine, vgd::node::Texture *pNode, glo::Texture *pResource );

	/**
	 * @brief
	 */
	void synchronize( vgeGL::engine::Engine* pGLEngine, vgd::node::Texture *pNode, glo::Texture * pResource );

	/**
	 * @brief
	 */
	void texSubImage(	vgeGL::engine::Engine *pGLEngine, vgd::node::Texture *pNode,
						glo::Texture *pTexture,
						TexInfo& texInfo );

protected:

	/**
	 * @brief Definition of the different image state.
	 */
	enum State 
	{
		NOIIMAGE_VALIDATED,
		IIMAGE_VALIDATED,
		NOIIMAGE_DIRTY,
		IIMAGE_DIRTY
	};

	/**
	 * @brief Computes state of Texture.image field.
	 *
	 * @return the state of the Texture.image field (one value among NOIIMAGE_VALIDATED,  IIMAGE_VALIDATED, NOIIMAGE_DIRTY or IIMAGE_DIRTY).
	 */
	State preSynchronize(	vgeGL::engine::Engine *, vgd::node::Texture *, ::glo::Texture *,
							TexInfo& );



	/**
	 * @name Internal helpers
	 */
	//@{

	/**
	 * @brief Informations on texture map and texture parameters.
	 */
	struct TexInfo
	{
		TexInfo()
		:	//iimage
			//
			//borderSize			(	0		),
			imageSize			(	0, 0, 0 ),
			imageSizePOT		(	0, 0, 0 ),
			texDimension		(	-1		),
			internalFormat		(	0		),
			format				(	0		),
			type				(	0		),
			texSize				(	0, 0, 0 ),
			resizeForTex		(	false	)
		{}

		/**
		 * @name preSynchronize
		 */
		//@{

		vgd::Shp< vgd::basic::IImage >	iimage;		//!< the incoming image (from texture node)

		//@}



		/**
		 * @name computeTexImageParams
		 */
		//@{
			
		//GLint		borderSize;

		vgm::Vec3i	imageSize;
		vgm::Vec3i	imageSizePOT;

		int			texDimension;

		GLint		internalFormat;
		GLenum		format;
		GLenum		type;

		vgm::Vec3i	texSize;
		bool		resizeForTex;
		//@}
	};
	//@}

	/**
	 * @brief Computes all texture informations needed for glTexImage function.
	 */
	void computeTexInfo( vgeGL::engine::Engine *pGLEngine, vgd::node::Texture *pNode, ::glo::Texture * pTexture, TexInfo& texInfo );

	/**
	 * @brief Computes texture image parameters and fills TexInfo structure with theses parameters.
	 *
	 * @remarks This method takes care of POT/NPOT image (by using GL_ARB_texture_non_power_of_two or by resizing incoming image).
	 */
	void computeTexImageParams( vgd::node::Texture *pNode, ::glo::Texture * pTexture, TexInfo& texInfo );

	/**
	 * @brief Takes care of texture size limit.
	 *
	 * Tests if the incoming image must be resized, i.e. image size exceed maximum texture size.
	 *
	 * @todo Uses texture proxies.
	 */
	void clampTexImageSize( vgeGL::engine::Engine *pGLEngine, ::glo::Texture * pTexture, TexInfo& texInfo );

	/**
	 * @brief Tests if the computed texture parameters are compatblies with the currrent real texture.
	 * 
	 * @return true if compatible, false if not.
	 */
	const bool isTextureCompatible( vgeGL::engine::Engine *pGLEngine, vgd::node::Texture *pNode, ::glo::Texture * pTexture, const TexInfo& texInfo );

	/**
	 * @brief Tests if computed texture size is compatible with the real texture size
	 *
	 * @return true if compatible, false if not.
	 */
	const bool isTextureSizeCompatible( ::glo::Texture * pTexture, const TexInfo& texInfo );

	/**
	 * @brief
	 */
	void synchronizeParametersAndEnv(	vgeGL::engine::Engine *pGLEngine, vgd::node::Texture *pNode,
										::glo::Texture *pTexture );


	/**
	 * @brief Returns the internal and external OpenGL format for the given image.
	 *
	 * @return a pair containing the internal format in its first component and the external format in its second component
	 */
	const boost::tuple< GLint, GLenum > chooseFormats( vgd::Shp< vgd::basic::IImage >, vgd::node::Texture * );

private:
	static GLenum	m_wrapParameter[];
	static GLint	m_wrapValue[];

	static GLenum	m_filterParameter[];
	static GLint	m_filterValue[];

	/*static GLint	m_functionValue[];
	
	static GLenum	m_combineParameter[];
	static GLint	m_combineValue[];
	
	static GLenum	m_sourceParameter[];
	static GLint	m_sourceValue[];
	
	static GLenum	m_operandParameter[];
	static GLint	m_operandValue[];

	static GLenum	m_scaleParameter[];*/
};



} // namespace painter

} // namespace handler

} // namespace vgeGL

#endif //#ifndef _VGEGL_HANDLER_PAINTER_TEXTURE_HPP
