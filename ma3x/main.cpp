//
//  main.cpp
//  ma3x
//
//  Created by Bojan Bilić on 03/06/16.
//  Copyright © 2016 Bojan Bilić. All rights reserved.
//

#include <iostream>
#include "matrix_test.hpp"
//#include "matrix.hpp"

int main (int argc, const char * argv[])
{
//    Matrix i_4 = Matrix::get_identity_matrix_of_order(14);
//    std::cout << i_4 << i_4;
    using test_type = int;
    all_tests_did_run_successfully<test_type>();
    test_filling_with_random_values<test_type>();
    return 0;
}
