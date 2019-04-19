#include "Scene.h"
#include "Camera.h"
#include "Model.h"
#include <string>

Scene::Scene()
{
    SetupCamera();
    LoadModels();
}

Scene::~Scene()
{
    for (auto model : models)
    {
        delete model;
    }

    if (mainCamera)
    {
        delete mainCamera;
        mainCamera = NULL;
    }
}

void Scene::Update(unsigned int delta)
{
    for (auto model : models)
    {
        model->Update(delta);
        visibleModels.push(model);
    }
}

void Scene::LoadModels()
{
    std::string path = "test.obj";
    models.push_back(new Model(path));
}

void Scene::SetupCamera()
{
    mainCamera = new Camera(2,1000,120,1280,720);
    mainCamera->LookAt(Vector3f(0, 0, 0));
}
