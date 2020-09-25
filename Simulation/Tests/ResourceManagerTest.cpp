#include "ResourceManagerTest.h"

bool ResourceManagerTest::Test()
{
	bool allPassed = false;

	allPassed = ShaderTesting();
	allPassed = TextureTesting();
	allPassed = ModelTesting();

	return allPassed;
}

bool ResourceManagerTest::ShaderTesting()
{
    Graphics graphics = Graphics(500, 800, "Using shaders");
    graphics.MakeWindowCurrent();
    graphics.SetResizeCallback([](GLFWwindow* win, int w, int h) { glViewport(0, 0, w, h); });

    graphics.InitializeGLAD();

    // build and compile our shader program
    // ------------------------------------
    ResMgr->CreateShader("ourShader", "../Data/Shaders/3.3.shader.vs", "../Data/Shaders/3.3.shader.fs"); // you can name your shader files however you like

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // positions         // colors
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
    };

    unsigned int VBO, VAO;
    Graphics::GenerateVertexArrays(VAO);
    Graphics::GenerateBuffer(VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    Graphics::BindArray(VAO);

    Graphics::BindBufferAndData(Graphics::BufferType::ARRAY, VBO, sizeof(vertices), vertices);

    // position attribute
    Graphics::VertexAttirbutePointer(0, 3, 6 * sizeof(float), (void*)0);
    // color attribute
    Graphics::VertexAttirbutePointer(1, 3, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    // glBindVertexArray(0);


    // render loop
    // -----------
    while (!graphics.ShouldWindowClose())
    {
        // input
        // -----
        if (graphics.KeyPressed(GLFW_KEY_ESCAPE))
            graphics.SetWindowShouldClose();

        // render
        // ------
        graphics.Clear(0.2f, 0.3f, 0.3f, 1.0f);

        // render the triangle
        ResMgr->RetrieveShader("ourShader")->Use();
        Graphics::BindArray(VAO);
        Graphics::DrawArrays(Graphics::Shape::TRIANGLES, 0, 3);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        graphics.SwapBuffers();
        graphics.PollForEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    Graphics::DeleteArrays(VAO, 1);
    Graphics::DeleteBuffers(VBO, 1);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    graphics.Terminate();

    return true;
}

bool ResourceManagerTest::TextureTesting()
{


	return false;
}

bool ResourceManagerTest::ModelTesting()
{
	return false;
}
