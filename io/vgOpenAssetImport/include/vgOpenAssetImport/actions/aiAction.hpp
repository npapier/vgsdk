// VGSDK - Copyright (C) 2013, 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGOPENASSETIMPORT_ACTIONS_AIACTION_HPP
#define _VGOPENASSETIMPORT_ACTIONS_AIACTION_HPP

#include "vgOpenAssetImport/vgOpenAssetImport.hpp"

#include <vgAlg/actions/IAction.hpp>
#include <vgAlg/actions/input/INodeInput.hpp>

struct aiScene;


namespace vgOpenAssetImport
{
namespace actions
{

/**
 * @brief	Base class for action based on OpenAssetImport scenes.
 *
 * This class manages the OpenAssetImport scene creation and destruction, and delegates the
 * real action job to subclasses through the aiExecute() method. Thus subclasses have to implement
 * this method, but never override execute() directly.
 */
struct VGOPENASSETIMPORT_API aiAction : public vgAlg::actions::IAction, vgAlg::actions::input::INodeInput
{
	/**
	 * @name	Overrides
	 */
	//@{
	virtual void execute();
	//@}

protected:

	/**
	 * @brief	Perform the action of the given OpenAssetScene
	 *
	 * @param	scene	a pointer to the OpenAssetImport scene to act on
	 *
	 * @return	true to refresh canvas, false otherwise
	 */
	virtual const bool aiExecute( const aiScene * scene ) = 0;
};


} // namespace actions

} // namespace vgOpenAssetImport

#endif //#ifndef _VGOPENASSETIMPORT_ACTIONS_AIPOSTPROCESSING_HPP
