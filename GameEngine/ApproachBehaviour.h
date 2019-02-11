#ifndef APPROACH_BEHAVIOUR_H
#define APPROACH_BEHAVIOUR_H

#include "Behaviour.h"
#include "cMeshObject.h"

class ApproachBehaviour : public Behaviour {
public:
	ApproachBehaviour(cMeshObject* agent, cMeshObject* target, float maxSpeed, float maxForce, float radius, float shootRadius, float shotInterval);
	virtual ~ApproachBehaviour(void);

	virtual void update(float dt);

private:
	cMeshObject* mTarget;
	cMeshObject* mAgent;
	float mMaxSpeed;
	float mMaxForce; //steering speed
	float mRadius;
	float mShootRadius;
	float mTimeElapsedSinceLastShot;
	float mTimeToWait; //between shots
	bool mStart;
};

#endif
