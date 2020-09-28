#include "GraphicsTest.h"

#include <iostream>

void ProcessInput(GLFWwindow* window, CameraTest* camera = nullptr, float dt = 0.0f)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        Graphics::SetWindowShouldClose(window);

    if (camera)
    {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera->MoveCamera(Camera_Movement::FORWARD, dt);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera->MoveCamera(Camera_Movement::LEFT, dt);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera->MoveCamera(Camera_Movement::BACKWARD, dt);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera->MoveCamera(Camera_Movement::RIGHT, dt);
    }
}

class ShaderTest
{
public:
    Shader ID;

    ShaderTest(std::string name, const char* vPath, const char* fPath, const char* gPath = nullptr) : ID(name, vPath, fPath, gPath) { }
};

class TextureTest
{
public:
    unsigned int ID;

    TextureTest(const char* path) : ID(TextureLoader::New(path)) { }
};

class ModelTest
{
public:
    ModelTest(const char* path) : mMeshes(Model(path)) { };

    void Draw(unsigned int shaderID)
    {
        mMeshes.Draw(shaderID);
    }

private:
    Model mMeshes;
};

bool GraphicsTest::Test()
{
    bool allPassed = false;

    allPassed = HelloWindow();
    allPassed = HelloTriangle();
    allPassed = UsingShaders();
    allPassed = Textures();
    allPassed = CameraAndCubes();
    allPassed = IntroToLighting();
    allPassed = Lighting();
    allPassed = ModelOne();
    allPassed = RobertsonModel();

    return allPassed;
}

void GraphicsTest::MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
    GraphicsTest* This = (GraphicsTest*)glfwGetWindowUserPointer(window);

    if (This->FirstMouse)
    {
        This->lastX = xPos;
        This->lastY = yPos;
        This->FirstMouse = false;
    }

    float xOff = xPos - This->lastX;
    float yOff = This->lastY - yPos;

    This->lastX = xPos;
    This->lastY = yPos;

    This->camera.RotateCamera(xOff, yOff);
}

void GraphicsTest::ScrollCallback(GLFWwindow* window, double xOff, double yOff)
{
    GraphicsTest* This = (GraphicsTest*)glfwGetWindowUserPointer(window);

    This->camera.ChangeZoom(yOff);
}

bool GraphicsTest::HelloWindow()
{
    Graphics* graphics = &Graphics::Instance();
    graphics->Init(SCR_WIDTH, SCR_HEIGHT, "Hello window");
    graphics->MakeWindowCurrent();
    graphics->SetResizeCallback([](GLFWwindow* win, int w, int h) { glViewport(0, 0, w, h); });

    graphics->InitializeGLAD();

    // render loop
    // -----------
    while (!graphics->ShouldWindowClose())
    {
        // input
        // -----
        ProcessInput(graphics->Window());

        // render
        // ------
        graphics->Clear(0.2f, 0.3f, 0.3f, 1.0f);
        
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        graphics->SwapBuffers();
        graphics->PollForEvents();
    }

    graphics->Terminate();

    return true;
}

