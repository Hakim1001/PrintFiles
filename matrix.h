#ifndef MATRIX_H
#define MATRIX_H
#include <vector>


typedef std::vector<float> Row;
class matrix: public std::vector<std::vector<float>>                                          //Класс матица для матричного преобразования кооординат
{
public:
    matrix(int rows, int columns);
    matrix(std::initializer_list<std::vector<float>> matrix);

    const matrix operator*(const matrix &obj) const;

private:
    int rows_;
    int columns_;
};

#endif // MATRIX_H
