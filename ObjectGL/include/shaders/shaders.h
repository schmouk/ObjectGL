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
#include <cstddef>
#include <string>
#include "GL/glew.h"
#include "../objects/object.h"

using namespace std;


//===========================================================================
/** The base class for all OpenGL Shader Objects.
*/
class Shader : public SharableObject {
public:

    bool compiled; //!< the compilation status of this shader.

    /** \brief Empty constructor.
    * 
    * Creates an OpenGL shader object according to its type  and 
    * associates a GLuint identifier to it.  Once created,  this
    * identifier  can be further accessed directly via attribute
    * '.name'.
    * 
    * Notice: in case of any type of error at creation time, the
    *          associated identifier is 0.
    * 
    * Users  are  strongly encouraged to create shaders from the
    * inheriting classes rather than from this base class.  This
    * should  avoid  any shader type error at construction time.
    * See also inheriting classes ComputeShader, FramgentShader,
    * GeometryShader, VertexShader, TessellationEvaluationShader 
    * and TessellationControlShader.
    *
    * \param type : one of GL_COMPUTE_SHADER, GL_FRAGMENT_SHADER,
    *       GL_GEOMETRY_SHADER, GL_VERTEX_SHADER,
    *       GL_TESS_EVALUATION_SHADER, GL_TESS_CONTROL_SHADER.
    */
    Shader(GLenum type)
        : SharableObject(glCreateShader(type)), compiled(false)
    {}

    /** \brief Constructor with source code setting from file.
    *
    * Creates an OpenGL shader object according to its type  and
    * associates a GLuint identifier to it.  Once created,  this
    * identifier  can be further accessed directly via attribute
    * '.name'. Sets also the source code for this shader object.
    *
    * Notice: in case of any type of error at creation time, the
    *         associated identifier is 0.
    *
    * Users  are  strongly encouraged to create shaders from the
    * inheriting classes rather than from this base class.  This
    * should  avoid  any shader type error at construction time.
    * See also inheriting classes ComputeShader, FramgentShader,
    * GeometryShader, VertexShader, TessellationEvaluationShader
    * and TessellationControlShader.
    *
    * \param type : one of GL_COMPUTE_SHADER, GL_FRAGMENT_SHADER,
    *        GL_GEOMETRY_SHADER, GL_VERTEX_SHADER,
    *        GL_TESS_EVALUATION_SHADER, GL_TESS_CONTROL_SHADER.
    * \param file_path : a reference to the path of the file that
    *        contains the whole source code of this shader.
    * 
    * \sa set_source_code.
    */
    Shader(GLenum type, const string& filepath)
        : SharableObject(glCreateShader(type)), compiled(false)
    {
        load_source_code(filepath);
    }

    /** \brief Constructor with source code setting from file.
    *
    * Creates an OpenGL shader object according to its type  and
    * associates a GLuint identifier to it.  Once created,  this
    * identifier  can be further accessed directly via attribute
    * '.name'. Sets also the source code for this shader object.
    *
    * Notice: in case of any type of error at creation time, the
    *          associated identifier is 0.
    *
    * Users  are  strongly encouraged to create shaders from the
    * inheriting classes rather than from this base class.  This
    * should  avoid  any shader type error at construction time.
    * See also inheriting classes ComputeShader, FramgentShader,
    * GeometryShader, VertexShader, TessellationEvaluationShader
    * and TessellationControlShader.
    *
    * \param type : one of GL_COMPUTE_SHADER, GL_FRAGMENT_SHADER,
    *        GL_GEOMETRY_SHADER, GL_VERTEX_SHADER,
    *        GL_TESS_EVALUATION_SHADER, GL_TESS_CONTROL_SHADER.
    * \param file_path : a C NULL-terminated  string  describing 
    *        to  the  path  of  the  file that contains the whole 
    *        source code of this shader.
    * 
    * \sa set_source_code.
    */
    Shader(GLenum type, const char* filepath)
        : SharableObject(glCreateShader(type)), compiled(false)
    {
        load_source_code(filepath);
    }


    /** \brief Copy constructor is not allowed on shaders.
    */
    Shader(const Shader& copy) = delete;


