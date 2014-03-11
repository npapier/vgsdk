#ifndef _VGD_TRANSACTION_FIELD_TMULTIFIELD_HPP
#define _VGD_TRANSACTION_FIELD_TMULTIFIELD_HPP

#include <vgd/field/TMultiField.hpp>
#include <vgd/transaction/Transaction.hpp>

#include <vector>

namespace vgd {
	namespace field {
		template <typename T> struct TMultiField;
	}
}


namespace vgd
{
namespace transaction
{
namespace field
{

/**
 * @brief template class for all multi field transaction.
 */
template <typename T> struct TMultiField : public vgd::field::TMultiField<T>, public Transaction
{
	/**
	 * @brief The corresponding non transactional field.
	 */

	typedef vgd::field::TMultiField<T> Field;

	/**
	 * @name Constructor
	 */
	//@{
	/**
	 * @brief Creator.
	 */

	TMultiField(const Field* field);
	//@}

	/**
	 * @brief apply.
	 */

	void apply();

protected:
	/**
	 * @brief The field.
	 */
	Field* m_field;
};


template <typename T> TMultiField<T>::TMultiField(const Field*  field) : vgd::field::TMultiField<T>(field->name()) {
	m_field = const_cast<Field*>(field);
	startEditingRW();
	vgd::field::EditorRO<Field > e(field);
	reserve(field->size());
	insert(0,e->begin(),e->end());
}

template <typename T> void TMultiField<T>::apply(){
	vgd::field::EditorRW<Field > e(m_field);
	swap(*m_field);
	finishEditing();
}


} } } // namespace vgd transaction field

#endif // _VGD_TRANSACTION_FIELD_TMULTIFIELD_HPP
