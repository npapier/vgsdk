// VGSDK - Copyright (C) 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGOPENASSETIMPORT_ACTIONS_AIPOSTPROCESSING_HPP
#define _VGOPENASSETIMPORT_ACTIONS_AIPOSTPROCESSING_HPP

#include "vgOpenAssetImport/vgOpenAssetImport.hpp"

#include <vgAlg/actions/IAction.hpp>
#include <vgAlg/actions/input/INodeInput.hpp>

struct aiScene;


namespace vgOpenAssetImport
{

namespace actions
{

/**
 * @brief	Base class to apply post processing using assimp on a node.
 */
struct VGOPENASSETIMPORT_API aiPostProcessing : public vgAlg::actions::IAction, vgAlg::actions::input::INodeInput
{
	aiPostProcessing();

	virtual void execute();
protected:
	/**
	 * @bried Called by execute()
	 *
	 * @return true to refresh canvas, false otherwise
	 */
	virtual const bool apply( const aiScene * scene )=0;
};


struct VGOPENASSETIMPORT_API aiExportCollada : public aiPostProcessing
{
protected:
	virtual const bool apply( const aiScene * scene );
};


struct VGOPENASSETIMPORT_API aiExportObj : public aiPostProcessing
{
protected:
	virtual const bool apply( const aiScene * scene );
};


struct VGOPENASSETIMPORT_API aiExportStl : public aiPostProcessing
{
protected:
	virtual const bool apply( const aiScene * scene );
};


struct VGOPENASSETIMPORT_API aiExportPly : public aiPostProcessing
{
protected:
	virtual const bool apply( const aiScene * scene );
};


} // namespace actions

} // namespace vgOpenAssetImport

#endif //#ifndef _VGOPENASSETIMPORT_ACTIONS_AIPOSTPROCESSING_HPP
