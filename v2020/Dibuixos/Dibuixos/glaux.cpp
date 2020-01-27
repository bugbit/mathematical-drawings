/*
MIT License

Copyright (c) 2019 Sistema Solar

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "pch.h"
#include "glAux.h"

ErrOrOk GLAux::LoadShader(GLuint &_id, const char* _vertexPath, const char* _fragmentPath, const char* _geometryPath)
{
	ErrOrOk err = __OK__;
	// 1. retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	std::ifstream gShaderFile;

	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		vShaderFile.open(_vertexPath);
		fShaderFile.open(_fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
		// if geometry shader path is present, also load a geometry shader
		if (_geometryPath != nullptr)
		{
			gShaderFile.open(_geometryPath);
			std::stringstream gShaderStream;
			gShaderStream << gShaderFile.rdbuf();
			gShaderFile.close();
			geometryCode = gShaderStream.str();
		}
	}
	catch (std::ifstream::failure e)
	{
		return ThrowError("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ");
	}

	const char* vShaderCode = vertexCode.c_str();
	const char * fShaderCode = fragmentCode.c_str();
	// 2. compile shaders
	unsigned int vertex, fragment;
	// vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	if (!IsOk((err = CheckCompileErrors(vertex, "VERTEX"))))
		return err;

	// fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	if (!IsOk((err = CheckCompileErrors(fragment, "FRAGMENT"))))
		return err;

	// if geometry shader is given, compile geometry shader
	unsigned int geometry;
	if (_geometryPath != nullptr)
	{
		const char * gShaderCode = geometryCode.c_str();
		geometry = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometry, 1, &gShaderCode, NULL);
		glCompileShader(geometry);
		if (!IsOk((err = CheckCompileErrors(geometry, "GEOMETRY"))))
			return err;
	}
	// shader Program
	GLuint id = glCreateProgram();

	glAttachShader(id, vertex);
	glAttachShader(id, fragment);
	if (_geometryPath != nullptr)
		glAttachShader(id, geometry);
	glLinkProgram(id);
	if (!IsOk((err = CheckCompileErrors(id, "PROGRAM"))))
		return err;

	// delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	if (_geometryPath != nullptr)
		glDeleteShader(geometry);

	_id = id;

	return err;
}

ErrOrOk GLAux::CheckCompileErrors(GLuint _shader, std::string _type)
{
	GLint success;
	GLchar infoLog[1024];

	if (_type != "PROGRAM")
	{
		glGetShaderiv(_shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(_shader, 1024, NULL, infoLog);

			return ThrowError(new std::string("ERROR::SHADER_COMPILATION_ERROR of type: " + _type + "\n" + infoLog + "\n -- --------------------------------------------------- -- "));
		}
	}
	else
	{
		glGetProgramiv(_shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(_shader, 1024, NULL, infoLog);

			return ThrowError(new std::string("ERROR::PROGRAM_LINKING_ERROR of type: " + _type + "\n" + infoLog + "\n -- --------------------------------------------------- -- "));
		}
	}

	return __OK__;
}
