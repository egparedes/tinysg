/*************************************************************************
 * TinySG, Copyright (C) 2007, 2008  J.D. Yamokoski
 * All rights reserved.
 * Email: yamokosk at gmail dot com
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2.1 of the License,
 * or (at your option) any later version. The text of the GNU Lesser General
 * Public License is included with this library in the file LICENSE.TXT.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the file LICENSE.TXT for
 * more details.
 *
 *************************************************************************/

#ifndef HPP_FLOAT_CONSTANTS
#define HPP_FLOAT_CONSTANTS

namespace constants
{
// A collection of basic mathematical constants, accurate to 40 decimal digits.
// C++ floating-point type is float.

// Written by .\makeConstants.cpp Thu May  5 18:40:10 2005
// Version 2.0, using Victor Shoup's NTL version 5.4 (www.shoup.net/ntl)

// Copyright Paul A. Bristow 1998-2005.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// From www.hetp.u-net.com/public/math_constants.zip
// For documentation and sources see constants.htm
// Queries and corrections to pbristow@hetp.u-net.com

// The objective is to achieve the full accuracy possible
// with IEC559/IEEE745 floating-point hardware and C++ language.
// This has no extra cost to the user, but reduces irritating effects
// caused by the inevitable limitations of floating point calculations.
// At least these manifest as spurious least significant digits,
// at worst algorithms that fail because comparisons fail.
// 40 decimal digits ensures no loss of accuracy even for 128-bit floating point.

static const float zero = 0.F; // zero
static const float one = 1.F; // unity
static const float two = 2.F; // two
static const float three = 3.F; // three
static const float four = 4.F; // four
static const float five = 5.F; // five
static const float six = 6.F; // six
static const float seven = 7.F; // seven
static const float ten = 10.F; // ten
static const float third = 0.3333333333333333333333333333333333333333F; // 1/3
static const float twoThirds = 0.6666666666666666666666666666666666666667F; // 2/3
static const float threeQuarters = 0.75F; // 3/4
static const float sqrtTwo = 1.41421356237309504880168872420969807857F; // sqrt(2)
static const float sqrtThree = 1.732050807568877293527446341505872366943F; // sqrt(3)
static const float sqrtFive = 2.236067977499789696409173668731276235441F; // sqrt(5)
static const float sqrtTen = 3.16227766016837933199889354443271853372F; // sqrt(10)
static const float sqrt32 = 5.656854249492380195206754896838792314279F; // sqrt(10)
static const float oneDivSqrt2 = 0.7071067811865475244008443621048490392848F; // 1/sqrt(2)
static const float halfSqrt2 = 0.7071067811865475244008443621048490392848F; // sqrt(2)/2
static const float twoPowThreeDivTwo = 2.828427124746190097603377448419396157139F; // 2^(3/2)
static const float twoPowMinusThreeDivTwo = 0.3535533905932737622004221810524245196424F; // 2^(-3/2)
static const float cubeRootTwo = 1.25992104989487316476721060727822835057F; // 2^1/3
static const float oneDivCubeRootTwo = 0.7937005259840997373758528196361541301957F; // 1/(2^1/3)
static const float cubeRootThree = 1.442249570307408382321638310780109588392F; // 3^1/3
static const float cubeRootFour = 1.587401051968199474751705639272308260391F; // 4^1/3
static const float oneDivCubeRootFour = 0.6299605249474365823836053036391141752851F; // 1/(4^1/3)
static const float cubeRootTen = 2.154434690031883721759293566519350495259F; // 10^1/3
static const float fourthRootTwo = 1.189207115002721066717499970560475915293F; // 2^1/4
static const float logTwo = 0.6931471805599453094172321214581765680755F; // ln(2)
static const float logLogTwo = -0.3665129205816643270124391582326694694543F; // ln(ln(2))
static const float logTwoDivTwo = 0.3465735902799726547086160607290882840378F; // ln(2) / 2
static const float logThree = 1.098612288668109691395245236922525704647F; // ln(3)
static const float logFour = 1.386294361119890618834464242916353136151F; // ln(4)
static const float logFive = 1.609437912434100374600759333226187639526F; // ln(5)
static const float logSix = 1.791759469228055000812477358380702272723F; // ln(6)
static const float logSeven = 1.945910149055313305105352743443179729637F; // ln(7)
static const float logTen = 2.302585092994045684017991454684364207601F; // ln(10)
static const float oneDivLogTen = 0.4342944819032518276511289189166050822944F; // 1 / ln(10)
static const float oneDivLogTwo = 1.442695040888963407359924681001892137427F; // 1 / ln(2)
static const float log10Two = 0.3010299956639811952137388947244930267682F; // log10(2)
static const float pi = 3.141592653589793238462643383279502884197F; // Archimedes constant pi
static const float halfPi = 1.570796326794896619231321691639751442099F; // pi / 2
static const float quarterPi = 0.7853981633974483096156608458198757210493F; // pi / 4
static const float thirdPi = 1.047197551196597746154214461093167628066F; // pi / 3
static const float sixthPi = 0.5235987755982988730771072305465838140329F; // pi / 6
static const float twoPi = 6.283185307179586476925286766559005768394F; // 2 * pi
static const float twoThirdsPi = 2.094395102393195492308428922186335256131F; // 2/3 * pi
static const float threePi = 9.424777960769379715387930149838508652592F; // 3 * pi
static const float threeQuartersPi = 2.356194490192344928846982537459627163148F; // pi * 3/4
static const float fourThirdsPi = 4.188790204786390984616857844372670512263F; // pi * 4/3
static const float oneDivPi = 0.3183098861837906715377675267450287240689F; // 1 / pi
static const float twoDivPi = 0.6366197723675813430755350534900574481378F; // 2 / pi
static const float oneDivTwoPi = 0.1591549430918953357688837633725143620345F; // 1 / (2 * pi)
static const float sqrtPi = 1.772453850905516027298167483341145182798F; // sqrt(pi)
static const float sqrtQuarterPi = 0.8862269254527580136490837416705725913988F; // sqrt(pi / 4)
static const float sqrtHalfPi = 1.253314137315500251207882642405522626503F; // sqrt(pi / 2)
static const float sqrtTwoPi = 2.506628274631000502415765284811045253007F; // sqrt(2 * pi)
static const float sqrtTwoDivPi = 0.7978845608028653558798921198687637369517F; // sqrt(2 / pi)
static const float oneDivSqrtPi = 0.5641895835477562869480794515607725858441F; // 1 / sqrt(pi)
static const float oneDivSqrtTwoPi = 0.3989422804014326779399460599343818684759F; // 1 / sqrt(2 * pi)
static const float sqrtOneDivPi = 0.5641895835477562869480794515607725858441F; // sqrt(1 / pi)
static const float piSqr = 9.869604401089358618834490999876151135314F; // pi^2
static const float oneDivPiSqr = 0.1013211836423377714438794632097276389044F; // 1 / pi^2
static const float piCubed = 31.00627668029982017547631506710139520223F; // pi^3
static const float cubeRootPi = 1.464591887561523263020142527263790391739F; // pi^1/3
static const float oneDivCubeRootPi = 0.6827840632552956814670208331581645981084F; // 1 / pi^1/3
static const float logSqrtPi = 0.5723649429247000870717136756765293558236F; // ln(sqrt(pi))
static const float logSqrtTwoPi = 0.9189385332046727417803297364056176398614F; // ln(sqrt(2 * pi))
static const float logSqrtHalfPi = 0.2257913526447274323630976149474410717859F; // ln(sqrt(pi / 2))
static const float logPi = 1.144729885849400174143427351353058711647F; // ln(pi)
static const float logTwoPi = 1.837877066409345483560659472811235279723F; // ln(2 * pi)
static const float piPowPi = 36.46215960720791177099082602269212366637F; // pi ^ pi
static const float e = 2.718281828459045235360287471352662497757F; // e
static const float twoE = 5.436563656918090470720574942705324995514F; // 2 * e
static const float halfE = 1.359140914229522617680143735676331248879F; // e / 2
static const float piPowE = 22.45915771836104547342715220454373502759F; // pi ^ e
static const float oneDivE = 0.3678794411714423215955237701614608674458F; // 1/e
static const float ePowE = 15.15426224147926418976043027262991190553F; // e^e
static const float sqrtE = 1.648721270700128146848650787814163571654F; // sqrt(e)
static const float oneDivSqrtE = 0.6065306597126334236037995349911804534419F; // 1/sqrt(e)
static const float eSqr = 7.38905609893065022723042746057500781318F; // e^2
static const float oneDivESqr = 0.1353352832366126918939994949724844034076F; // 1 / e^2
static const float eCubed = 20.08553692318766774092852965458171789699F; // e^3
static const float log10e = 0.4342944819032518276511289189166050822944F; // log10(e)
static const float oneDivLog10 = 2.302585092994045684017991454684364207601F; // 1/ln(10)
static const float logE = 1.F; // log(e)
static const float ePowPi = 23.14069263277926900572908636794854738027F; // e^pi
static const float ePowMinusPi = 0.04321391826377224977441773717172801127573F; // e^-pi
static const float ePowHalfPi = 4.81047738096535165547303566670383312639F; // e^(pi/2)
static const float ePowQuarterPi = 2.193280050738015456559769659278738223462F; // e^(pi/4)
static const float ePowMinusHalfPi = 0.2078795763507619085469556198349787700339F; // e^(-pi/2)
static const float ePowMinusE = 0.06598803584531253707679018759684642493858F; // e^-e
static const float degree = 0.01745329251994329576923690768488612713443F; // radians = pi / 180.
static const float radian = 57.29577951308232087679815481410517033241F; // degrees = 180 / pi
static const float sinOne = 0.8414709848078965048756572286947630345821F; // sin(1)
static const float cosOne = 0.5403023058681397650104827334871515631676F; // cos(1)
static const float sinhOne = 1.175201193643801378385660427738912403584F; // sinh(1)
static const float coshOne = 1.543080634815243712409937870688736438751F; // cosh(1)
static const float phi = 1.61803398874989484820458683436563811772F; // (1 + sqrt(5)) /2;
static const float logPhi = 0.4812118250596034474977589134243684231352F; // ln(phi)
static const float oneDivLnPhi = 2.078086921235027537601322606117795767742F; // 1/ln(phi)
static const float gamma = 0.5772156649015328606065120900824024310422F; // Euler's gamma constant
static const float oneDivGamma = 1.732454714600633473583025315860829681156F; // 1/gamma
static const float gammaSqr = 0.3331779238077186743183761363552442266594F; // gamma^2
static const float gammaCubed = 0.1923155168211845896631923744196359071217F; // gamma^3
static const float ePowGamma = 1.78107241799019798523650410310717954917F; // e^gamma
static const float ePowMinusGamma = 0.5614594835668851698241432147908807867657F; // e^-gamma
static const float logGamma = -0.5495393129816448223376617688029077883307F; // ln(gamma)
static const float gammaSixth = 5.566316001780235204250096895207726111399F; // gamma(1/6)
static const float logGammaSixth = 1.716733435078240460527846309587930757279F; // ln(gamma(1/6))
static const float gammaQuarter = 3.625609908221908311930685155867672002995F; // gamma(1/4)
static const float logGammaQuarter = 1.288022524698077457370610440219717295925F; // ln(gamma(1/4))
static const float gammaThird = 2.678938534707747633655692940974677644129F; // gamma(1/3)
static const float logGammaThird = 0.9854206469277670691871740369779613917356F; // ln(gamma(1/3))
static const float gammaHalf = 1.772453850905516027298167483341145182798F; // gamma(1/2) == sqrt(pi)
static const float logGammaHalf = 0.5723649429247000870717136756765293558236F; // ln(gamma(1/2))
static const float gammaTwoThirds = 1.354117939426400416945288028154513785519F; // gamma(2/3)
static const float logGammaTwoThirds = 0.3031502751475235686758628173720110356635F; // ln(gamma(2/3))
static const float gammaThreeQuarters = 1.225416702465177645129098303362890526851F; // gamma(3/4)
static const float logGammaThreeQuarters = 0.2032809514312953714814329718624296997597F; // ln(gamma(3/4))
static const float gammaFiveSixths = 1.128787029908125961260901090258842013327F; // gamma(5/6)
static const float logGammaFiveSixths = 0.1211436313311050230328131632233045224434F; // ln(gamma(5/6))
static const float gammaOne = 1.F; // by definition.
static const float gammaTwo = 1.F; // by definition.
static const float gammaThree = 2.F; // factorial(2) == 2!
static const float logGammaThree = 0.6931471805599453094172321214581765680755F; // ln(gamma(3))
static const float gammaFour = 6.F; // factorial(3) == 3!
static const float logGammaFour = 1.791759469228055000812477358380702272723F; // ln(gamma(4))
static const float gammaFive = 24.F; // factorial(4) == 4!
static const float logGammaFive = 3.178053830347945619646941601297055408874F; // ln(gamma(5))
static const float gammaSix = 120.F; // factorial(5)
static const float logGammaSix = 4.7874917427820459942477009345232430484F; // ln(gamma(6))
static const float logGammaMin = 0.3795537188395179971250638364384648368782F; // log(gamma(1.46))  minimum value is 0.88...
static const float gammaMin = 1.461632144968362341262659542325721328468F; // gamma(1.46) has the minimum value of 0.88...
static const float gammaMinValue = 0.885603194410888700278815900582588733208F; // gamma(1.46) minimum value.
static const float cf10 = 1.030640834100712935881776094116936840925F; // Continued fraction (base 10)
static const float zetaTwo = 1.644934066848226436472415166646025189219F; // Zeta(2) or Pi^(2/6) = sum(1/n**2, n=1..infinity
static const float zetaThree = 1.202056903159594285399738161511449990765F; // zeta(3)

}

#endif
// End of float_constants.hpp
