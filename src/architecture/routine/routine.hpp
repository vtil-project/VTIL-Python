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
#include <pybind11/iostream.h>

using namespace vtil;
namespace py = pybind11;


namespace vtil::python
{
	class memory_input_stream : public std::istream
	{
		class memory_in_buffer : public std::basic_streambuf<char>
		{
			public:
			memory_in_buffer( const uint8_t* p, size_t l )
			{
				setg( ( char* ) p, ( char* ) p, ( char* ) p + l );
			}
		};

		memory_in_buffer _buffer;

		public:
		memory_input_stream( const uint8_t* p, size_t l ) : std::istream( &_buffer ), _buffer( p, l )
		{
			rdbuf( &_buffer );
		}
	};

	class memory_output_buffer : public std::streambuf
	{
		std::string data;

		protected:
		virtual int_type overflow( int_type c )
		{
			if ( c != EOF )
				data.push_back( c );
			return c;
		}

		public:
		std::string& get_contents() { return data; }
	};

	class routine_py : public py::class_<routine>
	{
		public:
		routine_py( const handle& scope, const char* name )
			: class_( scope, name )
		{
			( *this )
				// Static helpers
				//
				.def_static( "load", &load_routine, py::arg( "path" ) )
				.def( "save", &save_routine, py::arg( "path" ) )

				.def_static( "load", py::overload_cast< py::object >( &load ), py::arg("fd") )
				.def( "save", &save, py::arg("fd"), py::arg("as_bytes") = true )

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

		static routine* load( py::object obj )
		{
			if ( !( py::hasattr( obj, "read" ) ) )
			{
				throw py::type_error( "Argument is not an object of a file-like type" );
			}

			// Use Python API to read from file
			//
			auto file_data = obj.attr( "read" )( );

			// Convert into string
			//
			if ( !py::isinstance<py::bytes>( file_data ) && !py::isinstance<py::bytes>( file_data ) )
				return nullptr;

			std::string data = py::isinstance<py::bytes>( file_data ) ? std::string( file_data.cast<py::bytes>() ) : std::string( file_data.cast<py::str>() );
			return load( data );
		}

		static routine* load( const std::string& data )
		{
			memory_input_stream stream( ( uint8_t* ) &data[ 0 ], data.size() );
			routine* rtn = nullptr;
			deserialize( stream, rtn );

			return rtn;
		}

		static void save( routine* rtn, py::object obj, bool as_bytes = true )
		{
			if ( !( py::hasattr( obj, "write" ) && py::hasattr( obj, "flush" ) ) )
			{
				throw py::type_error( "Argument is not an object of a file-like type" );
			}

			// Create an in memory output buffer
			//
			memory_output_buffer out_buffer;
			std::ostream out( &out_buffer );

			// Write to the buffer and then use Python API to write to file
			serialize( out, rtn );
			if ( as_bytes )
				obj.attr( "write" )( py::bytes( out_buffer.get_contents() ) );
			else
				obj.attr( "write" )( out_buffer.get_contents() );
		}
	};
}