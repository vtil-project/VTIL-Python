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
// | instruction_desc.hpp    | https://github.com/vtil-project/VTIL-Core      |
// |                         | https://github.com/pybind/pybind11             |
// |--------------------------------------------------------------------------|
//
#pragma once

#include <vtil/vtil>
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

using namespace vtil;
namespace py = pybind11;


namespace vtil::python
{
	class instruction_desc_py : public py::class_<instruction_desc>
	{
		public:
		instruction_desc_py( const handle& scope, const char* name )
			: class_( scope, name )
		{
			py::enum_<operand_type>( scope, "operand_type" )
				.value( "invalid", operand_type::invalid )

				.value( "read_imm", operand_type::read_imm )
				.value( "read_reg", operand_type::read_reg )
				.value( "read_any", operand_type::read_any ).value( "read", operand_type::read_any )

				.value( "write", operand_type::write )
				.value( "readwrite", operand_type::readwrite )
				;

			( *this )
				// Properties
				//
				.def_readonly( "name", &instruction_desc::name )
				.def_readonly( "operand_types", &instruction_desc::operand_types )
				.def_readonly( "is_volatile", &instruction_desc::is_volatile )
				.def_readonly( "symbolic_operator", &instruction_desc::symbolic_operator )
				.def_readonly( "branch_operands_rip", &instruction_desc::branch_operands_rip )
				.def_readonly( "branch_operands_vip", &instruction_desc::branch_operands_vip )
				.def_readonly( "memory_operand_index", &instruction_desc::memory_operand_index )
				.def_readonly( "memory_write", &instruction_desc::memory_write )
				.def_readonly( "is_volatile", &instruction_desc::is_volatile )

				// Functions
				//
				.def( "operand_count", &instruction_desc::operand_count )

				.def( "is_branching_virt", &instruction_desc::is_branching_virt )
				.def( "is_branching_real", &instruction_desc::is_branching_real )
				.def( "is_branching", &instruction_desc::is_branching )

				.def( "reads_memory", &instruction_desc::reads_memory )
				.def( "writes_memory", &instruction_desc::writes_memory )
				.def( "accesses_memory", &instruction_desc::accesses_memory )

				.def( "reduce", py::overload_cast< >( &instruction_desc::reduce ) )

				.def( "__repr__", &instruction_desc::to_string )
				.def( "__str__", &instruction_desc::to_string )
				.def( py::self == py::self )
				.def( py::self != py::self )
				.def( py::self < py::self )

				// End
				//
				;
		}
	};
}
