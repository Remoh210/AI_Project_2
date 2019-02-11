#include "FleeBehaviour.h"
#include <iostream>
//#include "HelpFuctions.h"


FleeBehaviour::FleeBehaviour(cMeshObject* agent, cMeshObject* target, float maxSpeed, float maxForce)
	: mAgent(agent)
	, mTarget(target)
	, mMaxSpeed(maxSpeed)
	, mMaxForce(maxForce)
{

}

FleeBehaviour::~FleeBehaviour(void)
{
}

void FleeBehaviour::update(float dt)
{

	if (mAgent == 0 || mTarget == 0) return;

	//desired vector
	glm::vec3 desired = mAgent->position - mTarget->position;
	glm::vec3 playerLook = mTarget->velocity;
	float dist = glm::distance(mAgent->position, mTarget->position);

	float d = glm::dot(desired, playerLook);
	float angle = glm::acos(d / (glm::length(desired)*glm::length(playerLook)));
	angle = angle * (180.0 / 3.14);
	std::cout << angle << std::endl;
	if (angle < 30.0f && dist < 60.0f) {

		//normalize it and scale by mMaxSpeed
		desired = glm::normalize(desired) * mMaxSpeed;
		//float d = glm::length(desired);
		/*if (d < 10.0f) {
			float m = map(d, 0, 10, 0, mMaxSpeed);
			desired = glm::normalize(desired) * m;
		}
		else {
			desired = glm::normalize(desired) * mMaxSpeed;
		}*/
		desired *= -1;
		glm::vec3 steering = desired - mAgent->velocity;

		if (glm::length(steering) > mMaxForce) {
			steering = glm::normalize(steering) * mMaxForce;
		}
		//steering = glm::normalize(desired) * mMaxForce;
		mAgent->accel = -steering;

		glm::mat4 rot = glm::inverse(glm::lookAt(mAgent->position, mAgent->position + mAgent->velocity, glm::vec3(0.0f, 1.0f, 0.0f)));
		mAgent->m_meshQOrientation = glm::quat(rot);
	}
	else
	{
		mAgent->velocity = glm::vec3(0.0f);
	}
}


