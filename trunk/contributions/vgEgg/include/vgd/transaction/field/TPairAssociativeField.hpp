#ifndef _VGD_TRANSACTION_FIELD_TPAIRASSICIATIVEFIELD_HPP
#define _VGD_TRANSACTION_FIELD_TPAIRASSICIATIVEFIELD_HPP


#include <vgd/field/TPairAssociativeField.hpp>
#include <vgd/transaction/Transaction.hpp>

namespace vgd
{
namespace field
{
template < typename KeyType, typename DataType > struct TPairAssociativeField;
}
}


namespace vgd
{
namespace transaction
{


template < typename KeyType, typename DataType > struct TPairAssociativeField : public vgd:field::TPairAssociativeField<KeyType, DataType> , public Transaction
{

	/**
	 * @brief The corresponding non transactional field.
	 */

	typedef vgd::field::TPairAssociativeField<KeyType, DataType> Field;


	/**
	 * @brief Creator.
	 */

	TPairAssociativeField(Field* field);


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


template < typename KeyType, typename DataType > TPairAssociativeField::TPairAssociativeField(Field* field) : vgd:field::TPairAssociativeField<KeyType, DataType>(field->name())
{
	startEditingRW();
	m_field = field;
	vgd::field::EditorRO<Field> e(field);
	m_map.clear();
	m_map.insert(e->begin(),e->end());
}


template < typename KeyType, typename DataType > TPairAssociativeField::apply()
{
	vgd::field::EditorRW<Field > e(m_field);
	e->swap(m_map);
	finishEditing();
}

}
}


#endif // _VGD_TRANSACTION_TPAIRASSICIATIVEFIELD_HPP
