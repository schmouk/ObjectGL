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
#include <cmath>
#include <Eigen/Dense>
#include "viewing/vectors.h"


//===========================================================================
// forward definitions
template<typename TScalar> class Mat;
typedef Mat<float>  MatF; //<! Transformation matrices with float  (32-bits) coefficients specialization.
typedef Mat<double> MatD; //<! Transformation matrices with double (64-bits) coefficients specialization.

template<typename TScalar> class MatTranslation;
typedef MatTranslation<float>  MatTranslationF; //<! Translation matrices with float  (32-bits) coefficients specialization.
typedef MatTranslation<double> MatTranslationD; //<! Translation matrices with double (64-bits) coefficients specialization.

template<typename TScalar> class MatRotation;
typedef MatRotation<float>  MatRotationF; //<! Rotation matrices with float  (32-bits) coefficients specialization.
typedef MatRotation<double> MatRotationD; //<! Rotation matrices with double (64-bits) coefficients specialization.


//===========================================================================
# define M_PI 3.141592653589793238462643383279502884L


//===========================================================================
/** \brief the base class for all Transformation Matrices.
*
* Template argument 'TScalar' specifies the type of the matrix
* scalar coefficients: float or double.
*
* \sa MatF and MatD specializations.
*/

template<typename TScalar>
class Mat : public Eigen::Matrix4<TScalar>
{
public:
    /** \brief Default Constructor.
    *
    * This constructor instantiates identity matrices.
    */
    Mat<TScalar>()
        : Eigen::Matrix4<TScalar>()
    {
        set_identity();
    }


    /** Returns an instance of the identity matrix. */
    static Mat<TScalar>& getIdentity()
    {
        return Mat<TScalar>().set_identity();
    }

    /** \brief returns the offsets column of this transformation matrix.
    */
    Vec3<TScalar>& offsets()
    {
        return Vec3<TScalar>((*this).col(3));
    }

    /** \brief returns the const offsets column (i.e. translation) of this transformation matrix.
    */
    const Vec3<TScalar>& offsets() const {
        return Vec3<TScalar>((*this).col(3));
    }


    /** Applies scaling on this transformation matrix (one same factor for each axis).
    *
    * \param factor : the scaling factor to be applied to each axis.
    * \return a reference to this matrix.
    */
    Mat<TScalar>& scaling(const TScalar factor)
    {
        return scaling(factor, factor, factor);
    }

    /** Applies scaling on this transformation matrix (a different factor per axis).
    *
    * \param factor_x : the scaling factor to be applied to the X-axis.
    * \param factor_y : the scaling factor to be applied to the Y-axis.
    * \param factor_z : the scaling factor to be applied to the Z-axis.
    * \return a reference to this matrix.
    */
    Mat<TScalar>& scaling(const TScalar factor_x, const TScalar factor_y, const TScalar factor_z)
    {
        // rescaling after moving at origin position (0,0,0)
        *(this)(0, 0) = factor_x;
        *(this)(1, 1) = factor_y;
        *(this)(2, 2) = factor_z;

        // moving back to previous offset position
        (*this)(0, 3) *= 1 - factor_x;
        (*this)(1, 3) *= 1 - factor_y;
        (*this)(2, 3) *= 1 - factor_z;
        
        // that's it!
        return *this;
    }

    /** Applies scaling on this transformation matrix (one factors Vec3).
    *
    * \param factor : the scaling factor vector to be applied to each axis.
    * \return a reference to this matrix.
    */
    Mat<TScalar>& scaling(const Vec3<TScalar>& factor)
    {
        return scaling(factor.x , factor.y, factor.z);
    }


    /** \brief Sets this matrix to be the identity one.
    *
    * \return a reference to this matrix.
    */
    Mat<TScalar>& set_identity() {
        (*this)(0, 0) = (*this)(1, 1) = (*this)(2, 2) = TScalar(1);
        return *this;
    }


