#ifndef _VGD_TRANSACTION_TRANSACTION_HPP
#define _VGD_TRANSACTION_TRANSACTION_HPP

#include <vgd/vgd.hpp>

namespace vgd {
/**
 * @brief Classes for transaction operations on fields.
 *
 * Modifications can be recorded and applied later, for instance in an
 * other thread.
 */
namespace transaction {

/**
 * @brief Class with an apply method.
 *
 * This is just an interface class that provides the apply method.
 */
struct VGD_API Transaction {
	/**
	 * @brief apply function.
	 */
	virtual void apply()=0;
};

} } // namespace vgd transaction


#endif // _VGD_TRANSACTION_TRANSACTION_HPP
