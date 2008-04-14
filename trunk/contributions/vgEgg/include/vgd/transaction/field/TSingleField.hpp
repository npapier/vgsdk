#ifndef _VGD_TRANSACTION_FIELD_TSINGLEFIELD_HPP
#define _VGD_TRANSACTION_FIELD_TSINGLEFIELD_HPP

#include <vgd/field/TSingleField.hpp>
#include <vgd/transaction/Transaction.hpp>

namespace vgd {
	namespace field {
		template <typename T> struct TSingleField;
	}
}


namespace vgd
{
namespace transaction
{
namespace field
{

/**
 * @brief template class for all single field transaction.
 */

template <typename T> struct TSingleField : public vgd::field::TSingleField<T>, public Transaction
{
	/**
	 * @brief The corresponding non transactional field.
	 */

	typedef vgd::field::TSingleField<T> Field;


	/**
	 * @brief Creator.
	 */

	TSingleField(Field* field);

	/**
	 * @brief apply.
	 */

	void apply();

private:
	/**
	 * @brief The field.
	 */
	Field* m_field;
};


template <typename T> TSingleField<T>::TSingleField(Field*  field) : vgd::field::TSingleField<T>(field->name()) {
	startEditingRW();
	m_field = field;
	vgd::field::EditorRO<Field> e(field);
	m_item = e->getValue();
}

template <typename T> void TSingleField<T>::apply(){
	vgd::field::EditorRW<Field> e(m_field);	
	e->setValue(m_item);
	finishEditing();
}

} } } // namespace vgd transaction field

#endif // _VGD_TRANSACTION_FIELD_TSINGLEFIELD_HPP
