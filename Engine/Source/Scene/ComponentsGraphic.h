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

    // Rename to AnimatedModel or SkinnedModel
    struct ModelComponent
    {
        // TODO: DO NOT LOAD MODELS, TEXTURES LIKE THIS, CREATE A RESOURCE MANAGER

        // These are the "editor" things, for now we use paths, but later just filenames cuz rres
        std::string ModelPath = "";
        std::string TexturePath = "";
        std::string AnimationPath = "";

        // Maybe we can store unqie id's for these mf's, think about that

        // These are the runtime things
        // Load in the model and copy it (because animation fucks it up)
        Raylib::Model Model = { 0 };
        Raylib::Texture2D Texture;
        Raylib::ModelAnimation* Animations;
        int AnimsCount = 0;
        unsigned int AnimIndex = 0;
        unsigned int AnimCurrentFrame = 0;
        // Animation TODO: might be a seperate component maybe not idonfukinknow
        
        ModelComponent(std::string_view path)
        {
            ModelPath = path.data();
            Model = Raylib::LoadModel(path.data());
        }

        ModelComponent(std::string_view modelPath, std::string_view materialPath)
        {
            ModelPath = modelPath.data();
            TexturePath = materialPath.data();

            Model = Raylib::LoadModel(modelPath.data());

            Raylib::Image img = Raylib::LoadImage(materialPath.data());
            Raylib::ImageMipmaps(&img);
            Texture = Raylib::LoadTextureFromImage(img);
            Model.materials[0].maps[Raylib::MATERIAL_MAP_DIFFUSE].texture = Texture;
            UnloadImage(img);
        }

        ModelComponent(std::string_view modelPath, std::string_view materialPath, std::string_view animPath)
        {
            ModelPath = modelPath.data();
            TexturePath = materialPath.data();

            Model = Raylib::LoadModel(modelPath.data());

            Raylib::Image img = Raylib::LoadImage(materialPath.data());
            Raylib::ImageMipmaps(&img);
            Texture = Raylib::LoadTextureFromImage(img);
            Model.materials[0].maps[Raylib::MATERIAL_MAP_DIFFUSE].texture = Texture;
            UnloadImage(img);

            Animations = Raylib::LoadModelAnimations(animPath.data(), &AnimsCount);
        }

        ModelComponent() = default;
        ModelComponent(const ModelComponent&) = default;

        // SetModel
        // SetTexture
        // SetAnimation
    };

    struct BillboardComponent
    {
        // You know what this is
    };

    struct StaticModelComponent
    {
        // This is just a non-bone animated model
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
        enum class ProjectionType { Perspective = 0, Orthographic = 1 };

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