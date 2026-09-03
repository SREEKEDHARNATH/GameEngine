#include "SpriteComponent.h"
#include "Texture.h"
#include "imgui.h"
#include "vector_float4.hpp"
#include <array>
#include <memory>
#include "Window.h"

SpriteComponent::SpriteComponent(){
    init();
}
SpriteComponent::~SpriteComponent(){
    destroy();
}
void SpriteComponent::init(){
    id = Window::getCounter();
}
void SpriteComponent::destroy(){
    texture->destroy();
}

const glm::vec4& SpriteComponent::getColor() const{
    return color;
}
void SpriteComponent::setColor(const glm::vec4& val){
    color=val;
}
void SpriteComponent::Imgui(){
    ImGui::Begin("Sprite");
    ImGui::ColorEdit4("Color", &color.x);
    ImGui::End();

}
const unsigned long long SpriteComponent::getId(){
    return id;
}

const std::shared_ptr<Texture::Texture>& SpriteComponent::getTexturePtr() const{
    return texture;
}
const std::array<glm::vec4, 2> SpriteComponent::getTexCoords() const{
    return std::array<glm::vec4, 2>({texCoordMin, texCoordMax});
}

void SpriteComponent::setTexturePtr(const Texture::Texture& val){
    if (texture && (texture.use_count() == 1)){
        texture->destroy();
    }
    texture = std::make_shared<Texture::Texture>(val);
}
void SpriteComponent::setTexCoords(const std::array<glm::vec4, 2>& texCoords){
    texCoordMin=texCoords[0];
    texCoordMax=texCoords[1];
}
