#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Singleton.h"

#include <string>
#include <iostream>

/** @class Graphics
 *
 *	@brief Window management and graphics utility class
 *
 *	@author Aaron Thomson
 *	@uthor Nicholas Subianto
 */
class Graphics
	: public Singleton<Graphics>
{
public:
	/** @enum BufferType
	 *  @brief Defines what kind of buffer we want to use
	 */
	enum class BufferType { ELEMENT, ARRAY };

	/** @enum Shape
	 *	@brief Defines what kind of shape we want to draw
	 */
	enum class Shape { TRIANGLES };

	/** @enum DataType
	 *	@brief Converter to opengl data types 
	 */
	enum class DataType { UNSIGNED_INT, FLOAT };

	/** @enum Unit
	 *	@breif What texture unit to use
	 */
	enum class Unit { ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE };

	/** @enum Capability
	 *	@brief Capability of the graphics to use 
	 */
	enum class Capability { DEPTH };

	/** @brief Constructor
	 */
	Graphics();
	
	/** @brief Initializes a window and context
	 *
	 *	@param width The width of the window
	 *	@param height The height of the window
	 *	@param title The title of the window
	 */
	void Init(int width, int height, std::string title);
	
	/** @brief Destructor
	 */
	~Graphics();

	/** @brief Initializes GLAD
	 */
	void InitializeGLAD();

	/** @brief Returns a pointer to the current window context held
	 */
	GLFWwindow* Window() const;

	/** @brief OpenGL call to bring the current window to the front
	 */
	void MakeWindowCurrent();
	
	/** @breif Window resize callback assignment function
	 */
	void SetResizeCallback(void(*resize)(GLFWwindow*, int, int));
	
	/** @brief Mouse button callback assignment function
	 */
	void SetMouseButtonCallback(void(*mouseBtn)(GLFWwindow*, int, int, int));
	
	/** @brief Mouse cursor callback assignment function
	 */
	void SetCursorCallback(void(*cursor)(GLFWwindow*, double, double));
	
	/** @brief Scroll wheel callback assignment function
	 */
	void SetScrollCallback(void(*scroll)(GLFWwindow*, double, double));
	
	/** @brief Keyboard callback assignment function
	 */
	void SetKeyboardCallback(void(*keys)(GLFWwindow*, int, int, int, int));

	/** @brief OpenGL call to indicate not to wipe the buffers between frames for key presses
	 */
	void StickyKeys();
	
	/** @brief OpenGL call to capture the mouse movement
	 */
	void CaptureMouse();

	/** @brief Queries if the window shuold be closed
	 */
	bool ShouldWindowClose();
	
	/** @brief Indicates the window should be closed
	 */
	void SetWindowShouldClose();
	
	/** @brief Static function to indicate to any window it should close
	 */
	static void SetWindowShouldClose(GLFWwindow* window);

	/** @brief Clears the current windows background colour
	 */
	void Clear(float r = 0.0f, float b = 0.0f, float g = 0.0f, float a = 0.0f);

	/** @brief Swaps the buffers of the current window
	 */
	void SwapBuffers();
	
	/** @brief OpenGL call to wait for an event to fire
	 */
	void PollForEvents();

	/** @brief Queries if a key has been pressed
	 *
	 *	@param key The key code to check
	 */
	bool KeyPressed(int key);
	
	/** @brief Captures and stores the mouse's current position
	 *
	 *	@param x The mouse's x position
	 *	@param y The mouse's y position
	 */
	void MousePos(double& x, double& y);

	/** @brief Kills the current window
	 */
	void Terminate();

	/** @brief Static function to generate a vertex array for rendering
	 */
	static void GenerateVertexArrays(unsigned int& ID, int n = 1);
	
	/** @brief Static function to generate a buffer for rendering
	 */
	static void GenerateBuffer(unsigned int& ID, int n = 1);

	/** @brief Binds a vertex array
	 */
	static void BindArray(unsigned int ID);
	
	/** @brief Binds a buffer
	 */
	static void BindBuffer(BufferType type, unsigned int ID);
	
	/** @brief Binds a buffer and some data
	 */
	static void BindBufferAndData(BufferType type, unsigned int ID, GLsizeiptr sizeptr, const void* data);
	
	/** @brief Creates a vertex attribute pointer 
	 */
	static void VertexAttirbutePointer(int index, int size, GLsizei stride, const void* offset);

	/** @brief Unbinds a buffer
	 */
	static void UnbindBuffer(BufferType type);
	
	/** @brief Unbinds an array
	 */
	static void UnbindArray();

	/** @brief Draws from an element buffer
	 */
	static void DrawElements(Shape shapes, GLsizei count, DataType type, const void* indices);
	
	/** @brief Draws from an array buffer
	 */
	static void DrawArrays(Shape shapes, int first, GLsizei count);

	/** @brief Deletes buffers
	 */
	static void DeleteBuffers(unsigned int& ID, int n);
	
	/** @brief Deletes arrays
	 */
	static void DeleteArrays(unsigned int& ID, int n);

	/** @brief Deletes a shader program
	 */
	static void DeleteProgram(unsigned int ID);

	/** @brief Binds a texture to a unit
	 */
	static void BindTextureOnUnit(Unit unit, unsigned int ID);

	/** @brief Sets the window pointer to a user defined object
	 */
	static void SetWindowUserPointer(GLFWwindow* window, void* pointer);

	/** @brief Enables a capability
	 */
	static void Enable(Capability cap);
	
	/** @brief Disables a capability
	 */
	static void Disable(Capability cap);

	/** @brief Returns the current program run time
	 */
	static float GetTime();

	/** @brief Returns the screen width
	 */
	double ScreenWidth() const;
	
	/** @brief Returns the screen height
	 */
	double ScreenHeight() const;

	/** @brief Returns the aspect ratio o fthe screen
	 */
	float AspectRatio() const;

private:
	/** @brief Initializes GLFW
	 */
	void InitializeGLFW();

	/** @brief Converts from our enum to a GLenum
	 */
	static GLenum Deserialise(BufferType type);
	static GLenum Deserialise(Shape type);
	static GLenum Deserialise(DataType type);
	static GLenum Deserialise(Unit unit);
	static GLenum Deserialise(Capability cap);

	double mScreenWidth = 0.0;	/*<! The srcreen width */
	double mScreenHeight = 0.0;	/*<! The screen height */

	GLFWwindow* mWindow = nullptr;	/*<! The window pointer */
};
