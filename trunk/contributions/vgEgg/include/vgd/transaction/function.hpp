#ifndef _VGD_TRANSACTION_FUNCTION_HPP
#define _VGD_TRANSACTION_FUNCTION_HPP

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <vgd/Shp.hpp>
#include <vgd/transaction/Transaction.hpp>

namespace
{
template < typename T >
struct NotARef
{
	typedef T Type;
};

template < typename T >
struct NotARef< T& >
{
	typedef T Type;
};


}


namespace vgd
{
namespace transaction
{

/**
 * @brief Transaction for a function with no args.
 */
struct function : public Transaction
{
	/**
	 * @brief Static factory.
	 */
	static vgd::Shp< function > create( boost::function< void ( void ) > f )
	{
		return vgd::makeShp( new function( f ) );
	}

	/**
	 * @brief The apply function calling the function.
	 */
	void apply()
	{
		m_f();
	}

protected:
	/**
	 * @brief Creator.
	 */
	function( boost::function< void ( void ) > f )
	:	m_f( f )
	{}

	/**
	 * @brief The function.
	 */
	boost::function< void ( void ) > m_f;
};
	



/**
 * @name Non-member Function
 */
//@{
/**
 * @brief Template factory for functions with no args.
 */
template < typename T0 >
vgd::Shp< function > createFunctionTransaction( boost::function< T0() > f )
{
	return function::create( f );
}

/**
 * @brief Template factory for functions with no args.
 */
template < typename T0 >
vgd::Shp< function > createFunctionTransaction( T0 f () )
{
	return function::create( f );
}

/**
 * @brief Template factory for functions with one single arg.
 */
template < typename T0, typename T1, typename P1 >
vgd::Shp< function > createFunctionTransaction( boost::function< T0 ( T1 ) > f, P1 p1 )
{
	return function::create( boost::bind( f, p1 ) );
}

/**
 * @brief Template factory for functions with one single arg.
 */
template < typename T0, typename T1, typename P1 >
vgd::Shp< function > createFunctionTransaction( T0 f ( T1 ), P1 p1 )
{
	return function::create( boost::bind( f, p1 ) );
}

/**
 * @brief Template factory for functions with two args.
 */
template < typename T0, typename T1, typename T2, typename P1, typename P2 >
vgd::Shp< function > createFunctionTransaction( boost::function< T0 ( T1, T2 ) > f, P1 p1, P2 p2 )
{
	return function::create( boost::bind( f, p1, p2 ) );
}

/**
 * @brief Template factory for functions with two args.
 */
template < typename T0, typename T1, typename T2, typename P1, typename P2 >
vgd::Shp< function > createFunctionTransaction( T0 f ( T1, T2 ), P1 p1, P2 p2 )
{
	return function::create( boost::bind( f, p1, p2 ) );
}

/**
 * @brief Template factory for functions with three args.
 */
template < typename T0, typename T1, typename T2, typename T3, typename P1, typename P2, typename P3 >
vgd::Shp<function > createFunctionTransaction( boost::function< T0 ( T1, T2, T3 ) > f, P1 p1, P2 p2, P3 p3 )
{
	return function::create( boost::bind( f, p1, p2, p3 ) );
}

/**
 * @brief Template factory for functions with three args.
 */
template < typename T0, typename T1, typename T2, typename T3, typename P1, typename P2, typename P3 >
vgd::Shp<function > createFunctionTransaction( T0 f ( T1, T2, T3 ), P1 p1, P2 p2, P3 p3 )
{
	return function::create( boost::bind( f, p1, p2, p3 ) );
}
//@}

/**
 * @name Member functions
 */
//@{
/**
 * @brief Template factory for member functions with no args.
 */
template < typename B, typename C, typename T0 >
vgd::Shp< function > createFunctionTransaction( B object, T0 ( C::*f )() )
{
	return function::create( boost::bind( f, object ) );
}

/**
 * @brief Template factory for member functions with one single arg.
 */
template < typename B, typename C, typename T0, typename T1, typename P1 > vgd::Shp< function >
createFunctionTransaction( B object, T0 ( C::*f )( T1 ), P1 p1 )
{
	return function::create( boost::bind( f, object, p1 ) );
}

/**
 * @brief Template factory for member functions with two args.
 */
template < typename B, typename C, typename T0, typename T1, typename T2, typename P1, typename P2 > vgd::Shp< function >
createFunctionTransaction( B object, T0 ( C::*f )( T1, T2 ), P1 p1, P2 p2 )
{
	return function::create( boost::bind( f, object, p1, p2 ) );
}

/**
 * @brief Template factory for member functions with two args.
 */
template < typename B, typename C, typename T0, typename T1, typename T2, typename T3, typename P1, typename P2, typename P3 >
vgd::Shp< function > createFunctionTransaction( B object, T0 ( C::*f )( T1, T2, T3 ), P1 p1, P2 p2, P3 p3 )
{
	return function::create( boost::bind(f ,object, p1, p2, p3 ) );
}

//@}






} // namespace vgd
} // namespace transaction


#endif // _VGD_TRANSACTION_FUNCTION_HPP
