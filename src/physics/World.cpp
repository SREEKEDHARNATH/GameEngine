#include "World.h"
#include "box2d.h"
#include "id.h"
#include "math_functions.h"
#include "types.h"

namespace physics {

    void world::init(b2Vec2 gravity, b2Vec2 groundPos){
        worldDef=b2DefaultWorldDef();
        worldDef.gravity=gravity;
        worldId=b2CreateWorld(&worldDef);

        groundDef=b2DefaultBodyDef();
        groundDef.position=groundPos;
        groundId = b2CreateBody(worldId, &groundDef);

        hasInited=true;
    }

    void world::createBody(b2BodyId& bodyId,b2BodyDef& bodyDef, b2Vec2& bodyPos, b2BodyType type, bool fixedRotation, void* userData){
        if (hasInited){
            bodyDef = b2DefaultBodyDef();
            bodyDef.position=bodyPos;
            bodyDef.type=type;
            bodyDef.motionLocks.angularZ = fixedRotation;
            bodyDef.userData = userData;
            bodyId = b2CreateBody(worldId, &bodyDef);
        }
    }
    void world::destroy(){
        b2DestroyWorld(worldId);
        hasInited=false;
    }
    void world::simulate(float fps, int subStepCount){
        b2World_Step(worldId, 1.0f/fps, subStepCount);
    }
    b2WorldId world::getId(){return worldId;}

}
