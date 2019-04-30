#if !defined(CAMERA_H)
#define CAMERA_H
#include "EulerAngles.h"
#include "Geometry.h"
#include "Vector3.hpp"
#include "MathUtil.h"
class Camera
{
  public:
    Camera(float near_z,float far_z,float fov,float viewport_width,float viewport_height);
    Camera(Camera &&) = default;
    Camera(const Camera &) = default;
    Camera &operator=(Camera &&) = default;
    Camera &operator=(const Camera &) = default;

    void Update(unsigned int delta);
    void LookAt(Vector3f target);
    float theta = 0;
    Vector3f GetForward();
    
    const Vector3f& GetPos() const
    {
      return pos;
    }
    
    void SetPos(const Vector3f p)
    {
      pos = p;
      translate = TranslateMatrix(-pos.x, -pos.y, -pos.z);
      CalcToCameraMatrix();
    }

  private:
    Vector3f pos{0, 0, -10};
    EulerAngles dir{0, 0, 0};

    //uvn相机模型的朝向向量
    // Vector3f u;
    // Vector3f v;
    // Vector3f n;


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

    void CalcToCameraMatrix();
    void CalcPerMatrix();

  public:
    //变换矩阵
    Matrix4x4 mCam;    //世界坐标->相机坐标
    Matrix4x4 mPer;    //相机坐标->透视坐标
    Matrix4x4 mScreen; //透视坐标->屏幕坐标
private:
//平移和旋转的逆矩阵
  Matrix4x4 translate;
  Matrix4x4 rotation;
};

#endif // CAMERA_H
