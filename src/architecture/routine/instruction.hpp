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
// | instruction.hpp         | https://github.com/vtil-project/VTIL-Core      |
// |                         | https://github.com/pybind/pybind11             |
// |--------------------------------------------------------------------------|
//
#pragma once

#include <vtil/vtil>
#include <pybind11/pybind11.h>

using namespace vtil;
namespace py = pybind11;


namespace vtil::python
{
	class instruction_py : public py::class_<instruction>
	{
		public:
		instruction_py( const handle& scope, const char* name )
			: class_( scope, name )
		{
			( *this )
				// Properties
				//
				.def_readwrite( "base", &instruction::base )
				.def_readwrite( "operands", &instruction::operands )
				.def_readwrite( "vip", &instruction::vip )

				.def_readwrite( "sp_offset", &instruction::sp_offset )
				.def_readwrite( "sp_index", &instruction::sp_index )
				.def_readwrite( "sp_reset", &instruction::sp_reset )

				.def_readwrite( "explicit_volatile", &instruction::explicit_volatile )

				// Functions
				//
				.def( "is_valid", &instruction::is_valid )
				.def( "make_volatile", &instruction::make_volatile )
				.def( "is_pseudo", &instruction::is_pseudo )
				.def( "is_volatile", &instruction::is_volatile )
				.def( "access_size", &instruction::access_size )
				.def( "memory_location", py::overload_cast< >( &instruction::memory_location ) )
				.def( "enum_operands", py::overload_cast< >( &instruction::enum_operands ) )
				.def( "reduce", py::overload_cast< >( &instruction::reduce ) )

				.def( "__repr__", [ ] ( const instruction& ins ) { return ins.to_string( false ); } )
				.def( "__str__", [ ] ( const instruction& ins ) { return ins.to_string( false ); } )

				// End
				//
				;
		}
	};
}
