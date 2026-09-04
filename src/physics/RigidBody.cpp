#include "RigidBody.h"
#include "box2d.h"
#include "id.h"

namespace physics {

    void RigidBody::create(){
        if (physicsWorld){
            bodyDef = b2DefaultBodyDef();
            bodyDef.position=bodyPos;
            bodyDef.type=type;
            bodyDef.motionLocks.angularZ = fixedRotation;
            bodyDef.userData = userData;
            bodyDef.allowFastRotation=fastRotation;
            bodyDef.angularVelocity=angularVelocity;
            bodyDef.angularDamping=angularDamping;
            bodyDef.rotation=rotation;
            bodyId = b2CreateBody(physicsWorld->getId(), &bodyDef);
        }
    }
    void RigidBody::destroy(){
        if (b2Body_IsValid(bodyId)) {
            b2DestroyBody(bodyId);
            bodyId = b2_nullBodyId;

        }
    }
    const b2Vec2& RigidBody::getBodyPos() const {
        return bodyPos;
    }

    const b2BodyType RigidBody::getType() const {
        return type;
    }

    const bool RigidBody::getFixedRotation() const {
        return fixedRotation;
    }

    const void* RigidBody::getUserData() const {
        return userData;
    }

    const bool RigidBody::getFastRotation() const {
        return fastRotation;
    }

    const float RigidBody::getAngularVelocity() const {
        return angularVelocity;
    }

    const float RigidBody::getAngularDamping() const {
        return angularDamping;
    }

    const b2Rot& RigidBody::getRotation() const {
        return rotation;
    }

    const bool RigidBody::getIsBullet() const {
        return isBullet;
    }

    const world* RigidBody::getPhysicsWorld() const {
        return physicsWorld;
    }


    void RigidBody::setBodyPos(const b2Vec2& newBodyPos) {
        bodyPos = newBodyPos;
    }

    void RigidBody::setType(b2BodyType newType) {
        type = newType;
    }

    void RigidBody::setFixedRotation(bool newFixedRotation) {
        fixedRotation = newFixedRotation;
    }

    void RigidBody::setUserData(void* newUserData) {
        userData = newUserData;
    }

    void RigidBody::setFastRotation(bool newFastRotation) {
        fastRotation = newFastRotation;
    }

    void RigidBody::setAngularVelocity(float newAngularVelocity) {
        angularVelocity = newAngularVelocity;
    }

    void RigidBody::setAngularDamping(float newAngularDamping) {
        angularDamping = newAngularDamping;
    }

    void RigidBody::setRotation(const b2Rot& newRotation) {
        rotation = newRotation;
    }

    void RigidBody::setIsBullet(bool newIsBullet) {
        isBullet = newIsBullet;
    }

    void RigidBody::setPhysicsWorld(world* newPhysicsWorld) {
        physicsWorld = newPhysicsWorld;
    }
}
