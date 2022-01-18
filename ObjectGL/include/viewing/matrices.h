#pragma once
/**
MIT License

Copyright (c) 2022 Philippe Schmouker, ph.schmouker (at) gmail.com

Permission is hereby granted,  free of charge,  to any person obtaining a copy
of this software and associated documentation files (the "Software"),  to deal
in the Software without restriction,  including without limitation the  rights
to use,  copy,  modify,  merge,  publish,  distribute, sublicense, and/or sell
copies of the Software,  and  to  permit  persons  to  whom  the  Software  is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS",  WITHOUT WARRANTY OF ANY  KIND,  EXPRESS  OR
IMPLIED,  INCLUDING  BUT  NOT  LIMITED  TO  THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT  SHALL  THE
AUTHORS  OR  COPYRIGHT  HOLDERS  BE  LIABLE  FOR  ANY CLAIM,  DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,  ARISING FROM,
OUT  OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

//===========================================================================
#include "Eigen/Core"

using namespace std;


//===========================================================================
/** \brief The class of Translation Matrices.
*
* Template argument 'TScalar' specifies the type of the matrix 
* scalar coefficients: float or double.
*/
template<typename TScalar>
class MATTranslation : Eigen::Matrix<Scalar, 4, 4, Eigen::ColMajor>
{
public:

    /** \brief Constructor (3 offset values)
    *
    * \param x_offset : the translation related to the X-axis.
    * \param y_offset : the translation related to the Y-axis.
    * \param z_offset : the translation related to the Z-axis.
    */
    MATTranslation<TScalar>(const TScalar x_offset = 0, const TScalar y_offset = 0, const TScalar z_offset = 0)
        : Eigen::DiagonalMatrix<TScalar, 4, 4>()
    {
        set(x_offset, y_offset, z_offset);
    }

    /** \brief Constructor (1 offset vector)
    *
    * \param offset : a reference to the vector3 offset.
    */
    MATTranslation<TScalar>(Eigen::Vector<TScalar, 3>& offset)
        : Eigen::DiagonalMatrix<TScalar, 4, 4>()
    {
        set(offset);
    }

    /** \brief Sets the translation coefficients of this matrix.
    *
    * \param x_offset : the translation related to the X-axis.
    * \param y_offset : the translation related to the Y-axis.
    * \param z_offset : the translation related to the Z-axis.
    */
    void set(const TScalar x_offset, const TScalar y_offset, const TScalar z_offset) {
        set(Eigen::Vector<TScalar, 4>(x_offset, y_offset, z_offset, TScalar(1)));
    }

    /** \brief Sets the translation coefficients of this matrix.
    *
    * \param offset : a reference to a vector3 offset.
    */
    void set(Eigen::Vector<TScalar, 3>& offset) {
        set(Eigen::Vector<TScalar, 4>(offset[0], offset[1], offset[2], TScalar(1))));
    }

    /** \brief Sets the translation coefficients of this matrix.
    *
    * \param offset : a reference to an homogeneous vector4 offset.
    */
    void set(Eigen::Vector<TScalar, 4>& offset) {
        this.col(3) = offset;
    }
};