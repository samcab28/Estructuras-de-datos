#include <iostream>
#include <random>

int main() {
    int minNum = 1;
    int maxNum = 100;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(minNum, maxNum);

    int randomNumber = dis(gen);
    std::cout << "Número aleatorio: " << randomNumber << std::endl;

    return 0;
}
