#include "Maths.h"
using namespace Maths;


template<int R, int C>
float* Maths::Matrix<R, C>::floatPtr()
{
    return &m[0][0];
}


// ---------- MATRIX CONSTRUCTORS ---------- //

template<int R, int C>
Maths::Matrix<R, C>::Matrix(const bool& identity)
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

template<int R, int C>
Maths::Matrix<R, C>::Matrix(const Matrix<R, C>& matrix)
{
    assert(R >= 2 && C >= 2/*, "Matrix size is too small."*/);
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            m[i][j] = matrix[i][j];
}

template<int R, int C>
Maths::Matrix<R, C>::Matrix(const float matrix[R][C])
{
    assert(R > 2 && C > 2/*, "Matrix size is too small."*/);
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            m[i][j] = matrix[i][j];
}

template<int R, int C>
Maths::Matrix<R, C>::Matrix(const float& a, const float& b, const float& c, const float& d)
{
    assert(R == 2 && C == 2/*, "Matrix size doesn't correspond to the number of initializers."*/);
    m[0][0] = a; m[0][1] = b;
    m[1][0] = c; m[1][1] = d;
}

template<int R, int C>
Maths::Matrix<R, C>::Matrix(const float& a, const float& b, const float& c, 
                            const float& d, const float& e, const float& f, 
                            const float& g, const float& h, const float& i)
{
    assert(R == 3 && C == 3/*, "Matrix size doesn't correspond to the number of initializers."*/);
    m[0][0] = a; m[0][1] = b; m[0][2] = c;
    m[1][0] = d; m[1][1] = e; m[1][2] = f;
    m[2][0] = g; m[2][1] = h; m[2][2] = i;
}

template<int R, int C>
Maths::Matrix<R, C>::Matrix(const float& a, const float& b, const float& c, const float& d, 
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

template<int R, int C>
Maths::Matrix<R, C>::Matrix(const Mat2& a, const Mat2& b, const Mat2& c, const Mat2& d)
{
    assert(R == 4 && C == 4/*, "Matrix size doesn't correspond to the number of initializers."*/);
    m[0][0] = a[0][0]; m[0][1] = a[0][1]; m[0][2] = b[0][0]; m[0][3] = b[0][1];
    m[1][0] = a[1][0]; m[1][1] = a[1][1]; m[1][2] = b[1][0]; m[1][3] = b[1][1];
    m[2][0] = c[0][0]; m[2][1] = c[0][1]; m[2][2] = d[0][0]; m[2][3] = d[0][1];
    m[3][0] = c[1][0]; m[3][1] = c[1][1]; m[3][2] = d[1][0]; m[3][3] = d[1][1];
}


// ---------- MATRIX OPERATORS ---------- //

template<int R, int C>
Matrix<R, C> Maths::Matrix<R, C>::operator=(const Matrix<R, C>& matrix)
{
    if (&matrix == this) return *this;

    // Matrix content copy
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            m[i][j] = matrix[i][j];

    return *this;
}

template<int R, int C>
Matrix<R, C> Maths::Matrix<R, C>::operator=(float** matrix)
{
    assert(sizeof(matrix) / sizeof(float) == R * C/*, "The given matrix is of the wrong size."*/);

    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            m[i][j] = matrix[i][j];

    return *this;
}

template<int R, int C>
Matrix<R, C> Maths::Matrix<R, C>::operator+(const float& val) const
{
    Matrix<R, C> tmp;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            tmp[i][j] = m[i][j] + val;
    return tmp;
}

template<int R, int C>
inline Matrix<R, C> Matrix<R, C>::operator+(const Matrix<R, C>& matrix) const
{
    Matrix<_R, _C> tmp;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            tmp[i][j] = m[i][j] + matrix[i][j];
    return tmp;
}

template<int R, int C>
Matrix<R, C> Maths::Matrix<R, C>::operator-() const
{
    Matrix<R, C> tmp;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            tmp[i][j] = -m[i][j];
    return tmp;
}

template<int R, int C>
Matrix<R, C> Maths::Matrix<R, C>::operator-(const float& val) const
{
    Matrix<R, C> tmp;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            tmp[i][j] = m[i][j] - val;
    return tmp;
}

template<int R, int C>
Matrix<R, C> Maths::Matrix<R, C>::operator-(const Matrix<R, C>& matrix) const
{
    Matrix<R, C> tmp;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            tmp[i][j] = m[i][j] - matrix[i][j];
    return tmp;
}

template<int R, int C>
Matrix<R, C> Maths::Matrix<R, C>::operator*(const float& val) const
{
    Matrix<R, C> tmp;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            tmp[i][j] = m[i][j] * val;
    return tmp;
}

template<int R, int C> template<int _R, int _C>
Matrix<(R>_R ? R : _R), (C>_C ? C : _C)> Matrix<R, C>::operator*(const Matrix<_R, _C>& matrix) const
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

template<int R, int C>
Matrix<R, C> Maths::Matrix<R, C>::operator/(const float& val) const
{
    Matrix<R, C> tmp;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            tmp[i][j] = m[i][j] / val;
    return tmp;
}

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

template<int R, int C>
void Maths::Matrix<R, C>::operator-=(const float& val)
{
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            m[i][j] -= val;
}

template<int R, int C>
void Maths::Matrix<R, C>::operator-=(const Matrix<R, C>& matrix)
{
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            m[i][j] -= matrix[i][j];
}

template<int R, int C>
void Maths::Matrix<R, C>::operator*=(const float& val)
{
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            m[i][j] *= val;
}

template<int R, int C>
Matrix<R, C> Maths::Matrix<R, C>::operator^(const float& n) const
{
    Matrix<R, C> tmp;
    for (int n0 = 0; n0 < n; n0++)
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)
                tmp[i][j] *= m[i][j];
    return tmp;
}


