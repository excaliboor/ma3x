//
//  matrix.hpp
//  ma3x
//
//  Created by Bojan Bilić on 03/06/16.
//  Copyright © 2016 Bojan Bilić. All rights reserved.
//

#ifndef matrix_hpp
#define matrix_hpp

#include <stdio.h>
#include <initializer_list>
#include <cstdlib>

#define MA3X_MIN_WIDTH  1
#define MA3X_MIN_HEIGHT 1
#define MA3X_MAX_WIDTH  10000
#define MA3X_MAX_HEIGHT 10000


struct MatrixDimensions {
    int width = 0,
        height = 0;

    MatrixDimensions& operator = (MatrixDimensions& new_MD)
    {
        height = new_MD.height;
        width = new_MD.width;
        return *this;
    }

    MatrixDimensions(int w = 0, int h = 0) {
        width = w; height = h;
    };
};


struct Coordinates {
    int x, y;
};


/* template class declaration */
template <typename TYPE> class Matrix
{
protected:
    MatrixDimensions Dimensions;
    TYPE* values;
public:
    Matrix (MatrixDimensions);
    Matrix (MatrixDimensions MD, TYPE const *const values) : Matrix (MD) {
        for (int j = 0; j<MD.height; ++j)
        {
            int width = MD.width;
            for (int i = 0; i<width; ++j)
                this->set({i, j}, *(values+(i*width)+j));
        }
    }
    ~Matrix();

    // getters
    int get_height () const;
    int get_width () const;

    // operations
    inline bool has_same_dimensions_as (const Matrix&);
    inline bool is_square_matrix ();
    inline int const value_at (const Coordinates&) const;
    inline void set (const Coordinates&, const TYPE);
    inline void set (int, int, const TYPE);
    Matrix& add (const Matrix&);
    Matrix& dot_multiply_with (const int);
    Matrix dot_multiply_with (const Matrix&);
    Matrix transposed ();
    
    // class methods
    static Matrix get_identity_matrix_of_order(const int);
};


/* template class definition */
template <typename TYPE> Matrix<TYPE>::Matrix(MatrixDimensions dimensions)
{
#define validate_width(w) (((MA3X_MAX_WIDTH) < (w))     \
                            ? (MA3X_MAX_WIDTH)          \
                            : (((w) < (MA3X_MIN_WIDTH))     \
                                ? (MA3X_MIN_WIDTH)          \
                                : (w)))
#define validate_height(h) (((MA3X_MAX_HEIGHT) < (h))   \
                            ? (MA3X_MAX_HEIGHT)         \
                            : (((h) < (MA3X_MIN_HEIGHT))    \
                                ? (MA3X_MIN_HEIGHT)         \
                                : (h)))
    this->Dimensions.width = validate_width(dimensions.width);
    this->Dimensions.height = validate_height(dimensions.height);
    this->values = (TYPE *) malloc(
                                   sizeof(TYPE)
                                   * this->Dimensions.width
                                   * this->Dimensions.height
                                   );
#undef validate_height
#undef validate_width
}


template <typename TYPE> Matrix<TYPE>::~Matrix()
{
    if (this->values != nullptr)
        free( this->values );
}


template <typename TYPE> int Matrix<TYPE>::get_height() const
{
    return this->Dimensions.height;
}


template <typename TYPE> int Matrix<TYPE>::get_width() const
{
    return this->Dimensions.width;
}


template <typename TYPE> inline bool Matrix<TYPE>::has_same_dimensions_as(const Matrix& that)
{
    return (this->Dimensions.width == that.Dimensions.width
            && this->Dimensions.height == that.Dimensions.height);
}


template <typename TYPE> inline bool Matrix<TYPE>::is_square_matrix()
{
    return (this->Dimensions.width == this->Dimensions.height);
}


template <typename TYPE> inline int const Matrix<TYPE>::value_at (const Coordinates &c) const
{
    return *( this->values + (this->Dimensions.width * c.y) + c.x );
}


template <typename TYPE> inline void Matrix<TYPE>::set (const Coordinates &c, const TYPE value)
{
    *( this->values + (this->Dimensions.width * c.y) + c.x ) = value;
}


template <typename TYPE> inline void Matrix<TYPE>::set(int i, int j, const TYPE value)
{
    // TODO: test which one of the two lines below is faster
    //    this->set({i, j}, value);
    *( this->values + (this->get_width() * j) + i ) = value;
}


template <typename TYPE> Matrix<TYPE>& Matrix<TYPE>::add ( const Matrix& that )
{
    if ( this->has_same_dimensions_as( that ) )
    {
        int width = this->Dimensions.width;
        int height = this->Dimensions.height;
        for (int j = 0; j<height; ++j)
        {
            for (int i = 0; i<width; ++i)
            {
                Coordinates c = {i, j};
                this->set (c, this->value_at(c) + that.value_at(c));
            }
        }
        return *this;
    }
    else
        throw "Can't add matrices: Adding matrices with different dimensions";
}


template <typename TYPE> Matrix<TYPE>& Matrix<TYPE>::dot_multiply_with (const int m)
{
    int width = this->Dimensions.width;
    int height = this->Dimensions.height;
    for (int j = 0; j<height; ++j)
    {
        for (int i = 0; i<width; ++i)
        {
            Coordinates c = {i, j};
            this->set (c,  this->value_at(c) * m);
        }
    }
    
    return *this;
}


template <typename TYPE> Matrix<TYPE> Matrix<TYPE>::dot_multiply_with (const Matrix& that)
{
    if (this->Dimensions.width == that.Dimensions.height)
    {
        int connector = this->Dimensions.width;
        Matrix new_matrix = Matrix ({that.Dimensions.width, this->Dimensions.height});
        for (int j=0; j<new_matrix.Dimensions.height; ++j)
        {
            for (int i=0; i<new_matrix.Dimensions.width; ++i)
            {
                TYPE sum = 0;
                for (int r=0; r<connector; ++r)
                    sum += this->value_at({i, r}) * that.value_at({r, j});
                new_matrix.set(i, j, sum );
            }
        }
        
        return new_matrix;
    }
    else
        throw "Can't multiply matrices: ()";
}

template <typename TYPE> Matrix<TYPE> Matrix<TYPE>::transposed ()
{
    Matrix new_matrix = Matrix ({this->Dimensions.height, this->Dimensions.width});
    for (int j=0; j<new_matrix.Dimensions.height; ++j)
    {
        for (int i=0; i<new_matrix.Dimensions.width; ++i)
            new_matrix.set(i, j, this->value_at({j, i}) );
    }
    
    return new_matrix;
}


template <typename TYPE> Matrix<TYPE> Matrix<TYPE>::get_identity_matrix_of_order(const int order)
{
    Matrix identity_matrix = Matrix({order, order});
    for (int j = 0; j<order; ++j)
    {
        for (int i = 0; i<order; ++i)
        {
            TYPE value = 0;
            if (i == j)
                value = 1;
            identity_matrix.set(i, j, value);
        }
    }
    
    return identity_matrix;
}

#endif /* matrix_hpp */
