#ifndef SEEK_BEHAVIOUR_H
#define SEEK_BEHAVIOUR_H

#include "Behaviour.h"
#include "cMeshObject.h"

class SeekBehaviour : public Behaviour {
public:
	SeekBehaviour(cMeshObject* agent, cMeshObject* target, float maxSpeed, float maxForce);
	virtual ~SeekBehaviour(void);

	virtual void update(float dt);

private:
	cMeshObject* mTarget;
	cMeshObject* mAgent;
	float mMaxSpeed;
	float mMaxForce; //steering speed
};

#endif
