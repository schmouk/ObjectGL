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
#include <Eigen/Dense>


//===========================================================================
// forward definitions
template<typename TScalar> class Vec3;

typedef Vec3<float>  Vec3f; //<! 3-D Vectors with float  (32-bits) components specialization.
typedef Vec3<double> Vec3d; //<! 3-D Vectors with double (64-bits) components specialization.


template<typename TScalar> class Vec4;

typedef Vec4<float>  Vec4f; //<! 4-D (homogeneous) Vectors with float  (32-bits) components specialization.
typedef Vec4<double> Vec4d; //<! 4-D (homogeneous) Vectors with double (64-bits) components specialization.


//===========================================================================
/** \brief The generic class of 3-D Vectors.
*
* Template argument 'TScalar' specifies the type of the vector
* scalar components: float or double.
* 
* \sa Vec4, Vec3f and Vec3d.
*/
template<typename TScalar>
class Vec3 : public Eigen::Vector3<TScalar>
{
public:

    /** \brief Constructor (three axis coordinate values)
    *
    * \param x : the X-axis coordinate. Defaults to 0.
    * \param y : the Y-axis coordinate. Defaults to 0.
    * \param z : the Z-axis coordinate. Defaults to 0.
    */
    Vec3<TScalar>(const TScalar x = 0, const TScalar y = 0, const TScalar z = 0)
        : Eigen::Vector3<TScalar>(x, y, z)
    {}

    /** \brief Constructor (one Vec3 reference)
    *
    * \param copy : a reference to the 3-D vector to copy.
    */
    Vec3<TScalar>(Vec3<TScalar>& copy)
        : Eigen::Vector3<TScalar>(copy)
    {}

    /** \brief Constructor (one Vec3 const reference)
    *
    * \param copy : a reference to the 3-D vector to copy.
    */
    Vec3<TScalar>(const Vec3<TScalar>& copy)
        : Eigen::Vector3<TScalar>(copy)
    {}

    /** \brief Constructor (one Vec4 reference)
    *
    * Copy with removal of the last homogeneous coefficient.
    * \param copy : a reference to the 4-D vector to copy.
    */
    Vec3<TScalar>(Vec4<TScalar>& copy)
        : Eigen::Vector4<TScalar>(copy(0), copy(1), copy(2))
    {}

    /** \brief Constructor (one Vec4 const reference)
    *
    * Copy with removal of the last homogeneous coefficient.
    * \param copy : a reference to the 4-D vector to copy.
    */
    Vec3<TScalar>(const Vec4<TScalar>& copy)
        : Eigen::Vector4<TScalar>(copy(0), copy(1), copy(2))
    {}


    /** \brief Sets this vector components values (three TScalar args). */
    void set(const TScalar x, const TScalar y, const TScalar z)
    {
        x(x); y(y); z(z);
    }

    /** \brief Sets this vector components values (one 3-D vector arg). */
    void set(const Vec3<TScalar> &vec)
    {
        x(vec.x); y(vec.y); z(vec.z);
    }

    /** \brief Sets this vector components values (one 4-D vector arg). */
    void set(const Vec4<TScalar>& vec)
    {
        x(vec.x); y(vec.y); z(vec.z);
    }


    /** \brief x coordinate getter. */
    const TScalar x() { return (*this)(0); }
    /** \brief x coordinate setter. */
    const TScalar x(const TScalar val) { return (*this)(0) = val; }

    /** \brief y coordinate getter. */
    const TScalar y() { return (*this)(1); }
    /** \brief y coordinate setter. */
    const TScalar y(const TScalar val) { return (*this)(1) = val; }
    
    /** \brief z coordinate getter. */
    const TScalar z() { return (*this)(2); }
    /** \brief z coordinate setter. */
    const TScalar z(const TScalar val) { return (*this)(2) = val; }
};


//===========================================================================
/** \brief The generic class of 4-D Vectors.
*
* Template argument 'TScalar' specifies the type of the vector
* scalar components: float or double.
*
* \sa Vec3, Vec4f and Vec4d.
*/
template<typename TScalar>
class Vec4 : public Eigen::Vector4<TScalar>
{
public:

    /** \brief Constructor (three axis + homogeneous coordinate values)
    *
    * \param x : the X-axis coordinate. Defaults to 0.
    * \param y : the Y-axis coordinate. Defaults to 0.
    * \param z : the Z-axis coordinate. Defaults to 0.
    * \param w : the homogeneous component. Defaults to 1.
    */
    Vec4<TScalar>(const TScalar x = 0, const TScalar y = 0, const TScalar z = 0, const TScalar w = 1)
        : Eigen::Vector4<TScalar>(x, y, z, w)
    {}

    /** \brief Constructor (one Vec4 reference)
    *
    * \param copy : a reference to the 3-D vector to copy.
    */
    Vec4<TScalar>(Vec4<TScalar>& copy)
        : Eigen::Vector4<TScalar>(copy)
    {}

    /** \brief Constructor (one Vec4 const reference)
    *
    * \param copy : a reference to the 3-D vector to copy.
    */
    Vec4<TScalar>(const Vec4<TScalar>& copy)
        : Eigen::Vector4<TScalar>(copy)
    {}

    /** \brief Constructor (one Vec3 reference + homogeneous coordinate)
    *
    * \param copy : a reference to the 4-D vector to copy.
    * \param w : the homogeneous coordinate. Defaults to 1.0.
    */
    Vec4<TScalar>(Vec3<TScalar>& copy, const TScalar w = TScalar(1))
        : Eigen::Vector4<TScalar>(copy(0), copy(1), copy(2), w)
    {}

    /** \brief Constructor (one Vec3 const reference + homogeneous coordinate)
    *
    * \param copy : a reference to the 4-D vector to copy.
    * \param w : the homogeneous coordinate. Defaults to 1.0.
    */
    Vec4<TScalar>(const Vec3<TScalar>& copy, const TScalar w = TScalar(1))
        : Eigen::Vector4<TScalar>(copy(0), copy(1), copy(2), w)
    {}


    /** \brief Sets this vector components values (four TScalar args). */
    void set(const TScalar x, const TScalar y, const TScalar z, const TScalar w = TScalar(1))
    {
        x(x); y(y); z(z); w(w);
    }

    /** \brief Sets this vector components values (one 3-D vector arg). */
    void set(const Vec3<TScalar>& vec)
    {
        x(vec.x); y(vec.y); z(vec.z); w(TScalar(1));
    }

    /** \brief Sets this vector components values (one 4-D vector arg). */
    void set(const Vec4<TScalar>& vec)
    {
        x(vec.x); y(vec.y); z(vec.z); w(vec.w);
    }

    /** \brief x coordinate getter. */
    const TScalar x() { return (*this)(0); }
    /** \brief x coordinate setter. */
    const TScalar x(const TScalar val) { return (*this)(0) = val; }

    /** \brief y coordinate getter. */
    const TScalar y() { return (*this)(1); }
    /** \brief y coordinate setter. */
    const TScalar y(const TScalar val) { return (*this)(1) = val; }
    
    /** \brief z coordinate getter. */
    const TScalar z() { return (*this)(2); }
    /** \brief z coordinate setter. */
    const TScalar z(const TScalar val) { return (*this)(2) = val; }
    
    /** \brief w coordinate getter. */
    const TScalar w() { return (*this)(3); }
    /** \brief w coordinate setter. */
    const TScalar w(const TScalar val) { return (*this)(3) = val; }
};
