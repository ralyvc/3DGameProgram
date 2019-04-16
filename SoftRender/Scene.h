#include <queue>
#include <vector>


class Camera;
class Model;
class Scene
{
  public:
    Scene();
    Scene(Scene &&) = default;
    Scene(const Scene &) = default;
    Scene &operator=(Scene &&) = default;
    Scene &operator=(const Scene &) = default;
    ~Scene();
    void Update(unsigned int delta);



  private:
    void LoadModels();
    void SetupCamera();
    std::vector<Model *> models;
    Camera *mainCamera;
};
