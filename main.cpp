#include <iostream>
#include <algorithm>
#include "matrix.h"

int main()
{
    using CurrentMatrixType = Matrix<int>;

    // printing of a matrix
    auto printMatrix = [](const CurrentMatrixType& m, const std::string& name = "")
    {
        auto isValid = m.IsValid();
        std::cout << "Matrix " << name << " is " << (isValid ? "" : "not ") << "valid";
        std::cout << std::endl;
        for (std::size_t i = 0; i < m.GetNumRows() && isValid; ++i)
        {
            for (std::size_t j = 0; j < m.GetNumColumns(); ++j)
                std::cout << m.at(i, j) << " ";
            std::cout << std::endl;
        }
        std::cout << std::endl;
    };

    CurrentMatrixType m1(3,4,-1);

    // operator[]
    m1[2][1] = 5;
    printMatrix(m1, "m1");

    // copy with default copy operator
    auto m2 = m1;
    printMatrix(m2, "m1 copy by default copy constructor");

    // for-loop
    for (auto& v : m2)
        v += 2;

    printMatrix(m2, "m2 = m1 + 2");

    // operator+
    auto m3 = m1 + m2;
    printMatrix(m3, "m3 = m1 + m2");

    // operator| : for concatenating matrices with same number of rows
    auto m4 = m3 | m1;
    printMatrix(m4, "m4 = m3 | m1");

    CurrentMatrixType k(2,2,2);
    printMatrix(k, "k");

    // operator| won't work with inappropriate input
    auto km = m1 | k;
    printMatrix(km, "km = m1 | k");

    // move by default copy operator
    auto m5 = std::move(m1);
    printMatrix(m5, "m5 = std::move(m1)");
    printMatrix(m1, "m1 after move");
    m1 = m5;
    printMatrix(m1, "m1 = m5");

    return 0;
}
