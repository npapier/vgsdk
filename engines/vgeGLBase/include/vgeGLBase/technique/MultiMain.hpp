//// VGSDK - Copyright (C) 2008, 2009, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_TECHNIQUE_MULTIMAIN_HPP
//#define _VGEGLBASE_TECHNIQUE_MULTIMAIN_HPP
//
//#include <vgd/node/TransformDragger.hpp>
//#include "vgeGLBase/itf/IUnderlay.hpp"
//#include "vgeGLBase/technique/Technique.hpp"
//#include <map>
//
//
//
//namespace vgeGLBase
//{
//
//namespace technique
//{
//
//
//
///**
// * @brief Windows emulation in a single framebuffer.
// *
// * This technique is useful to simulate windows in a single framebuffer. The technique ForwardRendering is used as rendering backend, but could be changed using get/setPaintTechnique() methods.
// *
// *
// * @todo MultiMain => MultiView or MultiWindow
// * @todo Window flipping in x and/or y
// * @todo Renders in Texture/FBO
// * @todo Composes windows to add transparency
// *
// * @ingroup g_techniques_vgeGL
// * @ingroup g_techniques
// */
//struct VGEGLBASE_API MultiMain : public vgeGLBase::technique::Technique, public vgeGLBase::itf::IUnderlay
//{
//	// *********************************************************************************************************
//	/**
//	 * @brief Definition of a functor to configure/unconfigure scene graph just before/after the rendering of a window.
//	 */
//	struct /*VGEGLBASE_API*/ SceneGraphConfigurator
//	{
//		/**
//		 * @brief Configures the scene graph
//		 *
//		 * @return true if scene graph topology has been modified, false otherwise
//		 */
//		virtual const bool	apply( vge::visitor::TraverseElementVector * /*traverseElements*/ )			{ return false; }
//
//		/**
//		 * @brief Undoing the scene graph configuration done in apply().
//		 */
//		virtual void		unapply(	vge::visitor::TraverseElementVector * /*traverseElements */ )		{}
//	};
//
//
//
//	/**
//	 * @brief	Definition of a composite configurator that allows to combine several scene graph configurators in one.
//	 */
//	struct /*VGEGLBASE_API*/ CompositeConfigurator : public SceneGraphConfigurator
//	{
//		/**
//		 * @name	Child Configurator Management
//		 */
//		//@{
//		/**
//		 * @brief	Adds a new configurator.
//		 *
//		 * @param	configurator	a configurator to add
//		 */
//		void add( vgd::Shp< SceneGraphConfigurator > configurator )
//		{
//			if( ! has(configurator) )
//			{
//				m_children.push_back(configurator);
//			}
//		}
//		/**
//		 * @brief	Looks for the first configurator that matches the given type.
//		 *
//		 * @return	A shared pointer to the encountered configurator, or empty if none.
//		 */
//		template< typename ConfiguratorType >
//		vgd::Shp< ConfiguratorType > find() const
//		{
//			vgd::Shp< ConfiguratorType >   result;
//
//			for( Container::const_iterator i = m_children.begin(); i != m_children.end(); ++i )
//			{
//				result = vgd::dynamic_pointer_cast< ConfiguratorType >( *i );
// 
//				if( result )
//				{
//					break;
//				}
//			}
//
//			return result;
//		}
//		
//		/**
//		 * @brief	Tells if the given configurator is already part of the composite.
//		 *
//		 * @param	configurator	a configurator
//		 *
//		 * @return	true or false
//		 */
//		const bool has( vgd::Shp< SceneGraphConfigurator > configurator ) const
//		{
//			return std::find(m_children.begin(), m_children.end(), configurator) != m_children.end();
//		}
//		
//		/**
//		 * @brief	Removes a given configurator.
//		 *
//		 * @param	configurator	a configurator to remove
//		 */
//		void remove( vgd::Shp< SceneGraphConfigurator > configurator )
//		{
//			Container::iterator	newEnd = std::remove(m_children.begin(), m_children.end(), configurator);
//			m_children.erase(newEnd, m_children.end());
//		}
//		//@}
//		
//		/**
//		 * @name	Overrides
//		 */
//		//@{
//		const bool apply( vge::visitor::TraverseElementVector * traverseElements )
//		{
//			bool	topologyChanged = false;
//			
//			for( Container::iterator i = m_children.begin(); i != m_children.end(); ++i )
//			{
//				vgd::Shp< SceneGraphConfigurator >	configurator( *i );
//				
//				topologyChanged = topologyChanged || configurator->apply( traverseElements );
//			}
//			return topologyChanged;
//		}
//		
//		void unapply( vge::visitor::TraverseElementVector * traverseElements )
//		{
//			for( Container::iterator i = m_children.begin(); i != m_children.end(); ++i )
//			{
//				vgd::Shp< SceneGraphConfigurator >	configurator( *i );
//				
//				configurator->unapply( traverseElements );
//			}
//		}
//		//@}
//		
//	private:
//		typedef std::vector< vgd::Shp< SceneGraphConfigurator > >	Container;
//		
//		Container	m_children;	///< Holds references to child configurators
//	};
//
//
//
//	/**
//	 * @brief Change the view point of a multi-main window using its dragger.
//	 */
//	struct ViewPointConfigurator : public vgeGLBase::technique::MultiMain::SceneGraphConfigurator
//	{
//		/**
//		 * @brief Constructor
//		 *
//		 * @param dragger		the dragger node that must be modified.
//		 * @param rotation		the rotation to apply to the dragger
//		 */
//		ViewPointConfigurator( vgd::Shp< vgd::node::TransformDragger > dragger, const vgm::Rotation rotation )
//		:	m_dragger( dragger ),
//			m_rotation( rotation )
//		{}
//
//		/**
//		 * @name Overridden
//		 */
//		//@{
//		const bool apply( vge::visitor::TraverseElementVector * /*traverseElements*/ )
//		{
//			if ( m_dragger )
//			{
//				m_rotationBackup = m_dragger->getRotation();
//				m_dragger->setRotation( m_rotationBackup * m_rotation );
//				vgm::MatrixR mat = m_dragger->computeMatrixFromFields();
//				m_dragger->setMatrix( mat );
//			}
//			
//			return false;
//		}
//	   
//		void unapply( vge::visitor::TraverseElementVector * /*traverseElements*/ )
//		{
//			if ( m_dragger )
//			{
//				m_dragger->setRotation( m_rotationBackup );
//				vgm::MatrixR mat = m_dragger->computeMatrixFromFields();
//				m_dragger->setMatrix( mat );
//			}
//		}
//		//@}
//
//	private:
//		vgd::Shp< vgd::node::TransformDragger >	m_dragger;
//		const vgm::Rotation						m_rotation;
//		vgm::Rotation							m_rotationBackup;
//	};
//
//
//
//	// *********************************************************************************************************
//	/**
//	 * @brief State definition of window border
//	 */
//	struct VGEGLBASE_API WindowBorder
//	{
//		WindowBorder(	const bool			hasBorder	= true,
//						const vgm::Vec4f	color		= vgm::Vec4f(1.f, 1.f, 1.f, 1.f),
//						const float			width	= 4.f )
//		:	m_hasBorder( hasBorder		),
//			m_color	( color ),
//			m_width	( width )
//		{}
//
//
//		/**
//		 * @brief Tests if the window has a border.
//		 *
//		 * @return true if the window has a border, false otherwise.
//		 */
//		const bool hasBorder() const { return m_hasBorder; }
//
//		/**
//		 * @brief Sets window border state.
//		 *
//		 * @param hasBorder	true to have a border around the window, false otherwise
//		 */
//		void setBorder( const bool hasBorder ) { m_hasBorder = hasBorder; }
//
//
//		/**
//		 * @brief Retrieves the border color.
//		 *
//		 * @return the rgba border color.
//		 */
//		const vgm::Vec4f getColor() const { return m_color; }
//
//		/**
//		 * @brief Sets the border color.
//		 *
//		 * @param borderColor	the rgba color used to draw window border.
//		 */
//		void setColor( const vgm::Vec4f borderColor ) { m_color = borderColor; }
//
//
//		/**
//		 * @brief Retrieves the width of the window border.
//		 *
//		 * @return the width of the window border
//		 */
//		const float getWidth() const { return m_width; }
//
//		/**
//		 * @brief Sets the width of the window border.
//		 *
//		 * @param borderWidth	the width of the window border
//		 *
//		 * @pre borderWidth >= 2 and borderWidth <=10
//		 * @remark 
//		 */
//		void setWidth( const float borderWidth )
//		{
//			assert(borderWidth >= 2 && "Out of range value for window border width.");
//			assert(borderWidth <= 10 && "Out of range value for window border width.");
//			m_width = borderWidth; 
//		}
//
//	private:
//		bool								m_hasBorder;	///< True if the window has a border
//		vgm::Vec4f							m_color;		///< Border color
//		float								m_width;		///< Width of the window border.
//	};
//
//
//	/**
//	 * @brief Window properties definition
//	 *
//	 * A window has a name. Its position and size are defined by \c geometry and \c zOrder properties.
//	 * @see g_coordinatesSystem
//	 *
//	 * The \c configurator property defines a functor used to configure the scene graph for this window. Typically this functor moves the camera.
//	 *
//	 * A window could be visible or invisible.
//	 * Each window could have a border (or not) with a different color and a different width.
//	 */
//	struct VGEGLBASE_API Window
//	{
//		/**
//		 * @name Constructors
//		 */
//		//@{
//
//		/**
//		 * @brief Default constructor
//		 *
//		 * @post getGeometry().isInvalid() == true
//		 * @post getConfigurator() == 0
//		 */
//		vgDEPRECATED( Window(	const int			zOrder		= 0,
//								const bool			isVisible	= true,
//								const bool			hasBorder	= true,
//								const vgm::Vec4f	borderColor	= vgm::Vec4f(1.f, 1.f, 1.f, 1.f),
//								const float			borderWidth	= 3.f ) )
//		:	m_name			("defaultNameFromDeprecatedConstructor"	),
//			m_zOrder		(	zOrder		),
//			//m_configurator
//			m_isVisible		( isVisible		),
//			m_borderState	( hasBorder, borderColor, borderWidth )
//		{
//			m_geometry.setInvalid();
//		}
//
//		/**
//		 * @brief Default constructor
//		 *
//		 * @post getGeometry().isInvalid() == true
//		 * @post getConfigurator() == 0
//		 */
//		Window(	const std::string	name,
//				const int			zOrder		/*= 0*/,
//				const bool			isVisible	= true,
//				const WindowBorder	borderState = WindowBorder() )
//		:	m_name			(	name		),
//			m_zOrder		(	zOrder		),
//			//m_configurator
//			m_isVisible		( isVisible		),
//			m_borderState	( borderState	)
//		{
//			m_geometry.setInvalid();
//		}
//		//@}
//
//
//		/**
//		 * @name Accessors
//		 */
//		//@{
//
//		/**
//		 * @brief Retrieves the window name.
//		 */
//		const std::string& getName() const { return m_name; }
//
//
//		/**
//		 * @brief Retrieves the window geometry.
//		 *
//		 * @return the rectangle that defined the geometry of the window
//		 */
//		const vgm::Rectangle2f getGeometry() const { return m_geometry; }
//
//		/**
//		 * @brief Sets the window geometry.
//		 *
//		 * @param geometry	the rectangle that defined the geometry of the window
//		 */
//		void setGeometry( const vgm::Rectangle2f& geometry ) { m_geometry = geometry; }
//
//
//		/**
//		 * @brief Retrieves the window z-order.
//		 *
//		 * @return the z-order value
//		 */
//		const int getZOrder() const { return m_zOrder; }
//
//		/**
//		 * @brief Sets the window z-order.
//		 *
//		 * @param zOrder	the window z-order value
//		 */
//		void setZOrder( const int zOrder ) { m_zOrder = zOrder; }
//
//
//		/**
//		 * @brief Retrieves the window configurator functor.
//		 *
//		 * @return the functor
//		 */
//		const vgd::Shp< SceneGraphConfigurator > getConfigurator() const { return m_configurator; }
//
//		/**
//		 * @brief Sets the window configurator functor.
//		 *
//		 * @param configurator	the functor
//		 */
//		void setConfigurator( const vgd::Shp< SceneGraphConfigurator >  configurator ) { m_configurator = configurator; }
//
//
//		/**
//		 * @brief Tests if the window is visible.
//		 *
//		 * @return true if the window is visible, false otherwise.
//		 */
//		const bool isVisible() const { return m_isVisible; }
//
//		/**
//		 * @brief Sets window visible state.
//		 *
//		 * @param isVisible	true to show the window, false to hide it
//		 */
//		void setVisible( const bool isVisible = true ) { m_isVisible = isVisible; }
//
//
//		/**
//		 * @brief Returns the window border state
//		 */
//		const WindowBorder& getBorderState() const { return m_borderState; }
//
//		/**
//		 * @brief Sets the window border state
//		 *
//		 * @param borderState	the state of window border
//		 */
//		void setBorderState( const WindowBorder& borderState ) { m_borderState = borderState; }
//
//
//		/**
//		 * @brief Tests if the window has a border.
//		 *
//		 * @return true if the window has a border, false otherwise.
//		 */
//		const bool hasBorder() const { return m_borderState.hasBorder(); }
//
//		/**
//		 * @brief Sets window border state.
//		 *
//		 * @param hasBorder	true to have a border around the window, false otherwise
//		 */
//		void setBorder( const bool hasBorder ) { m_borderState.setBorder( hasBorder ); }
//
//
//		/**
//		 * @brief Retrieves the border color.
//		 *
//		 * @return the rgba border color.
//		 */
//		const vgm::Vec4f getBorderColor() const { return m_borderState.getColor(); }
//
//		/**
//		 * @brief Sets the border color.
//		 *
//		 * @param borderColor	the rgba color used to draw window border.
//		 */
//		void setBorderColor( const vgm::Vec4f borderColor ) { m_borderState.setColor( borderColor ); }
//
//
//		/**
//		 * @brief Retrieves the width of the window border.
//		 *
//		 * @return the width of the window border
//		 */
//		const float getBorderWidth() const { return m_borderState.getWidth(); }
//
//		/**
//		 * @brief Sets the width of the window border.
//		 *
//		 * @param borderWidth	the width of the window border
//		 *
//		 * @pre borderWidth >= 2 and borderWidth <=10
//		 * @remark 
//		 */
//		void setBorderWidth( const float borderWidth )
//		{
//			assert(borderWidth >= 2 && "Out of range value for window border width.");
//			assert(borderWidth <= 10 && "Out of range value for window border width.");
//			m_borderState.setWidth( borderWidth );
//		}
//		//@}
//
//
//		/**
//		 * brief Swaps two windows
//		 *
//		 * param window2	the second window
//		 */
//		/*void swap( Window& window2 )
//		{
//			std::swap( m_geometry,		window2.m_geometry );
//			std::swap( m_zOrder,		window2.m_zOrder );
//			std::swap( m_configurator,	window2.m_configurator );
//			std::swap( m_isVisible,		window2.m_isVisible );
//			std::swap( m_borderState,	window2.m_borderState );
//		}*/
//
//
//	private:
//		std::string							m_name;			///< Name of the window
//		vgm::Rectangle2f					m_geometry;		///< Geometry of the window (position and size in the framebuffer).
//		/// @todo rel or abs for geometry
//		int									m_zOrder;		///< Z-order of the window (position in window stack).
//
//		vgd::Shp< SceneGraphConfigurator >	m_configurator;	///< Functor to configure the scene graph for this window.
//
//		bool								m_isVisible;	///< True if the window is visible, false otherwise
//		WindowBorder						m_borderState;	///< State of the window border ( existence, color, width ).
//	};
//
//
//
//	// *********************************************************************************************************
//
//	/**
//	 * @brief Default constructor
//	 */
//	MultiMain();
//
//
//
//	/**
//	 * @name Windows accessors
//	 *
//	 * A window is identified uniquely by its name.
//	 *
//	 * @todo renameWindow( const std::string oldName, const std::string newName );
//	 */
//	//@{
//
//	/**
//	 * @brief Adds a new window.
//	 *
//	 * @param name		name of the window
//	 * @param zOrder		see Window
//	 * @param hasBorder	see Window
//	 * @param borderColor	see Window
//	 * @param borderWidth	see Window
//	 *
//	 * @remark By default, a new window is visible. See Window::setVisible() and Window::isVisible().
//	 */
//	vgDEPRECATED( vgd::Shp< Window > addWindow(	const std::string	name,
//									const int			zOrder		/*= 0*/,
//									const bool			hasBorder	= true,
//									const vgm::Vec4f	borderColor	= vgm::Vec4f(1.f, 1.f, 1.f, 1.f),
//									const float			borderWidth	= 3.f ) );
//
//	/**
//	 * @brief Adds a new window.
//	 *
//	 * @param name		name of the window
//	 * @param zOrder		see Window
//	 * @param borderState	see Window
//	 *
//	 * @remark By default, a new window is visible. See Window::setVisible() and Window::isVisible().
//	 */
//	vgd::Shp< Window > addWindow(	const std::string	name,
//									const int			zOrder		= 0,
//									const WindowBorder	borderState = WindowBorder() );
//
//	/**
//	 * @brief Removes one window.
//	 *
//	 * @param name		name of the window to remove
//	 *
//	 * @return true if the window has been removed, false otherwise.
//	 */
//	const bool removeWindow( const std::string name );
//
//	/**
//	 * @brief Removes all windows.
//	 *
//	 * @return true if the window has been removed, false otherwise.
//	 */
//	const bool removeAllWindows();
//
//	/**
//	 @brief Retrieves the desired window.
//	 *
//	 * @param name		name of the window
//	 *
//	 * @return the desired window
//	 */
//	vgd::Shp< Window > getWindow( const std::string name );
//
//	/**
//	 @brief Retrieves the desired window.
//	 *
//	 * @param name		name of the window
//	 *
//	 * @return the desired window
//	 */
//	const vgd::Shp< Window > getWindow( const std::string name ) const;
//
//	// @todo getAllWindows() returns a list of window name
//
//	//@}
//
//
//	/**
//	 * @name Implements IUnderlay interface
//	 */
//	//@{
//
//	void setUnderlay( vgd::Shp< vgd::node::LayerPlan > underlay );
//
//	vgd::Shp< vgd::node::LayerPlan > getUnderlay();
//
//	//@}
//
//
//
//	/*VGEGLBASE_API */void apply( vgeGLBase::engine::Engine * /*engine*/, vge::visitor::TraverseElementVector * /*traverseElements*/ );
//
//
//
//	/**
//	 * @name Accessors to technique used to paint a window
//	 * 
//	 * Design Pattern \c Strategy
//	 */
//	//@{
//
//	/**
//	 * @brief Returns the current technique used to paint a window
//	 * 
//	 * @return the current technique used to paint a window
//	 */
//	vgd::Shp< vgeGLBase::technique::Technique > getPaintTechnique() const;
//	
//	/**
//	 * @brief Sets the current technique used to paint a window
//	 * 
//	 * @param technique		the current technique used to paint a window
//	 */
//	void setPaintTechnique( vgd::Shp< vgeGLBase::technique::Technique > technique );
//
//	//@}
//
//
//
//private:
//	/**
//	 * @brief Draws the border for the given window
//	 */
//	void drawBorder( vgeGLBase::engine::Engine * engine, const vgd::Shp< MultiMain::Window > window, const vgm::Rectangle2i newViewport2i );
//
//	typedef std::map< std::string, vgd::Shp< Window > > WindowContainer;	///< Definition of window container
//	WindowContainer							m_windows;		///< The container of windows
//
//	vge::visitor::NodeCollectorExtended<>	m_collectorExt;	///< Collector of nodes. Useful because scene graph topology could be different for each window.
//	
//	vgd::Shp< vgd::node::LayerPlan >		m_underlay;		///< Underlay from SceneManager
//
//	vgd::Shp< vgeGLBase::technique::Technique >	m_paintTechnique; ///< technique used by MultiMain to paint a window
//};
//
//
//
//} // namespace technique
//
//} // namespace vgeGLBase
//
//#endif //#ifndef _VGEGLBASE_TECHNIQUE_MULTIMAIN_HPP
//