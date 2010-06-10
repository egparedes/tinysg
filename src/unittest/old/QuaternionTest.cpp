#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>

#include <iostream>
#include <linalg/Quaternion.h>

// each test file may contain any number of test cases; each test case has to have unique name
BOOST_AUTO_TEST_CASE( simple_multiply )
{
	BOOST_TEST_MESSAGE( "Testing a simple quaternion product..." );
    sml::math::Quaternion q1( sml::math::Quaternions::identity );
	sml::math::Quaternion q2( sml::math::Quaternions::identity );

    // reports 'error in "test2": check i == 2 failed [0 != 2]'
    BOOST_CHECK_EQUAL( q1, q1*q2 );
}

BOOST_AUTO_TEST_CASE( complex_multiply )
{
	BOOST_TEST_MESSAGE( "Testing a more complex quaternion product..." );

	sml::math::Real angle1 = 60.*sml::math::pi/180.;
	ColumnVector axis1(3); axis1 << 3. << 2. << 0.;

	sml::math::Real angle2 = 115*sml::math::pi/180.;
	ColumnVector axis2(3); axis2 << 0. << -1. << 2.;

    sml::math::Quaternion q1 = sml::math::quaternionFromAngleAxis(angle1, axis1);
	BOOST_MESSAGE("q1 = " << q1);
	sml::math::Quaternion q2 = sml::math::quaternionFromAngleAxis(angle2, axis2);
	BOOST_MESSAGE("q2 = " << q2);

	// Do multiplication
	sml::math::Quaternion q3 = q2*q1;
	BOOST_MESSAGE("q2*q1 = " << q3);
	// Check new angle
	sml::math::Real theta = 2.*::std::acos(q3.real());

    BOOST_CHECK( std::fabs(theta * 180./sml::math::pi - 110.51) < 0.001 );
}

BOOST_AUTO_TEST_CASE( norm_check )
{
	BOOST_TEST_MESSAGE( "Testing versor properties of BOOST quaternions..." );

	sml::math::Real angle1 = 60.*sml::math::pi/180.;
	ColumnVector axis1(3); axis1 << 3. << 2. << 0.;

	sml::math::Real angle2 = 115*sml::math::pi/180.;
	ColumnVector axis2(3); axis2 << 0. << -1. << 2.;

    sml::math::Quaternion q1 = sml::math::quaternionFromAngleAxis(angle1, axis1);
	BOOST_MESSAGE("q1 = " << q1);
	sml::math::Quaternion q2 = sml::math::quaternionFromAngleAxis(angle2, axis2);
	BOOST_MESSAGE("q2 = " << q2);

	// Do multiplication
	sml::math::Quaternion q3 = q2*q1;
	for (int n=0; n<500000; ++n)
		q3 = q3*q2;

	for (int n=0; n<500000; ++n)
		q3 = q1*q3;

	// Check normalization of axis
	sml::math::Real thetaHalf = ::std::acos( q3.real() );
	sml::math::Real i = q3.R_component_2()/::std::sin(thetaHalf),
					j = q3.R_component_3()/::std::sin(thetaHalf),
					k = q3.R_component_4()/::std::sin(thetaHalf);
	sml::math::Real norm = ::std::sqrt( ::std::pow(i,2.) + ::std::pow(j,2.) + ::std::pow(k,2.));

	// After one million operations, error should be less than 1 in a billion
    BOOST_CHECK( ::std::fabs(1. - norm) < 1e-9 );
}
