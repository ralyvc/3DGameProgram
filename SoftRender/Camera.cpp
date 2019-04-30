#include "Camera.h"
#include "Geometry.h"
#include "MathUtil.h"
Camera::Camera( float near_z, float far_z, float fov, float viewport_width, float viewport_height)
{
    near_clip_z = near_z;
    far_clip_z = far_z;
    this->viewport_width = viewport_width;
    this->viewport_height = viewport_height;
    viewport_center_x = (viewport_width - 1) / 2;
    viewport_center_y = (viewport_height - 1) / 2;
    aspect_ratio = viewport_width / viewport_height;
    mCam.Identity();
    mPer.Identity();
    mScreen.Identity();
    this->fov = fov;
    viewplane_width = 2;
    viewplane_height = viewplane_width / aspect_ratio;
    float tan_fov_div2 = tan(RadiansFromDegrees(fov / 2));
    view_dist = viewplane_width / 2.0 / tan_fov_div2;
    Vector3f pt(0, 0, 0);

    //法向量
    Vector3f vn;
    vn = Vector3f(view_dist, 0, -viewplane_width / 2);
    rt_clip_plane = Plane(vn, pt);
    vn = Vector3f(-view_dist, 0, -viewplane_width / 2);
    lt_clip_plane = Plane(vn, pt);
    vn = Vector3f(0, view_dist, -viewplane_width / 2);
    tp_clip_plane = Plane(vn, pt);
    vn = Vector3f(0, -view_dist, -viewplane_width / 2);
    bt_clip_plane = Plane(vn, pt);

    translate = TranslateMatrix(-pos.x, -pos.y, -pos.z);
    rotation = RotationMatrix(dir).Transpose();
    CalcToCameraMatrix();

    CalcPerMatrix();
}

void Camera::LookAt(Vector3f target)
{
    auto n = (target - pos).normalized();
    Vector3f v = Vector3f(0, 1, 0);
    auto u = (v.crossProduct(n)).normalized();
    v = n.crossProduct(u);

    rotation(0, 0) = u.x;
    rotation(1, 0) = u.y;
    rotation(2, 0) = u.z;

    rotation(0, 1) = v.x;
    rotation(1, 1) = v.y;
    rotation(2, 1) = v.z;

    rotation(0, 2) = n.x;
    rotation(1, 2) = n.y;
    rotation(2, 2) = n.z;

    CalcToCameraMatrix();

    dir = EulerAngles(RotationMatrix(rotation.Transpose()));
}

Vector3f Camera::GetForward()
{
    return Vector3f(mCam(0, 2), mCam(1, 2), mCam(2, 2));
}

void Camera::CalcToCameraMatrix()
{
    mCam = translate * rotation;
}


void Camera::CalcPerMatrix()
{
    mPer.Zero();
    mPer(0, 0) = 2 * near_clip_z / viewplane_width;
    mPer(1, 1) = 2 * near_clip_z / viewplane_height;
    mPer(2, 3) = far_clip_z / (far_clip_z - near_clip_z);
    mPer(2, 2) = -mPer(2, 2) * near_clip_z;
    mPer(3, 2) = 1;
}


void Camera::Update(unsigned int delta)
{

    //CalcPerMatrix();

    //LookAt(Vector3f(0, 0, 0));
    //auto rot = AngleAxis(theta, Vector3f(0, 1, 0));

    //mCam = RotationMatrix(rot).Transpose() * TranslateMatrix(-pos.x, -pos.y, -pos.z);

    //dir = EulerAngles(mCam);

}