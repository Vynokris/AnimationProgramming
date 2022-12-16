#include <cassert>
#include <sstream>
#include <iostream>

#include "Matrix.h"
#include "MathConstants.h"
#include "AngleAxis.h"
#include "Quaternion.h"


// ----- Constructors ----- //

// Default constructor.
template<int R, int C>
Maths::Matrix<R, C>::Matrix(const bool& identity)
{
    assert(R >= 2 && C >= 2/*, "Maths::Matrix size is too small."*/);

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
template<int R, int C>
Maths::Matrix<R, C>::Matrix(const Matrix<R, C>& matrix)
{
    assert(R >= 2 && C >= 2/*, "Maths::Matrix size is too small."*/);
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            m[i][j] = matrix[i][j];
}

// Matrix from float 2D array.
template<int R, int C>
Maths::Matrix<R, C>::Matrix(const float matrix[R][C])
{
    assert(R > 2 && C > 2/*, "Maths::Matrix size is too small."*/);
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            m[i][j] = matrix[i][j];
}

// Matrix from euler angles.
template <int R, int C>
Maths::Matrix<R, C>::Matrix(const Vector3& eulerAngles)
{
    assert(R == 4 && C == 4);
    *this = Quaternion::FromEuler(eulerAngles).ToMatrix();
}

// Matrix from angle-axis.
template <int R, int C>
Maths::Matrix<R, C>::Matrix(const AngleAxis& angleAxis)
{
    assert(R == 4 && C == 4);
    *this = angleAxis.ToMatrix();
}

// Matrix from quaternion.
template <int R, int C>
Maths::Matrix<R, C>::Matrix(const Quaternion& quaternion)
{
    assert(R == 4 && C == 4);
    *this = quaternion.ToMatrix();
}

// Matrix 2x2 constructor.
template<int R, int C>
Maths::Matrix<R, C>::Matrix(const float& m00, const float& m01, const float& m10, const float& m11)
{
    assert(R == 2 && C == 2/*, "Maths::Matrix size doesn't correspond to the number of initializers."*/);
    m[0][0] = m00; m[0][1] = m01;
    m[1][0] = m10; m[1][1] = m11;
}

// Matrix 3x3 constructor.
template<int R, int C>
Maths::Matrix<R, C>::Matrix(const float& m00, const float& m01, const float& m02, 
                            const float& m10, const float& m11, const float& m12, 
                            const float& m20, const float& m21, const float& m22)
{
    assert(R == 3 && C == 3/*, "Maths::Matrix size doesn't correspond to the number of initializers."*/);
    m[0][0] = m00; m[0][1] = m01; m[0][2] = m02;
    m[1][0] = m10; m[1][1] = m11; m[1][2] = m12;
    m[2][0] = m20; m[2][1] = m21; m[2][2] = m22;
}

// Matrix 4x4 constructor.
template<int R, int C>
Maths::Matrix<R, C>::Matrix(const float& m00, const float& m01, const float& m02, const float& m03, 
                            const float& m10, const float& m11, const float& m12, const float& m13, 
                            const float& m20, const float& m21, const float& m22, const float& m23, 
                            const float& m30, const float& m31, const float& m32, const float& m33)
{
    assert(R == 4 && C == 4/*, "Maths::Matrix size doesn't correspond to the number of initializers."*/);
    m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = m03;
    m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = m13;
    m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = m23;
    m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
}

// Matrix 4x4 constructor (from 2x2 matrices).
template<int R, int C>
Maths::Matrix<R, C>::Matrix(const Mat2& a, const Mat2& b, const Mat2& c, const Mat2& d)
{
    assert(R == 4 && C == 4/*, "Maths::Matrix size doesn't correspond to the number of initializers."*/);
    m[0][0] = a[0][0]; m[0][1] = a[0][1]; m[0][2] = b[0][0]; m[0][3] = b[0][1];
    m[1][0] = a[1][0]; m[1][1] = a[1][1]; m[1][2] = b[1][0]; m[1][3] = b[1][1];
    m[2][0] = c[0][0]; m[2][1] = c[0][1]; m[2][2] = d[0][0]; m[2][3] = d[0][1];
    m[3][0] = c[1][0]; m[3][1] = c[1][1]; m[3][2] = d[1][0]; m[3][3] = d[1][1];
}


// ----- Static constructors ----- //

// Translation matrix.
template <int R, int C>
Maths::Matrix<R, C> Maths::Matrix<R, C>::FromTranslation(const Vector3& translation)
{
    return Mat4(1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                translation.x, translation.y, translation.z, 1);
}

// Rotation matrices.
template <int R, int C> Maths::Matrix<R, C> Maths::Matrix<R, C>::FromPitch     (const float&      angle     ) { return AngleAxis(angle, { 1, 0, 0 }).ToMatrix(); }
template <int R, int C> Maths::Matrix<R, C> Maths::Matrix<R, C>::FromRoll      (const float&      angle     ) { return AngleAxis(angle, { 0, 1, 0 }).ToMatrix(); }
template <int R, int C> Maths::Matrix<R, C> Maths::Matrix<R, C>::FromYaw       (const float&      angle     ) { return AngleAxis(angle, { 0, 0, 1 }).ToMatrix(); }
template <int R, int C> Maths::Matrix<R, C> Maths::Matrix<R, C>::FromEuler     (const Vector3&    angles    ) { return Quaternion::FromEuler(angles).ToMatrix(); }
template <int R, int C> Maths::Matrix<R, C> Maths::Matrix<R, C>::FromAngleAxis (const AngleAxis&  angleAxis ) { return angleAxis .ToMatrix(); }
template <int R, int C> Maths::Matrix<R, C> Maths::Matrix<R, C>::FromQuaternion(const Quaternion& quaternion) { return quaternion.ToMatrix(); }

// Scale matrix.
template <int R, int C>
Maths::Matrix<R, C> Maths::Matrix<R, C>::FromScale(const Vector3& scale)
{
    return Mat4(scale.x, 0, 0, 0,
                0, scale.y, 0, 0,
                0, 0, scale.z, 0,
                0, 0, 0, 1);
}

// Transform matrix.
template <int R, int C>
Maths::Matrix<R, C> Maths::Matrix<R, C>::FromTransform(const Vector3& pos, const Quaternion& rot, const Vector3& scale, const bool& reverse)
{
    if (reverse)
    {
        // TODO: Untested.
        return FromTranslation(pos)        *
               rot.GetInverse().ToMatrix() *
               FromScale(scale);
    }
    return FromScale(scale) *
           rot.ToMatrix()   * 
           FromTranslation(pos);
}


// ---------- MATRIX OPERATORS ---------- //

// Matrix copy.
template<int R, int C>
Maths::Matrix<R, C>& Maths::Matrix<R, C>::operator=(const Matrix& matrix)
{
    if (&matrix == this) return *this;

    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            m[i][j] = matrix[i][j];

    return *this;
}

template<int R, int C>
Maths::Matrix<R, C>& Maths::Matrix<R, C>::operator=(float** matrix)
{
    assert(sizeof(matrix) / sizeof(float) == R * C/*, "The given matrix is of the wrong size."*/);

    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            m[i][j] = matrix[i][j];

    return *this;
}

// Matrix addition.
template<int R, int C>
Maths::Matrix<R, C> Maths::Matrix<R, C>::operator+(const float& val) const
{
    Matrix tmp;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            tmp[i][j] = m[i][j] + val;
    return tmp;
}

template<int R, int C>
Maths::Matrix<R, C> Maths::Matrix<R, C>::operator+(const Matrix& matrix) const
{
    Matrix tmp;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            tmp[i][j] = m[i][j] + matrix[i][j];
    return tmp;
}

// Matrix subtraction and inversion.
template<int R, int C>
Maths::Matrix<R, C> Maths::Matrix<R, C>::operator-() const
{
    Matrix tmp;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            tmp[i][j] = -m[i][j];
    return tmp;
}

template<int R, int C>
Maths::Matrix<R, C> Maths::Matrix<R, C>::operator-(const float& val) const
{
    Matrix tmp;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            tmp[i][j] = m[i][j] - val;
    return tmp;
}

template<int R, int C>
Maths::Matrix<R, C> Maths::Matrix<R, C>::operator-(const Matrix<R, C>& matrix) const
{
    Matrix tmp;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            tmp[i][j] = m[i][j] - matrix[i][j];
    return tmp;
}

// Matrix multiplication.
template<int R, int C>
Maths::Matrix<R, C> Maths::Matrix<R, C>::operator*(const float& val) const
{
    Matrix tmp;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            tmp[i][j] = m[i][j] * val;
    return tmp;
}

template<int R, int C> template<int R2, int C2>
Maths::Matrix<(R > R2 ? R : R2), (C > C2 ? C : C2)> Maths::Matrix<R, C>::operator*(const Matrix<R2, C2>& matrix) const
{
    assert(C == R2/*, "Given matrices cannot be multiplied."*/);

    Matrix<(R > R2 ? R : R2), (C > C2 ? C : C2)> result;
    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C2; j++)
        {
            result[i][j] = 0;
            for (int k = 0; k < R2; k++)
                result[i][j] += m[i][k] * matrix[k][j];
        }
    }
    return result;
}

