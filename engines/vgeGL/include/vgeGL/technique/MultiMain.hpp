// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_TECHNIQUE_MULTIMAIN_HPP
#define _VGEGL_TECHNIQUE_MULTIMAIN_HPP

#include "vgeGL/technique/Main.hpp"
#include <map>



namespace vgeGL
{

namespace technique
{



/**
 * @brief Windows emulation in a single framebuffer.
 *
 * This technique is useful to simulate windows in a single framebuffer. The technique Main is used as rendering backend.
 *
 * @todo MultiTechnique instead of MultiMain to be able to use another technique for the rendering (Shadow technique for example...).
 * @todo Window flipping in x and/or y
 * @todo Renders in FBO
 * @todo Composes windows to add transparency
 *
 * @ingroup g_techniques_vgeGL
 * @ingroup g_techniques
 */
struct VGEGL_API MultiMain : public Main
{
	/**
	 * @brief Definition of a functor to configure/unconfigure scene graph just before/after the rendering of a window.
	 */
	struct VGEGL_API SceneGraphConfigurator
	{
		/**
		 * @brief Configures the scene graph
		 *
		 * @return true if scene graph topology has been modified, false otherwise
		 */
		virtual const bool	apply( vge::visitor::TraverseElementVector * /*traverseElements*/ )			{ return false; }

		/**
		 * @brief Undoing the scene graph configuration done in apply().
		 */
		virtual void		unapply(	vge::visitor::TraverseElementVector * /*traverseElements */ )		{}
	};
	
	/**
	 * @brief	Definition of a composite configurator that allows to combine several scene graph configurators in one.
	 */
	struct /*VGEGL_API*/ CompositeConfigurator : public SceneGraphConfigurator
	{
		/**
		 * @name	Child Configurator Management
		 */
		//@{
		/**
		 * @brief	Adds a new configurator.
		 *
		 * @param	configurator	a configurator to add
		 */
		void add( vgd::Shp< SceneGraphConfigurator > configurator )
		{
			if( ! has(configurator) )
			{
				m_children.push_back(configurator);
			}
		}
		
		/**
		 * @brief	Tells if the given configurator is already part of the composite.
		 *
		 * @param	configurator	a configurator
		 *
		 * @return	true or false
		 */
		const bool has( vgd::Shp< SceneGraphConfigurator > configurator ) const
		{
			return std::find(m_children.begin(), m_children.end(), configurator) != m_children.end();
		}
		
		/**
		 * @brief	Removes a given configurator.
		 *
		 * @param	configurator	a configurator to remove
		 */
		void remove( vgd::Shp< SceneGraphConfigurator > configurator )
		{
			Container::iterator	newEnd = std::remove(m_children.begin(), m_children.end(), configurator);
			m_children.erase(newEnd, m_children.end());
		}
		//@}
		
		/**
		 * @name	Overrides
		 */
		//@{
		const bool apply( vge::visitor::TraverseElementVector * traverseElements )
		{
			bool	topologyChanged = false;
			
			for( Container::iterator i = m_children.begin(); i != m_children.end(); ++i )
			{
				vgd::Shp< SceneGraphConfigurator >	configurator( *i );
				
				topologyChanged = topologyChanged || configurator->apply( traverseElements );
			}
			return topologyChanged;
		}
		
		void unapply( vge::visitor::TraverseElementVector * traverseElements )
		{
			for( Container::iterator i = m_children.begin(); i != m_children.end(); ++i )
			{
				vgd::Shp< SceneGraphConfigurator >	configurator( *i );
				
				configurator->unapply( traverseElements );
			}
		}
		//@}
		
	private:
		typedef std::vector< vgd::Shp< SceneGraphConfigurator > >	Container;
		
		Container	m_children;	///< Holds references to child configurators
	};

	/**
	 * @brief Window properties definition
	 *
	 * The window position and size is defined by \c geometry and \c zOrder properties.
	 * @see g_coordinatesSystem
	 *
	 * The \c configurator property defines a functor used to configure the scene graph for this window. Typically this functor moves the camera.
	 *
	 * Each window could have a border (or not) with a different color and a different width.
	 */
	struct VGEGL_API Window
	{
		/**
		 * @brief Default constructor
		 *
		 * @post getGeometry().isInvalid() == true
		 * @post getConfigurator()
		 */
		Window(	const int			zOrder		= 0,
				const bool			isVisible	= true,
				const bool			hasBorder	= true,
				const vgm::Vec4f	borderColor	= vgm::Vec4f(1.f, 1.f, 1.f, 1.f),
				const float			borderWidth	= 3.f )
		:	m_zOrder		(	zOrder		),
			//m_configurator
			m_isVisible		( isVisible		),
			m_hasBorder		( hasBorder		),
			m_borderColor	( borderColor	),
			m_borderWidth	( borderWidth	)
		{
			m_geometry.setInvalid();
		}

		/**
		 * @brief Retrieves the window geometry.
		 *
		 * @return the rectangle that defined the geometry of the window
		 */
		const vgm::Rectangle2f getGeometry() const { return m_geometry; }

		/**
		 * @brief Sets the window geometry.
		 *
		 * @param geometry	the rectangle that defined the geometry of the window
		 */
		void setGeometry( const vgm::Rectangle2f& geometry ) { m_geometry = geometry; }


		/**
		 * @brief Retrieves the window z-order.
		 *
		 * @return the z-order value
		 */
		const int getZOrder() const { return m_zOrder; }

