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
// | basic_block_helper.hpp  | https://github.com/vtil-project/VTIL-Core      |
// |                         | https://github.com/pybind/pybind11             |
// |--------------------------------------------------------------------------|
//
#pragma once
#include <vtil/vtil>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

using namespace vtil;
using namespace vtil::logger;
using namespace vtil::symbolic;

namespace py = pybind11;


namespace basic_block_helper
{
	auto tmp( basic_block& bbl, py::args args )
	{
		std::vector<register_desc> tmps;
		for ( size_t i = 0; i < args.size(); ++i )
		{
			tmps.push_back( bbl.tmp( py::cast<bitcnt_t>( args[ i ] ) ) );
		}

		return tmps;
	}
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
