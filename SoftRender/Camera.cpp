#include "Camera.h"
#include "Geometry.h"
#include "MathUtil.h"
Camera::Camera(const Vector3f &pos, const Vector3f &dir, float near_z, float far_z, float fov, float viewport_width, float viewport_height)
{
    this->pos = pos;
    this->dir = dir;
    this->u = Vector3f(1, 0, 0);
    this->v = Vector3f(0, 1, 0);
    this->n = Vector3f(0, 0, 1);
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

    CalcMatrix();
}




void Camera::CalcMatrix()
{
    Matrix4x4 matRotInv = RotationMatrix(dir).Transpose();
    Matrix4x4 matTranslate = TranslateMatrix(-pos.x, -pos.y, -pos.z);
    mCam = matTranslate * matRotInv;
    mPer.Zero();
    mPer(0, 0) = 2 * near_clip_z / viewplane_width;
    mPer(1, 1) = 2 * near_clip_z / viewplane_height;
    mPer(2, 2) = far_clip_z / (far_clip_z - near_clip_z);
    mPer(2, 3) = -mPer(2, 2) * near_clip_z;
    mPer(3, 2) = 1;
}

void Camera::Update()
{

}