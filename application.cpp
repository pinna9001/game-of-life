#include "./application.h"
#include "./render.h"

#include <iostream>
#include <chrono>
#include <thread>

bool running = false;
int* arrayaddr;

int main(void)
{
	GLFWwindow* window;

	int array[96] = { 33, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 , 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 , 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 , 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 , 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 , 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 , 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 33, 0 };
	int array2[96] = { 0 };

	arrayaddr = array;
	int* result = array2;

	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(640, 480, "Conways's Game of Life", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	gladLoadGL((GLADloadfunc)glfwGetProcAddress);

	glViewport(0, 0, 640, 480);

	setInputHandler(window);

	Renderer* renderer = new Renderer();

	while (!glfwWindowShouldClose(window))
	{

		renderer->render(arrayaddr);

		glfwSwapBuffers(window);

		glfwPollEvents();

		if (running) {
			updateArray(arrayaddr, result);
			int* newArray = result;
			result = arrayaddr;
			arrayaddr = newArray;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}

	delete renderer;

	glfwTerminate();
	return 0;
}

void setInputHandler(GLFWwindow* window) 
{
	glfwSetMouseButtonCallback(window, mouseButtonCallBack);
	glfwSetKeyCallback(window, keyCallBack);
}

void mouseButtonCallBack(GLFWwindow* window, int button, int action, int mods) 
{
	if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS) 
	{
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		int xPos = int(x);
		int yPos = int(y);
		xPos /= 10;
		yPos /= 10;
		yPos = 47 - yPos;
		int mask = 1 << (xPos % 32);
		int currentValue = arrayaddr[yPos * 2 + xPos / 32] & mask;
		if (currentValue != 0) 
		{
			arrayaddr[yPos * 2 + xPos / 32] &= ~mask;
		}
		else 
		{
			arrayaddr[yPos * 2 + xPos / 32] |= mask;
		}
	}
}

void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods) 
{
	if (key == GLFW_KEY_P && action == GLFW_PRESS)
	{
		running = !running;
	}
}

void updateArray(int* array, int* result) 
{
	for (int i = 0; i < 48; i++)
	{
		for (int j = 0; j < 64; j += 1)
		{
			unsigned int mask = 1 << (j % 32);
			int currentValue = array[i * 2 + j / 32] & mask;

			int sum = 0;
			if (j != 63) 
			{
				if ((array[i * 2 + ((j + 1) / 32)] & (1 << ((j + 1) % 32))) != 0) 
				{
					sum += 1;
				}
			}
			if (j != 0) 
			{
				if ((array[i * 2 + ((j - 1) / 32)] & (1 << ((j - 1) % 32))) != 0)
				{
					sum += 1;
				}
			}
			if (i != 0 && j != 63) 
			{
				if ((array[i * 2 - 2 + ((j + 1) / 32)] & (1 << ((j + 1) % 32))) != 0) 
				{
					sum += 1;
				}
			}
			if (i != 0)
			{
				if ((array[i * 2 - 2 + j / 32] & mask) != 0) 
				{
					sum += 1;
				}
			}
			if (i != 0 && j != 0)
			{
				if ((array[i * 2 - 2 + ((j - 1) / 32)] & (1 << ((j - 1) % 32))) != 0) 
				{
					sum += 1;
				}
			}
			if (i != 47 && j != 63) 
			{
				if ((array[i * 2 + 2 + ((j + 1) / 32)] & (1 << ((j + 1) % 32))) != 0) 
				{
					sum += 1;
				}
			}
			if (i != 47) 
			{
				if ((array[i * 2 + 2 + j / 32] & mask) != 0) 
				{
					sum += 1;
				}
			}
			if (i != 47 && j != 0) 
			{
				if ((array[i * 2 + 2 + ((j - 1) / 32)] & (1 << ((j - 1) % 32))) != 0) 
				{
					sum += 1;
				}
			}

			if (sum == 3 && currentValue == 0) 
			{
				result[i * 2 + j / 32] |= mask;
			}
			else if ((sum == 3 || sum == 2) && currentValue != 0) 
			{
				result[i * 2 + j / 32] |= mask;
			}
			else
			{
				result[i * 2 + j / 32] &= ~mask;
			}
		}
	}
}