    /** \brief Destructor
    */
    ~Shader()
    {}


    /** \brief Compiles this shader.
    * 
    * Compiles the source code for shader.  The results  of  the
    * compilation can be queried by calling 'get_compile_log()'.
    * In case of error, returns false and compilation log cont-
    * ains implementation-specific set of messages describing 
    * the compilation errors. In case of no error, returns true
    * and the compilation log is an empty string.
    * 
    * \return true if compiling is ok, or false else.
    * 
    * \sa get_compile_log.
    */
    bool compile();


    /** \brief Provides compilation logs.
    * 
    * \param info_log : a reference to  the  string  which  will
    *       finally  contain the logs of the last compilation of
    *       this shader.
    * \param max_size : the  maximum  length  accepted  for  the
    *       returned logs string, including the terminating NULL
    *       character. Defaults to 1024 chars.
    * 
    * \return a reference to a string which contains all compil-
    *       ation error logs.  This string is empty when compil-
    *       ing completed with no error.
    */
    void get_compile_log(string &info_log, const GLsizei max_length = 1024);


    /** Class method. Tests for the Shader-ness of a name.
    * 
    * \param name : the OpenGL identifier of an object to test
    *       against OpenGL Shader Objects identifiers.
    * 
    * \ return True if the 'name' (i.e. the GLuint) argument is
    *       the OpenGL identifier of a shader, or false else.
    */
    static bool is_shader(const GLuint name) {
        return glIsShader(name);
    }

    /** \brief Loads from file the source code of this shader.
    * 
    * Catches any I/O exceptions and provides an  error  message
    * on the console. In case of error, returns false.
    *
    * \param file_path : a reference to the  path  of  the  file
    *        that contains the whole source code of this shader.
    * 
    * \return true if loading was ok, or false else.
    */
    bool load_source_code(const string& filepath) {
        if (load_source_code(filepath.c_str())) {
            compiled = false;
            return true;
        }
        else
            return false;
    }


    /** \brief Loads from file the source code of this shader.
    *
    * Catches any I/O exceptions and provides an  error  message 
    * on the console. In case of error, returns false.
    * 
    * \param file_path : a C NULL-terminated  string  describing
    *        to  the  path  of  the  file that contains the whole
    *        source code of this shader.
    *
    * \return true if loading was ok, or false else.
    */
    bool load_source_code(const char* filepath);


    /** \brief Prepares the further deletion of this shader within the OpenGL context.
    *
    * Notice: this is not  the  same  action  as  deleting  this
    * shader object within the application environment.
    */
    void prepare_delete() {
        glDeleteShader(name);
    }


    /** \brief Sets the source code of this shader.
    * 
    * Sets the source code of this shader.
    * 
    * \param source_code : a reference to a string that contains
    *        the whole source code of this shader.
    * \sa old_source_code_to_string.
    */
    void set_source_code(const string& source_code) {
        glShaderSource(name, 1, (const GLchar *const *)source_code.c_str(), NULL);
        compiled = false;
    }


    /** \brief Transforms all version of source code to a single NULL-terminated string.
    * 
    * This is a class method. It takes as input the classical
    * and complex format of source code as used by OpenGL for
    * setting source code of shaders and transforms them into
    * a  single  NULL-terminated string that can be then used
    * as argument to method 'set_source_code()' as well as to
    * constructor with source code setting.
    * 
    * \param count : the number of entries in  next  argument
    *        array 'strings', each entry being a line of code.
    * \param strings: an array of strings that  can  each  be
    *        NULL-terminated or not. See next argument
    * \param length : an array of  count  elements,  each  of 
    *        which  specifies  the length of the corresponding 
    *        entry in 'strings'. If the value of an element in 
    *        the array length is a positive integer, the value 
    *        represents  the  number  of  characters  in   the 
    *        corresponding  string  element.  If  the value is 
    *        negative for particular elements,  that entry  in 
    *        string is assumed to be null-terminated.
    * \param out_source_code :  a  reference  to  the  output
    *        string that will contain the final source code.
    */
    static void old_source_code_to_string(
        GLsizei count,
        const GLchar** strings,
        const GLint* length,
        string& out_source_code);

};