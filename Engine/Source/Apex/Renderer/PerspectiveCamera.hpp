#pragma once
#include "glm/glm.hpp"

namespace Apex
{

    class PerspectiveCamera
    {
    public:
        PerspectiveCamera(/* TODO: TAKE IN SOME ARGUMETNS */);

        const glm::vec3& GetPosition() const { return m_Position; }
        void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }
        //void SetRotation(const glm::vec3& rotation) { m_Rotation = rotation; }
        // TODO: this above

        void SetProjection(float left, float right, float bottom, float top);
        const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
        const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
        const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix;; }
    private:
        void RecalculateViewMatrix();

    private:
        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ViewProjectionMatrix;

        glm::vec3 m_Position;
        //glm::vec3 m_Rotation;
        // TODO: others here
    };

}