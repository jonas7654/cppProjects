#include "matrix.hh"
#include <iomanip>

int main()
{
    Matrix<double,6,6> test;

    for (int i = 0; i < 6 ; i++)
    {
        for (int k = 0; k < 6 ; k++)
        {
            test.get(i,k) = 1 + i *3 + k ;
        }
    }
    
    std::cout << test.get(2,0) << std::endl;

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
    for (int i = 0; i < 1; i++) {
        for (int k = 0; k < 4; k++) {
            matrix1.get(i, k) = 2;
        }
    }

    // Initialize matrix2 with some other values for demonstration
    for (int i = 0; i < 4; i++) {
        for (int k = 0; k < 1; k++) {
            matrix2.get(i, k) = 2;
        }
    }

    std::cout << matrix1 << "\n" << matrix2 << std::endl;
    std::cout << matrix1 * matrix2 << std::endl;
    std::cout << matrix1 + matrix1 << std::endl;
    std::cout << matrix1 - matrix1 << std::endl;

    // Iterator Test
    std::cout << "Iterator Test" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    std::cout << "--------------------------------" << std::endl;


    Matrix<int,2,2> iteratorTest;
    Matrix<int,2,2>::Iterator it = iteratorTest.begin();

    for (int i = 0; i < 2 ; i++)
    {
        for (int k = 0 ; k < 2 ; k++)
        {
            iteratorTest.get(i,k) = i + 2*k;
        }
    }

    std::cout << iteratorTest << std::endl;
    while(it != iteratorTest.end())
    {
        std::cout << *it << " ";
        ++it;
    }
    std::cout << std::endl;
    return 0;
}

