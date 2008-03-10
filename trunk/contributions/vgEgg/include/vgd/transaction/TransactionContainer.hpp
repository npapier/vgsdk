#ifndef _VGD_TRANSACTION_TRANSACTIONCONTAINER_HPP
#define _VGD_TRANSACTION_TRANSACTIONCONTAINER_HPP

#include <vector>
#include <vgd/vgd.hpp>
#include <vgd/Shp.hpp>
#include <vgd/transaction/Transaction.hpp>

namespace vgd {
namespace transaction {

/**
 * @brief Container for transaction that is also a transaction.
 */
struct VGD_API TransactionContainer : public Transaction {
	/**
	 * @brief the apply function.
	 */
	void apply();
	/**
	 * @brief Add a transaction.
	 */
	void push_back(vgd::Shp<Transaction> transaction);
protected:
	/**
	 * @brief The list of transactions.
	 */
	std::vector<vgd::Shp<Transaction> > m_tList;
};


} } // namespace vgd transaction
#endif // _VGD_TRANSACTION_TRANSACTIONCONTAINER_HPP