		/**
		 * @brief Sets the window z-order.
		 *
		 * @param zOrder	the window z-order value
		 */
		void setZOrder( const int zOrder ) { m_zOrder = zOrder; }


		/**
		 * @brief Retrieves the window configurator functor.
		 *
		 * @return the functor
		 */
		const vgd::Shp< SceneGraphConfigurator > getConfigurator() const { return m_configurator; }

		/**
		 * @brief Sets the window configurator functor.
		 *
		 * @param configurator	the functor
		 */
		void setConfigurator( const vgd::Shp< SceneGraphConfigurator >  configurator ) { m_configurator = configurator; }



		/**
		 * @brief Tests if the window is visible.
		 *
		 * @return true if the window is visible, false otherwise.
		 */
		const bool isVisible() const { return m_isVisible; }

		/**
		 * @brief Sets window visible state.
		 *
		 * @param isVisible	true to show the window, false to hide it
		 */
		void setVisible( const bool isVisible = true ) { m_isVisible = isVisible; }



		/**
		 * @brief Tests if the window has a border.
		 *
		 * @return true if the window has a border, false otherwise.
		 */
		const bool hasBorder() const { return m_hasBorder; }

		/**
		 * @brief Sets window border state.
		 *
		 * @param hasBorder	true to have a border around the window, false otherwise
		 */
		void setBorder( const bool hasBorder ) { m_hasBorder = hasBorder; }



		/**
		 * @brief Retrieves the border color.
		 *
		 * @return the rgba border color.
		 */
		const vgm::Vec4f getBorderColor() const { return m_borderColor; }

		/**
		 * @brief Sets the border color.
		 *
		 * @param borderColor	the rgba color used to draw window border.
		 */
		void setBorderColor( const vgm::Vec4f borderColor ) { m_borderColor = borderColor; }



		/**
		 * @brief Retrieves the width of the window border.
		 *
		 * @return the width of the window border
		 */
		const float getBorderWidth() const { return m_borderWidth; }

		/**
		 * @brief Sets the width of the window border.
		 *
		 * @param borderWidth	the width of the window border
		 *
		 * @pre borderWidth >= 2 and borderWidth <=10
		 * @remark 
		 */
		void setBorderWidth( const float borderWidth )
		{
			assert(borderWidth >= 2 && "Out of range value for window border width.");
			assert(borderWidth <= 10 && "Out of range value for window border width.");
			m_borderWidth = borderWidth; 
		}



	private:
		vgm::Rectangle2f					m_geometry;		///< Geometry of the window (position and size in the framebuffer).
		/// @todo rel or abs for geometry
		int									m_zOrder;		///< Z-order of the window (position in window stack).

		vgd::Shp< SceneGraphConfigurator >	m_configurator;	///< Functor to configure the scene graph for this window.

		bool								m_isVisible;	///< True if the window is visible, false otherwise
		bool								m_hasBorder;	///< True if the window has a border
		vgm::Vec4f							m_borderColor;	///< Border color
		float								m_borderWidth;	///< Width of the window border.
	};

	/**
	 * @name Windows accessors
	 *
	 * A window is identified uniquely by its name.
	 *
	 * @todo renameWindow( const std::string oldName, const std::string newName );
	 */
	//@{

	/**
	 * @brief Adds a new window.
	 *
	 * @param name			name of the window
	 * @param zOrder		see Window
	 * @param hasBorder		see Window
	 * @param borderColor	see Window
	 * @param borderWidth	see Window
	 *
	 * @remark By default, a new window is visible. See Window::setVisible() and Window::isVisible().
	 */
	vgd::Shp< Window > addWindow(	const std::string	name,
									const int			zOrder		= 0,
									const bool			hasBorder	= true,
									const vgm::Vec4f	borderColor	= vgm::Vec4f(1.f, 1.f, 1.f, 1.f),
									const float			borderWidth	= 3.f );

	/**
	 * @brief Removes one window.
	 *
	 * @param name		name of the window to remove
	 *
	 * @return true if the window has been removed, false otherwise.
	 */
	const bool removeWindow( const std::string name );

	/**
	 * @brief Removes all windows.
	 *
	 * @return true if the window has been removed, false otherwise.
	 */
	const bool removeAllWindows();

	/**
	 @brief Retrieves the desired window.
	 *
	 * @param name		name of the window
	 *
	 * @return the desired window
	 */
	vgd::Shp< Window > getWindow( const std::string name );

	/**
	 @brief Retrieves the desired window.
	 *
	 * @param name		name of the window
	 *
	 * @return the desired window
	 */
	const vgd::Shp< Window > getWindow( const std::string name ) const;
	//@}



	/*VGEGL_API */void apply( vgeGL::engine::Engine * /*engine*/, vge::visitor::TraverseElementVector * /*traverseElements*/ );



private:
	/**
	 * @brief Draws the border for the given window
	 */
	void drawBorder( const vgd::Shp< MultiMain::Window > window, vgm::Rectangle2i newViewport2i );

	typedef std::map< std::string, vgd::Shp< Window > > WindowContainer;	///< Definition of window container
	WindowContainer							m_windows;						///< The container of windows

	vge::visitor::NodeCollectorExtended<> 	m_collectorExt;	///< Collector of nodes. Useful because scene graph topology could be different for each window.
};



} // namespace technique

} // namespace vgeGL

#endif //#ifndef _VGEGL_TECHNIQUE_MULTIMAIN_HPP
