#include "Scene.h"
#include <string>
#include "Model.h"
#include "Camera.h"

Scene::Scene()
{
    LoadModels();
    SetupCamera();
}

Scene::~Scene()
{
    for(auto model : models)
    {
        delete model;
    }   
}

void Scene::Update(unsigned int delta)
{
    for(auto model : models)
    {
        model->Update(delta);
    }
}

void Scene::LoadModels()
{
    std::string path = "";
    models.push_back(new Model(path));
}

void Scene::SetupCamera()
{
    
}