// ---------- MATRIX METHODS ---------- //

template<int R, int C>
bool Maths::Matrix<R, C>::isIdentity() const
{
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            if ((i != j && m[i][j] != 0) || (i == j && m[i][j] != 1))
                return false;
    return true;
}

template<int R, int C>
float Maths::Matrix<R, C>::det2() const
{
    return (m[0][0] * m[1][1]) - (m[0][1] * m[1][0]);
}

template<int R, int C>
float Maths::Matrix<R, C>::det3() const
{
    return m[0][0] * Mat2 { m[1][1], m[1][2], m[2][1], m[2][2] }.det2() -
           m[0][1] * Mat2 { m[1][0], m[1][2], m[2][0], m[2][2] }.det2() +
           m[0][2] * Mat2 { m[1][0], m[1][1], m[2][0], m[2][1] }.det2();
}

template<int R, int C>
float Maths::Matrix<R, C>::det4() const
{
    Mat3 a(m[1][1], m[1][2], m[1][3], m[2][1], m[2][2], m[2][3], m[3][1], m[3][2], m[3][3]);
    Mat3 b(m[1][0], m[1][2], m[1][3], m[2][0], m[2][2], m[2][3], m[3][0], m[3][2], m[3][3]);
    Mat3 c(m[1][0], m[1][1], m[1][3], m[2][0], m[2][1], m[2][3], m[3][0], m[3][1], m[3][3]);
    Mat3 d(m[1][0], m[1][1], m[1][2], m[2][0], m[2][1], m[2][2], m[3][0], m[3][1], m[3][2]);

    return (a.det3() * m[0][0] - b.det3() * m[0][1] + c.det3() * m[0][2] - d.det3() * m[0][3]);
}

template<int R, int C>
Mat2 Maths::Matrix<R, C>::inv2() const
{
    Mat2 val(m[1][1], -m[0][1], -m[1][0], m[0][0]);
    return val / val.det2();
}

template<int R, int C>
Mat3 Maths::Matrix<R, C>::inv3() const
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

template<int R, int C>
Mat4 Maths::Matrix<R, C>::inv4() const
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

