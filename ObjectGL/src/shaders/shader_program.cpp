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
#include "shaders/shaders_program.h"

using namespace std;


ShadersProgram::ShadersProgram(ShadersList& shaders, const bool immediate_use, const bool verbose)
    : Object(glCreateProgram()), linked(false)
{
    if (attach_shaders(shaders))
        if (compile_shaders(verbose))
            if (link())
                if (immediate_use)
                    use();
}


bool ShadersProgram::attach_shaders(ShadersList& shaders)
{
    bool ok = true;
    for(Shader* shader: shaders) {
        if (shader->name == 0)
            ok = false;
        else {
            glAttachShader(name, shader->name);
            prvt_attached_shaders.push_back(shader);
        }
    }
    return ok;
}


bool ShadersProgram::compile_shaders(const bool verbose)
{
    bool ok = true;
    for (ShadersList::iterator shader_it = prvt_attached_shaders.begin(); shader_it != prvt_attached_shaders.end(); ++shader_it) {
        if ((*shader_it)->is_ok()) {
            if (!(*shader_it)->compile()) {
                ok = false;
                if (verbose) {
                    string error_log;
                    (*shader_it)->get_compile_log(error_log);
                    cerr << error_log << endl;
                }
            }
        }
    }
    return ok;
}


bool ShadersProgram::detach_shader(Shader& shader)
{
    for (ShadersList::iterator shader_it = prvt_attached_shaders.begin(); shader_it != prvt_attached_shaders.end(); ++shader_it) {
        if ((*shader_it)->name == shader.name) {
            glDetachShader(name, shader.name);
            prvt_attached_shaders.erase(shader_it);
            return true;
        }
    }
    return false;
}


bool ShadersProgram::detach_shaders(ShadersList& shaders)
{
    bool ok = true;
    for (ShadersList::iterator shader_it = shaders.begin(); shader_it != shaders.end(); ++shader_it) {
        ok = ok && detach_shader(**shader_it);
    }
    return ok;
}


bool ShadersProgram::detach_all_shaders()
{
    for (ShadersList::iterator shader_it = prvt_attached_shaders.begin(); shader_it != prvt_attached_shaders.end(); ++shader_it) {
        glDetachShader(name, (*shader_it)->name);
    }
    prvt_attached_shaders.clear();
    return true;
}


bool ShadersProgram::link()
{
    GLint ok;
    glLinkProgram(name);
    glGetProgramiv(name, GL_LINK_STATUS, &ok);
    linked = (ok == GL_TRUE);
    return linked;
}


void ShadersProgram::get_linking_log(string& info_log, const GLsizei max_length)
{
    if (linked)
        info_log.clear();
    else {
        info_log.reserve(max_length);
        glGetProgramInfoLog(name, max_length - 1, NULL, &info_log.front());
    }
}