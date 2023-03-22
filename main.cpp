#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>


constexpr int WINDOW_INITIAL_WIDTH = 800;
constexpr int WINDOW_INITIAL_HEIGHT = 600;

const char* ReadFile(const char* fileName)
{
	std::string text{};
	std::fstream newfile;
	newfile.open(fileName, std::ios::in);
	if (newfile.is_open())
	{
		std::string tp;
		while (std::getline(newfile, tp))
		{
			text += tp + "\n";
		}

		newfile.close();
	}

	std::cout << text.c_str();
	return text.c_str();
}

void InitializeGLFW()
{
	glfwInit();

	// Tell GLFW we're using OpenGL 3.3 spec
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Tell GLFW we want to be restricted to the "core" profile of functionality
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// Callback that resizes the viewport we draw to whenever the OS window is resized
	glViewport(0, 0, width, height);
}

GLFWwindow* CreateWindow()
{
	GLFWwindow* window = glfwCreateWindow(WINDOW_INITIAL_WIDTH, WINDOW_INITIAL_HEIGHT, "Hello, world!", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		return nullptr;
	}

	glfwMakeContextCurrent(window);

	// Loads all the OpenGL function pointers from the graphics card drivers
	if (!gladLoadGLLoader((GLADloadproc)(glfwGetProcAddress)))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return nullptr;
	}

	// Create a viewport in the current OS window, start drawing at lower left corner, fill whole window.
	glViewport(0, 0, WINDOW_INITIAL_WIDTH, WINDOW_INITIAL_HEIGHT);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	return window;
}

bool TryCompileShader(GLenum shaderType, unsigned int& outShader, const char* shaderSource)
{
	outShader = glCreateShader(shaderType); // Create the shader, get the ID
	glShaderSource(outShader, 1, &shaderSource, NULL); // Attach the shader source
	glCompileShader(outShader); // Compile!

	int success;
	glGetShaderiv(outShader, GL_COMPILE_STATUS, &success); // Check if it compiled...
	
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(outShader, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERROR COMPILING VERTEX SHADER:\n" << infoLog << std::endl;
		return false;
	}

	return true;
}

bool TryLinkShaders(unsigned int vertexShader, unsigned int fragmentShader, unsigned int& shaderProgram)
{
	shaderProgram = glCreateProgram();
	std::cout << "PROGRAM ID 1: " << shaderProgram << std::endl;
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	int success;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success); // Check if it linked...

	if (!success)
	{
		char infoLog[512];
		glGetProgramInfoLog(shaderProgram, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERROR LINKING SHADERS:\n" << infoLog << std::endl;
		return false;
	}

	return true;
}

bool TryCompileAndLinkShaders(unsigned int& shaderProgram)
{
	unsigned int vertexShader;
	if (!TryCompileShader(GL_VERTEX_SHADER, vertexShader, "#version 330 core\nlayout (location = 0) in vec3 aPos; void main() { gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); }"))
	{
		return false;
	}

	std::cout << "VERT SHADER ID: " << vertexShader << std::endl;

	unsigned int fragmentShader;
	if (!TryCompileShader(GL_FRAGMENT_SHADER, fragmentShader, "#version 330 core\nout vec4 FragColor;\nvoid main() { FragColor = vec4(1.0f, 0.f, 0.f, 1.0f); }"))
	{
		return false;
	}

	std::cout << "FRAG SHADER ID: " << fragmentShader << std::endl;

	if (!TryLinkShaders(vertexShader, fragmentShader, shaderProgram))
	{
		return false;
	}

	std::cout << "PROGRAM ID 2: " << shaderProgram << std::endl;

	// The shader objects are no longer needed after linking
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return true;
}

void BufferVertexData(unsigned int vertexArraySize, GLfloat vertexArray[], unsigned int elementArraySize, unsigned int elementArray[], unsigned int& vao, unsigned int& vbo, unsigned int& ebo)
{
	// Bind the VAO to store everything in
	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);

	// Set up the vertex buffer
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // Bind the buffer as the VBO buffer
	glBufferData(GL_ARRAY_BUFFER, vertexArraySize, vertexArray, GL_STATIC_DRAW); // Stuff the vertex data into the buffer

	// Set up the element buffer
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementArraySize, elementArray, GL_STATIC_DRAW);

	// Tell OpenGL how our attribute is laid out in the array
	unsigned int location = 0;
	unsigned int coordsPerVertex = 3;
	unsigned int stride = coordsPerVertex * sizeof(float);
	unsigned int offset = 0;
	glVertexAttribPointer(location, coordsPerVertex, GL_FLOAT, GL_FALSE, stride, (void*)offset);

	// Must also enable it!
	glEnableVertexAttribArray(location);
}

void ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

int main()
{
	InitializeGLFW();

	GLFWwindow* window = CreateWindow();
	if (!window)
	{
		return -1;
	}

	unsigned int shaderProgram;
	if (!TryCompileAndLinkShaders(shaderProgram))
	{
		return -1;
	}

	// Gotta buffer the vertex data!!!
	// Notice each coordinate is in normalized device coordinates (-1 to 1)
	// With a z-coord of 0, the depth is the same for each
	GLfloat myTriangle[] = {
		-0.5f, -0.5f, 0.0f,
		 0.0f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
	};

	unsigned int elementIndices[] = {
		1, 2, 3,
		0, 2, 1
	};

	unsigned int vao;
	unsigned int vbo;
	unsigned int ebo;
	BufferVertexData(sizeof(myTriangle), myTriangle, sizeof(elementIndices), elementIndices, vao, vbo, ebo);

	while (window && !glfwWindowShouldClose(window))
	{
		ProcessInput(window);

		// ---------- rendering START!

		glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, sizeof(elementIndices), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// ---------- rendering END!

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
	glDeleteProgram(shaderProgram);
	glfwTerminate();

	return 0;
}
