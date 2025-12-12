#include "Matrices.h"

namespace Matrices
{
    Matrix::Matrix(int _rows, int _cols)
        : rows(_rows),
          cols(_cols)
    {
        a.assign(rows, std::vector<double>(cols, 0.0));
    }

    Matrix operator+(const Matrix& lhs, const Matrix& rhs)
    {
        int r = lhs.getRows();
        int c = lhs.getCols();
        Matrix result(r, c);
        for (int i = 0; i < r; ++i)
        {
            for (int j = 0; j < c; ++j)
            {
                result(i, j) = lhs(i, j) + rhs(i, j);
            }
        }
        return result;
    }

    Matrix operator*(const Matrix& lhs, const Matrix& rhs)
    {
        int r = lhs.getRows();
        int inner = lhs.getCols();
        int c = rhs.getCols();
        Matrix result(r, c);
        for (int i = 0; i < r; ++i)
        {
            for (int j = 0; j < c; ++j)
            {
                double sum = 0.0;
                for (int k = 0; k < inner; ++k)
                {
                    sum += lhs(i, k) * rhs(k, j);
                }
                result(i, j) = sum;
            }
        }
        return result;
    }

    bool operator==(const Matrix& lhs, const Matrix& rhs)
    {
        if (lhs.getRows() != rhs.getRows() || lhs.getCols() != rhs.getCols())
        {
            return false;
        }
        for (int i = 0; i < lhs.getRows(); ++i)
        {
            for (int j = 0; j < lhs.getCols(); ++j)
            {
                if (lhs(i, j) != rhs(i, j))
                {
                    return false;
                }
            }
        }
        return true;
    }

    bool operator!=(const Matrix& lhs, const Matrix& rhs)
    {
        return !(lhs == rhs);
    }

    std::ostream& operator<<(std::ostream& os, const Matrix& m)
    {
        for (int i = 0; i < m.getRows(); ++i)
        {
            for (int j = 0; j < m.getCols(); ++j)
            {
                os << m(i, j);
                if (j + 1 < m.getCols())
                {
                    os << ' ';
                }
            }
            if (i + 1 < m.getRows())
            {
                os << '\n';
            }
        }
        return os;
    }

    RotationMatrix::RotationMatrix(double theta)
        : Matrix(2, 2)
    {
        a[0][0] = std::cos(theta);
        a[0][1] = -std::sin(theta);
        a[1][0] = std::sin(theta);
        a[1][1] = std::cos(theta);
    }

    ScalingMatrix::ScalingMatrix(double scale)
        : Matrix(2, 2)
    {
        a[0][0] = scale;
        a[0][1] = 0.0;
        a[1][0] = 0.0;
        a[1][1] = scale;
    }

    TranslationMatrix::TranslationMatrix(double xShift, double yShift, int nCols)
        : Matrix(2, nCols)
    {
        for (int j = 0; j < nCols; ++j)
        {
            a[0][j] = xShift;
            a[1][j] = yShift;
        }
    }
}
