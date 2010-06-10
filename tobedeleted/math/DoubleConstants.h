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

#ifndef HPP_DOUBLE_CONSTANTS
#define HPP_DOUBLE_CONSTANTS

namespace constants
{
// A collection of basic mathematical constants, accurate to 40 decimal digits.
// C++ floating-point type is double.

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
// At least these manifest as spurious least significant digits;
// at worst as algorithms that fail because comparisons differ.
// 40 decimal digits ensures no loss of accuracy even for 128-bit floating point.

static const double zero = 0.; // zero
static const double one = 1.; // unity
static const double two = 2.; // two
static const double three = 3.; // three
static const double four = 4.; // four
static const double five = 5.; // five
static const double six = 6.; // six
static const double seven = 7.; // seven
static const double ten = 10.; // ten
static const double third = 0.3333333333333333333333333333333333333333; // 1/3
static const double twoThirds = 0.6666666666666666666666666666666666666667; // 2/3
static const double threeQuarters = 0.75; // 3/4
static const double sqrtTwo = 1.41421356237309504880168872420969807857; // sqrt(2)
static const double sqrtThree = 1.732050807568877293527446341505872366943; // sqrt(3)
static const double sqrtFive = 2.236067977499789696409173668731276235441; // sqrt(5)
static const double sqrtTen = 3.16227766016837933199889354443271853372; // sqrt(10)
static const double sqrt32 = 5.656854249492380195206754896838792314279; // sqrt(10)
static const double oneDivSqrt2 = 0.7071067811865475244008443621048490392848; // 1/sqrt(2)
static const double halfSqrt2 = 0.7071067811865475244008443621048490392848; // sqrt(2)/2
static const double twoPowThreeDivTwo = 2.828427124746190097603377448419396157139; // 2^(3/2)
static const double twoPowMinusThreeDivTwo = 0.3535533905932737622004221810524245196424; // 2^(-3/2)
static const double cubeRootTwo = 1.25992104989487316476721060727822835057; // 2^1/3
static const double oneDivCubeRootTwo = 0.7937005259840997373758528196361541301957; // 1/(2^1/3)
static const double cubeRootThree = 1.442249570307408382321638310780109588392; // 3^1/3
static const double cubeRootFour = 1.587401051968199474751705639272308260391; // 4^1/3
static const double oneDivCubeRootFour = 0.6299605249474365823836053036391141752851; // 1/(4^1/3)
static const double cubeRootTen = 2.154434690031883721759293566519350495259; // 10^1/3
static const double fourthRootTwo = 1.189207115002721066717499970560475915293; // 2^1/4
static const double logTwo = 0.6931471805599453094172321214581765680755; // ln(2)
static const double logLogTwo = -0.3665129205816643270124391582326694694543; // ln(ln(2))
static const double logTwoDivTwo = 0.3465735902799726547086160607290882840378; // ln(2) / 2
static const double logThree = 1.098612288668109691395245236922525704647; // ln(3)
static const double logFour = 1.386294361119890618834464242916353136151; // ln(4)
static const double logFive = 1.609437912434100374600759333226187639526; // ln(5)
static const double logSix = 1.791759469228055000812477358380702272723; // ln(6)
static const double logSeven = 1.945910149055313305105352743443179729637; // ln(7)
static const double logTen = 2.302585092994045684017991454684364207601; // ln(10)
static const double oneDivLogTen = 0.4342944819032518276511289189166050822944; // 1 / ln(10)
static const double oneDivLogTwo = 1.442695040888963407359924681001892137427; // 1 / ln(2)
static const double log10Two = 0.3010299956639811952137388947244930267682; // log10(2)
static const double pi = 3.141592653589793238462643383279502884197; // Archimedes constant pi
static const double halfPi = 1.570796326794896619231321691639751442099; // pi / 2
static const double quarterPi = 0.7853981633974483096156608458198757210493; // pi / 4
static const double thirdPi = 1.047197551196597746154214461093167628066; // pi / 3
static const double sixthPi = 0.5235987755982988730771072305465838140329; // pi / 6
static const double twoPi = 6.283185307179586476925286766559005768394; // 2 * pi
static const double twoThirdsPi = 2.094395102393195492308428922186335256131; // 2/3 * pi
static const double threePi = 9.424777960769379715387930149838508652592; // 3 * pi
static const double threeQuartersPi = 2.356194490192344928846982537459627163148; // pi * 3/4
static const double fourThirdsPi = 4.188790204786390984616857844372670512263; // pi * 4/3
static const double oneDivPi = 0.3183098861837906715377675267450287240689; // 1 / pi
static const double twoDivPi = 0.6366197723675813430755350534900574481378; // 2 / pi
static const double oneDivTwoPi = 0.1591549430918953357688837633725143620345; // 1 / (2 * pi)
static const double sqrtPi = 1.772453850905516027298167483341145182798; // sqrt(pi)
static const double sqrtQuarterPi = 0.8862269254527580136490837416705725913988; // sqrt(pi / 4)
static const double sqrtHalfPi = 1.253314137315500251207882642405522626503; // sqrt(pi / 2)
static const double sqrtTwoPi = 2.506628274631000502415765284811045253007; // sqrt(2 * pi)
static const double sqrtTwoDivPi = 0.7978845608028653558798921198687637369517; // sqrt(2 / pi)
static const double oneDivSqrtPi = 0.5641895835477562869480794515607725858441; // 1 / sqrt(pi)
static const double oneDivSqrtTwoPi = 0.3989422804014326779399460599343818684759; // 1 / sqrt(2 * pi)
static const double sqrtOneDivPi = 0.5641895835477562869480794515607725858441; // sqrt(1 / pi)
static const double piSqr = 9.869604401089358618834490999876151135314; // pi^2
static const double oneDivPiSqr = 0.1013211836423377714438794632097276389044; // 1 / pi^2
static const double piCubed = 31.00627668029982017547631506710139520223; // pi^3
static const double cubeRootPi = 1.464591887561523263020142527263790391739; // pi^1/3
static const double oneDivCubeRootPi = 0.6827840632552956814670208331581645981084; // 1 / pi^1/3
static const double logSqrtPi = 0.5723649429247000870717136756765293558236; // ln(sqrt(pi))
static const double logSqrtTwoPi = 0.9189385332046727417803297364056176398614; // ln(sqrt(2 * pi))
static const double logSqrtHalfPi = 0.2257913526447274323630976149474410717859; // ln(sqrt(pi / 2))
static const double logPi = 1.144729885849400174143427351353058711647; // ln(pi)
static const double logTwoPi = 1.837877066409345483560659472811235279723; // ln(2 * pi)
static const double piPowPi = 36.46215960720791177099082602269212366637; // pi ^ pi
static const double e = 2.718281828459045235360287471352662497757; // e
static const double twoE = 5.436563656918090470720574942705324995514; // 2 * e
static const double halfE = 1.359140914229522617680143735676331248879; // e / 2
static const double piPowE = 22.45915771836104547342715220454373502759; // pi ^ e
static const double oneDivE = 0.3678794411714423215955237701614608674458; // 1/e
static const double ePowE = 15.15426224147926418976043027262991190553; // e^e
static const double sqrtE = 1.648721270700128146848650787814163571654; // sqrt(e)
static const double oneDivSqrtE = 0.6065306597126334236037995349911804534419; // 1/sqrt(e)
static const double eSqr = 7.38905609893065022723042746057500781318; // e^2
static const double oneDivESqr = 0.1353352832366126918939994949724844034076; // 1 / e^2
static const double eCubed = 20.08553692318766774092852965458171789699; // e^3
static const double log10e = 0.4342944819032518276511289189166050822944; // log10(e)
static const double oneDivLog10 = 2.302585092994045684017991454684364207601; // 1/ln(10)
static const double logE = 1.; // log(e)
static const double ePowPi = 23.14069263277926900572908636794854738027; // e^pi
static const double ePowMinusPi = 0.04321391826377224977441773717172801127573; // e^-pi
static const double ePowHalfPi = 4.81047738096535165547303566670383312639; // e^(pi/2)
static const double ePowQuarterPi = 2.193280050738015456559769659278738223462; // e^(pi/4)
static const double ePowMinusHalfPi = 0.2078795763507619085469556198349787700339; // e^(-pi/2)
static const double ePowMinusE = 0.06598803584531253707679018759684642493858; // e^-e
static const double degree = 0.01745329251994329576923690768488612713443; // radians = pi / 180.
static const double radian = 57.29577951308232087679815481410517033241; // degrees = 180 / pi
static const double sinOne = 0.8414709848078965048756572286947630345821; // sin(1)
static const double cosOne = 0.5403023058681397650104827334871515631676; // cos(1)
static const double sinhOne = 1.175201193643801378385660427738912403584; // sinh(1)
static const double coshOne = 1.543080634815243712409937870688736438751; // cosh(1)
static const double phi = 1.61803398874989484820458683436563811772; // (1 + sqrt(5)) /2;
static const double logPhi = 0.4812118250596034474977589134243684231352; // ln(phi)
static const double oneDivLnPhi = 2.078086921235027537601322606117795767742; // 1/ln(phi)
static const double gamma = 0.5772156649015328606065120900824024310422; // Euler's gamma constant
static const double oneDivGamma = 1.732454714600633473583025315860829681156; // 1/gamma
static const double gammaSqr = 0.3331779238077186743183761363552442266594; // gamma^2
static const double gammaCubed = 0.1923155168211845896631923744196359071217; // gamma^3
static const double ePowGamma = 1.78107241799019798523650410310717954917; // e^gamma
static const double ePowMinusGamma = 0.5614594835668851698241432147908807867657; // e^-gamma
static const double logGamma = -0.5495393129816448223376617688029077883307; // ln(gamma)
static const double gammaSixth = 5.566316001780235204250096895207726111399; // gamma(1/6)
static const double logGammaSixth = 1.716733435078240460527846309587930757279; // ln(gamma(1/6))
static const double gammaQuarter = 3.625609908221908311930685155867672002995; // gamma(1/4)
static const double logGammaQuarter = 1.288022524698077457370610440219717295925; // ln(gamma(1/4))
static const double gammaThird = 2.678938534707747633655692940974677644129; // gamma(1/3)
static const double logGammaThird = 0.9854206469277670691871740369779613917356; // ln(gamma(1/3))
static const double gammaHalf = 1.772453850905516027298167483341145182798; // gamma(1/2) == sqrt(pi)
static const double logGammaHalf = 0.5723649429247000870717136756765293558236; // ln(gamma(1/2))
static const double gammaTwoThirds = 1.354117939426400416945288028154513785519; // gamma(2/3)
static const double logGammaTwoThirds = 0.3031502751475235686758628173720110356635; // ln(gamma(2/3))
static const double gammaThreeQuarters = 1.225416702465177645129098303362890526851; // gamma(3/4)
static const double logGammaThreeQuarters = 0.2032809514312953714814329718624296997597; // ln(gamma(3/4))
static const double gammaFiveSixths = 1.128787029908125961260901090258842013327; // gamma(5/6)
static const double logGammaFiveSixths = 0.1211436313311050230328131632233045224434; // ln(gamma(5/6))
static const double gammaOne = 1.; // by definition.
static const double gammaTwo = 1.; // by definition.
static const double gammaThree = 2.; // factorial(2) == 2!
static const double logGammaThree = 0.6931471805599453094172321214581765680755; // ln(gamma(3))
static const double gammaFour = 6.; // factorial(3) == 3!
static const double logGammaFour = 1.791759469228055000812477358380702272723; // ln(gamma(4))
static const double gammaFive = 24.; // factorial(4) == 4!
static const double logGammaFive = 3.178053830347945619646941601297055408874; // ln(gamma(5))
static const double gammaSix = 120.; // factorial(5)
static const double logGammaSix = 4.7874917427820459942477009345232430484; // ln(gamma(6))
static const double logGammaMin = 0.3795537188395179971250638364384648368782; // log(gamma(1.46))  minimum value is 0.88...
static const double gammaMin = 1.461632144968362341262659542325721328468; // gamma(1.46) has the minimum value of 0.88...
static const double gammaMinValue = 0.885603194410888700278815900582588733208; // gamma(1.46) minimum value.
static const double cf10 = 1.030640834100712935881776094116936840925; // Continued fraction (base 10)
static const double zetaTwo = 1.644934066848226436472415166646025189219; // Zeta(2) or Pi^(2/6) = sum(1/n**2, n=1..infinity
static const double zetaThree = 1.202056903159594285399738161511449990765; // zeta(3)

}
#endif
// End of double_constants.hpp
