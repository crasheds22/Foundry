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
    Graphics* graphics = &Graphics::Instance();
    graphics->Init(500, 800, "Using shaders");
    graphics->MakeWindowCurrent();
    graphics->SetResizeCallback([](GLFWwindow* win, int w, int h) { glViewport(0, 0, w, h); });

    graphics->InitializeGLAD();

    // build and compile our shader program
    // ------------------------------------
    ResMgr->CreateShader("shaShader", "../Data/Shaders/3.3.shader.vs", "../Data/Shaders/3.3.shader.fs"); // you can name your shader files however you like

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
    while (!graphics->ShouldWindowClose())
    {
        // input
        // -----
        if (graphics->KeyPressed(GLFW_KEY_ESCAPE))
            graphics->SetWindowShouldClose();

        // render
        // ------
        graphics->Clear(0.2f, 0.3f, 0.3f, 1.0f);

        // render the triangle
        ResMgr->RetrieveShader("shaShader")->Use();
        Graphics::BindArray(VAO);
        Graphics::DrawArrays(Graphics::Shape::TRIANGLES, 0, 3);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        graphics->SwapBuffers();
        graphics->PollForEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    Graphics::DeleteArrays(VAO, 1);
    Graphics::DeleteBuffers(VBO, 1);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    graphics->Terminate();

    return true;
}

bool ResourceManagerTest::TextureTesting()
{
    Graphics* graphics = &Graphics::Instance();
    graphics->Init(800, 500, "Textures");
    graphics->MakeWindowCurrent();
    graphics->SetResizeCallback([](GLFWwindow* win, int w, int h) { glViewport(0, 0, w, h); });

    graphics->InitializeGLAD();

    // build and compile our shader zprogram
    // ------------------------------------
    ResMgr->CreateShader("texShader", "../Data/Shaders/4.2.texture.vs", "../Data/Shaders/4.2.texture.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    unsigned int VBO, VAO, EBO;
    Graphics::GenerateVertexArrays(VAO);
    Graphics::GenerateBuffer(VBO);
    Graphics::GenerateBuffer(EBO);

    Graphics::BindArray(VAO);

    Graphics::BindBufferAndData(Graphics::BufferType::ARRAY, VBO, sizeof(vertices), vertices);

    Graphics::BindBufferAndData(Graphics::BufferType::ELEMENT, EBO, sizeof(indices), indices);

    // position attribute
    Graphics::VertexAttirbutePointer(0, 3, 8 * sizeof(float), (void*)0);
    // color attribute
    Graphics::VertexAttirbutePointer(1, 3, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    // texture coord attribute
    Graphics::VertexAttirbutePointer(2, 2, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    TextureLoader::FlipVertically();
    ResMgr->CreateTexture("texture1", "../Data/Textures/container.jpg");
    ResMgr->CreateTexture("texture2", "../Data/Textures/awesomeface.png");

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    Shader* ourShader = ResMgr->RetrieveShader("texShader");
    ourShader->Use(); // don't forget to activate/use the shader before setting uniforms!
    ourShader->setInt("texture1", 0);
    ourShader->setInt("texture2", 1);

    // render loop
    // -----------
    while (!graphics->ShouldWindowClose())
    {
        // input
        // -----
        if (graphics->KeyPressed(GLFW_KEY_ESCAPE))
            graphics->SetWindowShouldClose();

        // render
        // ------
        graphics->Clear(0.2f, 0.3f, 0.3f, 1.0f);

        // bind textures on corresponding texture units
        Graphics::BindTextureOnUnit(Graphics::Unit::ZERO, ResMgr->RetrieveTexture("texture1")->ID());
        Graphics::BindTextureOnUnit(Graphics::Unit::ONE, ResMgr->RetrieveTexture("texture2")->ID());

        // render container
        ourShader->Use();
        Graphics::BindArray(VAO);
        Graphics::DrawElements(Graphics::Shape::TRIANGLES, 6, Graphics::DataType::UNSIGNED_INT, 0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        graphics->SwapBuffers();
        graphics->PollForEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    Graphics::DeleteArrays(VAO, 1);
    Graphics::DeleteBuffers(VBO, 1);
    Graphics::DeleteBuffers(EBO, 1);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    graphics->Terminate();

    return true;
}

bool ResourceManagerTest::ModelTesting()
{
	return false;
}