    /** Translates the coordinates of this transformation matrix (3 offset values)
    *
    * \param x_offset : the translation related to the X-axis.
    * \param y_offset : the translation related to the Y-axis.
    * \param z_offset : the translation related to the Z-axis.
    * \return a reference to this matrix.
    */
    Mat<TScalar>& translate(const TScalar x_offset = 0, const TScalar y_offset = 0, const TScalar z_offset = 0)
    {
        (*this)(0, 3) = x_offset;
        (*this)(1, 3) = y_offset;
        (*this)(2, 3) = z_offset;
        return *this;
    }

    /** Translates coordinates of this transformation matrix (1 offset vector)
    *
    * \param offset : a reference to the Vec3 offset.
    */
    Mat<TScalar>& translate(const Vec3<TScalar>& offset)
    {
        return translate(offset.x(), offset.y(), offset.z());
    }


    /** \brief homogeneous coefficient w getter. */
    const TScalar w() const { return (*this)(3,3); }
    
    /** \brief homogeneous coefficient w setter. */
    const TScalar w(const TScalar val) { return (*this)(3,3) = val; }
};


//===========================================================================
/** \brief The class of Translation Matrices.
*
* Template argument 'TScalar' specifies the type of the matrix 
* scalar coefficients: float or double.
* 
* \sa MatTranslationF and MatTranslationD specializations.
*/
template<typename TScalar>
class MatTranslation : public Mat<TScalar>
{
public:

    /** \brief Constructor (3 offset values)
    *
    * \param x_offset : the translation related to the X-axis.
    * \param y_offset : the translation related to the Y-axis.
    * \param z_offset : the translation related to the Z-axis.
    */
    MatTranslation<TScalar>(const TScalar x_offset = 0, const TScalar y_offset = 0, const TScalar z_offset = 0)
        : Mat<TScalar>()
    {
        set(x_offset, y_offset, z_offset);
    }

    /** \brief Constructor (1 offset vector)
    *
    * \param offset : a reference to the Vec3 offset.
    */
    MatTranslation<TScalar>(const Vec3<TScalar>& offset)
        : Mat<TScalar>()
    {
        set(offset);
    }

    /** \brief Sets the translation coefficients of this matrix.
    *
    * \param x_offset : the translation related to the X-axis.
    * \param y_offset : the translation related to the Y-axis.
    * \param z_offset : the translation related to the Z-axis.
    */
    void set(const TScalar x_offset, const TScalar y_offset, const TScalar z_offset)
    {
        set(Vec4<TScalar>(x_offset, y_offset, z_offset, TScalar(1)));
    }

    /** \brief Sets the translation coefficients of this matrix.
    *
    * \param offset : a reference to a vector3 offset.
    */
    void set(Eigen::Vector<TScalar, 3>& offset)
    {
        set(Vec4<TScalar>(offset[0], offset[1], offset[2], TScalar(1)));
    }

    /** \brief Sets the translation coefficients of this matrix.
    *
    * \param offset : a reference to an homogeneous vector4 offset.
    */
    void set(Vec4<TScalar> offset)
    {
        (*this).col(3) = offset;
    }

    /** \brief Gets a Vec3 vector with the offset values.
    */
    Vec3<TScalar>& get_offsets_vector() {
        return Vec3<TScalar>(this->x(), this->y(), this->z());
    }

    /** \brief Gets a const Vec3 vector with the offset values.
    */
    const Vec3<TScalar>& get_offsets_vector() const {
        return Vec3<TScalar>(this->x(), this->y(), this->z());
    }

    /** \brief x_offset coordinate getter. */
    const TScalar x() { return (*this)(3, 0); }
    /** \brief x_offset coordinate setter. */
    const TScalar x(const TScalar val) { return (*this)(3, 0) = val; }
    /** \brief y_offset coordinate getter. */
    const TScalar y() { return (*this)(3, 1); }
    /** \brief y_offset coordinate setter. */
    const TScalar y(const TScalar val) { return (*this)(3, 1) = val; }
    /** \brief z_offset coordinate getter. */
    const TScalar z() { return (*this)(3, 2); }
    /** \brief z_offset coordinate setter. */
    const TScalar z(const TScalar val) { return (*this)(3, 2) = val; }
};


