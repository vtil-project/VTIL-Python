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
// | operands.hpp            | https://github.com/vtil-project/VTIL-Core      |
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
	class operand_py : public py::class_<operand>
	{
		public:
		operand_py( const handle& scope, const char* name )
			: class_( scope, name )
		{
			py::class_<operand::immediate_t>( scope, "operand::immediate_t" )
				// Constructor
				//
				.def( py::init<>() )
				.def( py::init<uint64_t, bitcnt_t>() )

				// Properties
				//
				.def_readwrite( "i64", &operand::immediate_t::i64 )
				.def_readwrite( "u64", &operand::immediate_t::u64 )

				.def_readwrite( "bit_count", &operand::immediate_t::bit_count )

				// Functions
				//
				.def( "reduce", py::overload_cast< >( &operand::immediate_t::reduce ) )
				;

			( *this )
				// Properties
				//
				.def_readwrite( "descriptor", &operand::descriptor )

				// Functions
				//
				.def( "imm", py::overload_cast< >( &operand::imm ) )
				.def( "reg", py::overload_cast< >( &operand::reg ) )

				.def( "size", &operand::size )
				.def( "bit_count", &operand::bit_count )

				.def( "is_register", &operand::is_register )
				.def( "is_immediate", &operand::is_immediate )
				.def( "is_valid", &operand::is_valid )

				.def( "reduce", py::overload_cast< >( &operand::reduce ) )

				.def( "__str__", &operand::to_string )
				.def( "__repr__", &operand::to_string )

				// End
				//
				;
		}
	};
}

namespace pybind11::detail
{
	template<> struct type_caster<operand> : public type_caster_base<operand>
	{
		using base = type_caster_base<operand>;

		template<typename T>
		bool explicit_cast( handle src )
		{
			return py::isinstance<T>( src ) && ( this->value = new operand( py::cast<T>( src ) ) );
		}

		public:
		bool load( handle src, bool convert )
		{
			if ( py::isinstance<py::int_>( src ) )
			{
				auto value = py::cast<uint64_t>( src );
				this->value = new operand( value, sizeof( value ) * 8 );
				return true;
			}

			return explicit_cast< arm64_reg >( src ) || explicit_cast< x86_reg >( src ) || explicit_cast< register_desc >( src );
		}

		static handle cast( operand* src, return_value_policy policy, handle parent )
		{
			return base::cast( src, policy, parent );
		}

		static handle cast( const operand* src, return_value_policy policy, handle parent )
		{
			return base::cast( src, policy, parent );
		}

		static handle cast( operand& src, return_value_policy policy, handle parent )
		{
			return base::cast( src, policy, parent );
		}

		static handle cast( const operand& src, return_value_policy policy, handle parent )
		{
			return base::cast( src, policy, parent );
		}
	};
}
