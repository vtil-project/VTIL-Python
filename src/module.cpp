// Copyright (c) 2020 Daniel (@L33T) and contributors of the VTIL Project   
// All rights reserved.   
//    
// Redistribution and use in source and binary forms, with or without   
// modification, are permitted provided that the following conditions are met: 
//    
// 1. Redistributions of source code must retain the above copyright notice,   
//    this list of conditions and the following disclaimer.   
// 2. Redistributions in binary form must reproduce the above copyright   
//    notice, this list of conditions and the following disclaimer in the   
//    documentation and/or other materials provided with the distribution.   
// 3. Neither the name of VTIL Project nor the names of its contributors
//    may be used to endorse or promote products derived from this software 
//    without specific prior written permission.   
//    
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE   
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE  
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE   
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR   
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF   
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS   
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN   
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)   
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE  
// POSSIBILITY OF SUCH DAMAGE.        
//

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

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "architecture/arch/identifier.hpp"
#include "architecture/arch/instruction_desc.hpp"
#include "architecture/arch/operands.hpp"
#include "architecture/arch/register_desc.hpp"
#include "architecture/routine/basic_block.hpp"
#include "architecture/routine/call_convention.hpp"
#include "architecture/routine/instruction.hpp"
#include "architecture/routine/routine.hpp"
#include "architecture/misc/debug.hpp"
#include "architecture/trace/tracer.hpp"
#include "architecture/trace/cached_tracer.hpp"
#include "architecture/symex/variable.hpp"

#include "common/util/fnv64.hpp"
#include "common/util/enumerator.hpp"

#include "compiler/common/interface.hpp"

#include "symex/expressions/unique_identifier.hpp"
#include "symex/expressions/expression.hpp"

#include "external/arm64_reg.hpp"
#include "external/x86_reg.hpp"

using namespace vtil::python;
namespace py = pybind11;


PYBIND11_MODULE(vtil, m) {
	// Hook error function
	//
	vtil::logger::error_hook = [ ] ( const std::string& msg )
	{
		throw std::runtime_error( msg );
	};

	// Namespaces
	//
	auto debugger = m.def_submodule( "debugger", "vtil::debugger" );
	auto optimizer = m.def_submodule( "optimizer", "vtil::optimizer" );
	auto symbolic = m.def_submodule( "symbolic", "vtil::symbolic" );


	// VTIL Architecture
	//
	{
		/* Architecture */
		architecture_identifier_py( m, "ArchID" );
		instruction_desc_py( m, "InstructionDesc" );
		operand_py( m, "Operand" );
		register_desc_py( m, "RegisterDesc" );

		/* Instruction Stream */
		basic_block_py( m, "BasicBlock" );
		call_convention_py( m, "CallConvetion" );
		instruction_py( m, "Instruction" );
		routine_py( m, "Routine" );

		/* Miscellaneous */
		debug_py( debugger, "Debug" );

		/* Value Tracing */
		tracer_py( m, "Tracer" );
		cached_tracer_py( m, "CachedTracer" );

		/* SymEx Integration */
		variable_py( symbolic, "Variable" );
	}


	// VTIL Common
	//
	{
		/* Utility */
		fnv64_hash_py( m, "FNV64" );
		enumerator_py( m, "Enumerator" );
	}


	// VTIL Compiler
	{
		/* Common */
		pass_interface_py( optimizer, "Interface" );
	}


	// VTIL SymEx
	//
	{
		/* Expressions */
		unique_identifier_py( symbolic, "UID" );
		expression_py( symbolic, "Expression" );
	}


	// External
	//
	{
		arm64_reg_py( m, "ARM64" );
		x86_reg_py( m, "AMD64" );
	}


#ifdef VERSION_INFO
	m.attr("__version__") = VERSION_INFO;
#else
	m.attr("__version__") = "dev";
#endif

}
