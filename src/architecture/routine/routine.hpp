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
// | routine.hpp             | https://github.com/vtil-project/VTIL-Core      |
// |                         | https://github.com/pybind/pybind11             |
// |--------------------------------------------------------------------------|
//
#pragma once

#include <vtil/vtil>
#include <pybind11/pybind11.h>
#include <pybind11/functional.h>

using namespace vtil;
namespace py = pybind11;


namespace vtil::python
{
	class routine_py : public py::class_<routine>
	{
		public:
		routine_py( const handle& scope, const char* name )
			: class_( scope, name )
		{
			( *this )
				// Static helpers
				//
				.def( "load", &load_routine )
				.def( "save", &save_routine )

				// Properties
				//
				.def_readonly( "arch_id", &routine::arch_id )
				.def_readonly( "explored_blocks", &routine::explored_blocks )
				.def_readonly( "entry_point", &routine::entry_point )
				.def_readwrite( "routine_convention", &routine::routine_convention )
				.def_readwrite( "subroutine_convention", &routine::subroutine_convention )

				// Functions
				//
				.def( "alloc", &alloc_helper )
				.def( "for_each", &routine::for_each )
				.def( "get_cconv", &routine::get_cconv )
				.def( "set_cconv", &routine::set_cconv )
				.def( "clone", &routine::clone )

				// End
				//
				;
		}

		private:
		static std::vector<register_desc> alloc_helper( routine& rtn, py::args args )
		{
			std::vector<register_desc> regs( args.size() );
			for ( auto [i, o] : zip( regs, args ) )
				i = rtn.alloc( py::cast<bitcnt_t>( o ) );
			return regs;
		}
	};
}