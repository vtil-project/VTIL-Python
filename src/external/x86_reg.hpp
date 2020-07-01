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
// | x86_reg.hpp             | https://github.com/pybind/pybind11             |
// |                         | https://github.com/aquynh/capstone/            |
// |                         | https://github.com/keystone-engine/keystone/   |
// |--------------------------------------------------------------------------|
//
#pragma once

#include <vtil/vtil>
#include <pybind11/pybind11.h>

namespace py = pybind11;


namespace vtil::python
{
	class x86_reg_py : public py::enum_<x86_reg>
	{
		public:
		x86_reg_py( const handle& scope, const char* name )
			: enum_( scope, name )
		{
			( *this )
				.value( "RAX", x86_reg::X86_REG_RAX ).value( "EAX", x86_reg::X86_REG_EAX ).value( "AX", x86_reg::X86_REG_AX ).value( "AH", x86_reg::X86_REG_AH ).value( "AL", x86_reg::X86_REG_AL )
				.value( "RBP", x86_reg::X86_REG_RBP ).value( "EBP", x86_reg::X86_REG_EBP ).value( "BP", x86_reg::X86_REG_BP ).value( "BPL", x86_reg::X86_REG_BPL )
				.value( "RBX", x86_reg::X86_REG_RBX ).value( "EBX", x86_reg::X86_REG_EBX ).value( "BX", x86_reg::X86_REG_BX ).value( "BH", x86_reg::X86_REG_BH ).value( "BL", x86_reg::X86_REG_BL )
				.value( "RCX", x86_reg::X86_REG_RCX ).value( "ECX", x86_reg::X86_REG_ECX ).value( "CX", x86_reg::X86_REG_CX ).value( "CH", x86_reg::X86_REG_CH ).value( "CL", x86_reg::X86_REG_CL )
				.value( "RDI", x86_reg::X86_REG_RDI ).value( "EDI", x86_reg::X86_REG_EDI ).value( "DI", x86_reg::X86_REG_DI ).value( "DIL", x86_reg::X86_REG_DIL )
				.value( "RDX", x86_reg::X86_REG_RDX ).value( "EDX", x86_reg::X86_REG_EDX ).value( "DX", x86_reg::X86_REG_DX ).value( "DH", x86_reg::X86_REG_DH ).value( "DL", x86_reg::X86_REG_DL )
				.value( "RIP", x86_reg::X86_REG_RIP ).value( "EIP", x86_reg::X86_REG_EIP ).value( "IP", x86_reg::X86_REG_IP )
				.value( "RSI", x86_reg::X86_REG_RSI ).value( "ESI", x86_reg::X86_REG_ESI ).value( "SI", x86_reg::X86_REG_SI ).value( "SIL", x86_reg::X86_REG_SIL )
				.value( "RSP", x86_reg::X86_REG_RSP ).value( "ESP", x86_reg::X86_REG_ESP ).value( "SP", x86_reg::X86_REG_SP ).value( "SPL", x86_reg::X86_REG_SPL )
				.value( "r8", x86_reg::X86_REG_R8 ).value( "r8d", x86_reg::X86_REG_R8D ).value( "r8w", x86_reg::X86_REG_R8W ).value( "r8b", x86_reg::X86_REG_R8B )
				.value( "r9", x86_reg::X86_REG_R9 ).value( "r9d", x86_reg::X86_REG_R9D ).value( "r9w", x86_reg::X86_REG_R9W ).value( "r9b", x86_reg::X86_REG_R9B )
				.value( "r10", x86_reg::X86_REG_R10 ).value( "r10d", x86_reg::X86_REG_R10D ).value( "r10w", x86_reg::X86_REG_R10W ).value( "r10b", x86_reg::X86_REG_R10B )
				.value( "r11", x86_reg::X86_REG_R11 ).value( "r11d", x86_reg::X86_REG_R11D ).value( "r11w", x86_reg::X86_REG_R11W ).value( "r11b", x86_reg::X86_REG_R11B )
				.value( "r12", x86_reg::X86_REG_R12 ).value( "r12d", x86_reg::X86_REG_R12D ).value( "r12w", x86_reg::X86_REG_R12W ).value( "r12b", x86_reg::X86_REG_R12B )
				.value( "r13", x86_reg::X86_REG_R13 ).value( "r13d", x86_reg::X86_REG_R13D ).value( "r13w", x86_reg::X86_REG_R13W ).value( "r13b", x86_reg::X86_REG_R13B )
				.value( "r14", x86_reg::X86_REG_R14 ).value( "r14d", x86_reg::X86_REG_R14D ).value( "r14w", x86_reg::X86_REG_R14W ).value( "r14b", x86_reg::X86_REG_R14B )
				.value( "r15", x86_reg::X86_REG_R15 ).value( "r15d", x86_reg::X86_REG_R15D ).value( "r15w", x86_reg::X86_REG_R15W ).value( "r15b", x86_reg::X86_REG_R15B )

				.value( "FS", x86_reg::X86_REG_FS )
				.value( "GS", x86_reg::X86_REG_GS )
				.value( "CS", x86_reg::X86_REG_CS )
				.value( "SS", x86_reg::X86_REG_SS )
				.value( "DS", x86_reg::X86_REG_DS )
				.value( "ES", x86_reg::X86_REG_ES )

				.value( "EFLAGS", x86_reg::X86_REG_EFLAGS )
				;
		}
	};
}
