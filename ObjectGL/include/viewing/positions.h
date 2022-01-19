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
#include "viewing/vectors.h"


//===========================================================================
// forward definitions
template<typename TScalar> class Position;

typedef Position<float>  PositionF; //<! Position with float  (32-bits) components specialization.
typedef Position<double> PositionD; //<! Position with double (64-bits) components specialization.


//===========================================================================
/** \brief The generic class of 3-D Positions.
*
* Template argument 'TScalar' specifies the type of the vector
* scalar components: float or double.
*
* \sa PositionF and PositionD.
*/
template<typename TScalar>
class Position : public Vec3<TScalar>
{
public:

    /** \brief Constructor (three axis coordinate values)
    *
    * \param x : the X-axis coordinate. Defaults to 0.
    * \param y : the Y-axis coordinate. Defaults to 0.
    * \param z : the Z-axis coordinate. Defaults to 0.
    */
    Position<TScalar>(TScalar x = 0, TScalar y = 0, TScalar z = 0)
        : Vec3<TScalar>(x, y, z)
    {}

    /** \brief Constructor (one Position reference)
    *
    * \param copy : a reference to the 3-D vector to copy.
    */
    Position<TScalar>(Position<TScalar>& copy)
        : Vec3<TScalar>(copy)
    {}

    /** \brief Constructor (one Position const reference)
    *
    * \param copy : a reference to the 3-D vector to copy.
    */
    Position<TScalar>(const Position<TScalar>& copy)
        : Vec3<TScalar>(copy)
    {}
};
