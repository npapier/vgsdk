#ifndef _VGD_TRANSACTION_ABSTRACTFIELD_HPP
#define _VGD_TRANSACTION_ABSTRACTFIELD_HPP

#include <vgd/vgd.hpp>
#include <vgd/Shp.hpp>
#include <vgd/transaction/Transaction.hpp>

namespace vgd {
	namespace field {
		struct AbstractField;
	}
}

namespace vgd {
namespace transaction {

	/**
	 * @brief Template class for the correspondancy between
	 * transactional and non-transactional field.
	 *
	 * Chaque type de Field F doit définir une classe template TBind<
	 * F< T > > qui fait le lien entre le champs non transactionel et
	 * le champ transactionel.
	 */
	template <typename T> struct TBind;

/**
 * @brief Abstract class for all transaction fields.
 *
 * @todo If the pointed field is destroyed we have a problem. To be
 * fixed, fields would need to be able notify their destruction (through
 * observers or shared pointers.)
 */
	struct VGD_API AbstractField : Transaction {
	/**
	 * @brief The creator.
	 */
	AbstractField(field::AbstractField* field);
	/**
	 * @brief The destructor.
	 */
	~AbstractField();
	/**
	 * @brief Template factory.
	 *
	 * Use template class TBind to bind a transactional field class to
	 * its corresponding non transactional one.
	 */
	template <typename F> static vgd::Shp<typename TBind<F>::TRANSACTION> createTransactionField(typename F* field){
		return vgd::makeShp(new TBind<F>::TRANSACTION(field));
	}
protected:
	/**
	 * @brief Pointer to the field.
	 */
	field::AbstractField* m_field;
};

} } // namespace vgd transaction

#endif // _VGD_TRANSACTION_ABSTRACTFIELD_HPP
