#include "vector.h"

/**
 * main - Entry point
 * Description: Executes and does functional calls
 * Return: Always 0 on success
 */

int main(void){
	int n = 4;
	int m = 4;

	double vecA[] = {1,2,3,4};
	double vecB[] = {5,6,7,8};
	double answer;

	answer = vector_vector(m, n, vecA, vecB);
	printf("The dot product is %f\n", answer);
	return (0);
}
