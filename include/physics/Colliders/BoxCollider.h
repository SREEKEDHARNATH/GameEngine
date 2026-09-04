#pragma once

#include "id.h"
#include "math_functions.h"
#include "vector_float2.hpp"
namespace physics {
    class BoxCollider {
    private:
        b2ShapeId shapeId = b2_nullShapeId;

    public:
        void init(b2BodyId bodyId, glm::vec2 size, float density = 1.0f, bool isSensor = false, glm::vec2 centre={0.0f,0.0f}, b2Rot rotation=(b2Rot)0.0f, float friction=0.3f, float bounciness=0.5f);
        void destroy();
        b2ShapeId getShapeId() const noexcept;
    };
}
