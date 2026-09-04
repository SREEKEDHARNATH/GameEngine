#pragma once

#include "id.h"
#include "vector_float2.hpp"
namespace physics {
    class CircleCollider {
    private:
        b2ShapeId shapeId = b2_nullShapeId;

    public:
        void init(b2BodyId bodyId, glm::vec2 centre, float radius, float density = 1.0f, bool isSensor = false, float bounciness=0.5f, float friction=0.3f);
        void destroy();
        b2ShapeId getShapeId() const noexcept;
    };
}
