#pragma once
#ifndef PURSUE_AND_EVADE_BEHAVIOUR_H
#define PURSUE_AND_EVADE_BEHAVIOUR_H

#include "Behaviour.h"
#include "cMeshObject.h"

class PursueAndEvadeBehaviour : public Behaviour {
public:
	PursueAndEvadeBehaviour(cMeshObject* agent, cMeshObject* target, float maxSpeed, float maxForce, float evadeDist);
	virtual ~PursueAndEvadeBehaviour(void);

	virtual void update(float dt);

private:
	cMeshObject* mTarget;
	cMeshObject* mAgent;
	float mMaxSpeed;
	float mMaxForce; //steering speed
	float mAngle; //Angle when start to flee
	float mSeekDist;
	float mEvadeDist;
};

#endif