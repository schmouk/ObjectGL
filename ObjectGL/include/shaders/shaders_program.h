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
#include <vector>

#include "GL/glew.h"

#include "objects/object.h"
#include "shaders.h"


//===========================================================================
typedef vector<Shader*> ShadersList; //< the type for lists of shaders.


//===========================================================================
/** The class of OpenGL Shaders Programs.
*/
class ShadersProgram : public Object {
public:

    bool linked; //!< the linking step status of this shaders program.


    /** \brief Empty constructor.
    *
    * Creates an OpenGL Shader Program object and associates  a
    * GLuint identifier to it. Once created, this identifier can
    * be further accessed directly via attribute '.name'.
    *
    * Notice: in case of any type of error at creation time, the
    *          associated identifier is 0.
    */
    ShadersProgram()
        : Object(glCreateProgram()), linked(false)
    {}


    /** \brief full constructor. May run (i.e. "use") the program if asked for.
    * 
    * Creates an OpenGL Shader Program object and associates  a
    * GLuint identifier to it. Once created, this identifier can
    * be further accessed directly via attribute '.name'.
    * 
    * Furthermore,  attach all specified shaders,  compiles them
    * when  needed,  links  all  of  them  and finally uses this
    * program if asked for.
    *
    * Notice: in case of any type of error at creation time, the
    *          associated identifier is 0.
    *
    * \param shaders : a  reference  to  a  vector  of  shaders
    *       references.
    * \param immediate_use: set this to true if  you  want  this
    *       program  to  be run (i.e. "used") as soon as it will
    *       have beenc reated and linked.  Set this to false  if
    *       you  want  to  delay this running (which will need a 
    *       further explicit call  to  method  'use()'  for  the
    *       running  to  take  place).  Defaults  to  false - no
    *       immediate use of this program.
    * \param verbose: set this to true to get verbose compilation
    *       of compiled shaders,  or set it to false to get muted
    *       compilations.
    */
    ShadersProgram(ShadersList& shaders, const bool immediate_use = false, const bool verbose = false);


    /** \brief Copy constructor is not allowed on shaders programs.
    */
    ShadersProgram(const ShadersProgram& copy) = delete;


    /** \brief Destructor.
    */
    ~ShadersProgram()
    {
        detach_all_shaders();
    }


    /** \brief Attaches a single shader to this program.
    * 
    * Associates a Shader with this shader program.
    *
    * Notice: A shader  object  can  be  attached  to  a  shader
    *   program at any time,  although its functionality will be
    *   available only after a successful  link  of  the  shader 
    *   program.  A  shader  object  can be attached to multiple 
    *   shader programs simultaneously.
    * 
    * \param shader : a reference to a shader to be attached to
    *       this program.
    * 
    * \return true if attach  succesfully  completed,  or  false
    *       else.
    *
    *  \sa attach_shaders, detach_shader.
    */
    bool attach_shader(Shader& shader) {
        ShadersList list(1, &shader);
        return attach_shaders(list);
    }


    /** \brief Attaches many shaders to this program.
    * 
    * Associates many Shaders with this shader program.
    *
    *  \param shaders : a  reference  to  a  vector  of  shaders
    *       references.
    * 
    * \return true if all shaders attachments succesfully compl-
    *       eted, or false else.
    *
    * \sa attach_shader, detach_all_shaders.
    */
    bool attach_shaders(ShadersList& shaders);


    /** \brief Compiles any attached shaders that has not yet been compiled.
    *
    * \param verbose : set this to true to get compilation error
    *       logs printed on error console, or set it to false to
    *       get mutaed compilation. Defaults to false.
    * 
    * \return true if all shaders compilations have  succesfully
    *       completed, or false else.
    */
    bool compile_shaders(const bool verbose = false);


    /** Detaches a Shader from this Shaders Program.
    * 
    * Removes the association  of  a  Shader  object  from  this
    * Shaders  Program.  If  shader is detached from program and 
    * had been previously marked for deletion (by calling method
    * 'delete_shader()', it is deleted at that time.
    * 
    * \param shader : a reference to the Shader to be detached.
    * 
    * \return : true if  operation  succesfullky  completed,  or 
    *       false else.
    * 
    * \sa detach_shaders, detach_all_shaders.
    */
    bool detach_shader(Shader& shader);


    /** Detaches a list of shaders from this Shaders Program.
    *
    * Removes the associations of a list of Shader objects  from 
    * this  Shaders  Program.  If  any  shader  is detached from 
    * program and had been previously marked  for  deletion  (by 
    * calling  method  'delete_shader()',  it is deleted at that 
    * time.
    *
    *  \param shaders : a  reference  to  a  vector  of  shaders
    *       references.
    *
    * \return : true if  operation  succesfullky  completed,  or
    *       false else.
    *
    * \sa detach_shader, detach_all_shaders.
    */
    bool detach_shaders(ShadersList& shaders);


    /** Detaches all shaders from this Shaders Program.
    *
    * Removes the associations of all Shader objects  from  this 
    * Shaders  Program.  If  any shader is detached from program 
    * and had been previously marked for  deletion  (by  calling 
    * method  'delete_shader()',  it is deleted at that time.
    *
    * \return : true if  operation  succesfullky  completed,  or
    *       false else.
    *
    * \sa detach_shader, detach_shaders.
    */
    bool detach_all_shaders();


    /** \brief Provides linking logs.
    *
    * \param info_log : a reference to  the  string  which  will
    *       finally contain the logs of the last linking of this
    *       shaders program.
    * \param max_size : the  maximum  length  accepted  for  the
    *       returned logs string, including the terminating NULL
    *       character. Defaults to 1024 chars.
    *
    * \return a reference to a string which contains all linking
    *       error  logs.  This  string  is  empty  when  linking
    *       completed with no error.
    */
    void get_linking_log(string& info_log, const GLsizei max_length = 1024);


    /** Class method. Tests for the Program-ness of a name.
    *
    * \param name : the OpenGL identifier of an object to test
    *       against OpenGL Shaders Program Objects identifiers.
    *
    * \ return True if the 'name' (i.e. the GLuint) argument is
    *       the OpenGL identifier  of  a  shaders  program,  or 
    *       false else.
    */
    static bool is_shaders_program(const GLuint name) {
        return glIsProgram(name);
    }


    /** Links all shaders that are attached to this program.
    * 
    * Processes all shader objects attached to this program,
    * to generate a completed shader program.  The result of 
    * the linking operation can be queried by calling 
    * 'get_linking_log()'.
    * 
    * \return true if linking succesfully completed, or false
    *       else.
    */
    bool link();


    /** \brief Prepares the further deletion of this program within the OpenGL context.
    *
    * Notice: this is not  the  same  action  as  deleting  this
    * shaders program object within the application environment.
    */
    void prepare_delete() {
        glDeleteProgram(name);
    }


    /** \brief Runs this shaders Program.
    * 
    * When calling method 'use()' with this  signature,  shaders
    * must  have  been succesfully compiled and attached to this
    * program, and they must have been successfully linked also.
    * No  error  will  be returned if any of the mandatory steps
    * before using thisprogram will have failed.  Meanwhile,  no
    * operation will take place in such a failure situation.
    */
    void use() {
        if (linked)
            glUseProgram(name);
    }


private:
    ShadersList prvt_attached_shaders;  // the list of shaders that are currently attached to this program.

};