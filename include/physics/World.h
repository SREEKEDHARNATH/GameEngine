#pragma once
#include "id.h"
#include "math_functions.h"
#include "types.h"

namespace physics {
    class world{
        private:
            b2WorldDef worldDef;
            b2WorldId worldId;

            b2BodyDef groundDef;
            b2BodyId groundId;

            bool hasInited=false;
        public:
            void init(b2Vec2 gravity=(b2Vec2){0.0f, -10.0f}, b2Vec2 groundPos=(b2Vec2){0.0f, -10.0f});

            void createBody(b2BodyId& bodyId,b2BodyDef& bodyDef, b2Vec2& bodyPos, b2BodyType type=b2_dynamicBody,bool fixedRotation = false, void* userData = nullptr);
            void destroy();
            void simulate(float fps=60.0f, int subStepCount=4);
            b2WorldId getId();

    };

}
