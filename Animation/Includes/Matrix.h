#pragma once

#include <cstdio>
#include <string>
#include <sstream>
#include <cassert>

namespace Maths
{
    class AngleAxis;
    class Quaternion;

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

        float* floatPtr();

        // ----- Constructors & Destructor ----- //

        Matrix(const bool& identity = false);
        Matrix(const Matrix<R, C>& matrix); // Copy operator.
        Matrix(const float matrix[R][C]);   // Matrix from float 2D array.

        // Matrix 2x2 constructor.
        Matrix(const float& a, const float& b, 
               const float& c, const float& d);

        // Matrix 3x3 constructor.
        Matrix(const float& a, const float& b, const float& c,
               const float& d, const float& e, const float& f,
               const float& g, const float& h, const float& i);

        // Matrix 4x4 constructor.
        Matrix(const float& a, const float& b, const float& c, const float& d,
               const float& e, const float& f, const float& g, const float& h,
               const float& i, const float& j, const float& k, const float& l,
               const float& M, const float& n, const float& o, const float& p);

        // Matrix 4x4 constructor (from 2x2 matrices).
        Matrix(const Mat2& a, const Mat2& b, const Mat2& c, const Mat2& d);

        ~Matrix() {}

        // ----- Operators ----- //

        // Matrix bracket operators.
        const float* operator[](int index) const { return m[index]; }
              float* operator[](int index)       { return m[index]; }

        // Matrix copy.
        Matrix<R, C> operator=(const Matrix<R, C>& matrix);
        Matrix<R, C> operator=(float** matrix);

        // Matrix addition.
        Matrix<R, C> operator+(const float& val) const;
        Matrix<R, C> operator+(const Matrix<R, C>& matrix) const;

        // Matrix substraction and inversion.
        Matrix<R, C> operator-() const;
        Matrix<R, C> operator-(const float& val) const;
        Matrix<R, C> operator-(const Matrix<R, C>& matrix) const;


        // Matrix multiplication.
        Matrix<R, C> operator*(const float& val) const;
        template<int _R, int _C>
        Matrix<(R > _R ? R : _R), (C > _C ? C : _C)> operator*(const Matrix<_R, _C>& matrix) const;

        // Matrix division by a scalar.
        Matrix<R, C> operator/(const float& val) const;

        // Matrix addition assignement.
        void operator+=(const float& val);
        void operator+=(const Matrix<R, C>& matrix);

        // Matrix substraction assignement.
        void operator-=(const float& val);
        void operator-=(const Matrix<R, C>& matrix);

        // Matrix multiplication assignement.
        void operator*=(const float& val);
        template<int _R, int _C>
        void operator*=(const Matrix<_R, _C>& matrix)
        {
            *this = *this * matrix;
        }

        // Matrix power.
        Matrix<R, C> operator^(const float& n) const;

        // ----- Methods ----- //

        // Getters.
        int   getRows()                    const { return R; }
        int   getColumns()                 const { return C; }
        float getMatrixValue(int i, int j) const { return m[i][j]; }
        bool  isSquare()                   const { return R == C; }
        bool  isIdentity() const;

        // Determinants.
        float det2() const;
        float det3() const;
        float det4() const;

        // Inverses.
        Mat2 inv2() const;
        Mat3 inv3() const;
        Mat4 inv4() const;

        // Transposition.
        Matrix<R, C> transpose() const;

        // Conversion to angle axis rotation (matrix must be 3x3 or 4x4 rotation only).
        AngleAxis  toAngleAxis (); 

        // Conversion to quaternion (matrix must be 3x3 or 4x4 rotation only).
        Quaternion toQuaternion(); 

        // Prints matrix contents.
        void print(const bool& showSize = true) const;

        // Returns matrix contents as string.
        std::string printStr(const bool& showSize = true) const;
    };

    Mat4 getTranslationMatrix(const Vector3& translation);
    Mat4 getScaleMatrix      (const Vector3& scale);
    Mat4 getXRotationMatrix  (const float& angle);
    Mat4 getYRotationMatrix  (const float& angle);
    Mat4 getZRotationMatrix  (const float& angle);
    Mat4 getRotationMatrix   (const Vector3& rotation, const bool& reverse = false);
    Mat4 getTransformMatrix  (const Vector3& position, const Vector3& rotation, const Vector3& scale, const bool& reverse = false, const bool& transformNormals = false);
}