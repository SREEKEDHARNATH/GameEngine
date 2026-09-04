#include "CircleCollider.h"
#include "box2d.h"
#include "collision.h"
#include "id.h"
#include "math_functions.h"
#include "types.h"
#include "vector_float2.hpp"
#include <algorithm>
namespace physics {

    void CircleCollider::init(b2BodyId bodyId, glm::vec2 centre, float radius, float density, bool isSensor, float bounciness, float friction) {
            b2Circle circle;
            circle.center = (b2Vec2){centre.x, centre.y};
            circle.radius=radius;

            b2ShapeDef shapeDef = b2DefaultShapeDef();
            shapeDef.density = density;
            shapeDef.isSensor = isSensor;
            shapeDef.material.friction=friction;
            shapeDef.material.restitution=std::min(std::max(0.0f, bounciness), 1.0f);
            shapeDef.userData = this;
            shapeId = b2CreateCircleShape(bodyId, &shapeDef, &circle);
        }

    void CircleCollider::destroy() {
            if (b2Shape_IsValid(shapeId)) {
                b2DestroyShape(shapeId, true);
                shapeId = b2_nullShapeId;
            }
        }

    b2ShapeId CircleCollider::getShapeId() const noexcept { return shapeId; }

}
