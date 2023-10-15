#pragma once
#include <glm/glm.hpp>

namespace Raylib {
    // NOTE: this is because of WinUser.h :)
    #undef LoadImage
    #include <raylib.h>
}

// TODO: should abstact away raylib as much as possible
// create wrapper classes for Mesh, Camera, etc...

namespace Apex {

    struct ModelComponent
    {
        // TODO: DO NOT LOAD MODELS, TEXTURES LIKE THIS, CREATE A RESOURCE MANAGER
        Raylib::Model Model = { 0 };
        
        ModelComponent(std::string_view path)
        {
            Model = Raylib::LoadModel(path.data());
        }

        ModelComponent(std::string_view modelPath, std::string_view materialPath)
        {
            Model = Raylib::LoadModel(modelPath.data());

            Raylib::Image img = Raylib::LoadImage(materialPath.data());
            Raylib::ImageMipmaps(&img);
            Raylib::Texture2D texture = Raylib::LoadTextureFromImage(img);
            Model.materials[0].maps[Raylib::MATERIAL_MAP_DIFFUSE].texture = texture;
            UnloadImage(img);
        }
        ModelComponent() = default;
        ModelComponent(const ModelComponent&) = default;
        // should have one more constructor that takes in a smart pointer to the mesh and shit
    };

    /*
    struct MeshComponent
    {
        MeshComponent() = default;
        MeshComponent(const MeshComponent&) = default;
    };
    */

    struct CameraComponent
    {
        // NOTE: this lines up with Raylib's
        enum class ProjectionType { Perspective = 0, Orthographic };

        // TODO: abstract camera away man
        Raylib::Camera3D Camera = { 0 };
        bool Primary = false;

        CameraComponent(Raylib::Camera3D camera)
        {
            Camera = camera;
        }
        CameraComponent()
        {
            // Default camera
            Camera.position = { 5.0f, 5.0f, 5.0f };
            Camera.target = { 0.0f, 0.0f, 0.0f };
            Camera.up = { 0.0f, 1.0f, 0.0f };
            Camera.fovy = 63.0f;
            Camera.projection = (int)ProjectionType::Perspective;
        }
        CameraComponent(const CameraComponent&) = default;
    };
    
}