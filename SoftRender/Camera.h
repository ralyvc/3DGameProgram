#if !defined(CAMERA_H)
#define CAMERA_H
#include "EulerAngles.h"
#include "Geometry.h"
#include "Vector3.hpp"
class Camera
{
  public:
    Camera(const Vector3f&  pos,const Vector3f &dir, float near_z,float far_z,float fov,float viewport_width,float viewport_height);
    Camera(Camera &&) = default;
    Camera(const Camera &) = default;
    Camera &operator=(Camera &&) = default;
    Camera &operator=(const Camera &) = default;

    void Update();

  private:
    Vector3f pos;
    EulerAngles dir;

    //uvn相机模型的朝向向量
    Vector3f u;
    Vector3f v;
    Vector3f n;

    Vector3f target;

    //水平视距和垂直视距
    float view_dist;

    //水平和垂直方向上的视野
    float fov;

    float near_clip_z;
    float far_clip_z;

    Plane rt_clip_plane;
    Plane lt_clip_plane;
    Plane tp_clip_plane;
    Plane bt_clip_plane;

    //视平面的宽度和高度
    float viewplane_width;
    float viewplane_height;

    //屏幕/视口的大小
    float viewport_width;
    float viewport_height;
    float viewport_center_x;
    float viewport_center_y;

    //屏幕宽高比
    float aspect_ratio;

    void CalcMatrix();

  public:
    //变换矩阵
    Matrix4x4 mCam;    //世界坐标->相机坐标
    Matrix4x4 mPer;    //相机坐标->透视坐标
    Matrix4x4 mScreen; //透视坐标->屏幕坐标

};

#endif // CAMERA_H
