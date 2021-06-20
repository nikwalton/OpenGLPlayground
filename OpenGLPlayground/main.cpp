//
//  main.cpp
//  OpenGLPlayground
//
//  Created by Nikolaus Walton on 6/18/21.

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

//window settings
const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;


//temp storing glsl shader for now
const char *vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\n";

int main() {
	// initalize and configure glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	//create the window
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Playground", NULL, NULL);
	if (window == NULL) {
		std::cout << "GLFW Window Creation Failed!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	//loading opengl function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "GLAD intialization failed!" << std::endl;
		return -1;
	}
	
	//shader program
	//vertex shader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// shader error checking
	int success;
	char log[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 521, NULL, log);
		std::cout << "Error shader: vertex compilation failed!\n" << log << std::endl;
	}

	//define triangle
	float verticies[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};
	
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);
	
	//MARK: Render Loop!
	while (!glfwWindowShouldClose(window)) {
		//input
		processInput(window);
		
		glClearColor(0.2f, 0.3f, 0.3, 0.1f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
		
	}
	

	
	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow *window){
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
}
