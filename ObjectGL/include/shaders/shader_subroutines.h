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

#include "shaders_program.h"

using namespace std;


//===========================================================================
/** The base class for all Shader subroutines uniform variables Objects.
* 
* \sa ComputeSubroutine, FragmentSubroutine, GeometrySubroutine,
*     TessControlSubroutine, TessEvaluationSubroutine and 
*     VertexSubroutine in this same file.
*/
class ShaderSubroutine {
public:

    /** \brief Constructor with 'const char*' signature.
    *
    * Prepares all the mandatory stuff to  be  later  able  to
    * select the Shader targetted subroutine to be used by the
    * shader running code.
    *
    * \param program : a reference to the Shader Program which
    *       is currently in use.
    * \param shader_type : the type of the targetted shader.
    * \param subroutine_name : the name of the subroutine type
    *       to be used for the selection of the final subrout-
    *       ine.
    */
    ShaderSubroutine(
        ShadersProgram& program,
        GLenum shader_type,
        const char* subroutine_name);


    /** \brief Constructor with 'const string&' signature.
    *
    * Prepares all the mandatory stuff to  be  later  able  to
    * select the Shader targetted subroutine that will be used 
    * by the shader runing code.
    *
    * \param program : a reference to the Shader Program which
    *       is currently in use.
    * \param shader_type : the type of the targetted shader.
    * \param subroutine_name : the name of the subroutine type
    *       to be used for the selection of the final subrout-
    *       ine.
    */
    ShaderSubroutine(
        ShadersProgram& program,
        GLenum shader_type,
        const string& subroutine_name);


    /** \brief Destructor.
    */
    ~ShaderSubroutine()
    {}


    /** \brief Returns the ok status of this shader subroutine.
    */
    const bool is_ok() {
        return prvt_location >= 0 && prvt_location != GL_INVALID_OPERATION;
    }


    /** \brief selects the final function to be used within the targetted shader.
    * 
    * A plurality of functions are associated with the subroutine
    * uniform  variable  set  at  construction time.  This method
    * finally selects the one function that is  to  be  used  for
    * the processed code associated with this subroutine.
    * 
    * \param function_name : a C-string containing the name of the
    *       function toi be run on the Shader side.
    * 
    * \return true if selection  has  successfully  completed,  or
    *       false otherwise.
    * \sa select(const string&)
    */
    bool select(const char* function_name);


    /** \brief selects the final function to be used within the targetted shader.
    *
    * A plurality of functions are associated with the subroutine
    * uniform  variable  set  at  construction time.  This method
    * finally selects the one function that is  to  be  used  for
    * the processed code associated with this subroutine.
    *
    * \param function_name : a C++ string containing the  name  of 
    *       the function toi be run on the Shader side.
    *
    * \return true if selection  has  successfully  completed,  or
    *       false otherwise.
    * \sa select(const char*)
    */
    bool select(const string& function_name) {
        return select(function_name.c_str());
    }


    /*** /
    Parameter shadertype for the functions in this
    section may be {COMPUTE, VERTEX}_SHADER,
    TESS_{CONTROL, EVALUATION}_SHADER, or
    {FRAGMENT, GEOMETRY}_SHADER
    int GetSubroutineUniformLocation(
    uint program, enum shadertype,
    const char *name);

   
    void GetActiveSubroutineName(
    uint program, enum shadertype,
    uint index, sizei bufsize, sizei *length,
    char *name);
    
    void GetActiveSubroutineUniformName(
    uint program, enum shadertype,
    uint index, sizei bufsize, sizei *length,
    char *name);
    
    void GetActiveSubroutineUniformiv(
    uint program, enum shadertype,
    uint index, enum pname, int *values);
    
    pname: [NUM_]COMPATIBLE_SUBROUTINES
    void UniformSubroutinesuiv(
    enum shadertype, sizei count,
    const uint *indices);

    void glGetActiveSubroutineUniformiv(GLuint program,
    GLenum shadertype,
    GLuint index,
    GLenum pname,
    GLint *values);

    void glGetActiveSubroutineUniformName(GLuint program,
    GLenum shadertype,
    GLuint index,
    GLsizei bufsize,
    GLsizei *length,
    GLchar *name);

    void glGetActiveUniform(GLuint program, GLuint index,
    GLsizei bufSize, GLsizei *length,
    GLint *size, GLenum *type,
    GLchar *name);

    void glGetActiveUniformBlockiv(GLuint program,
    GLuint uniformBlockIndex,
    GLenum pname,
    GLint *params);

    void glGetActiveUniformBlockName(GLuint program,
    GLuint uniformBlockIndex,
    GLsizei bufSize,
    GLsizei *length,
    GLchar *uniformBlockName);

    void glGetActiveUniformName(GLuint program,
    GLuint uniformIndex,
    GLsizei bufSize, GLsizei *length,
    GLchar *uniformName);

    void glGetActiveUniformsiv(GLuint program,
    GLsizei uniformCount,
    const GLuint *uniformIndices,
    GLenum pname, GLint *params);
    /***/

private:
    ShadersProgram& prvt_program;
    GLint prvt_location;
    GLenum prvt_shader_type;
};