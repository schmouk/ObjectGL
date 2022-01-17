/**
MIT License

Copyright (c) 2022 Philippe Schmouker, ph.schmouker (at) gmail.com

Permission is hereby granted,  free of charge,  to any person obtaining a copy
of this software and associated documentation files (the "Software"),  to deal
in the Software without restriction,  including without limitation the  rights
to use,  copy,  modify,  merge,  publish,  distribute, sublicense, and/or sell
copies of the Software,  and  to  permit  persons  to  whom  the  Software  is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS",  WITHOUT WARRANTY OF ANY  KIND,  EXPRESS  OR
IMPLIED,  INCLUDING  BUT  NOT  LIMITED  TO  THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT  SHALL  THE
AUTHORS  OR  COPYRIGHT  HOLDERS  BE  LIABLE  FOR  ANY CLAIM,  DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,  ARISING FROM,
OUT  OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

//===========================================================================
#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "shaders/shaders.h"

using namespace std;


bool Shader::compile()
{
	if (!compiled) {
		GLint ok;
		glCompileShader(name);
		glGetShaderiv(name, GL_COMPILE_STATUS, &ok);
		compiled = (ok == GL_TRUE);
	}
	return compiled;
}


void Shader::get_compile_log(string& info_log, const GLsizei max_length)
{
	if (compiled)
		info_log.clear();
	else {
		info_log.reserve(max_length);
		glGetShaderInfoLog(name, max_length - 1, NULL, &info_log.front());
	}
}


bool Shader::load_source_code(const char* filepath)
{
	try {
		ifstream in_stream(filepath);

		ostringstream source_code;
		source_code << in_stream.rdbuf();
		in_stream.close();

		set_source_code(source_code.str());

		return true;
	}
	catch (ifstream::failure& e) {
		cerr << "!!! " << e.what() << endl;
		return false;
	}
}


void Shader::old_source_code_to_string(
		GLsizei count,
		const GLchar** strings,
		const GLint* lengths,
		string& out_source_code)
{
	for (int i = 0; i < count; ++i)
		if (lengths == NULL || lengths[i] < 0)
			// the current source line is NULL-terminated
			out_source_code += strings[i];
		else
			// the current source line is NOT NULL-terminated
			out_source_code += string(strings[i], size_t(lengths[i]));
}
