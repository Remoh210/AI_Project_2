#ifndef SEEK_AND_FLEE_BEHAVIOUR_H
#define SEEK_AND_FLEE_BEHAVIOUR_H

#include "Behaviour.h"
#include "cMeshObject.h"

class SeekAndFleeBehaviour : public Behaviour {
public:
	SeekAndFleeBehaviour(cMeshObject* agent, cMeshObject* target, float maxSpeed, float maxForce, float seekDist, float angle, float fleeDist);
	virtual ~SeekAndFleeBehaviour(void);

	virtual void update(float dt);

private:
	cMeshObject* mTarget;
	cMeshObject* mAgent;
	float mMaxSpeed;
	float mMaxForce; //steering speed
	float mAngle; //Angle when start to flee
	float mSeekDist;
	float mFleeDist;
};

#endif