// Matrix division by a scalar.
template<int R, int C>
Maths::Matrix<R, C> Maths::Matrix<R, C>::operator/(const float& val) const
{
    Matrix tmp;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            tmp[i][j] = m[i][j] / val;
    return tmp;
}

// Matrix addition assignment.
template<int R, int C>
void Maths::Matrix<R, C>::operator+=(const float& val)
{
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            m[i][j] += val;
}

template<int R, int C>
void Maths::Matrix<R, C>::operator+=(const Matrix<R, C>& matrix)
{
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            m[i][j] += matrix[i][j];
}

// Matrix subtraction assignment.
template<int R, int C>
void Maths::Matrix<R, C>::operator-=(const float& val)
{
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            m[i][j] -= val;
}

template<int R, int C>
void Maths::Matrix<R, C>::operator-=(const Matrix& matrix)
{
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            m[i][j] -= matrix[i][j];
}

// Matrix multiplication assignment.
template<int R, int C>
void Maths::Matrix<R, C>::operator*=(const float& val)
{
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            m[i][j] *= val;
}

template <int R, int C>
template <int R2, int C2>
void Maths::Matrix<R, C>::operator*=(const Matrix<R2, C2>& matrix)
{
    *this = *this * matrix;
}

// Matrix power.
template<int R, int C>
Maths::Matrix<R, C> Maths::Matrix<R, C>::operator^(const float& n) const
{
    Matrix tmp;
    for (int n0 = 0; n0 < n; n0++)
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)
                tmp[i][j] *= m[i][j];
    return tmp;
}

