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
FITNESS FOR A PARTICULAR PURprvt_posE AND NONINFRINGEMENT.  IN NO EVENT  SHALL  THE
AUTHORS  OR  COPYRIGHT  HOLDERS  BE  LIABLE  FOR  ANY CLAIM,  DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,  ARISING FROM,
OUT  OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

//===========================================================================
#include <Eigen/Dense>

#include "viewing/matrices.h"
#include "viewing/positions.h"


//===========================================================================
// forward definitions
template<typename TScalar> class Camera;

typedef Camera<float>  CameraF; //<! Cameras type with float  (32-bits) component values
typedef Camera<double> CameraD; //<! Cameras type with double (64-bits) component values


template<typename TScalar> class OrthoCamera;

typedef OrthoCamera<float>  OrthoCameraF; //<! Orthographic Cameras type with float  (32-bits) component values
typedef OrthoCamera<double> OrthoCameraD; //<! Orthographic Cameras type with double (64-bits) component values


//===========================================================================
/** \brief The generic class for camera models.
*
* Template argument 'TScalar' specifies the type of
* the cameras scalar components: float or double.
*
* \sa OrthoCamera, CameraF and CameraD.
*/
template<typename TScalar>
class Camera
{
public:

    /** \brief Empty constructor.
    *
    * Sets all attributes of this camera to  value  0. 
    * Such a camera cannot be used for the calculation 
    * of projection images. Atributes have to be set
    * with dedicated setters.
    */
    Camera<TScalar>()
        : prvt_pos(0, 0, 0),
          prvt_dir(0, 0, 0),
          prvt_width(0),
          prvt_height(0),
          prvt_angle(0),
          prvt_near_plane_dist(0),
          prvt_far_plane_dist(0),
          prvt_modified(true)
    {}

    /** \brief Constructor (6 prvt_pos and dir components).
    *
    * \param x : the x position of the eye of the camera
    * \param y : the y position of the eye of the camera
    * \param z : the z position of the eye of the camera
    * \param dir_x : the x position of the targeted viewing point
    * \param dir_y : the y position of the targeted viewing point
    * \param dir_z : the z position of the targeted viewing point
    * \param angle : the prvt_angle of rotation of the vertical axis of the camera. Caution: degrees, not radians!
    * \param width : the width of the viewing near-plane for the camera projection, in pixels
    * \param height : the height of the viewing near-plane for the camera projection, in pixels
    * \param near_plane_dist : the distance of the near plane (i.e. projection plane) for this camera
    * \param far_plane_dist : the distance of the far plane (i.e. far culling plane) for this camera
    */
    Camera<TScalar>(const TScalar x,
        const TScalar y,
        const TScalar z,
        const TScalar dir_x,
        const TScalar dir_y,
        const TScalar dir_z,
        const TScalar angle,
        const TScalar width,
        const TScalar height,
        const TScalar near_plane_dist,
        const TScalar far_plane_dist)
        : prvt_pos(x, y, z),
          prvt_dir(dir_x, dir_y, dir_z),
          prvt_width(width),
          prvt_height(height),
          prvt_angle(angle),
          prvt_near_plane_dist(near_plane_dist),
          prvt_far_plane_dist(far_plane_dist),
          prvt_modified(true)
    {
        assert(near_plane_dist < far_plane_dist);
        assert(width > 0);
        assert(height > 0);
    }

    /** \brief Constructor (3 prvt_pos components and 1 dir vector).
    *
    * \param x : the x position of the eye of the camera
    * \param y : the y position of the eye of the camera
    * \param z : the z position of the eye of the camera
    * \param dir : the 3D position of the targeted viewing point
    * \param angle : the angle of rotation of the vertical axis of the camera. Caution: degrees, not radians!
    * \param width : the width of the viewing near-plane for the camera projection, in pixels
    * \param height : the height of the viewing near-plane for the camera projection, in pixels
    * \param near_plane_dist : the distance of the near plane (i.e. projection plane) for this camera
    * \param far_plane_dist : the distance of the far plane (i.e. far culling plane) for this camera
    */
    Camera<TScalar>(const TScalar x,
        const TScalar y,
        const TScalar z,
        const Vec3<TScalar> dir,
        const TScalar angle,
        const TScalar width,
        const TScalar height,
        const TScalar near_plane_dist,
        const TScalar far_plane_dist)
        : prvt_pos(x, y, z),
          prvt_dir(dir),
          prvt_width(width),
          prvt_height(height),
          prvt_angle(angle),
          prvt_near_plane_dist(near_plane_dist),
          prvt_far_plane_dist(far_plane_dist),
          prvt_modified(true)
    {
        assert(near_plane_dist < far_plane_dist);
        assert(width > 0);
        assert(height > 0);
    }

