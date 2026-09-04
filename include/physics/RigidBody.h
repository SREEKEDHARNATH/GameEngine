#pragma once

#include "World.h"
#include "id.h"
#include "math_functions.h"
#include "types.h"
namespace physics {
    class RigidBody{
        private:
            b2BodyId bodyId;
            b2BodyDef bodyDef;
            b2Vec2 bodyPos;
            b2BodyType type=b2_dynamicBody;
            bool fixedRotation=false;
            void* userData=this;
            bool fastRotation=false;
            float angularVelocity=1.0f, angularDamping=0.0f;
            b2Rot rotation=(b2Rot)0.0f;
            bool isBullet=false;
            world* physicsWorld=nullptr;

        public:
            void create();
            void destroy();

            const b2Vec2& getBodyPos() const;
            const b2BodyType getType() const;
            const bool getFixedRotation() const;
            const void* getUserData() const;
            const bool getFastRotation() const;
            const float getAngularVelocity() const;
            const float getAngularDamping() const;
            const b2Rot& getRotation() const;
            const bool getIsBullet() const;
            const world* getPhysicsWorld() const;

            void setBodyPos(const b2Vec2& newBodyPos);
            void setType(b2BodyType newType);
            void setFixedRotation(bool newFixedRotation);
            void setUserData(void* newUserData);
            void setFastRotation(bool newFastRotation);
            void setAngularVelocity(float newAngularVelocity);
            void setAngularDamping(float newAngularDamping);
            void setRotation(const b2Rot& newRotation);
            void setIsBullet(bool newIsBullet);
            void setPhysicsWorld(world* newPhysicsWorld);
    };
}
