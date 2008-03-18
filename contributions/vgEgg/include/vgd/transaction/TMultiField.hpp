#ifndef _VGD_TRANSACTION_TMULTIFIELD_HPP
#define _VGD_TRANSACTION_TMULTIFIELD_HPP

#include <vgd/transaction/AbstractField.hpp>

#include <vector>

namespace vgd {
	namespace field {
		template <typename T> struct TMultiField;
	}
}


namespace vgd {
namespace transaction {

template <typename T> struct TMultiField;

/**
 * @brief Template class for the correspondancy between
 * transactional and non-transactional field.
 *
 * Specialization for TMultiField.
 */
template <typename V> struct TBind<field::TMultiField<V> > {
	typedef TMultiField<V> TRANSACTION;
};

/**
 * @brief template class for all multi field transaction.
 */
template <typename T>
struct TMultiField : public AbstractField {
	/**
	 * @brief The corresponding non transactional field.
	 */
	typedef field::TMultiField<T> Field;
	/**
	 * @brief Creator.
	 */
	TMultiField(Field* field);
	/**
	 * @name value accessors.
	 */
	//@{
	/**
	 * @brief get a pointer to the array.
	 */
	T* get();
	//@}
	/**
	 * @brief apply.
	 */
	void apply();
protected:
	/**
	 * @brief The vector.
	 */
	std::vector< T > m_vectorMF;
};


template <typename T> TMultiField<T>::TMultiField(Field*  field) : AbstractField(field) {
	field::EditorRO<field::TMultiField<T> > e(field);
	m_vectorMF.reserve(field->size());
	m_vectorMF.assign(e->begin(),e->end());
}

template <typename T> T* TMultiField<T>::get(){
	if(m_vectorMF.size()==0)
		return 0;
	else
		return &m_vectorMF[0];
}

template <typename T> void TMultiField<T>::apply(){
	field::EditorRW<field::TMultiField<T> > e(static_cast<field::TMultiField<T>*>(m_field));
	e->swap(m_vectorMF);
}


} } // namespace vgd transaction

#endif // _VGD_TRANSACTION_TMULTIFIELD_HPP
