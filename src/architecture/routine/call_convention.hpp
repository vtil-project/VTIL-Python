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
// | call_convention.hpp     | https://github.com/vtil-project/VTIL-Core      |
// |                         | https://github.com/pybind/pybind11             |
// |--------------------------------------------------------------------------|
//
#pragma once

#include <vtil/vtil>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

using namespace vtil;
namespace py = pybind11;


namespace vtil::python
{
	struct call_convention_amd64_py
	{
		// Dummy amd64 struct
		//
	};

	struct call_convention_arm64_py
	{
		// Dummy arm64 struct
		//
	};

	class call_convention_py : public py::class_<call_convention>
	{
		public:
		call_convention_py( const handle& scope, const char* name )
			: class_( scope, name )
		{
			py::class_<call_convention_amd64_py>( scope, "call_convetion::amd64" )
				// Static properties
				//
				.def_readonly_static( "preserve_all_convention", &amd64::preserve_all_convention )
				.def_readonly_static( "default_call_convention", &amd64::default_call_convention )

				// End
				//
				;

			py::class_<call_convention_arm64_py>( scope, "call_convetion::arm64" )
				// Static properties
				//
				.def_readonly_static( "preserve_all_convention", &arm64::preserve_all_convention )
				.def_readonly_static( "default_call_convention", &arm64::default_call_convention )
				.def_readonly_static( "vector_call_convention", &arm64::vector_call_convention )

				// End
				//
				;

			( *this )
				// Constructors
				//
				.def( py::init<std::vector<register_desc>, std::vector<register_desc>, std::vector<register_desc>, register_desc, size_t, bool>() )

				// Static properties
				//
				.def_property_readonly_static( "amd64", [ ] ( py::object& ) { static auto instance = call_convention_amd64_py(); return instance; } )
				.def_property_readonly_static( "arm64", [ ] ( py::object& ) { static auto instance = call_convention_arm64_py(); return instance; } )

				// Properties
				//
				.def_readonly( "volatile_registers", &call_convention::volatile_registers )
				.def_readonly( "param_registers", &call_convention::param_registers )
				.def_readonly( "retval_registers", &call_convention::retval_registers )
				.def_readonly( "frame_register", &call_convention::frame_register )
				.def_readonly( "shadow_space", &call_convention::shadow_space )
				.def_readonly( "purge_stack", &call_convention::purge_stack )

				// End
				//
				;
		}
	};
}
