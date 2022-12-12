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
    private:
        float M[R][C];
        
    public:
        // ----- Constructors ----- //

        Matrix(const bool& identity = false); // Default constructor.
        Matrix(const Matrix<R, C>& matrix);   // Copy operator.
        Matrix(const float matrix[R][C]);     // Matrix from float 2D array.

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
               const float& m, const float& n, const float& o, const float& p);

        // Matrix 4x4 constructor (from 2x2 matrices).
        Matrix(const Mat2& a, const Mat2& b, const Mat2& c, const Mat2& d);

        
        // ----- Operators ----- //

        // Matrix bracket operators.
        const float* operator[](int index) const { return M[index]; }
              float* operator[](int index)       { return M[index]; }

        // Matrix copy.
        Matrix<R, C>& operator=(const Matrix<R, C>& matrix);
        Matrix<R, C>& operator=(float** matrix);

        // Matrix addition.
        Matrix<R, C> operator+(const float& val) const;
        Matrix<R, C> operator+(const Matrix<R, C>& matrix) const;

        // Matrix subtraction and inversion.
        Matrix<R, C> operator-() const;
        Matrix<R, C> operator-(const float& val) const;
        Matrix<R, C> operator-(const Matrix<R, C>& matrix) const;


        // Matrix multiplication.
        Matrix<R, C> operator*(const float& val) const;
        template<int R2, int C2>
        Matrix<(R > R2 ? R : R2), (C > C2 ? C : C2)> operator*(const Matrix<R2, C2>& matrix) const;

        // Matrix division by a scalar.
        Matrix<R, C> operator/(const float& val) const;

        // Matrix addition assignment.
        void operator+=(const float& val);
        void operator+=(const Matrix<R, C>& matrix);

        // Matrix subtraction assignment.
        void operator-=(const float& val);
        void operator-=(const Matrix<R, C>& matrix);

        // Matrix multiplication assignment.
        void operator*=(const float& val);
        template<int R2, int C2>
        void operator*=(const Matrix<R2, C2>& matrix);

        // Matrix power.
        Matrix<R, C> operator^(const float& n) const;
        Matrix<R, C> Pow      (const float& n) const;

        // ----- Methods ----- //

        // Getters.
        float* AsPtr();                                               // Returns a pointer to the matrix's float array.
        int    GetRows()                    const { return R; }       // Returns the matrix's number of rows.
        int    GetColumns()                 const { return C; }       // Returns the matrix's number of columns.
        float  GetMatrixValue(int i, int j) const { return M[i][j]; } // Returns the element at the given indices.
        bool   IsSquare()                   const { return R == C; }  // Returns true if the matrix is square, false if not.
        bool   IsIdentity() const;                                    // Returns true if the matrix is identity.

        // Determinants.
        float Det2() const; // Returns a 2x2 matrix's determinant.
        float Det3() const; // Returns a 3x3 matrix's determinant.
        float Det4() const; // Returns a 4x4 matrix's determinant.

        // Inverses.
        Mat2 Inv2() const; // Returns the inverse of a 2x2 matrix's.
        Mat3 Inv3() const; // Returns the inverse of a 3x3 matrix's.
        Mat4 Inv4() const; // Returns the inverse of a 4x4 matrix's.

        // Transposition.
        void         Transpose    ();       // Transposes the matrix.
        Matrix<R, C> GetTransposed() const; // Returns a transposed copy of this matrix.

        // Conversions.
        AngleAxis   ToAngleAxis () const;                        // Conversion to angle axis rotation (matrix must be 3x3 or 4x4 rotation only).
        Quaternion  ToQuaternion() const;                        // Conversion to quaternion (matrix must be 3x3 or 4x4 rotation only).
        std::string ToString(const bool& showSize = true) const; // Returns matrix contents as string.
        void        Print   (const bool& showSize = true) const; // Prints matrix contents.
    };

    Mat4 GetTranslationMatrix(const Vector3& translation);
    Mat4 GetXRotationMatrix  (const float& angle);
    Mat4 GetYRotationMatrix  (const float& angle);
    Mat4 GetZRotationMatrix  (const float& angle);
    Mat4 GetRotationMatrix   (const Vector3& rotation, const bool& reverse = false);
    Mat4 GetScaleMatrix      (const Vector3& scale);
    Mat4 GetTransformMatrix  (const Vector3& position, const Vector3&    rotation, const Vector3& scale, const bool& reverse = false, const bool& transformNormals = false);
    Mat4 GetTransformMatrix  (const Vector3& position, const Quaternion& rotation, const Vector3& scale, const bool& reverse = false, const bool& transformNormals = false);
}

#include "Matrix.inl"