    /** \brief Constructor (1 prvt_pos vector and 3 dir components).
    *
    * \param prvt_pos : the 3D position of the eye of the camera
    * \param dir_x : the x position of the targeted viewing point
    * \param dir_y : the y position of the targeted viewing point
    * \param dir_z : the z position of the targeted viewing point
    * \param angle : the angle of rotation of the vertical axis of the camera. Caution: degrees, not radians!
    * \param width : the width of the viewing near-plane for the camera projection, in pixels
    * \param height : the height of the viewing near-plane for the camera projection, in pixels
    * \param near_plane_dist : the distance of the near plane (i.e. projection plane) for this camera
    * \param far_plane_dist : the distance of the far plane (i.e. far culling plane) for this camera
    */
    Camera<TScalar>(const Position<TScalar> prvt_pos,
        const TScalar dir_x,
        const TScalar dir_y,
        const TScalar dir_z,
        const TScalar angle,
        const TScalar width,
        const TScalar height,
        const TScalar near_plane_dist,
        const TScalar far_plane_dist)
        : prvt_pos(pos),
          prvt_dir(dir_x, dir_y, dir_z),
          prvt_width(width),
          prvt_height(height),
          prvt_angle(angle),
          prvt_near_plane_dist(near_plane_dist),
          prvt_far_plane_dist(far_plane_dist),
          prvt_modified(true)
    {
        assert(near_plane_dist < far_plane_dist);
        assert(width > 0);
        assert(height > 0);
    }

    /** \brief Constructor (2 prvt_pos and dir vectors).
    *
    * \param pos : the 3D position of the eye of the camera
    * \param dir : the 3D position of the targeted viewing point
    * \param angle : the prvt_angle of rotation of the vertical axis of the camera. Caution: degrees, not radians!
    * \param width : the prvt_width of the viewing near-plane for the camera projection, in pixels
    * \param height : the prvt_height of the viewing near-plane for the camera projection, in pixels
    * \param near_plane_dist : the distance of the near plane (i.e. projection plane) for this camera
    * \param far_plane_dist : the distance of the far plane (i.e. far culling plane) for this camera
    */
    Camera<TScalar>(const Position<TScalar> pos,
        const Position<TScalar> dir,
        const TScalar angle,
        const TScalar width,
        const TScalar height,
        const TScalar near_plane_dist,
        const TScalar far_plane_dist)
        : prvt_pos(pos),
          prvt_dir(dir),
          prvt_width(width),
          prvt_height(height),
          prvt_angle(angle),
          prvt_near_plane_dist(near_plane_dist),
          prvt_far_plane_dist(far_plane_dist),
          prvt_modified(true)
    {
        assert(near_plane_dist < far_plane_dist);
        assert(width > 0);
        assert(height > 0);
    }


    /** \brief Returns a pointer to the projection matrix associated with this camera.
    *
    * Notice: Automatically evaluates the matrix before returning
    *       it when any modification took place  after  the  last
    *       call to thismethod and before its current call.
    * 
    * \return a pointer to this camera projection matrix, or NULL
    *       if current status of this camera specification is not
    *       ok - for instance, because or wrong width,  height or
    *       inverted near and far planes distances.
    */
    Mat<TScalar>* projection_matrix()
    {
        if (is_ok()) {
            if (prvt_modified)
                prvt_evaluate_matrix();
            return &prvt_mat;
        }
        else
            return (Mat<TScalar>*) NULL;
    }

    /** \brief shortcut to method 'projection_matrix'. */
    inline Mat<TScalar>* M() { return projection_matrix(); }


    /** \brief Returns true if this camera specification is ok, or false otherwise. */
    const bool is_ok() const
    {
        return prvt_near_plane_dist > 0 && prvt_width > 0 && prvt_height > 0 && prvt_pos != prvt_dir;
    }


    /** \brief camera eye position getter. */
    const Position<TScalar>& pos() const
    {
        return prvt_pos;
    }

    /** \brief camera eye position setter (three scalar args). */
    void pos(const TScalar x, const TScalar y, const TScalar z)
    {
        prvt_pos.set(x, y, z);
        prvt_modify();
    }

    /** \brief camera eye position setter (one position arg). */
    void pos(const Position<TScalar>& pos)
    {
        prvt_pos.set(pos);
        prvt_modify();
    }


    /** \brief camera viewing targeted position getter. */
    const Position<TScalar>& dir() const
    {
        return prvt_dir;
    }

    /** \brief camera viewing targeted position setter (three scalar args). */
    void dir(const TScalar x, const TScalar y, const TScalar z)
    {
        prvt_dir.set(x, y, z);
        prvt_modify();
    }

