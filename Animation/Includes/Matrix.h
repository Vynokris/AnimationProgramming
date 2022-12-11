#pragma once

#include "Math.h"

#include <cstdio>
#include <string>
#include <sstream>
#include <cassert>

namespace Maths
{
    // Forward declaration of the matrix class.
    template<int R, int C>
    class Matrix;

    // Shortcuts for square matrices.
    typedef Matrix<2, 2> Mat2;
    typedef Matrix<3, 3> Mat3;
    typedef Matrix<4, 4> Mat4;

    // Matrix class.
    template<int R, int C>
    class Matrix
    {
    public:
        // ------- Members ------ //
        float m[R][C];
        float* ptr = &m[0][0];

        // ----- Constructors & Destructor ----- //
        Matrix(bool identity = false)
        {
            assert(R >= 2 && C >= 2/*, "Matrix size is too small."*/);

            if (!identity)
            {
                for (int i = 0; i < R; i++)
                    for (int j = 0; j < C; j++)
                        m[i][j] = 0;
            }
            else
            {
                for (int i = 0; i < R; i++)
                    for (int j = 0; j < C; j++)
                        if (i == j)
                            m[i][j] = 1;
                        else
                            m[i][j] = 0;
            }
        }

        // Copy operator.
        Matrix(const Matrix<R, C>& matrix)
        {
            assert(R >= 2 && C >= 2/*, "Matrix size is too small."*/);
            for (int i = 0; i < R; i++)
                for (int j = 0; j < C; j++)
                    m[i][j] = matrix[i][j];
        }

        // Matrix from float 2D array.
        Matrix(const float matrix[R][C])
        {
            assert(R > 2 && C > 2/*, "Matrix size is too small."*/);
            for (int i = 0; i < R; i++)
                for (int j = 0; j < C; j++)
                    m[i][j] = matrix[i][j];
        }

        // Matrix 2 constructor.
        Matrix(const float& a, const float& b, const float& c, const float& d)
        {
            assert(R == 2 && C == 2/*, "Matrix size doesn't correspond to the number of initializers."*/);
            m[0][0] = a; m[0][1] = b;
            m[1][0] = c; m[1][1] = d;
        }

        // Matrix 3 constructor.
        Matrix(const float& a, const float& b, const float& c,
               const float& d, const float& e, const float& f,
               const float& g, const float& h, const float& i)
        {
            assert(R == 3 && C == 3/*, "Matrix size doesn't correspond to the number of initializers."*/);
            m[0][0] = a; m[0][1] = b; m[0][2] = c;
            m[1][0] = d; m[1][1] = e; m[1][2] = f;
            m[2][0] = g; m[2][1] = h; m[2][2] = i;
        }

        // Matrix 4 constructor.
        Matrix(const float& a, const float& b, const float& c, const float& d,
               const float& e, const float& f, const float& g, const float& h,
               const float& i, const float& j, const float& k, const float& l,
               const float& M, const float& n, const float& o, const float& p)
        {
            assert(R == 4 && C == 4/*, "Matrix size doesn't correspond to the number of initializers."*/);
            m[0][0] = a; m[0][1] = b; m[0][2] = c; m[0][3] = d;
            m[1][0] = e; m[1][1] = f; m[1][2] = g; m[1][3] = h;
            m[2][0] = i; m[2][1] = j; m[2][2] = k; m[2][3] = l;
            m[3][0] = M; m[3][1] = n; m[3][2] = o; m[3][3] = p;
        }

        // Matrix 4 constructor (from 2x2 matrices).
        Matrix(const Mat2& a, const Mat2& b, const Mat2& c, const Mat2& d)
        {
            assert(R == 4 && C == 4/*, "Matrix size doesn't correspond to the number of initializers."*/);
            m[0][0] = a[0][0]; m[0][1] = a[0][1]; m[0][2] = b[0][0]; m[0][3] = b[0][1];
            m[1][0] = a[1][0]; m[1][1] = a[1][1]; m[1][2] = b[1][0]; m[1][3] = b[1][1];
            m[2][0] = c[0][0]; m[2][1] = c[0][1]; m[2][2] = d[0][0]; m[2][3] = d[0][1];
            m[3][0] = c[1][0]; m[3][1] = c[1][1]; m[3][2] = d[1][0]; m[3][3] = d[1][1];
        }

        ~Matrix() {}

        // ----- Operators ----- //

        // Matrix bracket operators.
        const float* operator[](int index) const { return m[index]; }
              float* operator[](int index)       { return m[index]; }

        // Matrix copy.
        Matrix<R, C> operator=(const Matrix<R, C>& matrix)
        {
            if (&matrix == this) return *this;

            // Matrix content copy
            for (int i = 0; i < R; i++)
                for (int j = 0; j < C; j++)
                    m[i][j] = matrix[i][j];

            return *this;
        }

