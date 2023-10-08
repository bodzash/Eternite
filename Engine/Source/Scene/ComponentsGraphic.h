#pragma once
#include <glm/glm.hpp>

namespace Raylib {
    #include <raylib.h>
}

// TODO: should abstact away raylib as much as possible
// create wrapper classes for these

namespace Apex {

    struct MeshComponent
    {
        // TODO: do not use strings, use a smart pointer (ref or scope) :D
        //std::string Name;
        Raylib::Model Model = { 0 };

        MeshComponent(std::string_view path)
        {
            Model = Raylib::LoadModel(path.data());
        }
        MeshComponent() = default;
        MeshComponent(const MeshComponent&) = default;
        // should have one more constructor that takes in a smart pointer to the mesh
    };

    struct CameraComponent
    {
        Raylib::Camera3D Camera = { 0 };
        bool Primary = false;

        CameraComponent(Raylib::Camera3D camera)
        {
            Camera = camera;
        }
        CameraComponent()
        {
            // Default camera
            Camera.position = { 0.0f, 0.0f, 0.0f };
            Camera.target = { 1.0f, 0.0f, 0.0f };
            Camera.up = { 0.0f, 1.0f, 0.0f };
            Camera.fovy = 63.0f;
            Camera.projection = Raylib::CAMERA_PERSPECTIVE;
        }
        CameraComponent(const CameraComponent&) = default;
    };
    

}