template<int R, int C>
Matrix<R, C> Maths::Matrix<R, C>::transpose() const
{
    Matrix<C, R> result;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            result[j][i] = m[i][j];
    return result;
}

template<int R, int C>
inline AngleAxis Matrix<R, C>::toAngleAxis()
{
    assert(R == C && (R == 3 || R == 4));
    const float angle = acos((m[0][0] + m[1][1] + m[2][2] - 1) / 2);
    const float n     = 2 * sin(angle);

    if (angle == 0 || angle == PI) printf("Rot mat to angle axis is probably wrong...");

    return AngleAxis(
        angle,
        {
            (m[2][1]-m[1][2]) / n,
            (m[0][2]-m[2][0]) / n,
            (m[1][0]-m[0][1]) / n
        }
    );
}

template<int R, int C>
Quaternion Maths::Matrix<R, C>::toQuaternion()
{
    assert(R == C && (R == 3 || R == 4));
    const float w = sqrt(1 + m[0][0] + m[1][1] + m[2][2]) / 2;
    return Quaternion(
        w,
        (m[2][1]-m[1][2]) / (4*w),
        (m[0][2]-m[2][0]) / (4*w),
        (m[1][0]-m[0][1]) / (4*w)
    );
}

template<int R, int C>
void Maths::Matrix<R, C>::print(const bool& showSize) const
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

template<int R, int C>
std::string Maths::Matrix<R, C>::printStr(const bool& showSize) const
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


// ---------- MATRIX STATIC METHODS ---------- //

Mat4 Maths::getTranslationMatrix(const Vector3& translation)
{
    return Mat4(1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                -translation.x, translation.y, translation.z, 1);
}

Mat4 Maths::getScaleMatrix(const Vector3& scale)
{
    return Mat4(scale.x, 0, 0, 0,
                0, scale.y, 0, 0,
                0, 0, scale.z, 0,
                0, 0, 0, 1);
}

Mat4 Maths::getXRotationMatrix(const float& angle)
{
    return Mat4(1, 0, 0, 0,
                0, cosf(angle), sinf(angle), 0,
                0, -sinf(angle), cosf(angle), 0,
                0, 0, 0, 1);
}

Mat4 Maths::getYRotationMatrix(const float& angle)
{
    return Mat4(cosf(angle), 0, -sinf(angle), 0,
                0, 1, 0, 0,
                sinf(angle), 0, cosf(angle), 0,
                0, 0, 0, 1);
}

Mat4 Maths::getZRotationMatrix(const float& angle)
{
    return Mat4(cosf(angle), sinf(angle), 0, 0,
                -sinf(angle), cosf(angle), 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1);
}

Mat4 Maths::getRotationMatrix(const Vector3& rotation, const bool& reverse)
{
    // For cameras.
    if (reverse)
    {
        return getYRotationMatrix(rotation.y) *
               getXRotationMatrix(-rotation.x) *
               getZRotationMatrix(rotation.z);
    }
    // For objects in world space.
    else
    {
        return getZRotationMatrix(rotation.z) *
               getXRotationMatrix(-rotation.x) *
               getYRotationMatrix(rotation.y);
    }
}

Mat4 Maths::getTransformMatrix(const Vector3& position, const Vector3& rotation, const Vector3& scale, const bool& reverse, const bool& transformNormals)
{
    // For cameras.
    if (reverse)
    {
        return getTranslationMatrix(position)   *
               getYRotationMatrix  (rotation.y) *
               getXRotationMatrix  (rotation.x) *
               getZRotationMatrix  (rotation.z) *
               getScaleMatrix      (scale);
    }
    // For normals.
    else if (transformNormals)
    {
        return getTransformMatrix(position, rotation, scale).inv4().transpose();
    }
    // For objects in world space.
    else
    {
        return getScaleMatrix      (scale)      *
               getZRotationMatrix  (rotation.z) *
               getXRotationMatrix  (rotation.x) *
               getYRotationMatrix  (rotation.y) *
               getTranslationMatrix(position);
    }
}