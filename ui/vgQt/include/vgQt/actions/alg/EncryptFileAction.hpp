// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGQT_ACTIONS_ALG_ENCRYPTFILEACTION_HPP_
#define _VGQT_ACTIONS_ALG_ENCRYPTFILEACTION_HPP_

#include <vgAlg/actions/IAction.hpp>

#include "vgQt/vgQt.hpp"

namespace vgQt
{

namespace actions
{

namespace alg
{


/**
 * @brief Encrypt a file.
 */
struct VGQT_API EncryptFileAction : public vgAlg::actions::IAction
{
    EncryptFileAction();

    ~EncryptFileAction();

    virtual void execute();

private:

};



} // namespace alg

} // namespace actions

} // namespace vgQt


#endif // _VGQT_ACTIONS_ALG_ENCRYPTFILEACTION_HPP_

