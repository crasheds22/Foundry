#include "GraphicsTest.h"

#include <fstream>
#include <sstream>
#include <iostream>

bool GraphicsTest::Test()
{
    bool allPassed;

    allPassed = DefaultWindowTest();

	allPassed = Shaders();

    return allPassed;
}

bool GraphicsTest::DefaultWindowTest()
{
    Graphics::InitializeGLFW();

    GLFWwindow* window = Graphics::CreateWindow(800, 500, "Default Window");

    Graphics::MakeContextCurrent(window);

    Graphics::AssignFrameBufferSizeCallback(window, [](GLFWwindow* win, int w, int h) { glViewport(0, 0, w, h); });

    Graphics::InitializeGlad();

    while (!Graphics::ShouldWindowClose(window))
    {
        if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
            Graphics::SetWindowShouldClose(window);

        Graphics::Clear(1.0f, 0.5, 0.0f, 1.0f);

        Graphics::SwapBuffers(window);
        Graphics::PollForEvents();
    }

    Graphics::TerminateGLFW();

    return true;
}

bool GraphicsTest::Shaders()
{
    Graphics::InitializeGLFW();

    GLFWwindow* window = Graphics::CreateWindow(800, 500, "Shaders");
    Graphics::MakeContextCurrent(window);
    Graphics::AssignFrameBufferSizeCallback(window, [](GLFWwindow* win, int w, int h) { glViewport(0, 0, w, h); });

    Graphics::InitializeGlad();

	//Retrieve vertex and fragment source code from file
	std::string vCode, fCode;
	std::ifstream vFile, fFile;

	vFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		//open files
		vFile.open("../Shaders/Vertex/shader.vert");
		fFile.open("../Shaders/Fragment/shader.frag");

		//read constents into stream
		std::stringstream vStream, fStream;
		vStream << vFile.rdbuf();
		fStream << fFile.rdbuf();

		//close files
		vFile.close();
		fFile.close();

		//convert stream to string
		vCode = vStream.str();
		fCode = fStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR IN LOADING SHADER" << std::endl;
		return false;
	}

	int vertexShader = Graphics::VertexShader(vCode.c_str());
	int fragmentShader = Graphics::FragmentShader(fCode.c_str());
	int shaderProg = Graphics::LinkShaders(vertexShader, fragmentShader);

	float vertices[] =
	{
		 0.5f,  0.5f, 0.0f,
		 0.0f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	unsigned int indices[] =
	{
		0, 1, 3,
		1, 2, 3
	};

	unsigned int VBO, VAO, EBO;
	Graphics::GenerateArrays(&VAO);

	Graphics::GenerateBuffers(&VBO);
	Graphics::GenerateBuffers(&EBO);

	Graphics::BindArray(VAO);

	Graphics::BindBuffer(eTarget::ArrayBuffer, VBO);
	Graphics::BufferData(eMode::ArrayBuffer, sizeof(vertices), vertices, eUsage::StaticDraw);

	Graphics::BindBuffer(eTarget::ArrayBuffer, EBO);
	Graphics::BufferData(eMode::ArrayBuffer, sizeof(indices), indices, eUsage::StaticDraw);

	Graphics::VertexAtttribPointer(0, 3, eType::Float, false, 3 * sizeof(float), (void*)0);
	Graphics::EnableVertexAttribArray();

	Graphics::BindArray(0);

	while (!Graphics::ShouldWindowClose(window))
	{
		if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
			Graphics::SetWindowShouldClose(window);

		Graphics::Clear(0.2f, 0.3f, 0.3f, 1.0f);

		Graphics::UseShaderProgram(shaderProg);
		Graphics::BindArray(VAO);
		Graphics::DrawElements(eMode::Traingles, 6, eType::Unsigned_int, 0);

		Graphics::SwapBuffers(window);
		Graphics::PollForEvents();
	}

	Graphics::TerminateGLFW();

    return true;
}
