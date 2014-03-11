// VGSDK - Copyright (C) 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGGTK_CONTAINERDIALOG_HPP_
#define _VGGTK_CONTAINERDIALOG_HPP_

#include <gtkmm.h>

#include <vgd/Shp.hpp>
#include "vgGTK/vgGTK.hpp"

namespace vgGTK { struct Container; }



namespace vgGTK
{



/**
 * @brief A dialog box containing a Container
 */
struct VGGTK_API ContainerDialog : public Gtk::Dialog
{
	/**
	 * @brief Constructor
	 */
	ContainerDialog( Gtk::Window * toplevel, const std::string dialogName, vgd::Shp< vgGTK::Container > container = vgd::Shp<vgGTK::Container>() );

	/**
	 * @brief Virtual destructor
	 */
	virtual ~ContainerDialog() {}


	/**
	 * @brief	Retrieves the container.
	 */
	vgd::Shp< vgGTK::Container > get();

private:

	vgd::Shp< vgGTK::Container > m_container;		///< reference on container uses by the container dialog
};



} // namespace vgGTK



#endif // _VGGTK_CONTAINERDIALOG_HPP_
