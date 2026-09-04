#include "BoxCollider.h"
#include "box2d.h"
#include "collision.h"
#include "id.h"
#include "math_functions.h"
#include "types.h"
#include "vector_float2.hpp"
#include <algorithm>
namespace physics {

    void BoxCollider::init(b2BodyId bodyId, glm::vec2 size, float density, bool isSensor, glm::vec2 centre, b2Rot rotation, float friction, float bounciness) {
            b2Polygon box = b2MakeOffsetBox(size.x * 0.5f, size.y * 0.5f, (b2Vec2){centre.x, centre.y}, rotation);

            b2ShapeDef shapeDef = b2DefaultShapeDef();
            shapeDef.density = density;
            shapeDef.isSensor = isSensor;
            shapeDef.material.friction = friction;
            shapeDef.material.restitution=std::min(std::max(0.0f, bounciness), 1.0f);
            shapeDef.userData=this;
            shapeId = b2CreatePolygonShape(bodyId, &shapeDef, &box);
        }

    void BoxCollider::destroy() {
            if (b2Shape_IsValid(shapeId)) {
                b2DestroyShape(shapeId, true);
                shapeId = b2_nullShapeId;
            }
        }

    b2ShapeId BoxCollider::getShapeId() const noexcept { return shapeId; }

}
