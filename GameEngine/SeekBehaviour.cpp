#include "SeekBehaviour.h"

#include <iostream>

SeekBehaviour::SeekBehaviour(cMeshObject* agent, cMeshObject* target, float maxSpeed, float maxForce)
	: mAgent(agent)
	, mTarget(target)
	, mMaxSpeed(maxSpeed)
	, mMaxForce(maxForce)
{

}

SeekBehaviour::~SeekBehaviour(void)
{
}

void SeekBehaviour::update(float dt)
{
	
	if (mAgent == 0 || mTarget == 0) return;


		glm::vec3 desired = mTarget->position - mAgent->position;
		//normalize it and scale by mMaxSpeed
		desired = glm::normalize(desired) * mMaxSpeed;
		float d = glm::length(desired);
		if (d < 20.0f) {
			float m = map(d, 0, 10, 0, mMaxSpeed);
			desired = glm::normalize(desired) * m;
		}
		else {
			desired = glm::normalize(desired) * mMaxSpeed;
		}

		glm::vec3 steering = desired - mAgent->velocity;

		if (glm::length(steering) > mMaxForce) {
			steering = glm::normalize(steering) * mMaxForce;
		}
		//steering = glm::normalize(desired) * mMaxForce;
		mAgent->accel = steering;

		glm::mat4 rot = glm::inverse(glm::lookAt(mAgent->position, mAgent->position + mAgent->velocity, glm::vec3(0.0f, 1.0f, 0.0f)));
		mAgent->m_meshQOrientation = glm::quat(rot);
	
}