template <int R, int C>
Maths::Matrix<R, C> Maths::Matrix<R, C>::Pow(const float& n) const
{
    return *this ^ n;
}


// ---------- MATRIX METHODS ---------- //

// Getters.
template<int R, int C>
float* Maths::Matrix<R, C>::AsPtr()
{
    return &m[0][0];
}

template<int R, int C>
bool Maths::Matrix<R, C>::IsIdentity() const
{
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if ((i != j && m[i][j] != 0) || (i == j && m[i][j] != 1))
                return false;
        }
    }
    return true;
}

template <int R, int C>
bool Maths::Matrix<R, C>::IsSymmetrical() const
{
    for (int i = 0; i < R; i++) {
        for (int j = i+1; j < C; j++) {
            if (roundInt(m[i][j]*10000)/10000.f != roundInt(m[j][i]*10000)/10000.f) // Round to 5 floating points.
                return false;
        }
    }
    return true;
}

// Determinants.
template<int R, int C>
float Maths::Matrix<R, C>::Det2() const
{
    return (m[0][0] * m[1][1]) - (m[0][1] * m[1][0]);
}

template<int R, int C>
float Maths::Matrix<R, C>::Det3() const
{
    return m[0][0] * Mat2 { m[1][1], m[1][2], m[2][1], m[2][2] }.Det2() -
           m[0][1] * Mat2 { m[1][0], m[1][2], m[2][0], m[2][2] }.Det2() +
           m[0][2] * Mat2 { m[1][0], m[1][1], m[2][0], m[2][1] }.Det2();
}

