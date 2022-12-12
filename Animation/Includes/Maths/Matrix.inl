#include "Matrix.h"
#include "AngleAxis.h"
#include "Quaternion.h"
using namespace Maths;


// ---------- MATRIX CONSTRUCTORS ---------- //

// Default constructor.
template<int R, int C>
inline Matrix<R, C>::Matrix(const bool& identity)
{
    assert(R >= 2 && C >= 2/*, "Matrix size is too small."*/);

    if (!identity)
    {
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)
                M[i][j] = 0;
    }
    else
    {
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)
                if (i == j)
                    M[i][j] = 1;
                else
                    M[i][j] = 0;
    }
}

// Copy operator.
template<int R, int C>
inline Matrix<R, C>::Matrix(const Matrix<R, C>& matrix)
{
    assert(R >= 2 && C >= 2/*, "Matrix size is too small."*/);
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            M[i][j] = matrix[i][j];
}

// Matrix from float 2D array.
template<int R, int C>
inline Matrix<R, C>::Matrix(const float matrix[R][C])
{
    assert(R > 2 && C > 2/*, "Matrix size is too small."*/);
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            M[i][j] = matrix[i][j];
}

// Matrix 2x2 constructor.
template<int R, int C>
inline Matrix<R, C>::Matrix(const float& a, const float& b, const float& c, const float& d)
{
    assert(R == 2 && C == 2/*, "Matrix size doesn't correspond to the number of initializers."*/);
    M[0][0] = a; M[0][1] = b;
    M[1][0] = c; M[1][1] = d;
}

// Matrix 3x3 constructor.
template<int R, int C>
inline Matrix<R, C>::Matrix(const float& a, const float& b, const float& c, 
                            const float& d, const float& e, const float& f, 
                            const float& g, const float& h, const float& i)
{
    assert(R == 3 && C == 3/*, "Matrix size doesn't correspond to the number of initializers."*/);
    M[0][0] = a; M[0][1] = b; M[0][2] = c;
    M[1][0] = d; M[1][1] = e; M[1][2] = f;
    M[2][0] = g; M[2][1] = h; M[2][2] = i;
}

// Matrix 4x4 constructor.
template<int R, int C>
inline Matrix<R, C>::Matrix(const float& a, const float& b, const float& c, const float& d, 
                            const float& e, const float& f, const float& g, const float& h, 
                            const float& i, const float& j, const float& k, const float& l, 
                            const float& m, const float& n, const float& o, const float& p)
{
    assert(R == 4 && C == 4/*, "Matrix size doesn't correspond to the number of initializers."*/);
    M[0][0] = a; M[0][1] = b; M[0][2] = c; M[0][3] = d;
    M[1][0] = e; M[1][1] = f; M[1][2] = g; M[1][3] = h;
    M[2][0] = i; M[2][1] = j; M[2][2] = k; M[2][3] = l;
    M[3][0] = m; M[3][1] = n; M[3][2] = o; M[3][3] = p;
}

// Matrix 4x4 constructor (from 2x2 matrices).
template<int R, int C>
inline Matrix<R, C>::Matrix(const Mat2& a, const Mat2& b, const Mat2& c, const Mat2& d)
{
    assert(R == 4 && C == 4/*, "Matrix size doesn't correspond to the number of initializers."*/);
    M[0][0] = a[0][0]; M[0][1] = a[0][1]; M[0][2] = b[0][0]; M[0][3] = b[0][1];
    M[1][0] = a[1][0]; M[1][1] = a[1][1]; M[1][2] = b[1][0]; M[1][3] = b[1][1];
    M[2][0] = c[0][0]; M[2][1] = c[0][1]; M[2][2] = d[0][0]; M[2][3] = d[0][1];
    M[3][0] = c[1][0]; M[3][1] = c[1][1]; M[3][2] = d[1][0]; M[3][3] = d[1][1];
}


// ---------- MATRIX OPERATORS ---------- //

// Matrix copy.
template<int R, int C>
inline Matrix<R, C>& Matrix<R, C>::operator=(const Matrix<R, C>& matrix)
{
    if (&matrix == this) return *this;

    // Matrix content copy
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            M[i][j] = matrix[i][j];

    return *this;
}

template<int R, int C>
inline Matrix<R, C>& Matrix<R, C>::operator=(float** matrix)
{
    assert(sizeof(matrix) / sizeof(float) == R * C/*, "The given matrix is of the wrong size."*/);

    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            M[i][j] = matrix[i][j];

    return *this;
}

