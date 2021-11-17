# simple-matrix

Matrix class is able to:
- be copied and moved (by default methods)
- be iterated like for `(auto v : m)`, where `m` is matrix class object
- be concatenated with other matrix with same number of rows as

        A|B = a_11 a_22 b_11
              a_21 a_22 b_12
              
- give modifying access to its elements via `m[i][j]` (without bounds check)
- and non-modifying access - via `m(i, j)` (with implicit bounds check provided by underlying `std::vector`)
- sum matrices as `A = B + C`

## Output of `main()`:

    Matrix m1 is valid
    -1 -1 -1 -1 
    -1 -1 -1 -1 
    -1 5 -1 -1 

    Matrix m1 copy by default copy constructor is valid
    -1 -1 -1 -1 
    -1 -1 -1 -1 
    -1 5 -1 -1 

    Matrix m2 = m1 + 2 is valid
    1 1 1 1 
    1 1 1 1 
    1 7 1 1 

    Matrix m3 = m1 + m2 is valid
    0 0 0 0 
    0 0 0 0 
    0 12 0 0 

    Matrix m4 = m3 | m1 is valid
    0 0 0 0 -1 -1 -1 -1 
    0 0 0 0 -1 -1 -1 -1 
    0 12 0 0 -1 5 -1 -1 

    Matrix k is valid
    2 2 
    2 2 

    Matrix km = m1 | k is not valid

    Matrix m5 = std::move(m1) is valid
    -1 -1 -1 -1 
    -1 -1 -1 -1 
    -1 5 -1 -1 

    Matrix m1 after move is not valid

    Matrix m1 = m5 is valid
    -1 -1 -1 -1 
    -1 -1 -1 -1 
    -1 5 -1 -1
