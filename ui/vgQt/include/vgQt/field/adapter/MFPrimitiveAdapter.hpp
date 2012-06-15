// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGQT_FIELD_ADAPTER_MFPRIMITIVEADAPTER_HPP_
#define _VGQT_FIELD_ADAPTER_MFPRIMITIVEADAPTER_HPP_

#include <vgd/node/Primitive.hpp>

#include "vgQt/field/adapter/MFAdapter.hpp"

#include <QTreeWidget>

namespace vgQt
{

namespace field
{

namespace adapter
{

/**
 * @brief	Multi-field editor adapter for vgd::node::Primitive values.
 */
struct MFPrimitiveAdapter : public MFAdapter< vgd::node::Primitive >
{

private:

};

} // namespace adapter

} // namespace field

} // namespace vgQt

#endif // _VGQT_FIELD_ADAPTER_MFPRIMITIVEADAPTER_HPP_
