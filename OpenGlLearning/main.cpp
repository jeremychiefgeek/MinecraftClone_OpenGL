#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

bool fullscreen = true;
int monitorNum = 0;

// Functions called in main
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

GLFWmonitor* getSecondMonitor()
{
	int numOfMonitors = 0;
	GLFWmonitor** userMonitors = glfwGetMonitors(&numOfMonitors);
	return userMonitors[1];
}

void processInput(GLFWwindow* window)
{
	// Escape key sets window to close
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	// Do Full screen here.
	if (glfwGetKey(window, GLFW_KEY_F11) == GLFW_PRESS)
	{

		fullscreen = !fullscreen;
		if (monitorNum == 1)
		{
			monitorNum = 0;
			const GLFWvidmode* primaryMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
			if (fullscreen)
				glfwSetWindowSize(window, primaryMode->width, primaryMode->height);
			else
				glfwSetWindowSize(window, 800, 600);
		}
		else
		{
			monitorNum = 1;
			const GLFWvidmode* secondaryMode = glfwGetVideoMode(getSecondMonitor());
			if (fullscreen)
				glfwSetWindowSize(window, secondaryMode->width, secondaryMode->height);//glfwSetWindowMonitor(window, getSecondMonitor(), 0, 0, secondaryMode->width, secondaryMode->height, secondaryMode->refreshRate);
			else
				glfwSetWindowSize(window, 800, 600);
		}

	}

	/*if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS)
	{
		if (monitorNum == 1)
		{
			monitorNum = 0;
			const GLFWvidmode* primaryMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
			if (fullscreen)
				glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, primaryMode->width, primaryMode->height, primaryMode->refreshRate);
			else
				glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, 800, 600, primaryMode->refreshRate);
		}
		else
		{
			monitorNum = 1;
			const GLFWvidmode* secondaryMode = glfwGetVideoMode(getSecondMonitor());
			if (fullscreen)
				glfwSetWindowMonitor(window, getSecondMonitor(), 0, 0, secondaryMode->width, secondaryMode->height, secondaryMode->refreshRate);
			else
				glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, 800, 600, secondaryMode->refreshRate);
		}
	}*/
}


void monitorTesting(GLFWwindow* window)
{
	int numOfMonitors = 0;
	GLFWmonitor **userMonitors;
	userMonitors = glfwGetMonitors(&numOfMonitors);
	std::cout << "Number of Monitors: " << numOfMonitors << std::endl;
	GLFWmonitor *mon;
	for (int i = 0; i <= numOfMonitors - 1; i++) {
		mon = userMonitors[i];
		std::cout << "Monitor: " << glfwGetMonitorName(mon) << std::endl; 
	}
}

// Needed for all C++ projects
int main()
{
	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	int windowSizeWidth = 800;
	int windowSizeHeight = 600;
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	
	GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* primaryMonMode = glfwGetVideoMode(primaryMonitor);
	glfwWindowHint(GLFW_RED_BITS, primaryMonMode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, primaryMonMode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, primaryMonMode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, primaryMonMode->refreshRate);

	windowSizeHeight = primaryMonMode->height;
	windowSizeWidth = primaryMonMode->width;

	GLFWwindow* window = glfwCreateWindow(primaryMonMode->width, primaryMonMode->height, "LearnOpenGl", NULL, NULL);

	// Create our window object
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Before we call any OpenGL function we need to load glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD." << std::endl;
		return -1;
	}

	// Set Window Hints for Primary Monitor

	// Set the viewport so that GLAD and OpenGL knows window constraints
	glViewport(0, 0, windowSizeWidth, windowSizeHeight);

	// Set callbacks for different events
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// monitorTesting(window);


	// Render/Game Loop
	while (!glfwWindowShouldClose(window))
	{
		// Process key and joystick input here
		processInput(window);

		// Change BG COlor to check if working
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// When window should close, you should terminate the window.
	glfwTerminate();
	return 0;
}