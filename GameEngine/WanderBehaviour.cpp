#include "WanderBehaviour.h"
//#include <GLFW/glfw3.h>
#include <iostream>
#include "globalStuff.h"


float RandomFloat(float a, float b);
WanderBehaviour::WanderBehaviour(cMeshObject* agent, float maxSpeed, float maxForce, float timeToWait, glm::vec3 RelPos, float upLim, float dwLim)
	: mAgent(agent)
	//, mTarget(target)
	, mMaxSpeed(maxSpeed)
	, mMaxForce(maxForce)
	, mTimeToWait(timeToWait)
	, mRelPos(RelPos)
	, mUpLim(upLim)
	, mDwnLim(dwLim)
{
	mStart = true;
	mCurTarget = glm::vec3(mRelPos.x + RandomFloat(mDwnLim, mUpLim), 0.0f, mRelPos.z + RandomFloat(mDwnLim, mUpLim));
	mTimeWaitedSoFar = 0.0f;
}

WanderBehaviour::~WanderBehaviour(void)
{
}

void WanderBehaviour::update(float dt)
{
	//float curTime = 3.1f;
	if (mAgent == 0) return;
	
	


	if (glm::distance(mAgent->position, mCurTarget) > 5.0f) {

		glm::vec3 desired = mCurTarget - mAgent->position;
		//normalize it and scale by mMaxSpeed
		desired = glm::normalize(desired) * mMaxSpeed;
		float d = glm::length(desired);
		if (d < 10.0f) {
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
		//
	}
	else if (mTimeToWait != 0.0f)
	{ 
		mAgent->velocity = glm::vec3(0.0f);
		if (mStart) {
			mTimeWaitedSoFar = 0.0f;
			mStart = false;
		}
		//mAgent->velocity = glm::vec3(0.0f);
		//mAgent->accel = glm::vec3(0.0f);
		mTimeWaitedSoFar += (float)dt;
		if (mTimeWaitedSoFar > mTimeToWait)
		{
			mCurTarget = glm::vec3(mRelPos.x + RandomFloat(mDwnLim, mUpLim), 0.0f, mRelPos.z + RandomFloat(mDwnLim, mUpLim));
			mStart = true;
		}
	}
	else
	{
		mCurTarget = glm::vec3(mRelPos.x + RandomFloat(mDwnLim, mUpLim), 0.0f, mRelPos.z + RandomFloat(mDwnLim, mUpLim));
	}
	
	cMeshObject* pDebugSph = findObjectByFriendlyName("DebugSphere");
	pDebugSph->position = mCurTarget;
	pDebugSph->setUniformScale(2.0f);
	pDebugSph->setDiffuseColour(glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 iden = glm::mat4(1.0f);
	DrawObject(pDebugSph, iden, program);
	
}


float RandomFloat(float a, float b) {
	//srand(glfwGetTime());
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}
