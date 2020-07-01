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
// | module.cpp              | https://github.com/vtil-project/VTIL-Core      |
// |                         | https://github.com/pybind/pybind11             |
// |                         | https://github.com/aquynh/capstone/            |
// |                         | https://github.com/keystone-engine/keystone/   |
// |--------------------------------------------------------------------------|
//
#include <vtil/vtil>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "helpers/basic_block_helper.hpp"
#include "helpers/operand_helper.hpp"

using namespace vtil;
using namespace vtil::logger;
using namespace vtil::symbolic;


// Module Export
// 
namespace py = pybind11;

PYBIND11_MODULE(vtil, m) {

	/**************************
	* architecture_identifier *
	**************************/
	py::enum_<architecture_identifier>( m, "architecture_identifier" )
		.value( "amd64", architecture_identifier::architecture_amd64 )
		.value( "arm64", architecture_identifier::architecture_arm64 )
		.value( "virtual", architecture_identifier::architecture_virtual );

	/**************************
	*        arm64_reg        *
	**************************/
	py::enum_<arm64_reg>( m, "arm64_reg" )
		.value( "X0", arm64_reg::ARM64_REG_X0 ).value( "W0", arm64_reg::ARM64_REG_W0 )
		.value( "X1", arm64_reg::ARM64_REG_X1 ).value( "W1", arm64_reg::ARM64_REG_W1 )
		.value( "X2", arm64_reg::ARM64_REG_X2 ).value( "W2", arm64_reg::ARM64_REG_W2 )
		.value( "X3", arm64_reg::ARM64_REG_X3 ).value( "W3", arm64_reg::ARM64_REG_W3 )
		.value( "X4", arm64_reg::ARM64_REG_X4 ).value( "W4", arm64_reg::ARM64_REG_W4 )
		.value( "X5", arm64_reg::ARM64_REG_X5 ).value( "W5", arm64_reg::ARM64_REG_W5 )
		.value( "X6", arm64_reg::ARM64_REG_X6 ).value( "W6", arm64_reg::ARM64_REG_W6 )
		.value( "X7", arm64_reg::ARM64_REG_X7 ).value( "W7", arm64_reg::ARM64_REG_W7 )
		.value( "X8", arm64_reg::ARM64_REG_X8 ).value( "W8", arm64_reg::ARM64_REG_W8 )
		.value( "X9", arm64_reg::ARM64_REG_X9 ).value( "W9", arm64_reg::ARM64_REG_W9 )
		.value( "X10", arm64_reg::ARM64_REG_X10 ).value( "W10", arm64_reg::ARM64_REG_W10 )
		.value( "X11", arm64_reg::ARM64_REG_X11 ).value( "W11", arm64_reg::ARM64_REG_W11 )
		.value( "X12", arm64_reg::ARM64_REG_X12 ).value( "W12", arm64_reg::ARM64_REG_W12 )
		.value( "X13", arm64_reg::ARM64_REG_X13 ).value( "W13", arm64_reg::ARM64_REG_W13 )
		.value( "X14", arm64_reg::ARM64_REG_X14 ).value( "W14", arm64_reg::ARM64_REG_W14 )
		.value( "X15", arm64_reg::ARM64_REG_X15 ).value( "W15", arm64_reg::ARM64_REG_W15 )
		.value( "X16", arm64_reg::ARM64_REG_X16 ).value( "W16", arm64_reg::ARM64_REG_W16 ).value( "IP0", arm64_reg::ARM64_REG_IP0 )
		.value( "X17", arm64_reg::ARM64_REG_X17 ).value( "W17", arm64_reg::ARM64_REG_W17 ).value( "IP1", arm64_reg::ARM64_REG_IP1 )
		.value( "X18", arm64_reg::ARM64_REG_X18 ).value( "W18", arm64_reg::ARM64_REG_W18 )
		.value( "X19", arm64_reg::ARM64_REG_X19 ).value( "W19", arm64_reg::ARM64_REG_W19 )
		.value( "X20", arm64_reg::ARM64_REG_X20 ).value( "W20", arm64_reg::ARM64_REG_W20 )
		.value( "X21", arm64_reg::ARM64_REG_X21 ).value( "W21", arm64_reg::ARM64_REG_W21 )
		.value( "X22", arm64_reg::ARM64_REG_X22 ).value( "W22", arm64_reg::ARM64_REG_W22 )
		.value( "X23", arm64_reg::ARM64_REG_X23 ).value( "W23", arm64_reg::ARM64_REG_W23 )
		.value( "X24", arm64_reg::ARM64_REG_X24 ).value( "W24", arm64_reg::ARM64_REG_W24 )
		.value( "X25", arm64_reg::ARM64_REG_X25 ).value( "W25", arm64_reg::ARM64_REG_W25 )
		.value( "X26", arm64_reg::ARM64_REG_X26 ).value( "W26", arm64_reg::ARM64_REG_W26 )
		.value( "X27", arm64_reg::ARM64_REG_X27 ).value( "W27", arm64_reg::ARM64_REG_W27 )
		.value( "X28", arm64_reg::ARM64_REG_X28 ).value( "W28", arm64_reg::ARM64_REG_W28 )
		.value( "X29", arm64_reg::ARM64_REG_X29 ).value( "W29", arm64_reg::ARM64_REG_W29 ).value( "FP", arm64_reg::ARM64_REG_FP )
		.value( "X30", arm64_reg::ARM64_REG_X30 ).value( "W30", arm64_reg::ARM64_REG_W30 ).value( "LR", arm64_reg::ARM64_REG_LR )
		.value( "XZR", arm64_reg::ARM64_REG_XZR ).value( "WZR", arm64_reg::ARM64_REG_WZR )
		.value( "SP", arm64_reg::ARM64_REG_SP ).value( "WSP", arm64_reg::ARM64_REG_WSP )
		.value( "NZCV", arm64_reg::ARM64_REG_NZCV );

	/**************************
	*         x86_reg         *
	**************************/
	py::enum_<x86_reg>( m, "amd64_reg" )
		.value( "RAX", x86_reg::X86_REG_RAX );

	/**************************
	*      register_desc      *
	**************************/
	py::class_<register_desc>( m, "register_desc" )
		/* Static */
		.def_property_readonly_static( "SP", [ ] ( const py::object& ) { return REG_SP; } )
		.def_property_readonly_static( "FLAGS", [ ] ( const py::object& ) { return REG_FLAGS; } )
		.def_property_readonly_static( "IMGBASE", [ ] ( const py::object& ) { return REG_IMGBASE; } )

		/* Properties */
		.def_readwrite( "flags", &register_desc::flags )
		.def_readwrite( "combined_id", &register_desc::combined_id )
		.def_readwrite( "bit_count", &register_desc::bit_count )
		.def_readwrite( "bit_offset", &register_desc::bit_offset )

		/* Functions */
		.def( "is_valid", &register_desc::is_valid )
		.def( "is_flags", &register_desc::is_flags )
		.def( "is_undefined", &register_desc::is_undefined )
		.def( "is_local", &register_desc::is_local )
		.def( "is_global", &register_desc::is_global )
		.def( "is_virtual", &register_desc::is_virtual )
		.def( "is_physical", &register_desc::is_physical )
		.def( "is_volatile", &register_desc::is_volatile )
		.def( "is_read_only", &register_desc::is_read_only )
		.def( "is_stack_pointer", &register_desc::is_stack_pointer )
		.def( "is_image_base", &register_desc::is_image_base )
		.def( "is_special", &register_desc::is_special )
		.def( "is_internal", &register_desc::is_internal )

		.def( "get_mask", &register_desc::get_mask )
		.def( "overlaps", &register_desc::overlaps )
		.def( "to_string", &register_desc::to_string )

		.def( "reduce", py::overload_cast< >( &register_desc::reduce ) )

		.def( "__repr__", &register_desc::to_string )
		.def( "__str__", &register_desc::to_string )

		/* End */
		;

	/**************************
	*         operand         *
	**************************/
	py::class_<operand>( m, "operand" )
		/* Properties */
		.def_readwrite( "descriptor", &operand::descriptor )

		/* Functions */
		.def( "imm", py::overload_cast< >( &operand::imm ) )
		.def( "reg", py::overload_cast< >( &operand::reg ) )
		.def( "size", &operand::size )
		.def( "bit_count", &operand::bit_count )
		.def( "to_string", &operand::to_string )
		.def( "is_register", &operand::is_register )
		.def( "is_immediate", &operand::is_immediate )
		.def( "is_valid", &operand::is_valid )
		.def( "reduce", py::overload_cast< >( &operand::reduce ) )

		/* End */
		;

	/**************************
	*       basic_block       *
	**************************/
	py::class_<basic_block::iterator> bbl_it( m, "basic_block::iterator" );
	py::class_<basic_block::const_iterator> bbl_const_it( m, "basic_block::const_iterator" );
	auto py_basic_block = py::class_<basic_block>( m, "basic_block" )
		/* Properties */
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

		/* Functions */
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

		.def( "begin", py::overload_cast< vip_t, architecture_identifier >( &basic_block::begin ), py::arg( "arg0" ) = architecture_amd64 )
		.def( "fork", &basic_block::fork )
		.def( "tmp", [ ] ( basic_block& bbl, bitcnt_t size ) { return bbl.tmp( size ); } )
		.def( "tmp", &basic_block_helper::tmp )
		.def( "prepare_operand", [ ] ( basic_block& bbl, operand* op ) { return op; /* We use operand_helper to explicitly cast to operand */ } )

		.def( "shift_sp", &basic_block::shift_sp )
		.def( "vemits", &basic_block::vemits )
		.def( "pushf", &basic_block::pushf )
		.def( "popf", &basic_block::popf )

		.def( "push", [ ] ( basic_block& bbl, const operand& op ) { return bbl.push( op ); } )
		.def( "pop", [ ] ( basic_block& bbl, const operand& op ) { return bbl.pop( op ); } )

		.def( "hash", &basic_block::hash )

		/* End */
		;

	py_basic_block
		/* Functions */
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

	/**************************
	*        variable         *
	**************************/
	py::class_<variable::memory_t>( m, "memory_t" )
		/* Constructor */
		.def( py::init<>() )
		.def( py::init<pointer, bitcnt_t>() )

		/* Properties */
		.def_readwrite( "base", &variable::memory_t::base )
		.def_readwrite( "bit_count", &variable::memory_t::bit_count )

		/* Functions */
		.def( "decay", &variable::memory_t::decay )
		.def( "reduce", py::overload_cast< >( &variable::memory_t::reduce ) )

		/* End */
		;
	py::class_<variable>( m, "variable" )
		/* Constructor */
		.def( py::init<>() )
		.def( py::init<const il_const_iterator&, variable::descriptor_t>() )
		.def( py::init<const il_const_iterator&, const variable::memory_t&>() )
		.def( py::init<const il_const_iterator&, const variable::register_t&>() )
		.def( py::init<variable::descriptor_t>() )
		.def( py::init<const variable::memory_t&>() )
		.def( py::init<const variable::register_t&>() )

		/* Properties */
		.def_readwrite( "at", &variable::at )
		.def_readwrite( "descriptor", &variable::descriptor )
		.def_readwrite( "is_branch_depedant", &variable::is_branch_dependant )

		/* Functions */
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

		/* End */
		;

	/**************************
	*         tracer          *
	**************************/
	py::class_<tracer>( m, "tracer" )
		/* Constructor */
		.def( py::init<>() )

		/* Functions */
		.def( "trace", &tracer::trace )
		.def( "rtrace", &tracer::rtrace )

		.def( "trace_p", &tracer::trace_p )
		.def( "rtrace_p", &tracer::rtrace_p )

		.def( "trace_exp", &tracer::trace_exp )
		.def( "rtrace_exp", &tracer::rtrace_exp )
		.def( "trace_pexp", &tracer::trace_pexp )
		.def( "rtrace_pexp", &tracer::rtrace_pexp )

		.def( "__call__", &tracer::trace_p )

		/* End */
		;

	/**************************
	*        unique id        *
	**************************/
	py::class_<unique_identifier>( m, "uid" )
		/* Constructor */
		.def( py::init<std::string>() )

		/* Functions */
		.def( "hash", &unique_identifier::hash )
		.def( "__eq__", [ ] ( const unique_identifier& a, const unique_identifier& b ) { return a == b; } )
		.def( "__repr__", &unique_identifier::to_string )
		.def( "__str__", &unique_identifier::to_string );

	/**************************
	*       expression        *
	**************************/
	py::class_<expression>( m, "expression" )
		/* Constructor */
		.def( py::init<>() )
		.def( py::init<const expression&>() )

		.def( py::init<const unique_identifier&, bitcnt_t>() )

		.def( py::init<math::operator_id, const expression::reference&>() )
		.def( py::init<const expression::reference&, math::operator_id, const expression::reference&>() )

		/* Properties */
		.def_readwrite( "uid", &expression::uid )

		.def_readwrite( "op", &expression::op )
		.def_readwrite( "lhs", &expression::lhs )
		.def_readwrite( "rhs", &expression::rhs )

		.def_readwrite( "complexity", &expression::complexity )
		.def_readwrite( "depth", &expression::depth )
		.def_readwrite( "hash_value", &expression::hash_value )
		.def_readwrite( "simplify_hint", &expression::simplify_hint )
		.def_readwrite( "is_lazy", &expression::is_lazy )

		/* Functions */
		.def( "get_op_desc", &expression::get_op_desc )

		.def( "is_variable", &expression::is_variable )
		.def( "is_expression", &expression::is_expression )
		.def( "is_unary", &expression::is_unary )
		.def( "is_binary", &expression::is_binary )
		.def( "is_valid", &expression::is_valid )

		.def( "hash", &expression::hash )
		.def( "count_constants", &expression::count_constants )
		.def( "count_variables", &expression::count_variables )
		.def( "count_unique_variables", &expression::count_unique_variables )

		.def( "update", &expression::update )
		.def( "to_string", &expression::to_string )

		.def( "resize", py::overload_cast< bitcnt_t, bool >( &expression::resize ) )
		.def( "simplify", py::overload_cast< bool >( &expression::simplify ) )

		.def( "is_identical", &expression::is_identical )
		.def( "equals", &expression::equals )

		.def( "evaluate", &expression::evaluate )
		.def( "clone", &expression::clone )
		.def( "make_lazy", &expression::make_lazy )

		.def( "__repr__", &expression::to_string )
		.def( "__str__", &expression::to_string )

		/* End */
		;

#ifdef VERSION_INFO
	m.attr("__version__") = VERSION_INFO;
#else
	m.attr("__version__") = "dev";
#endif
}