bool GraphicsTest::HelloTriangle()
{
    Graphics* graphics = &Graphics::Instance();
    graphics->Init(SCR_WIDTH, SCR_HEIGHT, "Hello Triangles");
    graphics->MakeWindowCurrent();
    graphics->SetResizeCallback([](GLFWwindow* win, int w, int h) { glViewport(0, 0, w, h); });

    graphics->InitializeGLAD();

    // build and compile our shader program
    // ------------------------------------
    ShaderTest shader("0.1.disco", "../Data/Shaders/0.1.disco.vs", "../Data/Shaders/0.1.disco.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };
    unsigned int VBO, VAO, EBO;
    Graphics::GenerateVertexArrays(VAO);
    Graphics::GenerateBuffer(VBO);
    Graphics::GenerateBuffer(EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    Graphics::BindArray(VAO);

    Graphics::BindBufferAndData(Graphics::BufferType::ARRAY, VBO, sizeof(vertices), vertices);

    Graphics::BindBufferAndData(Graphics::BufferType::ELEMENT, EBO, sizeof(indices), indices);

    Graphics::VertexAttirbutePointer(0, 3, 3 * sizeof(float), (void*)0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    Graphics::UnbindBuffer(Graphics::BufferType::ARRAY);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    Graphics::UnbindArray();


    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); <------------------------------------ Dont forget this one, this is good for Debugging

    // render loop
    // -----------
    while (!graphics->ShouldWindowClose())
    {
        // input
        // -----
        ProcessInput(graphics->Window());

        // render
        // ------
        graphics->Clear(0.2f, 0.3f, 0.3f, 1.0f);

        // draw our first triangle
        shader.ID.Use();
        Graphics::BindArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        Graphics::DrawElements(Graphics::Shape::TRIANGLES, 6, Graphics::DataType::UNSIGNED_INT, 0);
        // glBindVertexArray(0); // no need to unbind it every time 

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
    shader.ID.DeleteShader();

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    graphics->Terminate();

    return true;
}

bool GraphicsTest::UsingShaders()
{
    Graphics* graphics = &Graphics::Instance();
    graphics->Init(SCR_WIDTH, SCR_HEIGHT, "Using shaders");
    graphics->MakeWindowCurrent();
    graphics->SetResizeCallback([](GLFWwindow* win, int w, int h) { glViewport(0, 0, w, h); });

    graphics->InitializeGLAD();

    // build and compile our shader program
    // ------------------------------------
    ShaderTest ourShader("3.3.triangle", "../Data/Shaders/3.3.shader.vs", "../Data/Shaders/3.3.shader.fs"); // you can name your shader files however you like

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
        ProcessInput(graphics->Window());

        // render
        // ------
        graphics->Clear(0.2f, 0.3f, 0.3f, 1.0f);

        // render the triangle
        ourShader.ID.Use();
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

bool GraphicsTest::Textures()
{
    Graphics* graphics = &Graphics::Instance();
    graphics->Init(SCR_WIDTH, SCR_HEIGHT, "Textures");
    graphics->MakeWindowCurrent();
    graphics->SetResizeCallback([](GLFWwindow* win, int w, int h) { glViewport(0, 0, w, h); });

    graphics->InitializeGLAD();

    // build and compile our shader zprogram
    // ------------------------------------
    ShaderTest ourShader("4.2.textureShader", "../Data/Shaders/4.2.texture.vs", "../Data/Shaders/4.2.texture.fs");

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
    TextureTest texture1("../Data/Textures/container.jpg");
    TextureTest texture2("../Data/Textures/awesomeface.png");

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader.ID.Use(); // don't forget to activate/use the shader before setting uniforms!
    ourShader.ID.setInt("texture1", 0);
    ourShader.ID.setInt("texture2", 1);

    // render loop
    // -----------
    while (!graphics->ShouldWindowClose())
    {
        // input
        // -----
        ProcessInput(graphics->Window());

        // render
        // ------
        graphics->Clear(0.2f, 0.3f, 0.3f, 1.0f);

        // bind textures on corresponding texture units
        Graphics::BindTextureOnUnit(Graphics::Unit::ZERO, texture1.ID);
        Graphics::BindTextureOnUnit(Graphics::Unit::ONE, texture2.ID);

        // render container
        ourShader.ID.Use();
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

bool GraphicsTest::CameraAndCubes()
{
    camera = CameraTest(glm::vec3(0.0f, 0.0f, 3.0f));

    deltaTime = 0.0f;
    lastFrame = 0.0f;
    lastX = 800.0f / 2.0f;
    lastY = 500.0f / 2.0f;
    FirstMouse = true;

    Graphics* graphics = &Graphics::Instance();
    graphics->Init(SCR_WIDTH, SCR_HEIGHT, "Camera and Cubes");
    graphics->MakeWindowCurrent();
    Graphics::SetWindowUserPointer(graphics->Window(), this);
    graphics->SetResizeCallback([](GLFWwindow* win, int w, int h) {glViewport(0, 0, w, h); });
    graphics->SetCursorCallback(GraphicsTest::MouseCallback);
    graphics->SetScrollCallback(GraphicsTest::ScrollCallback);

    // tell GLFW to capture our mouse
    graphics->CaptureMouse();

    graphics->InitializeGLAD();

    // configure global opengl state
    // -----------------------------
    Graphics::Enable(Graphics::Capability::DEPTH);

    // build and compile our shader zprogram
    // ------------------------------------
    ShaderTest ourShader("7.4.cameraShader", "../Data/Shaders/7.4.camera.vs", "../Data/Shaders/7.4.camera.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    // world space positions of our cubes
    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    unsigned int VBO, VAO;
    Graphics::GenerateVertexArrays(VAO);
    Graphics::GenerateBuffer(VBO);

    Graphics::BindArray(VAO);

    Graphics::BindBufferAndData(Graphics::BufferType::ARRAY, VBO, sizeof(vertices), vertices);

    // position attribute
    Graphics::VertexAttirbutePointer(0, 3, 5 * sizeof(float), (void*)0);
    // texture coord attribute
    Graphics::VertexAttirbutePointer(1, 2, 5 * sizeof(float), (void*)(3 * sizeof(float)));


    // load and create a texture 
    // -------------------------
    TextureLoader::FlipVertically();
    TextureTest texture1("../Data/Textures/container.jpg");
    TextureTest texture2("../Data/Textures/awesomeface.png");

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader.ID.Use();
    ourShader.ID.setInt("texture1", 0);
    ourShader.ID.setInt("texture2", 1);


    // render loop
    // -----------
    while (!graphics->ShouldWindowClose())
    {
        // per-frame time logic
        // --------------------
        float currentFrame = Graphics::GetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        ProcessInput(graphics->Window(), &camera, deltaTime);

        // render
        // ------
        graphics->Clear(0.2f, 0.3f, 0.3f, 1.0f);

        // bind textures on corresponding texture units
        Graphics::BindTextureOnUnit(Graphics::Unit::ZERO, texture1.ID);
        Graphics::BindTextureOnUnit(Graphics::Unit::ONE, texture2.ID);

        // activate shader
        ourShader.ID.Use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.GetZoom()), (float)800 / (float)500, 0.1f, 100.0f);
        ourShader.ID.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = camera.ViewMatrix();
        ourShader.ID.setMat4("view", view);

        // render boxes
        Graphics::BindArray(VAO);
        for (unsigned int i = 0; i < 10; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            ourShader.ID.setMat4("model", model);

            Graphics::DrawArrays(Graphics::Shape::TRIANGLES, 0, 36);
        }

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

bool GraphicsTest::IntroToLighting()
{
    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

    camera = CameraTest(glm::vec3(0.0f, 0.0f, 3.0f));

    deltaTime = 0.0f;
    lastFrame = 0.0f;
    lastX = SCR_WIDTH / 2.0f;
    lastY = SCR_HEIGHT / 2.0f;
    FirstMouse = true;

    Graphics* graphics = &Graphics::Instance();
    graphics->Init(SCR_WIDTH, SCR_HEIGHT, "Lights intro");
    graphics->MakeWindowCurrent();
    Graphics::SetWindowUserPointer(graphics->Window(), this);
    graphics->SetResizeCallback([](GLFWwindow* win, int w, int h) {glViewport(0, 0, w, h); });
    graphics->SetCursorCallback(GraphicsTest::MouseCallback);
    graphics->SetScrollCallback(GraphicsTest::ScrollCallback);

    // tell GLFW to capture our mouse
    graphics->CaptureMouse();

    graphics->InitializeGLAD();

    // configure global opengl state
    // -----------------------------
    Graphics::Enable(Graphics::Capability::DEPTH);

    // build and compile our shader zprogram
    // ------------------------------------
    ShaderTest lightingShader ("2.2.basicLight", "../Data/Shaders/2.2.basic_lighting.vs", "../Data/Shaders/2.2.basic_lighting.fs");
    ShaderTest lightCubeShader("2.2.lightCube" , "../Data/Shaders/2.2.light_cube.vs"    , "../Data/Shaders/2.2.light_cube.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };
    // first, configure the cube's VAO (and VBO)
    unsigned int VBO, cubeVAO;
    Graphics::GenerateVertexArrays(cubeVAO);
    Graphics::GenerateBuffer(VBO);

    Graphics::BindBufferAndData(Graphics::BufferType::ARRAY, VBO, sizeof(vertices), vertices);

    Graphics::BindArray(cubeVAO);

    // position attribute
    Graphics::VertexAttirbutePointer(0, 3, 6 * sizeof(float), (void*)0);
    // normal attribute
    Graphics::VertexAttirbutePointer(1, 3, 6 * sizeof(float), (void*)(3 * sizeof(float)));


    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightCubeVAO;
    Graphics::GenerateVertexArrays(lightCubeVAO);
    Graphics::BindArray(lightCubeVAO);

    Graphics::BindBuffer(Graphics::BufferType::ARRAY, VBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    Graphics::VertexAttirbutePointer(0, 3, 6 * sizeof(float), (void*)0);


    // render loop
    // -----------
    while (!graphics->ShouldWindowClose())
    {
        // per-frame time logic
        // --------------------
        float currentFrame = Graphics::GetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        ProcessInput(graphics->Window(), &camera, deltaTime);

        // render
        // ------
        graphics->Clear(0.1f, 0.1f, 0.1f, 1.0f);

        // be sure to activate shader when setting uniforms/drawing objects
        lightingShader.ID.Use();
        lightingShader.ID.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
        lightingShader.ID.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        lightingShader.ID.setVec3("lightPos", lightPos);
        lightingShader.ID.setVec3("viewPos", camera.GetPosition());

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.GetZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.ViewMatrix();
        lightingShader.ID.setMat4("projection", projection);
        lightingShader.ID.setMat4("view", view);

        // world transformation
        glm::mat4 model = glm::mat4(1.0f);
        lightingShader.ID.setMat4("model", model);

        // render the cube
        Graphics::BindArray(cubeVAO);
        Graphics::DrawArrays(Graphics::Shape::TRIANGLES, 0, 36);


        // also draw the lamp object
        lightCubeShader.ID.Use();
        lightCubeShader.ID.setMat4("projection", projection);
        lightCubeShader.ID.setMat4("view", view);
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
        lightCubeShader.ID.setMat4("model", model);

        Graphics::BindArray(lightCubeVAO);
        Graphics::DrawArrays(Graphics::Shape::TRIANGLES, 0, 36);


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        graphics->SwapBuffers();
        graphics->PollForEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    Graphics::DeleteArrays(cubeVAO, 1);
    Graphics::DeleteArrays(lightCubeVAO, 1);
    Graphics::DeleteBuffers(VBO, 1);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    graphics->Terminate();

    return true;
}

bool GraphicsTest::Lighting()
{
    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

    camera = CameraTest(glm::vec3(0.0f, 0.0f, 3.0f));

    deltaTime = 0.0f;
    lastFrame = 0.0f;
    lastX = SCR_WIDTH / 2.0f;
    lastY = SCR_HEIGHT / 2.0f;
    FirstMouse = true;

    Graphics* graphics = &Graphics::Instance();
    graphics->Init(SCR_WIDTH, SCR_HEIGHT, "Light scene");
    graphics->MakeWindowCurrent();
    Graphics::SetWindowUserPointer(graphics->Window(), this);
    graphics->SetResizeCallback([](GLFWwindow* win, int w, int h) { glViewport(0, 0, w, h); });
    graphics->SetCursorCallback(GraphicsTest::MouseCallback);
    graphics->SetScrollCallback(GraphicsTest::ScrollCallback);

    // tell GLFW to capture our mouse
    graphics->CaptureMouse();

    graphics->InitializeGLAD();

    // configure global opengl state
    // -----------------------------
    Graphics::Enable(Graphics::Capability::DEPTH);

    // build and compile our shader zprogram
    // ------------------------------------
    ShaderTest lightingShader ("6.multiLight", "../Data/Shaders/6.multiple_lights.vs", "../Data/Shaders/6.multiple_lights.fs");
    ShaderTest lightCubeShader("6.lightCube" , "../Data/Shaders/6.light_cube.vs"     , "../Data/Shaders/6.light_cube.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };
    // positions all containers
    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    // positions of the point lights
    glm::vec3 pointLightPositions[] = {
        glm::vec3(0.7f,  0.2f,  2.0f),
        glm::vec3(2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3(0.0f,  0.0f, -3.0f)
    };
    // first, configure the cube's VAO (and VBO)
    unsigned int VBO, cubeVAO;
    Graphics::GenerateVertexArrays(cubeVAO);
    Graphics::GenerateBuffer(VBO);

    Graphics::BindBufferAndData(Graphics::BufferType::ARRAY, VBO, sizeof(vertices), vertices);

    Graphics::BindArray(cubeVAO);
    Graphics::VertexAttirbutePointer(0, 3, 8 * sizeof(float), (void*)0);
    Graphics::VertexAttirbutePointer(1, 3, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    Graphics::VertexAttirbutePointer(2, 2, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightCubeVAO;
    Graphics::GenerateVertexArrays(lightCubeVAO);
    Graphics::BindArray(lightCubeVAO);

    Graphics::BindBuffer(Graphics::BufferType::ARRAY, VBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    Graphics::VertexAttirbutePointer(0, 3, 8 * sizeof(float), (void*)0);

    // load textures (we now use a utility function to keep the code more organized)
    // -----------------------------------------------------------------------------
    TextureTest diffuseMap("../Data/Textures/container2.png");
    TextureTest specularMap("../Data/Textures/container2_specular.png");

    // shader configuration
    // --------------------
    lightingShader.ID.Use();
    lightingShader.ID.setInt("material.diffuse", 0);
    lightingShader.ID.setInt("material.specular", 1);


    // render loop
    // -----------
    while (!graphics->ShouldWindowClose())
    {
        // per-frame time logic
        // --------------------
        float currentFrame = Graphics::GetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        ProcessInput(graphics->Window(), &camera, deltaTime);

        // render
        // ------
        graphics->Clear(0.1f, 0.1f, 0.1f, 1.0f);

        // be sure to activate shader when setting uniforms/drawing objects
        lightingShader.ID.Use();
        lightingShader.ID.setVec3("viewPos", camera.GetPosition());
        lightingShader.ID.setFloat("material.shininess", 32.0f);

        /*
           Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index
           the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
           by defining light types as classes and set their values in there, or by using a more efficient uniform approach
           by using 'Uniform buffer objects', but that is something we'll discuss in the 'Advanced GLSL' tutorial.
        */
        // directional light
        lightingShader.ID.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
        lightingShader.ID.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
        lightingShader.ID.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
        lightingShader.ID.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
        // point light 1
        lightingShader.ID.setVec3("pointLights[0].position", pointLightPositions[0]);
        lightingShader.ID.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
        lightingShader.ID.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
        lightingShader.ID.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
        lightingShader.ID.setFloat("pointLights[0].constant", 1.0f);
        lightingShader.ID.setFloat("pointLights[0].linear", 0.09);
        lightingShader.ID.setFloat("pointLights[0].quadratic", 0.032);
        // point light 2
        lightingShader.ID.setVec3("pointLights[1].position", pointLightPositions[1]);
        lightingShader.ID.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
        lightingShader.ID.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
        lightingShader.ID.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
        lightingShader.ID.setFloat("pointLights[1].constant", 1.0f);
        lightingShader.ID.setFloat("pointLights[1].linear", 0.09);
        lightingShader.ID.setFloat("pointLights[1].quadratic", 0.032);
        // point light 3
        lightingShader.ID.setVec3("pointLights[2].position", pointLightPositions[2]);
        lightingShader.ID.setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
        lightingShader.ID.setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
        lightingShader.ID.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
        lightingShader.ID.setFloat("pointLights[2].constant", 1.0f);
        lightingShader.ID.setFloat("pointLights[2].linear", 0.09);
        lightingShader.ID.setFloat("pointLights[2].quadratic", 0.032);
        // point light 4
        lightingShader.ID.setVec3("pointLights[3].position", pointLightPositions[3]);
        lightingShader.ID.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
        lightingShader.ID.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
        lightingShader.ID.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
        lightingShader.ID.setFloat("pointLights[3].constant", 1.0f);
        lightingShader.ID.setFloat("pointLights[3].linear", 0.09);
        lightingShader.ID.setFloat("pointLights[3].quadratic", 0.032);
        // spotLight
        lightingShader.ID.setVec3("spotLight.position", camera.GetPosition());
        lightingShader.ID.setVec3("spotLight.direction", camera.GetFront());
        lightingShader.ID.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
        lightingShader.ID.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
        lightingShader.ID.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
        lightingShader.ID.setFloat("spotLight.constant", 1.0f);
        lightingShader.ID.setFloat("spotLight.linear", 0.09);
        lightingShader.ID.setFloat("spotLight.quadratic", 0.032);
        lightingShader.ID.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
        lightingShader.ID.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.GetZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.ViewMatrix();
        lightingShader.ID.setMat4("projection", projection);
        lightingShader.ID.setMat4("view", view);

        // world transformation
        glm::mat4 model = glm::mat4(1.0f);
        lightingShader.ID.setMat4("model", model);

        // bind diffuse map
        Graphics::BindTextureOnUnit(Graphics::Unit::ZERO, diffuseMap.ID);
        // bind specular map
        Graphics::BindTextureOnUnit(Graphics::Unit::ONE, specularMap.ID);

        // render containers
        Graphics::BindArray(cubeVAO);
        for (unsigned int i = 0; i < 10; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            lightingShader.ID.setMat4("model", model);

            Graphics::DrawArrays(Graphics::Shape::TRIANGLES, 0, 36);
        }

        // also draw the lamp object(s)
        lightingShader.ID.Use();
        lightingShader.ID.setMat4("projection", projection);
        lightingShader.ID.setMat4("view", view);

        // we now draw as many light bulbs as we have point lights.
        Graphics::BindArray(lightCubeVAO);
        for (unsigned int i = 0; i < 4; i++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
            lightingShader.ID.setMat4("model", model);

            Graphics::DrawArrays(Graphics::Shape::TRIANGLES, 0, 36);
        }


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        graphics->SwapBuffers();
        graphics->PollForEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    Graphics::DeleteArrays(cubeVAO, 1);
    Graphics::DeleteArrays(lightCubeVAO, 1);
    Graphics::DeleteBuffers(VBO, 1);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    graphics->Terminate();

    return true;
}

bool GraphicsTest::ModelOne()
{
    Graphics* graphics = &Graphics::Instance();
    graphics->Init(SCR_WIDTH, SCR_HEIGHT, "Model One");
    graphics->MakeWindowCurrent();
    Graphics::SetWindowUserPointer(graphics->Window(), this);
    graphics->SetResizeCallback([](GLFWwindow* win, int w, int h) {glViewport(0, 0, w, h); });
    graphics->SetCursorCallback(GraphicsTest::MouseCallback);
    graphics->SetScrollCallback(GraphicsTest::ScrollCallback);

    // tell GLFW to capture our mouse
    graphics->CaptureMouse();

    graphics->InitializeGLAD();

    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    TextureLoader::FlipVertically();

    // configure global opengl state
    // -----------------------------
    Graphics::Enable(Graphics::Capability::DEPTH);

    // build and compile shaders
    // -------------------------
    ShaderTest ourShader("1.model", "../Data/Shaders/1.model_loading.vs", "../Data/Shaders/1.model_loading.fs");

    // load models
    // -----------
    ModelTest ourModel("../Data/Models/Backpack/backpack.obj");


    // draw in wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    while (!graphics->ShouldWindowClose())
    {
        // per-frame time logic
        // --------------------
        float currentFrame = Graphics::GetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        ProcessInput(graphics->Window(), &camera, deltaTime);

        // render
        // ------
        graphics->Clear(0.05f, 0.05f, 0.05f, 1.0f);

        // don't forget to enable shader before setting uniforms
        ourShader.ID.Use();

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.GetZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.ViewMatrix();
        ourShader.ID.setMat4("projection", projection);
        ourShader.ID.setMat4("view", view);

        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        ourShader.ID.setMat4("model", model);
        ourModel.Draw(ourShader.ID.ID());


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        graphics->SwapBuffers();
        graphics->PollForEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    graphics->Terminate();

    return true;
}

bool GraphicsTest::RobertsonModel()
{
    Graphics* graphics = &Graphics::Instance();
    graphics->Init(SCR_WIDTH, SCR_HEIGHT, "Model One");
    graphics->MakeWindowCurrent();
    Graphics::SetWindowUserPointer(graphics->Window(), this);
    graphics->SetResizeCallback([](GLFWwindow* win, int w, int h) {glViewport(0, 0, w, h); });
    graphics->SetCursorCallback(GraphicsTest::MouseCallback);
    graphics->SetScrollCallback(GraphicsTest::ScrollCallback);

    // tell GLFW to capture our mouse
    graphics->CaptureMouse();

    graphics->InitializeGLAD();

    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    TextureLoader::FlipVertically();

    // configure global opengl state
    // -----------------------------
    Graphics::Enable(Graphics::Capability::DEPTH);

    // build and compile shaders
    // -------------------------
    ShaderTest ourShader("1.model", "../Data/Shaders/1.model_loading.vs", "../Data/Shaders/1.model_loading.fs");

    // load models
    // -----------
    ModelTest ourModel("../Data/Models/Robertson/RobertsonBuilding.obj");


    // draw in wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    while (!graphics->ShouldWindowClose())
    {
        // per-frame time logic
        // --------------------
        float currentFrame = Graphics::GetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        ProcessInput(graphics->Window(), &camera, deltaTime);

        // render
        // ------
        graphics->Clear(0.05f, 0.05f, 0.05f, 1.0f);

        // don't forget to enable shader before setting uniforms
        ourShader.ID.Use();

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.GetZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.ViewMatrix();
        ourShader.ID.setMat4("projection", projection);
        ourShader.ID.setMat4("view", view);

        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        ourShader.ID.setMat4("model", model);
        ourModel.Draw(ourShader.ID.ID());


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        graphics->SwapBuffers();
        graphics->PollForEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    graphics->Terminate();

    return true;
}
