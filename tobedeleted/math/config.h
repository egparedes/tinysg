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
/*
 * config.h
 *
 *  Created on: Nov 14, 2008
 *      Author: yamokosk
 */

#ifndef CONFIG_H_
#define CONFIG_H_

// Define TinySG version
#define TINYSG_VERSION    ((TINYSG_VERSION_MAJOR << 16) | (TINYSG_VERSION_MINOR << 8) | TINYSG_VERSION_PATCH)

/*
 * Initial platform/compiler-related stuff to set.
 */
#define TINYSG_PLATFORM_WIN32 1
#define TINYSG_PLATFORM_LINUX 2
#define TINYSG_PLATFORM_APPLE 3

#define TINYSG_COMPILER_MSVC 1
#define TINYSG_COMPILER_GNUC 2
#define TINYSG_COMPILER_BORL 3

#define TINYSG_ENDIAN_LITTLE 1
#define TINYSG_ENDIAN_BIG 2

#define TINYSG_ARCHITECTURE_32 1
#define TINYSG_ARCHITECTURE_64 2

/*
 * Finds the compiler type and version.
 */
#if defined( _MSC_VER )
#   define TINYSG_COMPILER TINYSG_COMPILER_MSVC
#   define TINYSG_COMP_VER _MSC_VER

#elif defined( __GNUC__ )
#   define TINYSG_COMPILER TINYSG_COMPILER_GNUC
#   define TINYSG_COMP_VER (((__GNUC__)*100) + \
        (__GNUC_MINOR__*10) + \
        __GNUC_PATCHLEVEL__)

#elif defined( __BORLANDC__ )
#   define TINYSG_COMPILER TINYSG_COMPILER_BORL
#   define TINYSG_COMP_VER __BCPLUSPLUS__

#else
#   pragma error "No known compiler. Abort! Abort!"
#endif


/*
 * See if we can use __forceinline or if we need to use __inline instead
 */
#if TINYSG_COMPILER == TINYSG_COMPILER_MSVC
#   if TINYSG_COMP_VER >= 1200
#       define FORCEINLINE __forceinline
#   endif
#elif defined(__MINGW32__)
#   if !defined(FORCEINLINE)
#       define FORCEINLINE __inline
#   endif
#else
#   define FORCEINLINE __inline
#endif


/*
 * Finds the current platform
 */
#if defined( __WIN32__ ) || defined( _WIN32 )
#   define TINYSG_PLATFORM TINYSG_PLATFORM_WIN32
#elif defined( __APPLE_CC__)
#   define TINYSG_PLATFORM TINYSG_PLATFORM_APPLE
#else
#   define TINYSG_PLATFORM TINYSG_PLATFORM_LINUX
#endif


/*
 * Find the arch type
 */
#if defined(__x86_64__) || defined(_M_X64) || defined(__powerpc64__) || defined(__alpha__) || defined(__ia64__) || defined(__s390__) || defined(__s390x__)
#   define TINYSG_ARCH_TYPE TINYSG_ARCHITECTURE_64
#else
#   define TINYSG_ARCH_TYPE TINYSG_ARCHITECTURE_32
#endif


// For generating compiler warnings - should work on any compiler
// As a side note, if you start your message with 'Warning: ', the MSVC
// IDE actually does catch a warning :)
#define TINYSG_QUOTE_INPLACE(x) # x
#define TINYSG_QUOTE(x) TINYSG_QUOTE_INPLACE(x)
#define TINYSG_WARN( x )  message( __FILE__ "(" QUOTE( __LINE__ ) ") : " x "\n" )


//----------------------------------------------------------------------------
// Windows Settings
#if TINYSG_PLATFORM == TINYSG_PLATFORM_WIN32

// If we're not including this from a client build, specify that the stuff
// should get exported. Otherwise, import it.
#	if defined( TINYSG_STATIC_LIB )
		// Linux compilers don't have symbol import/export directives.
#   	define SOEXPORT
#   else
#   	if defined( TINYSG_NONCLIENT_BUILD )
#       	define SOEXPORT __declspec( dllexport )
#   	else
#           if defined( __MINGW32__ )
#               define SOEXPORT
#           else
#       	    define SOEXPORT __declspec( dllimport )
#           endif
#   	endif
#	endif
// Win32 compilers use _DEBUG for specifying debug builds.
#   ifdef _DEBUG
#       define TINYSG_DEBUG_MODE 1
#   else
#       define TINYSG_DEBUG_MODE 0
#   endif

// Disable unicode support on MingW at the moment, poorly supported in stdlibc++
// STLPORT fixes this though so allow if found
// MinGW C++ Toolkit supports unicode and sets the define __MINGW32_TOOLKIT_UNICODE__ in _mingw.h
#if defined( __MINGW32__ ) && !defined(_STLPORT_VERSION)
#   include<_mingw.h>
#   if defined(__MINGW32_TOOLBOX_UNICODE__)
#	    define TINYSG_UNICODE_SUPPORT 1
#   else
#       define TINYSG_UNICODE_SUPPORT 0
#   endif
#else
#	define TINYSG_UNICODE_SUPPORT 1
#endif

#endif
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
// Linux/Apple Settings
#if TINYSG_PLATFORM == TINYSG_PLATFORM_LINUX || TINYSG_PLATFORM == TINYSG_PLATFORM_APPLE

// Enable GCC symbol visibility
#   if defined( TINYSG_GCC_VISIBILITY )
#       define SOEXPORT  __attribute__ ((visibility("default")))
#   else
#       define SOEXPORT
#   endif

#endif

#endif
