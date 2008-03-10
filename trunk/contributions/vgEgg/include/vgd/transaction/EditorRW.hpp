#ifndef _VGD_TRANSACTION_EDITORRW_HPP
#define _VGD_TRANSACTION_EDITORRW_HPP

namespace vgd {
namespace transaction {

/**
 * @brief Editor RW for a given field.
 */

template <typename T> struct EditorRW {

	/**
	 * @brief Creator.
	 */
	EditorRW(typename T::Field* field);
	/**
	 * @brief copy constructor.
	 */
	EditorRW(const EditorRW& editor);
	/**
	 * @brief Operator =
	 */
	EditorRW& operator = (const EditorRW& editor);
	/**
	 * @name Accessors.
	 */
	//@{
	/**
	 * @brief operator->
	 */
	const vgd::Shp<T> operator->(){return m_pField;}
	/**
	 * @brief return the field;
	 */
	const vgd::Shp<T> getTransaction(){return m_pField;}
	//@}
protected:
	/**
	 * @brief Shared pointer to the transation field.
	 */
	vgd::Shp<T> m_pField;
};


template <typename T> EditorRW<T>::EditorRW(typename T::Field* field){
	m_pField = AbstractField::createTransactionField(field);
}


template <typename T> EditorRW<T>::EditorRW(const EditorRW& editor){
	m_pField=editor.m_pField;
	const_cast<EditorRW&>(editor).m_pField.reset();
}

template <typename T> EditorRW<T>& EditorRW<T>::operator=(const EditorRW& editor){
	m_pField=editor.m_pField;
	const_cast<EditorRW&>(editor).m_pField.reset();
	return (*this);
}

} } // namespace vgd transaction


#endif // _VGD_TRANSACTION_EDITORRW_HPP
