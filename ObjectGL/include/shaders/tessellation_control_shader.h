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
#include "GL/glew.h"
#include "shaders.h"


//===========================================================================
/** The class of OpenGL Tessellation Control Shader.
*/
class TessellationControlShader : public Shader {
public:

	/** \brief Empty constructor.
	*
	* Creates  an  OpenGL Tessellation Control Shader object and 
	* associates a GLuint identifier to it.  Once created,  this 
	* identifier  can be further accessed directly via attribute 
	* '.name'.
	*
	* Notice: in case of any type of error at creation time, the
	*		  associated identifier is 0.
	*/
	TessellationControlShader(const GLuint name = 0)
		: Shader(GL_TESS_CONTROL_SHADER)
	{}

	/** \brief Constructor with source code setting.
	*
	* Creates  an  OpenGL Tessellation Control Shader object and
	* associates a GLuint identifier to it.  Once created,  this
	* identifier  can be further accessed directly via attribute
	* '.name'. Sets also the source code for this shader object.
	*
	* Notice: in case of any type of error at creation time, the
	*		  associated identifier is 0.
	*
	* \param source_code : a NULL-terminated  string  containing
	*		the whole source code of this shader.
	*/
	TessellationControlShader(const GLchar* source_code)
		: Shader(GL_TESS_CONTROL_SHADER, source_code)
	{}

	~TessellationControlShader()
	{}
};