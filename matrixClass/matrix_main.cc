#include "matrix.hh"
#include <iomanip>
#include <algorithm>

int main()
{
    Matrix<double, 6, 6> test;

    for (int i = 0; i < 6; i++)
    {
        for (int k = 0; k < 6; k++)
        {
            test.get(i, k) = 1 + i * 3 + k;
        }
    }

    std::cout << test.get(2, 0) << std::endl;

    std::cout << "--------------------------------" << std::endl;
    std::cout << test << std::endl;

    std::cout << "--------------------------------" << std::endl;
    std::cout << test.transpose() << std::endl;

    std::cout << "--------------------------------" << std::endl;
    std::cout << "--------------------------------" << std::endl;

    std::cout << "--------------------------------" << std::endl;

    Matrix<int, 1, 4> matrix1;
    Matrix<int, 4, 1> matrix2;

    // Initialize matrix1
    for (int i = 0; i < 1; i++)
    {
        for (int k = 0; k < 4; k++)
        {
            matrix1.get(i, k) = 2;
        }
    }

    // Initialize matrix2 with some other values for demonstration
    for (int i = 0; i < 4; i++)
    {
        for (int k = 0; k < 1; k++)
        {
            matrix2.get(i, k) = 2;
        }
    }

    std::cout << matrix1 << "\n"
              << matrix2 << std::endl;
    std::cout << matrix1 * matrix2 << std::endl;
    std::cout << matrix1 + matrix1 << std::endl;
    std::cout << matrix1 - matrix1 << std::endl;

    // Iterator Test
    std::cout << "Iterator Test" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    std::cout << "--------------------------------" << std::endl;

    Matrix<int, 2, 2> iteratorTest;
    Matrix<int, 2, 2>::Iterator it = iteratorTest.begin();

    for (int i = 0; i < 2; i++)
    {
        for (int k = 0; k < 2; k++)
        {
            iteratorTest.get(i, k) = i + 2 * k;
        }
    }

    std::cout << iteratorTest << std::endl;
    while (it != iteratorTest.end())
    {
        std::cout << *it << " ";
        ++it;
    }
    std::cout << std::endl;

    std::sort(iteratorTest.begin(), iteratorTest.end());

    std::cout << "--------------------------------" << std::endl;

    std::cout << "--------------------------------" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    std::cout << "--------------------------------" << std::endl;

    // std::sort test
     // Create a Matrix object
    Matrix<int, 4, 4> matrix;

    // Fill the matrix with descending values
    int value = 16;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            matrix.get(i, j) = value--;
        }
    }

    // Print the original matrix
    std::cout << "Original Matrix:\n";
    std::cout << matrix << std::endl;

    // Create an iterator for the matrix
    Matrix<int, 4, 4>::Iterator itt = matrix.begin();

    // Print elements using the iterator
    std::cout << "Elements using iterator:\n";
    while (itt != matrix.end())
    {
        std::cout << *itt << " ";
        ++itt;
    }
    // Reverse Printing
    std::cout << std::endl <<"Reverse:" << std::endl;
    Matrix<int, 4, 4>::Iterator itReverse = matrix.end() - 1;
    while (itReverse != matrix.begin() - 1)
    {
        std::cout << *itReverse << " ";
        itReverse--;
    }

    std::cout << std::endl;
    std::cout << std::endl;
    // Sort the matrix elements
    std::sort(matrix.begin(), matrix.end());

    // Print the sorted matrix
    std::cout << "Sorted Matrix:\n";
    std::cout << matrix << std::endl;

    return 0;
}