// Matrix addition.
template<int R, int C>
inline Matrix<R, C> Matrix<R, C>::operator+(const float& val) const
{
    Matrix<R, C> tmp;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            tmp[i][j] = M[i][j] + val;
    return tmp;
}

template<int R, int C>
inline Matrix<R, C> Matrix<R, C>::operator+(const Matrix<R, C>& matrix) const
{
    Matrix<_R, _C> tmp;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            tmp[i][j] = M[i][j] + matrix[i][j];
    return tmp;
}

// Matrix subtraction and inversion.
template<int R, int C>
inline Matrix<R, C> Matrix<R, C>::operator-() const
{
    Matrix<R, C> tmp;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            tmp[i][j] = -M[i][j];
    return tmp;
}

template<int R, int C>
inline Matrix<R, C> Matrix<R, C>::operator-(const float& val) const
{
    Matrix<R, C> tmp;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            tmp[i][j] = M[i][j] - val;
    return tmp;
}

template<int R, int C>
inline Matrix<R, C> Matrix<R, C>::operator-(const Matrix<R, C>& matrix) const
{
    Matrix<R, C> tmp;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            tmp[i][j] = M[i][j] - matrix[i][j];
    return tmp;
}

// Matrix multiplication.
template<int R, int C>
inline Matrix<R, C> Matrix<R, C>::operator*(const float& val) const
{
    Matrix<R, C> tmp;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            tmp[i][j] = M[i][j] * val;
    return tmp;
}

template<int R, int C> template<int R2, int C2>
inline Matrix<(R > R2 ? R : R2), (C > C2 ? C : C2)> Matrix<R, C>::operator*(const Matrix<R2, C2>& matrix) const
{
    assert(C == R2/*, "Given matrices cannot be multiplied."*/);

    Matrix<(R > R2 ? R : R2), (C > C2 ? C : C2)> result;
    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C2; j++)
        {
            result[i][j] = 0;
            for (int k = 0; k < R2; k++)
                result[i][j] += M[i][k] * matrix[k][j];
        }
    }
    return result;
}

// Matrix division by a scalar.
template<int R, int C>
inline Matrix<R, C> Matrix<R, C>::operator/(const float& val) const
{
    Matrix<R, C> tmp;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            tmp[i][j] = M[i][j] / val;
    return tmp;
}

// Matrix addition assignment.
template<int R, int C>
inline void Matrix<R, C>::operator+=(const float& val)
{
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            M[i][j] += val;
}

template<int R, int C>
inline void Matrix<R, C>::operator+=(const Matrix<R, C>& matrix)
{
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            M[i][j] += matrix[i][j];
}

// Matrix subtraction assignment.
template<int R, int C>
inline void Matrix<R, C>::operator-=(const float& val)
{
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            M[i][j] -= val;
}

template<int R, int C>
inline void Matrix<R, C>::operator-=(const Matrix<R, C>& matrix)
{
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            M[i][j] -= matrix[i][j];
}

// Matrix multiplication assignment.
template<int R, int C>
inline void Matrix<R, C>::operator*=(const float& val)
{
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            M[i][j] *= val;
}

template <int R, int C>
template <int R2, int C2>
void Matrix<R, C>::operator*=(const Matrix<R2, C2>& matrix)
{
    *this = *this * matrix;
}

// Matrix power.
template<int R, int C>
inline Matrix<R, C> Matrix<R, C>::operator^(const float& n) const
{
    Matrix<R, C> tmp;
    for (int n0 = 0; n0 < n; n0++)
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)
                tmp[i][j] *= M[i][j];
    return tmp;
}

template <int R, int C>
Matrix<R, C> Matrix<R, C>::Pow(const float& n) const
{
    return *this ^ n;
}


// ---------- MATRIX METHODS ---------- //

// Getters.
template<int R, int C>
inline float* Matrix<R, C>::AsPtr()
{
    return &M[0][0];
}

template<int R, int C>
inline bool Matrix<R, C>::IsIdentity() const
{
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            if ((i != j && M[i][j] != 0) || (i == j && M[i][j] != 1))
                return false;
    return true;
}

// Determinants.
template<int R, int C>
inline float Matrix<R, C>::Det2() const
{
    return (M[0][0] * M[1][1]) - (M[0][1] * M[1][0]);
}

template<int R, int C>
inline float Matrix<R, C>::Det3() const
{
    return M[0][0] * Mat2 { M[1][1], M[1][2], M[2][1], M[2][2] }.Det2() -
           M[0][1] * Mat2 { M[1][0], M[1][2], M[2][0], M[2][2] }.Det2() +
           M[0][2] * Mat2 { M[1][0], M[1][1], M[2][0], M[2][1] }.Det2();
}

