#pragma once

#include "Component.h"
#include "Texture.h"
#include "vector_float4.hpp"
#include <array>
#include <memory>

class SpriteComponent : public Component{
    private:
        unsigned long long id;
        glm::vec4 color;
        std::shared_ptr<Texture::Texture> texture;
        glm::vec4 texCoordMin,texCoordMax;
    public:
        SpriteComponent();
        ~SpriteComponent();
        void init();
        void destroy();
        void Imgui();

        const glm::vec4& getColor() const;
        const std::shared_ptr<Texture::Texture>& getTexturePtr() const;
        const std::array<glm::vec4, 2> getTexCoords() const;
        const unsigned long long getId();

        void setColor(const glm::vec4& val);
        void setTexturePtr(const Texture::Texture& val);
        void setTexCoords(const std::array<glm::vec4, 2>& texCoords);
};
