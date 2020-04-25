// torch-test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <random>

#include <torch/torch.h>

using namespace std;

int main()
{
    at::Tensor w1 = torch::randn({ 6, 6 }).div(sqrtf(6)).set_requires_grad(true);
    cout << w1 << endl;
    std::cout << "Hello World!\n";
    system("pause");
}