
#ifndef FLEE_BEHAVIOUR_H
#define FLEE_BEHAVIOUR_H

#include "Behaviour.h"
#include "cMeshObject.h"

class FleeBehaviour : public Behaviour {
public:
	FleeBehaviour(cMeshObject* agent, cMeshObject* target, float maxSpeed, float maxForce);
	virtual ~FleeBehaviour(void);
	virtual void update(float dt);

private:
	cMeshObject* mTarget;
	cMeshObject* mAgent;
	float mMaxSpeed;
	float mMaxForce; //steering speed
};

#endif