        Matrix<R, C> operator=(float** matrix)
        {
            assert(sizeof(matrix) / sizeof(float) == R * C/*, "The given matrix is of the wrong size."*/);

            for (int i = 0; i < R; i++)
                for (int j = 0; j < C; j++)
                    m[i][j] = matrix[i][j];

            return *this;
        }

        // Matrix addition.
        Matrix<R, C> operator+(const float& val) const
        {
            Matrix<R, C> tmp;
            for (int i = 0; i < R; i++)
                for (int j = 0; j < C; j++)
                    tmp[i][j] = m[i][j] + val;
            return tmp;
        }

        template<int _R, int _C>
        Matrix<R, C> operator+(const Matrix<_R, _C>& matrix) const
        {
            assert(R == _R && C == _C/*, "Cannot add two matrices with different dimensions."*/); // Matrix must have the same dimension
            Matrix<_R, _C> tmp;
            for (int i = 0; i < R; i++)
                for (int j = 0; j < C; j++)
                    tmp[i][j] = m[i][j] + matrix[i][j];
            return tmp;
        }

        // Matrix substraction and inversion.
        Matrix<R, C> operator-()
        {
            Matrix<R, C> tmp;
            for (int i = 0; i < R; i++)
                for (int j = 0; j < C; j++)
                    tmp[i][j] = -m[i][j];
            return tmp;
        }

        Matrix<R, C> operator-(const float& val) const
        {
            Matrix<R, C> tmp;
            for (int i = 0; i < R; i++)
                for (int j = 0; j < C; j++)
                    tmp[i][j] = m[i][j] - val;
            return tmp;
        }

        template<int _R, int _C>
        Matrix<R, C> operator-(const Matrix<_R, _C>& matrix) const
        {
            assert(R == _R && C == _C/*, "Cannot substract matrices with different dimensions."*/);
            Matrix<_R, _C> tmp;
            for (int i = 0; i < R; i++)
                for (int j = 0; j < C; j++)
                    tmp[i][j] = m[i][j] - matrix[i][j];
            return tmp;
        }


        // Matrix multiplication.
        Matrix<R, C> operator*(const float& val) const
        {
            Matrix<R, C> tmp;
            for (int i = 0; i < R; i++)
                for (int j = 0; j < C; j++)
                    tmp[i][j] = m[i][j] * val;
            return tmp;
        }

        template<int _R, int _C>
        Matrix<(R > _R ? R : _R), (C > _C ? C : _C)> operator*(const Matrix<_R, _C>& matrix) const
        {
            assert(C == _R/*, "Given matrices cannot be multiplied."*/); // Size condition to calculate

            Matrix<(R > _R ? R : _R), (C > _C ? C : _C)> result;
            for (int i = 0; i < R; i++)
                for (int j = 0; j < _C; j++)
                {
                    result[i][j] = 0;
                    for (int k = 0; k < _R; k++)
                        result[i][j] += m[i][k] * matrix[k][j];
                }
            return result;
        }

        // Matrix division by a scalar.
        Matrix<R, C> operator/(const float& val) const
        {
            Matrix<R, C> tmp;
            for (int i = 0; i < R; i++)
                for (int j = 0; j < C; j++)
                    tmp[i][j] = m[i][j] / val;
            return tmp;
        }

        // Matrix addition assignement.
        void operator+=(const float& val)
        {
            for (int i = 0; i < R; i++)
                for (int j = 0; j < C; j++)
                    m[i][j] += val;
        }

        template<int _R, int _C>
        void operator+=(const Matrix<_R, _C>& matrix)
        {
            assert(R == _R && C == _C/*, "Cannot add matrices of differing sizes."*/);
            for (int i = 0; i < R; i++)
                for (int j = 0; j < C; j++)
                    m[i][j] += matrix[i][j];
        }

        // Matrix substraction assignement.
        void operator-=(const float& val)
        {
            for (int i = 0; i < R; i++)
                for (int j = 0; j < C; j++)
                    m[i][j] -= val;
        }

        template<int _R, int _C>
        void operator-=(const Matrix<_R, _C>& matrix)
        {
            assert(R == _R && C == _C/*, "Cannot substract matrices of differing sizes."*/);
            for (int i = 0; i < R; i++)
                for (int j = 0; j < C; j++)
                    m[i][j] -= matrix[i][j];
        }

        // Matrix multiplication assignement.
        void operator*=(const float& val)
        {
            for (int i = 0; i < R; i++)
                for (int j = 0; j < C; j++)
                    m[i][j] *= val;
        }
        template<int _R, int _C>
        void operator*=(const Matrix<_R, _C>& matrix)
        {
            *this = *this * matrix;
        }

        // Matrix power.
        Matrix<R, C> operator^(const float& n) const
        {
            Matrix<R, C> tmp;
            for (int n0 = 0; n0 < n; n0++)
                for (int i = 0; i < R; i++)
                    for (int j = 0; j < C; j++)
                        tmp[i][j] *= m[i][j];
            return tmp;
        }

        // ----- Methods ----- //

