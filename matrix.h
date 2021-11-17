#pragma once
#include<vector>

// Matrix class is able to:
// - be copied and moved (by default methods)
// - be iterated like for (auto v : m), where m is matrix class object
// - be concatenated with other matrix with same number of rows as
//    A|B = a_11 a_22 b_11
//          a_21 a_22 b_12
// - give modifying access to its elements via m[][] (without bounds check)
// - and non-modifying access - via m(i, j) (with implicit bounds check provided by std::vector)
// - sum matrices as A = B + C

template <class T = int>
class Matrix
{
    std::size_t numRows;
    std::size_t numColumns;
    std::vector<std::vector<T>> values;
public:
    Matrix(int numRows = 0, int numColumns = 0, T value = 0) :
        numRows(numRows),
        numColumns(numColumns)
    {
        values.clear();
        values.resize(numRows);

        for (auto& row : values)
            row.resize(numColumns/*, value*/);

        for (auto& v: *this)
            v = value;
    }

    static Matrix Invalid() { return Matrix(); }

    bool IsValid() const { 
        return 
            numRows > 0 && numColumns > 0 && 
            numRows == values.size() && numColumns == values[0].size(); 
    }

    Matrix operator+ (const Matrix& matrix) const
    {
        if (matrix.numColumns != numColumns ||
            matrix.numRows != numRows || !IsValid() || !matrix.IsValid())
            return Invalid();
        else
        {
            Matrix result = *this;

            for (int i = 0; i < numRows; ++i)
                for (int j = 0; j < numColumns; ++j)
                    result[i][j] += matrix.at(i, j);
            return result;
        }
    }

    Matrix operator| (const Matrix& matrix) const
    {
        Matrix result;
        if (matrix.numRows == numRows)
        {
            result = *this;
            for (auto i = 0; i < numRows; ++i)
            {
                auto& destination = result.values[i];
                auto& insertion = matrix.values[i];
                destination.insert(destination.end(), insertion.begin(), insertion.end());
            }
            result.numColumns += matrix.GetNumColumns();
        }

        return result;
    }

    using Row = std::vector<T>;
    Row& operator[] (size_t i) { return values[i]; }

    const T& at (int i, int j) const { return values.at(i).at(j); }
    std::size_t GetNumColumns() const { return numColumns; }
    std::size_t GetNumRows() const { return numRows; }

    class Iterator
    {
        std::size_t row;
        std::size_t col;
        Matrix* matrix;
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        Iterator(Matrix* matrix, int row = 0, int col = 0) : row(row), col(col), matrix(matrix) {}

        Iterator& operator++()
        {
            ++col;
            const auto numColumns = matrix->GetNumColumns();
            while(col > numColumns - 1)
            {
                ++row;
                col -= numColumns;
            }
            return *this;
        }

        Iterator operator++(int)
        {
            auto currentCopy = *this;
            ++(*this);
            return currentCopy;
        }

        reference operator*()
        {
            return (*matrix)[row][col];
        }

        pointer operator->()
        {
            return &((*matrix)[row][col]);
        }

        friend bool operator==(const Iterator& it1, const Iterator& it2) { return it1.matrix == it2.matrix && it1.row == it2.row && it1.col == it2.col; }
        friend bool operator!=(const Iterator& it1, const Iterator& it2) { return !(it1 == it2); }
    };

    Iterator begin() { return Iterator(this, 0, 0); }
    Iterator end() { return Iterator(this, numRows, 0); }
};
