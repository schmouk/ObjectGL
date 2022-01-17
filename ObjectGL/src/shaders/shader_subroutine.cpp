#pragma once
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
#include <string>
#include "GL/glew.h"

using namespace std;

#include "shaders/shader_subroutines.h"


ShaderSubroutine::ShaderSubroutine(
    ShadersProgram& program,
    GLenum shader_type,
    const char* subroutine_name)
    : prvt_program(program),
      prvt_location(glGetSubroutineUniformLocation(program.name, shader_type, subroutine_name)),
      prvt_shader_type(shader_type)
{}


ShaderSubroutine::ShaderSubroutine(
    ShadersProgram& program,
    GLenum shader_type,
    const string& subroutine_name)
    : prvt_program(program),
      prvt_location(glGetSubroutineUniformLocation(program.name, shader_type, subroutine_name.c_str())),
      prvt_shader_type(shader_type)
{}


bool ShaderSubroutine::select(const char* function_name)
{
    bool ok = is_ok();
    if (ok) {
        GLuint function_index = glGetSubroutineIndex(prvt_program.name, prvt_shader_type, function_name);
        ok = function_index != GL_INVALID_INDEX;
        
        if (ok) {
            GLsizei functions_count;
            glGetIntegerv(GL_MAX_SUBROUTINE_UNIFORM_LOCATIONS, &functions_count);

            GLuint* indices = new GLuint[functions_count];
            indices[prvt_location] = function_index;
            glUniformSubroutinesuiv(prvt_shader_type, functions_count, indices);

            delete[] indices;
        }
    }
    return ok;
}
