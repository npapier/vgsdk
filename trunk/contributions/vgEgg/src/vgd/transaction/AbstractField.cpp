#include <vgd/transaction/AbstractField.hpp>
#include <vgd/field/AbstractField.hpp>


namespace vgd {
namespace transaction {

AbstractField::AbstractField(field::AbstractField* field){
	m_field = field;
}

AbstractField::~AbstractField(){
}

} } // namespace vgd transaction
