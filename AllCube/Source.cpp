#include<iostream>
#include "solve.h"
#include<string>
#include "random.h"

int main() {
	std::string Cubo = randomize();
	std::cout << Cubo << std::endl;
	std::string solution = get_solution(Cubo);
	std::cout << solution << std::endl;
}