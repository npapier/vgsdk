#include <vgd/transaction/TransactionContainer.hpp>


namespace vgd
{
namespace transaction
{

void TransactionContainer::apply()
{
	std::vector<vgd::Shp<Transaction> >::iterator it;
	for(it=m_tList.begin();it!=m_tList.end();++it)
	{
		(*it)->apply();
	}
	m_tList.clear();
}

void TransactionContainer::add_transaction(vgd::Shp<Transaction> transaction)
{
	m_tList.push_back(transaction);
}

void TransactionContainer::clear()
{
	m_tList.clear();
}


} } // namespace vgd transaction
