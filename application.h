#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

void setInputHandler(GLFWwindow* window);
static void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);
static void mouseButtonCallBack(GLFWwindow* window, int button, int action, int mods);
void updateArray(int* array, int* result);