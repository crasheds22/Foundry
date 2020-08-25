#pragma once
#include "UnitTest.h"

#include <map>
#include <functional>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../Graphics/Shader.h"
#include "../Graphics/Texture.h"
#include "../Graphics/Graphics.h"

enum class Camera_Movement { FORWARD, BACKWARD, RIGHT, LEFT };

class CameraTest
{
public:
    CameraTest(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f) 
        : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MoveSpeed(2.5f), MouseSensitivity(0.1f), Zoom(45.0f)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;

        UpdateCameraVectors();

        MovementMapper = { {Camera_Movement::FORWARD, Front}, {Camera_Movement::BACKWARD, -Front}, {Camera_Movement::RIGHT, Right}, {Camera_Movement::LEFT, -Right} };
    }

    glm::mat4 ViewMatrix()
    {
        return glm::lookAt(Position, Position + Front, Up);
    }

    glm::vec3 GetPosition() const { return Position; }
    glm::vec3 GetRight() const { return Right; }
    glm::vec3 GetFront() const { return Front; }
    float GetZoom() const { return Zoom; }

    void MoveCamera(Camera_Movement Direction, float deltaTime)
    {
        float velocity = MoveSpeed * deltaTime;

        Position += MovementMapper[Direction] * velocity;
    }
    void RotateCamera(float xOff, float yOff, bool constrainPitch = true)
    {
        xOff *= MouseSensitivity;
        yOff *= MouseSensitivity;

        Yaw += xOff;
        Pitch += yOff;

        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;

            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }

        UpdateCameraVectors();
    }
    void ChangeZoom(float yOff)
    {
        Zoom -= yOff;
        if (Zoom < 1.0f)
            Zoom = 1.0f;

        if (Zoom > 45.0f)
            Zoom = 45.0f;
    }

    std::map<Camera_Movement, glm::vec3> MovementMapper { };

private:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    float Yaw;
    float Pitch;

    float MoveSpeed;
    float MouseSensitivity;

    float Zoom;

    void UpdateCameraVectors()
    {
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));

        Front = glm::normalize(front);
        Right = glm::normalize(glm::cross(Front, WorldUp));
        Up = glm::normalize(glm::cross(Right, Front));

        MovementMapper = { {Camera_Movement::FORWARD, Front}, {Camera_Movement::BACKWARD, -Front}, {Camera_Movement::RIGHT, Right}, {Camera_Movement::LEFT, -Right} };
    }
};

class GraphicsTest :
    public UnitTest
{
public:
    GraphicsTest() : UnitTest("Graphics Test") { };

    bool Test() override;

    static void MouseCallback(GLFWwindow* window, double xPos, double yPos);
    static void ScrollCallback(GLFWwindow* window, double xOff, double yOff);

    float deltaTime{};
    float lastFrame{};
    bool FirstMouse{};
    float lastX{};
    float lastY{};

    float SCR_WIDTH = 800.0f;
    float SCR_HEIGHT = 500.0f;

    CameraTest camera;
    
private:
    bool HelloWindow();
    bool HelloTriangle();
    bool UsingShaders();
    bool Textures();
    bool CameraAndCubes();
    bool IntroToLighting();
};