//===========================================================================
/** \brief The class of Rotation Matrices.
*
* Template argument 'TScalar' specifies the type of the matrix
* scalar coefficients: float or double.
*
* \sa MatRotationF and MatRotationD specializations.
*/
template<typename TScalar>
class MatRotation : public Mat<TScalar>
{
public:

    /** \brief The order of the rotations axis applications */
    typedef enum {
        R_XYZ,  //!< rotate on X-axis first, then on Y-axis and finally on Z-axis
        R_XZY,  //!< rotate on X-axis first, then on Z-axis and finally on Y-axis
        R_YXZ,  //!< rotate on Y-axis first, then on X-axis and finally on Z-axis
        R_YZX,  //!< rotate on Y-axis first, then on Z-axis and finally on X-axis
        R_ZXY,  //!< rotate on Z-axis first, then on X-axis and finally on Z-axis
        R_ZYX   //!< rotate on Z-axis first, then on Y-axis and finally on X-axis
    } RotateOrder;

    /** \brief Constructor (3 rotation values)
    *
    * CAUTION: Angles must be provided in degrees!
    *
    * \param x_angle : the rotation related to the X-axis.
    * \param y_angle : the rotation related to the Y-axis.
    * \param z_angle : the rotation related to the Z-axis.
    * \param axis_order : the enum valu for the order of rotations application.
    * \sa enum RotateOrder
    */
    MatRotation<TScalar>(const TScalar x_angle = 0,
                         const TScalar y_angle = 0, 
                         const TScalar z_angle = 0,
                         const RotateOrder axis_order = R_XYZ)
        : Mat<TScalar>()
    {
        rotate(x_angle, y_angle, z_angle, axis_order);
    }


    /** Applies rotation on axis according to specified order.
    *
    * CAUTION: Angles must be provided in degrees!
    *
    * \param x_angle : the rotation related to the X-axis.
    * \param y_angle : the rotation related to the Y-axis.
    * \param z_angle : the rotation related to the Z-axis.
    * \param axis_order : the enum valu for the order of rotations application.
    * \sa enum RotateOrder
    */
    MatRotation<TScalar>& rotate(const TScalar x_angle,
                                 const TScalar y_angle,
                                 const TScalar z_angle,
                                 const RotateOrder axis_order = R_XYZ)
    {
        // radian transforms
        x_angle *= M_PI / 180;
        y_angle *= M_PI / 180;
        z_angle *= M_PI / 180;

        // axis rotation matrices evaluation
        Mat<TScalar> Rx, Ry, Rz;

        Rx(1, 1) =    Rx(2, 2) = cos(x_angle);
        Rx(1, 2) = - (Rx(2, 1) = sin(x_angle));

        Ry(0, 0) =    Ry(2, 2) = cos(y_angle);
        Ry(0, 2) = - (Ry(2, 0) = sin(y_angle));

        Rz(0, 0) =    Rz(1, 1) = cos(z_angle);
        Rz(0, 1) = - (Rz(1, 0) = sin(z_angle));

        // application of axis-order multiplications (remember: right to left...)
        switch (axis_order) {
            case R_XYZ: *this = Rz * Ry * Rx; break;
            case R_XZY: *this = Ry * Rz * Rx; break;
            case R_YXZ: *this = Rz * Rx * Ry; break;
            case R_YZX: *this = Rx * Rz * Ry; break;
            case R_ZXY: *this = Ry * Rx * Rz; break;
            case R_ZYX: *this = Rx * Ry * Rz; break;
        }

        // that's it!
        return *this;
    }

};
