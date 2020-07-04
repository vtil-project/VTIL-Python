// BSD 3-Clause License
//
// Copyright (c) 2020, Daniel (@L33T), VTIL Project
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its
//    contributors may be used to endorse or promote products derived from
//    this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// Furthermore, the following pieces of software have additional copyrights
// licenses, and/or restrictions:
//
// |--------------------------------------------------------------------------|
// | File name               | Link for further information                   |
// |-------------------------|------------------------------------------------|
// | variable.hpp            | https://github.com/vtil-project/VTIL-Core      |
// |                         | https://github.com/pybind/pybind11             |
// |--------------------------------------------------------------------------|
//
#pragma once

#include <vtil/vtil>
#include <pybind11/pybind11.h>

using namespace vtil::symbolic;
namespace py = pybind11;


namespace vtil::python
{
	class variable_py : public py::class_<variable>
	{
		public:
		variable_py( const handle& scope, const char* name )
			: class_( scope, name )
		{
			// Related
			//
			py::class_<access_details>( scope, "access_details" )
				// Properties
				//
				.def_readwrite( "bit_offset", &access_details::bit_offset )
				.def_readwrite( "bit_count", &access_details::bit_count )

				.def_readwrite( "read", &access_details::read )
				.def_readwrite( "write", &access_details::write )
				.def_readwrite( "unknown", &access_details::unknown )

				.def( "is_unknown", &access_details::is_unknown )

				// End
				//
				;

			py::class_<variable::memory_t>( scope, "variable::memory_t" )
				// Constructor
				//
				.def( py::init<>() )
				.def( py::init<pointer, bitcnt_t>() )

				// Properties
				//
				.def_readwrite( "base", &variable::memory_t::base )
				.def_readwrite( "bit_count", &variable::memory_t::bit_count )

				// Functions
				//
				.def( "decay", &variable::memory_t::decay )
				.def( "reduce", py::overload_cast< >( &variable::memory_t::reduce ) )

				/* End */
				;
			
			( *this )
				// Constructor
				//
				.def( py::init<>() )
				.def( py::init<const il_const_iterator&, variable::descriptor_t>() )
				.def( py::init<const il_const_iterator&, const variable::memory_t&>() )
				.def( py::init<const il_const_iterator&, const variable::register_t&>() )
				.def( py::init<variable::descriptor_t>() )
				.def( py::init<const variable::memory_t&>() )
				.def( py::init<const variable::register_t&>() )

				// Properties
				//
				.def_readwrite( "at", &variable::at )
				.def_readwrite( "descriptor", &variable::descriptor )
				.def_readwrite( "is_branch_depedant", &variable::is_branch_dependant )

				// Functions
				//
				.def( "bind", &variable::bind )

				.def( "is_valid", &variable::is_valid )
				.def( "is_free_form", &variable::is_free_form )
				.def( "is_memory", &variable::is_memory )
				.def( "is_register", &variable::is_register )

				.def( "mem", py::overload_cast< >( &variable::mem ) )
				.def( "reg", py::overload_cast< >( &variable::reg ) )

				.def( "bit_count", &variable::bit_count )
				.def( "to_expression", &variable::to_expression )
				.def( "to_string", &variable::to_string )
				.def( "reduce", py::overload_cast< >( &variable::reduce ) )

				.def( "pack_all", &variable::pack_all )

				.def( "read_by", &variable::read_by )
				.def( "written_by", &variable::written_by )
				.def( "accessed_by", &variable::accessed_by )

				.def( "__repr__", &variable::to_string )
				.def( "__str__", &variable::to_string )

				// End
				//
				;
		}
	};
}
