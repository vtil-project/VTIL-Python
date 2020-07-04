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
// | interface.hpp           | https://github.com/vtil-project/VTIL-Core      |
// |                         | https://github.com/pybind/pybind11             |
// |--------------------------------------------------------------------------|
//
#pragma once

#include <vtil/vtil>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

using namespace vtil::optimizer;
namespace py = pybind11;


namespace vtil::python
{
	using pass_interface_t = pass_interface<>;

	class pass_interface_trampoline : public pass_interface_t
	{
		bool is_serial;

		public:
		pass_interface_trampoline( bool is_parallel ) : is_serial( !is_parallel ) {}

		size_t pass( basic_block* blk, bool xblock = false ) override
		{
			PYBIND11_OVERLOAD_PURE(
				size_t,
				pass_interface_t,
				pass_,
				blk, xblock
			);
		}

		size_t xpass( routine* rtn ) override
		{
			PYBIND11_OVERLOAD_INT( PYBIND11_TYPE( size_t ), PYBIND11_TYPE( pass_interface_t ), "xpass", rtn );

			size_t n = 0;
			if ( is_serial )
				rtn->for_each( [ & ] ( auto* bbl ) { n += this->pass( bbl, true ); } );
			else
				n = this->transform_parallel( rtn, [ & ] ( auto* bbl ) { py::gil_scoped_acquire acquire; return this->pass( bbl, true ); } );

			return n;
		}

		std::string name() override
		{
			PYBIND11_OVERLOAD(
				std::string,
				pass_interface_t,
				name
			);
		}

		private:
		size_t transform_parallel( routine* rtn, const std::function<size_t( basic_block* )>& fn )
		{
			std::atomic<size_t> n = { 0 };
			std::vector<std::thread> pool;
			pool.reserve( rtn->explored_blocks.size() );

			rtn->for_each( [ & ] ( auto* bbl ) { pool.emplace_back( [ & ] ( auto* b ) { n += fn( b ); }, bbl ); } );

			for ( auto& thread : pool )
			{
				thread.join();
			}

			return n;
		}
	};

	class pass_interface_py : public py::class_<pass_interface_t, pass_interface_trampoline>
	{
		public:
		pass_interface_py( const handle& scope, const char* name )
			: class_( scope, name )
		{
			( *this )
				// Constructor
				//
				.def( py::init_alias<bool>(), py::arg( "parallel" ) = true )

				// Functions
				//
				.def( "pass_", &pass_interface_t::pass )
				.def( "xpass", &pass_interface_t::xpass, py::call_guard<py::gil_scoped_release>() )
				.def( "name", &pass_interface_t::name )

				.def( "__call__", py::overload_cast< basic_block*, bool >( &pass_interface_t::operator() ) )
				.def( "__call__", py::overload_cast< routine* >( &pass_interface_t::operator() ) )
				;
		}
	};
}
