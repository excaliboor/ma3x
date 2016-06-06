//
//  matrix_test.hpp
//  ma3x
//
//  Created by Bojan Bilić on 06/06/16.
//  Copyright © 2016 Bojan Bilić. All rights reserved.
//

#ifndef matrix_test_hpp
#define matrix_test_hpp


#include <stdio.h>
#include <iostream>
#include "matrix.hpp"


#define _MA3X_TEST_MAX_VALUE    9

#define _MA3X_TEST_MAX_WIDTH    30
#define _MA3X_TEST_MAX_HEIGHT   30

#define _MA3X_TEST_COUNT_DEFAULT    10

#define _MA3X_TEST_COUNT_CREATION       _MA3X_TEST_COUNT_DEFAULT
#define _MA3X_TEST_COUNT_ADDITION       _MA3X_TEST_COUNT_DEFAULT
#define _MA3X_TEST_COUNT_MULTIPLICATION _MA3X_TEST_COUNT_DEFAULT
#define _MA3X_TEST_COUNT_PRINTING       _MA3X_TEST_COUNT_DEFAULT
#define _MA3X_TEST_COUNT_FILLING_TESTS  _MA3X_TEST_COUNT_DEFAULT


/* declarations */
template <typename TYPE> std::ostream & operator<<(std::ostream& s, const Matrix<TYPE>& matrix);

template <typename TYPE> bool all_tests_did_run_successfully();

bool test_creation();
bool test_addition();
bool test_multiplication();
template <typename TYPE> bool test_printing();
template <typename TYPE> bool test_filling_with_random_values();


/* definitions */
template <typename TYPE> std::ostream & operator<<(std::ostream& s, const Matrix<TYPE>& matrix)
{
    int m_h = matrix.get_height();
    int m_w = matrix.get_width();
    for (int j = 0; j < m_h; ++j)
    {
        for (int i = 0; i < m_w; ++i)
        {
            s << matrix.value_at({i, j}) << " ";
        }
        s << "\n";
    }
    s << "\n";
    return s;
}


template <typename TYPE> bool all_tests_did_run_successfully()
{
    return test_printing<TYPE>()
        && test_creation()
        && test_addition()
        && test_multiplication()
        && test_filling_with_random_values<TYPE>();
}


bool test_creation()
{
    /* TODO */
    return false;
}


bool test_addition()
{
    /* TODO */
    return false;
}


bool test_multiplication()
{
    /* TODO */
    return false;
}


template <typename TYPE> bool test_printing()
{
    for (int i = 0; i<10; ++i)
        std::cout << Matrix<TYPE>::get_identity_matrix_of_order(i);
    return true;
}


template <typename TYPE> Matrix<TYPE> RandomMatrix(bool set_srand = false)
{
    if (set_srand)
    {
        srand((unsigned int) time(nullptr));
        // set RNG nicely - first two rands() are repetitive so throw them away
        rand(); rand();
    }
    
    std::cout << "Generating random matrix:\n";
    int m_h = rand()% _MA3X_TEST_MAX_HEIGHT, m_w = rand()% _MA3X_TEST_MAX_WIDTH;
    m_h=m_w=0;
    std::cout << "Requested:" << std::endl << "Width: " << m_w << " / Height: " << m_h << std::endl;
    Matrix<TYPE> random_matrix = Matrix<TYPE>({m_w, m_h});
    m_h = random_matrix.get_height();
    m_w = random_matrix.get_width();
    std::cout << "Received:" << std::endl << "Width: " << m_w << " / Height: " << m_h << std::endl;
    for (int j = 0; j<m_h; ++j)
    {
        for (int i = 0; i<m_w; ++i)
            random_matrix.set(i, j, rand() % _MA3X_TEST_MAX_VALUE+1);
    }

    return random_matrix;
}


template <typename TYPE> bool test_filling_with_random_values()
{
    try {
        srand((unsigned int) time(nullptr));
        // set RNG nicely - first two rands() are repetitive so throw them away
        rand(); rand();
        for (int test_counter = 0; test_counter < _MA3X_TEST_COUNT_FILLING_TESTS; ++test_counter)
        {
            Matrix<TYPE> test_matrix = RandomMatrix<TYPE>(); //Matrix({m_w, m_h});
            std::cout << test_matrix;
        }
    } catch (...) {
        return false;
    }
    
    return true;
}


#undef _MA3X_TEST_COUNT_CREATION
#undef _MA3X_TEST_COUNT_ADDITION
#undef _MA3X_TEST_COUNT_MULTIPLICATION
#undef _MA3X_TEST_COUNT_PRINTING
#undef _MA3X_TEST_COUNT_FILLING_TESTS
#undef _MA3X_TEST_COUNT_DEFAULT

#undef _MA3X_TEST_MAX_WIDTH
#undef _MA3X_TEST_MAX_HEIGHT
#undef _MA3X_TEST_MAX_VALUE

#endif /* matrix_test_hpp */
