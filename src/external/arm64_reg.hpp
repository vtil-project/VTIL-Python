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
// | arm64_reg.hpp           | https://github.com/pybind/pybind11             |
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
	class arm64_reg_py : public py::enum_<arm64_reg>
	{
		public:
		arm64_reg_py( const handle& scope, const char* name )
			: enum_( scope, name )
		{
			( *this )
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
		}
	};
}