template<int R, int C>
inline float Matrix<R, C>::Det4() const
{
    Mat3 a(M[1][1], M[1][2], M[1][3], M[2][1], M[2][2], M[2][3], M[3][1], M[3][2], M[3][3]);
    Mat3 b(M[1][0], M[1][2], M[1][3], M[2][0], M[2][2], M[2][3], M[3][0], M[3][2], M[3][3]);
    Mat3 c(M[1][0], M[1][1], M[1][3], M[2][0], M[2][1], M[2][3], M[3][0], M[3][1], M[3][3]);
    Mat3 d(M[1][0], M[1][1], M[1][2], M[2][0], M[2][1], M[2][2], M[3][0], M[3][1], M[3][2]);

    return (a.Det3() * M[0][0] - b.Det3() * M[0][1] + c.Det3() * M[0][2] - d.Det3() * M[0][3]);
}

// Inverses.
template<int R, int C>
inline Mat2 Matrix<R, C>::Inv2() const
{
    Mat2 val(M[1][1], -M[0][1], -M[1][0], M[0][0]);
    return val / val.Det2();
}

template<int R, int C>
inline Mat3 Matrix<R, C>::Inv3() const
{
    Mat4 val(M[0][0], M[0][1], M[0][2], 0,
             M[1][0], M[1][1], M[1][2], 0,
             M[2][0], M[2][1], M[2][2], 0,
             0, 0, 0, 1);
    val = val.Inv4();
    Mat3 result(val.M[0][0], val.M[0][1], val.M[0][2],
                val.M[1][0], val.M[1][1], val.M[1][2],
                val.M[2][0], val.M[2][1], val.M[2][2]);
    return result;
}

template<int R, int C>
inline Mat4 Matrix<R, C>::Inv4() const
{
    Mat2 a(M[0][0], M[0][1], M[1][0], M[1][1]);
    Mat2 b(M[0][2], M[0][3], M[1][2], M[1][3]);
    Mat2 c(M[2][0], M[2][1], M[3][0], M[3][1]);
    Mat2 d(M[2][2], M[2][3], M[3][2], M[3][3]);

    Mat4 result =
    {
        (a - b * d.Inv2() * c).Inv2(), -(a - b * d.Inv2() * c).Inv2() * b * d.Inv2(),
        -(d - c * a.Inv2() * b).Inv2() * c * a.Inv2(), (d - c * a.Inv2() * b).Inv2()
    };

    return result;
}

// Transposition.
template <int R, int C>
void Matrix<R, C>::Transpose()
{
    *this = GetTransposed();
}

template<int R, int C>
inline Matrix<R, C> Matrix<R, C>::GetTransposed() const
{
    Matrix<C, R> result;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            result[j][i] = M[i][j];
    return result;
}


// Conversions.
template<int R, int C>
inline AngleAxis Matrix<R, C>::ToAngleAxis() const
{
    assert(R == C && (R == 3 || R == 4));
    const float angle = acos((M[0][0] + M[1][1] + M[2][2] - 1) / 2);
    const float n     = 2 * sin(angle);

    if (angle == 0 || angle == PI) printf("Rot mat to angle axis is probably wrong...");

    return AngleAxis(
        angle,
        {
            (M[2][1]-M[1][2]) / n,
            (M[0][2]-M[2][0]) / n,
            (M[1][0]-M[0][1]) / n
        }
    );
}

template<int R, int C>
inline Quaternion Matrix<R, C>::ToQuaternion() const
{
    assert(R == C && (R == 3 || R == 4));
    const float w = sqrt(1 + M[0][0] + M[1][1] + M[2][2]) / 2;
    return Quaternion(
        w,
        (M[2][1]-M[1][2]) / (4*w),
        (M[0][2]-M[2][0]) / (4*w),
        (M[1][0]-M[0][1]) / (4*w)
    );
}

template<int R, int C>
inline std::string Matrix<R, C>::ToString(const bool& showSize) const
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
            temp << std::fixed << M[i][j];
            output += temp.str() + ", ";
        }
        output += "\n";
    }
    return output + "\n";
}

template<int R, int C>
inline void Matrix<R, C>::Print(const bool& showSize) const
{
    // Print data
    if (showSize)
        printf("Matrix<%d,%d>\n", R, C);

    // Print content
    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++) printf("%.2f, ", M[i][j]);
        printf("\n");
    }
    printf("\n");
}
