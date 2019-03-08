#include "HelpFuctions.h"

float map(float value, float minA, float maxA, float minB, float maxB) {
	return (1 - ((value - minA) / (maxA - minA))) * minB + ((value - minA) / (maxA - minA)) * maxB;
}


float RandomFloat(float a, float b) {
	//srand(glfwGetTime());
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}