        // Getters.
        int getRows() { return R; }
        int getColumns() { return C; }
        float getMatrixValue(int i, int j) { return m[i][j]; }

        // Setters.

        // Arithmetic.
        bool isSquare() { return R == C; }

        bool isIdentity()
        {
            for (int i = 0; i < R; i++)
                for (int j = 0; j < C; j++)
                    if ((i != j && m[i][j] != 0) || (i == j && m[i][j] != 1))
                        return false;
            return true;
        }

        // Determinants.
        float det2()
        {
            return (m[0][0] * m[1][1]) - (m[0][1] * m[1][0]);
        }

        float det3()
        {
            return m[0][0] * Mat2 { m[1][1], m[1][2], m[2][1], m[2][2] }.det2() -
                   m[0][1] * Mat2 { m[1][0], m[1][2], m[2][0], m[2][2] }.det2() +
                   m[0][2] * Mat2 { m[1][0], m[1][1], m[2][0], m[2][1] }.det2();
        }

        float det4()
        {
            Mat3 a(m[1][1], m[1][2], m[1][3], m[2][1], m[2][2], m[2][3], m[3][1], m[3][2], m[3][3]);
            Mat3 b(m[1][0], m[1][2], m[1][3], m[2][0], m[2][2], m[2][3], m[3][0], m[3][2], m[3][3]);
            Mat3 c(m[1][0], m[1][1], m[1][3], m[2][0], m[2][1], m[2][3], m[3][0], m[3][1], m[3][3]);
            Mat3 d(m[1][0], m[1][1], m[1][2], m[2][0], m[2][1], m[2][2], m[3][0], m[3][1], m[3][2]);

            return (a.det3() * m[0][0] - b.det3() * m[0][1] + c.det3() * m[0][2] - d.det3() * m[0][3]);
        }

        // Inverses.
        Mat2 inv2()
        {
            Mat2 val(m[1][1], -m[0][1], -m[1][0], m[0][0]);
            return val / val.det2();
        }

        Mat3 inv3()
        {
            Mat4 val(m[0][0], m[0][1], m[0][2], 0,
                m[1][0], m[1][1], m[1][2], 0,
                m[2][0], m[2][1], m[2][2], 0,
                0, 0, 0, 1);
            val = val.inv4();
            Mat3 result(val.m[0][0], val.m[0][1], val.m[0][2],
                val.m[1][0], val.m[1][1], val.m[1][2],
                val.m[2][0], val.m[2][1], val.m[2][2]);
            return result;
        }

        Mat4 inv4()
        {
            Mat2 a(m[0][0], m[0][1], m[1][0], m[1][1]);
            Mat2 b(m[0][2], m[0][3], m[1][2], m[1][3]);
            Mat2 c(m[2][0], m[2][1], m[3][0], m[3][1]);
            Mat2 d(m[2][2], m[2][3], m[3][2], m[3][3]);

            Mat4 result =
            {
                (a - b * d.inv2() * c).inv2(), -(a - b * d.inv2() * c).inv2() * b * d.inv2(),
                -(d - c * a.inv2() * b).inv2() * c * a.inv2(), (d - c * a.inv2() * b).inv2()
            };

            return result;
        }

        // Transposition.
        Matrix<R, C> transpose()
        {
            Matrix<C, R> result;
            for (int i = 0; i < R; i++)
                for (int j = 0; j < C; j++)
                    result[j][i] = m[i][j];
            return result;
        }


        void print(bool showSize = true) const
        {
            // Print data
            if (showSize)
                printf("Matrix<%d,%d>\n", R, C);

            // Print content
            for (int i = 0; i < R; i++)
            {
                for (int j = 0; j < C; j++) printf("%.2f, ", m[i][j]);
                printf("\n");
            }
            printf("\n");
        }

        std::string printStr(bool showSize = true) const
        {
            std::string output = "";

            // Add data to output.
            if (showSize)
                output += "Matrix<" + std::to_string(R) + "," + std::to_string(C) + ">\n";

            // Add content to output.
            for (int i = 0; i < R; i++)
            {
                for (int j = 0; j < C; j++)
                {
                    std::ostringstream temp;
                    temp.precision(2);
                    temp << std::fixed << m[i][j];
                    output += temp.str() + ", ";
                }
                output += "\n";
            }
            return output + "\n";
        }

        float* floatPtr()
        {
            return &m[0][0];
        }
    };

    Mat4 getTranslationMatrix(const Vector3& translation);
    Mat4 getScaleMatrix      (const Vector3& scale);
    Mat4 getXRotationMatrix  (const float& angle);
    Mat4 getYRotationMatrix  (const float& angle);
    Mat4 getZRotationMatrix  (const float& angle);
    Mat4 getRotationMatrix   (const Vector3& rotation, const bool& reverse = false);
    Mat4 getTransformMatrix  (const Vector3& position, const Vector3& rotation, const Vector3& scale, const bool& reverse = false, const bool& transformNormals = false);
}