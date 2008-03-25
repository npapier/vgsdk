#ifndef _VGD_TRANSACTION_FUNCTION_HPP
#define _VGD_TRANSACTION_FUNCTION_HPP

#include <boost/function.hpp>
#include <vgd/Shp.hpp>
#include <vgd/transaction/Transaction.hpp>

namespace vgd
{
namespace transaction
{

/**
 * @brief Transaction for a function with no args.
 */
template <typename T0> struct function0 : public Transaction {
	/**
	 * @brief Static factory.
	 */
	static vgd::Shp<function0> create(boost::function<T0 (void)> f){
		return vgd::makeShp(new function0(f));
	}
	/**
	 * @brief The apply function calling the function.
	 */
	void apply(){
		m_f();
	}
protected:
	/**
	 * @brief Creator.
	 */
	function0(boost::function<T0 (void)> f)
	:	m_f( f )
	{}
	/**
	 * @brief The function.
	 */
	boost::function<T0 (void)> m_f;
};
	
/**
 * @brief Transaction for a function with one single arg.
 */
template <typename T0, typename T1> struct function1 : public Transaction {
	/**
	 * @brief Static factory.
	 */
	static vgd::Shp<function1> create(boost::function<T0 (T1)> f, T1 t1){
		return vgd::makeShp(new function1(f,t1));
	}
	/**
	 * @brief The apply function calling the function.
	 */
	void apply(){
		m_f(m_t1);
	}
protected:
	/**
	 * @brief Creator.
	 */
	function1(boost::function<T0 (T1)> f, T1 t1)
	:	m_f( f ),
		m_t1( t1 )
	{}
	/**
	 * @brief The function.
	 */
	boost::function<T0 (T1)> m_f;
	/**
	 * @brief The first Argument.
	 */
	T1 m_t1;
};

/**
 * @brief Transaction for a function with two args.
 */
template <typename T0, typename T1, typename T2> struct function2 : public Transaction {
	/**
	 * @brief Static factory.
	 */
	static vgd::Shp<function2> create(boost::function<T0 (T1, T2)> f, T1 t1, T2 t2){
		return vgd::makeShp(new function2(f,t1,t2));
	}
	/**
	 * @brief The apply function calling the function.
	 */
	void apply(){
		m_f(m_t1,m_t2);
	}
protected:
	/**
	 * @brief Creator.
	 */
	function2(boost::function<T0 (T1,T2)> f, T1 t1, T2 t2)
	:	m_f( f ),
		m_t1( t1 ),
		m_t2( t2 )
	{}
	/**
	 * @brief The function.
	 */
	boost::function<T0 (T1,T2)> m_f;
	/**
	 * @brief The first Argument.
	 */
	T1 m_t1;
	/**
	 * @brief The second Argument.
	 */
	T2 m_t2;
};


/**
 * @brief Transaction for a function with three args.
 */
	template <typename T0, typename T1, typename T2, typename T3> struct function3 : public Transaction {
	/**
	 * @brief Static factory.
	 */
		static vgd::Shp<function3> create(boost::function<T0 (T1,T2,T3)> f, T1 t1, T2 t2, T3 t3){
			return vgd::makeShp(new function3(f,t1,t2,t3));
	}
	/**
	 * @brief The apply function calling the function.
	 */
	void apply(){
		m_f(m_t1,m_t2,m_t3);
	}
protected:
	/**
	 * @brief Creator.
	 */
	function3(boost::function<T0 (T1,T2,T3)> f, T1 t1, T2 t2, T3 t3)
	:	m_f( f ),
		m_t1( t1 ),
		m_t2( t2 ),
		m_t3( t3 )
	{}
	/**
	 * @brief The function.
	 */
	boost::function<T0 (T1,T2,T3)> m_f;
	/**
	 * @brief The first Argument.
	 */
	T1 m_t1;
	/**
	 * @brief The second Argument.
	 */
	T2 m_t2;
	/**
	 * @brief The third Argument.
	 */
	T3 m_t3;
};


	/**
	 * @brief Template factory for functions with no args.
	 */
	template <typename T0> vgd::Shp<function0<T0> > createFunctionTransaction(boost::function<T0 ()> f){
		return function0<T0>::create(f);
	}
	/**
	 * @brief Template factory for functions with one single arg.
	 */
	template <typename T0, typename T1, typename P1> vgd::Shp<function1<T0,T1> > createFunctionTransaction(boost::function<T0 (T1)> f, P1 p1 ){
		return function1<T0,T1>::create(f, (T1)p1);
	}
	/**
	 * @brief Template factory for functions with two args.
	 */
	template <typename T0, typename T1, typename T2, typename P1, typename P2> vgd::Shp<function2<T0,T1,T2> > createFunctionTransaction(boost::function<T0 (T1, T2)> f, P1 p1, P2 p2){
		return function2<T0,T1,T2>::create(f, (T1)p1, (T2)p2);
	}
	/**
	 * @brief Template factory for functions with three args.
	 */
	template <typename T0, typename T1, typename T2, typename T3, typename P1, typename P2, typename P3>  vgd::Shp<function3<T0,T1,T2,T3> > createFunctionTransaction(boost::function<T0 (T1,T2,T3)> f, P1 p1, P2 p2, P3 p3){
		return function3<T0,T1,T2,T3>::create(f, (T1)p1, (T2)p2, (T3)p3);
	}
	/**
	 * @brief Template factory for member functions with no args.
	 */
	template <typename C,typename T0> vgd::Shp< function1< T0, C*> > createFunctionTransaction(C* object, T0 (C::*f)()){
		return function1<T0, C*>::create(f,object);
	}
	/**
	 * @brief Template factory for member functions with one single arg.
	 */
	template <typename C,typename T0, typename T1, typename P1> vgd::Shp< function2< T0, C*, T1> > createFunctionTransaction(C* object, T0 (C::*f)(T1), P1 p1){
		return function2<T0,C*,T1>::create(f,object,p1);
	}
	/**
	 * @brief Template factory for member functions with two args.
	 */
	template <typename C,typename T0, typename T1, typename T2, typename P1, typename P2> vgd::Shp< function3< T0, C*, T1, T2> > createFunctionTransaction(C* object, T0 (C::*f)(T1, T2), P1 p1, P2 p2){
		return function3<T0,C*,T1,T2>::create(f,object,p1,p2);
	}



} // namespace vgd
} // namespace transaction


#endif // _VGD_TRANSACTION_FUNCTION_HPP
