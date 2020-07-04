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
// | basic_block.hpp         | https://github.com/vtil-project/VTIL-Core      |
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
	class basic_block_py : public py::class_<basic_block>
	{
		public:
		basic_block_py( const handle& scope, const char* name )
			: class_( scope, name )
		{
			// Related
			// 
			py::class_<il_iterator>( scope, "il_iterator" )
				.def( "get", [ ] ( const il_iterator& it ) { return *it; } );
			py::class_<il_const_iterator>( scope, "il_const_iterator" )
				.def( "get", [ ] ( const il_const_iterator& it ) { return *it; } );

			( *this )
				// Constructor
				//
				.def( py::init( py::overload_cast< vip_t, vtil::architecture_identifier >( &basic_block::begin ) ), py::arg("entry_vip"), py::arg("arch_id") = architecture_amd64 )

				// Properties
				//
				.def_readwrite( "owner", &basic_block::owner )
				.def_readwrite( "entry_vip", &basic_block::entry_vip )
				.def_readwrite( "prev", &basic_block::prev )
				.def_readwrite( "sp_offset", &basic_block::sp_offset )
				.def_readwrite( "sp_index", &basic_block::sp_index )
				.def_readwrite( "next", &basic_block::next )
				.def_readwrite( "stream", &basic_block::stream )
				.def_readwrite( "last_temporary_index", &basic_block::last_temporary_index )
				.def_readwrite( "label_stack", &basic_block::label_stack )
				.def_readwrite( "context", &basic_block::context )

				// Functions
				//
				.def( "label_begin", &basic_block::label_begin )
				.def( "label_end", &basic_block::label_end )

				.def( "size", &basic_block::size )
				.def( "end", py::overload_cast< >( &basic_block::end ) )
				.def( "begin", py::overload_cast< >( &basic_block::begin ) )
				.def( "acquire", &basic_block::acquire )
				.def( "erase", &basic_block::erase )
				.def( "insert", [ ] ( basic_block& bbl, basic_block::const_iterator& it, instruction& ins ) { bbl.insert( it, std::move( ins ) ); } )
				.def( "push_back", [ ] ( basic_block& bbl, instruction& ins ) { bbl.push_back( ins ); } )
				.def( "is_complete", &basic_block::is_complete )

				.def( "fork", &basic_block::fork )
				.def( "tmp", [ ] ( basic_block& bbl, bitcnt_t size ) { return bbl.tmp( size ); } )
				.def( "tmp", &tmp_helper )
				.def( "prepare_operand", [ ] ( basic_block& bbl, operand* op ) { return op; /* We use type_caster to explicitly cast to operand */ } )

				.def( "shift_sp", &basic_block::shift_sp )
				.def( "vemits", &basic_block::vemits )
				.def( "pushf", &basic_block::pushf )
				.def( "popf", &basic_block::popf )

				.def( "push", [ ] ( basic_block& bbl, const operand& op ) { return bbl.push( op ); } )
				.def( "pop", [ ] ( basic_block& bbl, const operand& op ) { return bbl.pop( op ); } )

				.def( "hash", &basic_block::hash )

				// End
				//
				;

			( *this )
				// Functions
				// 
				.def( "mov", &basic_block::mov<const operand&, const operand&> )
				.def( "movsx", &basic_block::movsx<const operand&, const operand&> )
				.def( "store", &basic_block::str<const operand&, const operand&, const operand&> )
				.def( "ldd", &basic_block::ldd<const operand&, const operand&, const operand&> )

				.def( "neg", &basic_block::neg<const operand&> )
				.def( "add", &basic_block::add<const operand&, const operand&> )
				.def( "sub", &basic_block::sub<const operand&, const operand&> )
				.def( "div", &basic_block::div<const operand&, const operand&, const operand&> )
				.def( "idiv", &basic_block::idiv<const operand&, const operand&, const operand&> )
				.def( "mul", &basic_block::mul<const operand&, const operand&> )
				.def( "imul", &basic_block::imul<const operand&, const operand&> )
				.def( "mulhi", &basic_block::mulhi<const operand&, const operand&> )
				.def( "imulhi", &basic_block::imulhi<const operand&, const operand&> )
				.def( "rem", &basic_block::rem<const operand&, const operand&, const operand&> )
				.def( "irem", &basic_block::irem<const operand&, const operand&, const operand&> )

				.def( "popcnt", &basic_block::popcnt<const operand&> )
				.def( "bsf", &basic_block::bsf<const operand&> )
				.def( "bsr", &basic_block::bsr<const operand&> )
				.def( "bnot", &basic_block::bnot<const operand&> )
				.def( "bshr", &basic_block::bshr<const operand&, const operand&> )
				.def( "bshl", &basic_block::bshl<const operand&, const operand&> )
				.def( "bxor", &basic_block::bxor<const operand&, const operand&> )
				.def( "bor", &basic_block::bor<const operand&, const operand&> )
				.def( "band", &basic_block::band<const operand&, const operand&> )
				.def( "bror", &basic_block::bror<const operand&, const operand&> )
				.def( "brol", &basic_block::brol<const operand&, const operand&> )

				.def( "tg", &basic_block::tg<const operand&, const operand&, const operand&> )
				.def( "tge", &basic_block::tge<const operand&, const operand&, const operand&> )
				.def( "te", &basic_block::te<const operand&, const operand&, const operand&> )
				.def( "tne", &basic_block::tne<const operand&, const operand&, const operand&> )
				.def( "tle", &basic_block::tle<const operand&, const operand&, const operand&> )
				.def( "tl", &basic_block::tl<const operand&, const operand&, const operand&> )
				.def( "tug", &basic_block::tug<const operand&, const operand&, const operand&> )
				.def( "tuge", &basic_block::tuge<const operand&, const operand&, const operand&> )
				.def( "tule", &basic_block::tule<const operand&, const operand&, const operand&> )
				.def( "tul", &basic_block::tul<const operand&, const operand&, const operand&> )
				.def( "ifs", &basic_block::ifs<const operand&, const operand&, const operand&> )

				.def( "js", &basic_block::js<const operand&, const operand&, const operand&> )
				.def( "jmp", &basic_block::jmp<const operand&> )
				.def( "vexit", &basic_block::vexit<const operand&> )
				.def( "vxcall", &basic_block::vxcall<const operand&> )

				.def( "nop", &basic_block::nop<> )
				.def( "vemit", &basic_block::vemit<const operand&> )
				.def( "vpinr", &basic_block::vpinr<const operand&> )
				.def( "vpinw", &basic_block::vpinw<const operand&> )
				.def( "vpinrm", &basic_block::vpinrm<const operand&, const operand&> )
				.def( "vpinwm", &basic_block::vpinwm<const operand&, const operand&> );
		}

		private:
		static std::vector<register_desc> tmp_helper( basic_block& bbl, py::args args )
		{
			std::vector<register_desc> regs( args.size() );
			for ( auto [i, o] : zip( regs, args ) )
				i = bbl.tmp( py::cast<bitcnt_t>( o ) );
			return regs;
		}
	};
}

namespace pybind11::detail
{
	template<> struct type_caster<il_const_iterator> : public type_caster_base<il_const_iterator>
	{
		using base = type_caster_base<il_const_iterator>;

		public:
		bool load( handle src, bool convert )
		{
			if ( py::isinstance<basic_block::iterator>( src ) )
			{
				this->value = new il_const_iterator( py::cast<basic_block::iterator>( src ) );
				return true;
			}

			return false;
		}

		static handle cast( il_const_iterator src, return_value_policy policy, handle parent )
		{
			return base::cast( src, policy, parent );
		}
	};
}
