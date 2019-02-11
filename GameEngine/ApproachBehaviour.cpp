#include "ApproachBehaviour.h"
#include "shoot.h"

#include <iostream>
bool first = true;
ApproachBehaviour::ApproachBehaviour(cMeshObject* agent, cMeshObject* target, float maxSpeed, float maxForce, float radius, float shootRadius, float shotInterval)
	: mAgent(agent)
	, mTarget(target)
	, mMaxSpeed(maxSpeed)
	, mMaxForce(maxForce)
	, mRadius(radius)
	, mShootRadius(shootRadius)
	, mTimeToWait(shotInterval)

{
	//mRadius = 50.0f;
	mTimeElapsedSinceLastShot = 0.0f;
	//mTimeToWait = 1.0f;
	mStart = true;
}

ApproachBehaviour::~ApproachBehaviour(void)
{
}

void ApproachBehaviour::update(float dt)
{

	if (mAgent == 0 || mTarget == 0) return;
	float distance = glm::distance(mTarget->position, mAgent->position);
	if (distance < mRadius)
	{

		mAgent->accel = glm::vec3(0.0f);
		mAgent->velocity = mAgent->velocity * 0.99f;
		if (distance < mShootRadius) {
			if (mStart) {
				mTimeElapsedSinceLastShot = 0.0f;
				mStart = false;
			}
			//mAgent->velocity = glm::vec3(0.0f);
			
			mTimeElapsedSinceLastShot += (float)dt;
			if (mTimeElapsedSinceLastShot > mTimeToWait)
			{
				shoot(mAgent, mTarget, 80.0f, glm::vec3(0.0f, 0.0f, -5.0f));
				mStart = true;
			}
		}
	}
		
	else 
	{
		glm::vec3 desired = mTarget->position - mAgent->position;
		//normalize it and scale by mMaxSpeed
		desired = glm::normalize(desired) * mMaxSpeed;
		float d = glm::length(desired);
		if (d < mRadius) {
			float m = map(d, 0, mRadius, 0, mMaxSpeed);
			desired = glm::normalize(desired) * m;
		}
		else {
			desired = glm::normalize(desired) * mMaxSpeed;
		}

		glm::vec3 steering = desired - mAgent->velocity;

		if (glm::length(steering) > mMaxForce) {
			steering = glm::normalize(steering) * mMaxForce;
		}
		mAgent->accel = steering * 3.0f;


	}
	glm::mat4 rot = glm::inverse(glm::lookAt(mAgent->position, mTarget->position, glm::vec3(0.0f, 1.0f, 0.0f)));
	mAgent->m_meshQOrientation = glm::quat(rot);


}

