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
 * Code taken from the Orca-Robotics Project
 * http://orca-robotics.sf.net/
 */

#ifndef DYNAMICLOAD_DYNAMICLOAD_H
#define DYNAMICLOAD_DYNAMICLOAD_H

#include <tinysg/Exception.h>
#include <tinysg/dll.h>
#ifndef WIN32
#include <dlfcn.h>
#else
#define NOMINMAX
#include <windows.h>
#endif
#include <string>
#include <sstream>

namespace TinySG
{

//!
//! Uses a function in the lib to load an instance of 'LoadedClass'.
//!
//! Assumes the library has a 'maker' function with the signature:
//!   extern "C" {
//!     LoadedClass *makerFunc();
//!   }
//!
//! The type of this function should be typedef'd to MakerFunc somewhere, as in:
//!   typedef LoadedClass *MakerFunc();
//!
//!
template<class LoadedClass, typename MakerFunc>
LoadedClass *dynamicallyLoadClass( DynamicallyLoadedLibrary &lib, const char *makerFuncName )
{
#ifndef WIN32
    void *makerFuncHandle = dlsym(lib.handle(),makerFuncName);
    if ( makerFuncHandle == NULL )
    {
        std::stringstream ss;
        ss << "Failed to find symbol '"<<makerFuncName<<"' in library '"<<lib.name()<<"': "<<dlerror();
        SML_EXCEPT(Exception::ERR_DYNAMIC_LOAD_FAILED, ss.str());
    }
#else
    void *makerFuncHandle = (void*)GetProcAddress((HMODULE)lib.handle(),makerFuncName);
    if ( makerFuncHandle == NULL )
    {
        std::stringstream ss;
        ss << "Failed to find symbol '"<<makerFuncName<<"' in library '"<<lib.name()<<"': "<<GetLastError();
        SML_EXCEPT(Exception::ERR_DYNAMIC_LOAD_FAILED, ss.str());
    }
#endif

    MakerFunc *makerFunc = (MakerFunc*)makerFuncHandle;

    LoadedClass *loadedClass = makerFunc();
    return loadedClass;
};

} // namespace

#endif
