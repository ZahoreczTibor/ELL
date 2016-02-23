////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  [projectName]
//  File:     StringFormat.h (utilities)
//  Authors:  Ofer Dekel
//
//  [copyright]
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

// types
#include "types.h"

// stl
#include <iostream>

namespace utilities
{
    ///
    ///
    template<typename ArgType, typename ... ArgTypes>
    void StringFormat(std::ostream& os, const char* cstr, ArgType arg, ArgTypes ...args);

    ///
    ///
    template<typename ... ArgTypes>
    void StringFormat(std::ostream& os, const char* cstr, ArgTypes ...args);

    template<typename ... ArgTypes>
    std::string StringFormat(const char* cstr, ArgTypes ...args);
}

#include "../tcc/StringFormat.tcc"
