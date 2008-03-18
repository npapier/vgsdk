#ifndef _VGD_TRANSACTION_SINGLEFIELD_HPP
#define _VGD_TRANSACTION_SINGLEFIELD_HPP

#include <vgd/transaction/AbstractField.hpp>

namespace vgd {
	namespace field {
		template <typename T> struct TSingleField;
	}
}


namespace vgd {
namespace transaction {


template <typename T> struct TSingleField;
/**
 * @brief Template class for the correspondancy between
 * transactional and non-transactional field.
 *
 * Specialization for TMultiField.
 */
template <typename V> struct TBind<field::TSingleField<V> > {
	typedef TSingleField<V> TRANSACTION;
};

template <typename V>	TSingleField<V> bind_with(field::TSingleField<V>*);


/**
 * @brief template class for all single field transaction.
 */

template <typename T>
struct TSingleField : public AbstractField {
	/**
	 * @brief The corresponding non transactional field.
	 */
	typedef field::TSingleField<T> Field;
	/**
	 * @brief Creator.
	 */
	TSingleField(Field* field);
	/**
	 * @name value accessors.
	 */
	//@{
	/**
	 * @brief set the valiue.
	 */
	void setValue(const T& item);
	/**
	 * @brief get the value.
	 */
	const T& getValue() const;
	/**
	 * @brief get the value.
	 */
	T& getValue();
	//@}
		/**
	 * @brief apply.
	 */
	void apply();
protected:
	/**
	 * @brief The value.
	 */
    T m_item;
};

template <typename T> TSingleField<T>::TSingleField(Field*  field) : AbstractField(field) {
	field::EditorRO<Field> e(field);
	m_item = e->getValue();
}

template <typename T> void TSingleField<T>::setValue(const T& item){
	m_item = item;
}

template <typename T> const T& TSingleField<T>::getValue() const{
	return m_item;
}

template <typename T> T& TSingleField<T>::getValue(){
	return m_item;
}

template <typename T> void TSingleField<T>::apply(){
	field::EditorRW<Field> e(static_cast<Field*>(m_field));	
	e->setValue(m_item);
}

} } // namespace vgd transaction

#endif // _VGD_TRANSACTION_SINGLEFIELD_HPP