    /** \brief camera viewing targeted position setter (one position arg). */
    void dir(const Position<TScalar>& dir)
    {
        prvt_dir.set(dir);
        prvt_modify();
    }


    /** \brief Camera projection plane width getter (pixels) */
    const TScalar width() const
    {
        return prvt_width;
    }
    /** \brief Camera projection plane width setter (pixels). */
    void width(const TScalar new_width)
    {
        assert(new_width > 0);
        prvt_width = new_width;
        prvt_modify();
    }

    /** \brief Camera projection plane height getter (pixels) */
    const TScalar height() const
    {
        return prvt_height;
    }
    /** \brief Camera projection plane height setter (pixels). */
    void height(const TScalar new_height)
    {
        assert(new_height > 0);
        prvt_height = new_height;
        prvt_modify();
    }

    /** \brief Camera projection plane rotation angle getter (degrees, not radians!). */
    const TScalar angle() const
    {
        return prvt_angle;
    }
    /** \brief Camera projection plane rotation angle setter (degrees, not radians!). */
    void angle(const TScalar new_angle)
    {
        prvt_angle = new_angle;
        prvt_modify();
    }

    /** \brief Camera projection near plane distance getter. */
    const TScalar near_plane_dist() const
    {
        return prvt_near_plane_dist;
    }
    /** \brief Camera projection near plane distance setter. */
    void near_plane_dist(const TScalar new_dist)
    {
        assert(new_dist > 0);
        prvt_near_plane_dist = new_dist;
        prvt_modify();
    }

    /** \brief Camera projection far plane distance getter. */
    const TScalar far_plane_dist() const
    {
        return prvt_far_plane_dist;
    }
    /** \brief Camera projection far plane distance setter. */
    void far_plane_dist(const TScalar new_dist)
    {
        assert(new_dist > 0);
        prvt_far_plane_dist = new_dist;
        prvt_modify();
    }


private:
    TScalar prvt_width;             // the width of the viewing near-plane, in pixels.
    TScalar prvt_height;            // the height of the viewing near-plane, in pixels.
    TScalar prvt_angle;             // the angle of rotation of the vertical axis of the camera.
    TScalar prvt_near_plane_dist;   // the distance of the near plane (i.e. projection plane) for this camera.
    TScalar prvt_far_plane_dist;    // the distance of the far plane (i.e. far culling plane) for this camera.
    Position<TScalar> prvt_pos;     // the position of the camera origin.
    Position<TScalar> prvt_dir;     // the position of the camera viewing target.
    Mat<TScalar> prvt_mat;          // the projection matrix for this camera.
    bool prvt_modified;             // the modified status of this camera spec.


    void prvt_modify(const bool b_modified = true)
    {
        // modifies the internal status of this camera specification
        // if true, the projection matrix is no more valid and must be evaluated again.
        prvt_modified = b_modified;
    }

    void prvt_evaluate_matrix()
    {
        // the private evaluation of the transformation
        // matrix associated with this camera

        // first, sets the rotation matrix around the camera origin
        prvt_mat = Mat<TScalar>::get_identity();
        if (prvt_angle != 0) {
            prvt_mat(0, 0) =   prvt_mat(1, 1) = cos(prvt_angle);
            prvt_mat(0, 1) = -(prvt_mat(1, 0) = sin(prvt_angle));
        }

        // then, prepares the perspective transformation
        Mat<TScalar> perspective_mat;
        perspective_mat(0, 0) = 2 * prvt_near_plane_dist / prvt_width;
        perspective_mat(1, 1) = 2 * prvt_near_plane_dist / prvt_height;
        perspective_mat(2, 2) = (prvt_near_plane_dist + prvt_far_plane_dist) / (prvt_near_plane_dist - prvt_far_plane_dist);
        perspective_mat(2, 3) = 2 * prvt_near_plane_dist * prvt_far_plane_dist / (prvt_far_plane_dist - prvt_near_plane_dist);
        perspective_mat(3, 2) = -1;
        perspective_mat(3, 3) = 0;
        prvt_mat = perspective_mat * prvt_mat;

        // let's move to the eye position
        prvt_mat = MatTranslation<TScalar>(prvt_pos) * prvt_mat;

        // sets the current modification status to 'unmodified'.
        prvt_modify(false);
    }
};


//===========================================================================
/** \brief The generic class for orthographic projection cameras.
*
* Template argument 'TScalar' specifies the type of
* the cameras scalar components: float or double.
*
* \sa Camera, OrthoCameraF and OrthoCameraD.
*/
template<typename TScalar>
class OrthoCamera : public Camera<TScalar>
{
public:

};
