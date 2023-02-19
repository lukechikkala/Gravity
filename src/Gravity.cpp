#include "../include/Gravity.hpp"

namespace Gravity
{
void ProcessInput(GLFWwindow *window);

int Run()
{
	// GLFW Initialization
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	int window_width = 1080;
	int window_height = 720;

	GLFWwindow* window = glfwCreateWindow(window_width, window_height, "Gravity", NULL, NULL); // Replace first NULL with 'glfwGetPrimaryMonitor()' to run Full Screen on First Monitor.
	if (window == NULL)
	{
		std::cout << "Failed" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, window_width, window_height);
	// GLFW Initialized, hopefully :(
	//----------------------------------------------------------------------------------------------------

	// The cube that would one day hopefully feel gravity
	GLfloat Square_Vertices[] =
	{
//		Positions									// Colors
//		  X		  Y		 Z							 R		 G		 B
		-0.4f,	-0.4f,	0.0f,		/* Cyan */		0.0f,	1.0f,	1.0f,	//	0	A
		-0.4f,	 0.6f,	0.0f,		/* Cyan */		0.0f,	1.0f,	1.0f,	//	1	B
		-0.1f,	 0.6f,	0.0f,		/* Magenta */	1.0f,	0.0f,	1.0f,	//	2	C
		-0.1f,	-0.1f,	0.0f,		/* Magenta */	1.0f,	0.0f,	1.0f,	//	3	D
		 0.2f,	-0.1f,	0.0f,		/* Yellow */	1.0f,	1.0f,	0.0f,	//	4	E
		 0.2f,	-0.4f,	0.0f,		/* Yellow */	1.0f,	1.0f,	0.0f,	//	5	F
		-0.1f,	-0.4f,	0.0f,		/* Magenta */	1.0f,	0.0f,	1.0f	//	6	G
	};

	GLuint Square_Indices[] =
	{
		0, 1, 2,
		0, 2, 6,
		6, 3, 4,
		6, 4, 5
	};
	//----------------------------------------------------------------------------------------------------

	// Shader Program
	Gravity::Shader Square_Shader("include/shaders/shader.vs", "include/shaders/shader.fs");

	GLuint VAO, VBO, EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Square_Vertices), Square_Vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Square_Indices), Square_Indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//----------------------------------------------------------------------------------------------------

	// The main loop
	while (!glfwWindowShouldClose(window))
	{
		Gravity::ProcessInput( window );
		glClear(GL_COLOR_BUFFER_BIT);

		Square_Shader.use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

//----------------------------------------------------------------------------------------------------
		Gravity::GUI();
//----------------------------------------------------------------------------------------------------

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	//----------------------------------------------------------------------------------------------------

	// Some housekeeping
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glfwDestroyWindow(window);
	glfwTerminate();
	//----------------------------------------------------------------------------------------------------

	return 0;
}

void ProcessInput(GLFWwindow *window)
{
	if ( glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS )
	{
		glfwSetWindowShouldClose( window, true );
	}
}

//--------------------------------------------------------------------------------------------------
}	// namespace: Gravity