template<int R, int C>
float Maths::Matrix<R, C>::Det4() const
{
    Mat3 a(m[1][1], m[1][2], m[1][3], m[2][1], m[2][2], m[2][3], m[3][1], m[3][2], m[3][3]);
    Mat3 b(m[1][0], m[1][2], m[1][3], m[2][0], m[2][2], m[2][3], m[3][0], m[3][2], m[3][3]);
    Mat3 c(m[1][0], m[1][1], m[1][3], m[2][0], m[2][1], m[2][3], m[3][0], m[3][1], m[3][3]);
    Mat3 d(m[1][0], m[1][1], m[1][2], m[2][0], m[2][1], m[2][2], m[3][0], m[3][1], m[3][2]);

    return (a.Det3() * m[0][0] - b.Det3() * m[0][1] + c.Det3() * m[0][2] - d.Det3() * m[0][3]);
}

// Inverses.
template<int R, int C>
Maths::Mat2 Maths::Matrix<R, C>::Inv2() const
{
    Mat2 val(m[1][1], -m[0][1], -m[1][0], m[0][0]);
    return val / val.Det2();
}

template<int R, int C>
Maths::Mat3 Maths::Matrix<R, C>::Inv3() const
{
    Mat4 val(m[0][0], m[0][1], m[0][2], 0,
             m[1][0], m[1][1], m[1][2], 0,
             m[2][0], m[2][1], m[2][2], 0,
             0, 0, 0, 1);
    
    val = val.Inv4();
    
    Mat3 result(val.m[0][0], val.m[0][1], val.m[0][2],
                val.m[1][0], val.m[1][1], val.m[1][2],
                val.m[2][0], val.m[2][1], val.m[2][2]);
    
    return result;
}

template<int R, int C>
Maths::Mat4 Maths::Matrix<R, C>::Inv4() const
{
    const Mat2 a(m[0][0], m[0][1], m[1][0], m[1][1]);
    const Mat2 b(m[0][2], m[0][3], m[1][2], m[1][3]);
    const Mat2 c(m[2][0], m[2][1], m[3][0], m[3][1]);
    const Mat2 d(m[2][2], m[2][3], m[3][2], m[3][3]);

    Mat4 result =
    {
        (a - b * d.Inv2() * c).Inv2(), -(a - b * d.Inv2() * c).Inv2() * b * d.Inv2(),
        -(d - c * a.Inv2() * b).Inv2() * c * a.Inv2(), (d - c * a.Inv2() * b).Inv2()
    };

    return result;
}

// Transposition.
template <int R, int C>
void Maths::Matrix<R, C>::Transpose()
{
    *this = GetTransposed();
}

template<int R, int C>
Maths::Matrix<R, C> Maths::Matrix<R, C>::GetTransposed() const
{
    Matrix<C, R> result;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            result[j][i] = m[i][j];
    return result;
}


// Conversions.
template<int R, int C>
Maths::AngleAxis Maths::Matrix<R, C>::ToAngleAxis() const
{
    assert(R == C && (R == 3 || R == 4));
    const float angle = acos((m[0][0] + m[1][1] + m[2][2] - 1) / 2);
    const float n     = 2 * sin(angle);
    
    AngleAxis angleAxis;
    if (angle == 0.f || angle == PI) angleAxis = AngleAxis(angle, Vector3(m[1][2]-m[2][1], m[2][0]-m[0][2], m[0][1]-m[1][0]).GetNormalized().GetNegated());
    else                             angleAxis = AngleAxis(angle, Vector3(m[1][2]-m[2][1], m[2][0]-m[0][2], m[0][1]-m[1][0])/n);
    return angleAxis;
}

template<int R, int C>
Maths::Quaternion Maths::Matrix<R, C>::ToQuaternion() const
{
    const float w = -1 * sqrtf(1 + m[0][0] + m[1][1] + m[2][2]) / 2.f;
    return Quaternion(w,
                      (m[1][2] - m[2][1]) / (w * 4.f),
                      (m[2][0] - m[0][2]) / (w * 4.f),
                      (m[0][1] - m[1][0]) / (w * 4.f));
}

template<int R, int C>
std::string Maths::Matrix<R, C>::ToString(const int& precision) const
{
    std::ostringstream output;

    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            output.precision(precision);
            output << std::fixed << m[i][j];
            if (i < R-1 || j < C-1)
                output << ", ";
        }
        if (i < R-1)
            output << std::endl;
    }
    return output.str();
}
