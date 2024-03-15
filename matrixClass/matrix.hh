#pragma once

#include <iostream>
#include <array>
#include <cassert>

template <typename T, int N, int M>
class Matrix
{
private:
    std::array<std::array<T, M>, N> _matrix;


public:
    // Iterator
    class Iterator
    {
    public:
        // STL properties for an Iterator | https://en.cppreference.com/w/cpp/iterator/iterator_tags
        // Tags are important for the STL alogrithms to work efficiently.
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t; 
        using value_type = T;
        using pointer = value_type*;
        using reference = value_type&;

        // All iterators must be constructible, copy-constructible, copy-assignable, destructible and swappable

        // Implementing the Constructor is sufficient
        Iterator(pointer ptr) : _ptr(ptr) {}

        // Operators

        reference operator * () const
        {
            return *_ptr;
        }

        pointer operator -> ()
        {
            return _ptr;
        }

        // prefix increment
    Iterator &operator++()
    {
        // Works since arrays are one block of memory.
        ++_ptr;
        return *this;
    }
        // postfix increment
        Iterator& operator ++ (int)
        {
            Iterator thisTemp = *this;
                ++(*this);
                return thisTemp; 
            
        }

        bool operator == (const Iterator& other) const
        {
            return (_ptr == other._ptr);
        }

        bool operator != (const Iterator& other) const
        {
            return !(*this == other);
        }



    private:
        pointer _ptr;
        pointer _colEnd;
        pointer _rowEnd;
    };

    Iterator begin()
    {
        return Iterator(&_matrix[0][0]);
    }

    Iterator end()
    {
        return Iterator(&_matrix[N][M-1]);
    }

    ////////////////////////////////


    Matrix()
    {
        std::array<T, M> columns;
        columns.fill(0);

        _matrix.fill(columns);

        std::cout << "Matrix created" << std::endl;
    }

    T &get(int row, int column)
    {
        assert((row >= 0 && row < N && column >= 0 && column < M) && "Out of bounds");

        return _matrix[row][column];
    }

    Matrix<T, M, N> transpose()
    {
        Matrix<T, M, N> transposedMatrix;
        for (int i = 0; i < N; i++)
        {
            for (int k = 0; k < M; k++)
            {
                transposedMatrix._matrix[i][k] = _matrix[k][i];
            }
        }

        return transposedMatrix;
    }

    Matrix<T, N, M> add(const Matrix<T, N, M> &other)
    {
        Matrix<T, N, M> addedMatrix;

        for (int i = 0; i < N; i++)
        {
            for (int k = 0; k < M; k++)
            {
                addedMatrix._matrix[i][k] = _matrix[i][k] + other._matrix[i][k];
            }
        }
        return addedMatrix;
    }

    Matrix<T, N, M> subtract(const Matrix<T, N, M> &other)
    {
        Matrix<T, N, M> addedMatrix;

        for (int i = 0; i < N; i++)
        {
            for (int k = 0; k < M; k++)
            {
                addedMatrix._matrix[i][k] = _matrix[i][k] - other._matrix[i][k];
            }
        }
        return addedMatrix;
    }

    // NxM * MxP => NxP matrix
    template <int P>
    inline Matrix<T, N, P> multiply(Matrix<T, M, P> &other)
    {
        Matrix<T, N, P> multipliedMatrix;

        for (int l = 0; l < P; l++)
        {
            for (int i = 0; i < N; i++)
            {
                T sum = 0;
                for (int k = 0; k < M; k++)
                {
                    sum += _matrix[l][k] * other.get(k, i);
                }
                multipliedMatrix.get(l, i) = sum;
            }
        }

        return multipliedMatrix;
    }

    // Operator overloading

    Matrix<T, N, M> operator+(const Matrix<T, N, M> &other)
    {
        Matrix<T, N, M> addedMatrix;

        for (int i = 0; i < N; i++)
        {
            for (int k = 0; k < M; k++)
            {
                addedMatrix._matrix[i][k] = _matrix[i][k] + other._matrix[i][k];
            }
        }
        return addedMatrix;
    }

    Matrix<T, N, M> operator-(const Matrix<T, N, M> &other)
    {
        Matrix<T, N, M> addedMatrix;

        for (int i = 0; i < N; i++)
        {
            for (int k = 0; k < M; k++)
            {
                addedMatrix._matrix[i][k] = _matrix[i][k] - other._matrix[i][k];
            }
        }
        return addedMatrix;
    }

    template <int P>
    inline Matrix<T, N, P> operator*(Matrix<T, M, P> &other)
    {
        Matrix<T, N, P> multipliedMatrix;

        for (int l = 0; l < P; l++)
        {
            for (int i = 0; i < N; i++)
            {
                T sum = 0;
                for (int k = 0; k < M; k++)
                {
                    sum += _matrix[l][k] * other.get(k, i);
                }
                multipliedMatrix.get(l, i) = sum;
            }
        }

        return multipliedMatrix;
    }

    // ostream
    template <typename TT, int NN, int MM>
    friend std::ostream &operator<<(std::ostream &os, const Matrix<TT, NN, MM> &matrix);
};

template <typename T, int N, int M>
std::ostream &operator<<(std::ostream &os, const Matrix<T, N, M> &matrix)
{
    for (int i = 0; i < N; i++)
    {
        for (int k = 0; k < M; k++)
        {
            os << matrix._matrix[i][k] << " ";
        }
        std::cout << std::endl;
    }
    return os;
}



