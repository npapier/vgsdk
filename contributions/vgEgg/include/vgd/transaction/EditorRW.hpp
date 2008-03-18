#ifndef _VGD_TRANSACTION_EDITORRW_HPP
#define _VGD_TRANSACTION_EDITORRW_HPP

#include <vgd/Shp.hpp>

namespace vgd {
namespace transaction {


/**template <typename V> struct TBind<field::TMultiField<V> > {
	typedef TMultiField<V> TRANSACTION;
	};*/

	template <typename T> struct TBind;

/**
 * @brief Editor RW for a given object.
 */

template <typename OBJECT> struct EditorRW {
	/**
	 * @brief Creator.
	 */
	EditorRW(typename OBJECT* field);
	/**
	 * @brief Creator.
	 */
	EditorRW(typename vgd::Shp<OBJECT> field);
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
	const vgd::Shp<typename TBind<OBJECT>::TRANSACTION> operator->(){return m_pField;}
	/**
	 * @brief return the field;
	 */
	const vgd::Shp<typename TBind<OBJECT>::TRANSACTION> getTransaction(){return m_pField;}
	//@}
protected:
	/**
	 * @brief Shared pointer to the transation field.
	 */
	vgd::Shp<typename TBind<OBJECT>::TRANSACTION> m_pField;
};


template <typename OBJECT> EditorRW<OBJECT>::EditorRW(typename OBJECT* field){
	m_pField.reset(new TBind<OBJECT>::TRANSACTION(field));
}

template <typename OBJECT> EditorRW<OBJECT>::EditorRW(typename vgd::Shp<OBJECT> field){
	m_pField.reset(new TBind<OBJECT>::TRANSACTION(field));
}

template <typename OBJECT> EditorRW<OBJECT>::EditorRW(const EditorRW& editor){
	m_pField=editor.m_pField;
	const_cast<EditorRW&>(editor).m_pField.reset();
}

template <typename OBJECT> EditorRW<OBJECT>& EditorRW<OBJECT>::operator=(const EditorRW& editor){
	m_pField=editor.m_pField;
	const_cast<EditorRW&>(editor).m_pField.reset();
	return (*this);
}

} } // namespace vgd transaction


#endif // _VGD_TRANSACTION_EDITORRW_HPP
