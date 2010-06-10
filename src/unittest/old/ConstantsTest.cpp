#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#include <linalg/Math.h>

BOOST_AUTO_TEST_CASE( zero_check )
{
	sml::math::Real val1 = sml::math::zero;
	sml::math::Real val2 = sml::math::zero;

	BOOST_CHECK_EQUAL( val1, val2 );
}

BOOST_AUTO_TEST_CASE( addition_check )
{
	sml::math::Real val1 = sml::math::pi;
	sml::math::Real val2 = sml::math::halfPi;

	BOOST_CHECK_EQUAL( val1, sml::math::halfPi+sml::math::halfPi );
}

BOOST_AUTO_TEST_CASE( division_check )
{
	sml::math::Real val1 = sml::math::pi/sml::math::two;
	sml::math::Real val2 = sml::math::halfPi;

	BOOST_CHECK_EQUAL( val1, val2 );
}

BOOST_AUTO_TEST_CASE( multiply_check )
{
	sml::math::Real val1 = sml::math::pi;
	sml::math::Real val2 = sml::math::thirdPi * sml::math::three;

	BOOST_CHECK_EQUAL( val1, val2 );
}
