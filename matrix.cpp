#include "matrix.h"

matrix::matrix(int rows, int columns)
    : std::vector<Row>(rows, Row(columns))
    , rows_(rows)
    , columns_(columns)
{

}

matrix::matrix(std::initializer_list<Row> matrix)
    : std::vector<Row>(matrix)
    , rows_(matrix.size())
    , columns_(matrix.begin()->size())
{

}

const matrix matrix::operator*(const matrix &obj) const
{

    matrix res(rows_, obj.columns_);

    for (int j = 0; j < res.rows_; j++)
    {
        for (int i = 0; i < res.columns_; i++)
        {
            for (int k = 0; k < columns_; k++)
            {
                res[j][i] += (*this)[j][k] * obj[k][i];
            }
        }
    }

    return res;
}
