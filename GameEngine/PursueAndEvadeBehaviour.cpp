#include "PursueAndEvadeBehaviour.h"
#include "globalStuff.h"
cMeshObject* CheckProjDist(cMeshObject* agent, std::string projectileName, float evadeDist);
PursueAndEvadeBehaviour::PursueAndEvadeBehaviour(cMeshObject* agent, cMeshObject* target, float maxSpeed, float maxForce, float evadeDist)
	: mAgent(agent)
	, mTarget(target)
	, mMaxSpeed(maxSpeed)
	, mMaxForce(maxForce)
	, mEvadeDist(evadeDist)
{

}

PursueAndEvadeBehaviour::~PursueAndEvadeBehaviour(void)
{
}

void PursueAndEvadeBehaviour::update(float dt)
{
	

	if (mAgent == 0 || mTarget == 0) return;
//	glm::vec3 ToTarget = mTarget->position - mAgent->position;
	cMeshObject* bullet = CheckProjDist(mAgent, "beam", mEvadeDist);
	//EVADE BULLETS
	if(bullet)
	{
		
		float T = 1.1f;
		glm::vec3 futurePosition = bullet->position + bullet->velocity * T;
		
			//normalize it and scale by mMaxSpeed
		glm::vec3 undesired = futurePosition - mAgent->position;
		undesired = glm::normalize(undesired) * mMaxSpeed;
			//float d = glm::length(desired);
			/*if (d < 10.0f) {
				float m = map(d, 0, 10, 0, mMaxSpeed);
				desired = glm::normalize(desired) * m;
			}
			else {
				desired = glm::normalize(desired) * mMaxSpeed;
			}*/
		undesired *= -1.0f;
			glm::vec3 steering = undesired - mAgent->velocity;

			if (glm::length(steering) > mMaxForce) 
			{
				steering = glm::normalize(steering) * mMaxForce;
			}
			//steering = glm::normalize(desired) * mMaxForce;
			mAgent->accel = steering * 12.0f;

			glm::mat4 rot = glm::inverse(glm::lookAt(mAgent->position, mAgent->position + mAgent->velocity, glm::vec3(0.0f, 1.0f, 0.0f)));
			mAgent->m_meshQOrientation = glm::quat(rot);
		
	}
	else
	{

	//float T  = glm::length(ToTarget)/ mMaxSpeed;
	//float T = 10.0f;
	float T = glm::distance(mAgent->position, mTarget->position) / 30.0f;

	glm::vec3 futurePosition = mTarget->position + mTarget->velocity * T * 1.2f;

	glm::vec3 desired = futurePosition - mAgent->position;
	//normalize it and scale by mMaxSpeed
	desired = glm::normalize(desired) * mMaxSpeed;
	float d = glm::length(desired);
	if (d < 15.0f) {
		float m = map(d, 0, 15, 0, mMaxSpeed);
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
}


cMeshObject* CheckProjDist(cMeshObject* agent, std::string projectileName, float evadeDist)
{
	for (int i = 0; i < vec_pObjectsToDraw.size(); i++)
	{

		if(vec_pObjectsToDraw[i]->friendlyName == projectileName)
		{
			if (glm::distance(agent->position, vec_pObjectsToDraw[i]->position) < evadeDist) 
			{
				glm::vec3 ToPlayer = agent->position - vec_pObjectsToDraw[i]->position;
				glm::vec3 beemLook = vec_pObjectsToDraw[i]->velocity;
				float dot = glm::dot(ToPlayer, beemLook);
				float angle = glm::acos(dot / (glm::length(ToPlayer)*glm::length(beemLook)));
				angle = angle * (180.0 / 3.14);

				if (angle < 45.0f)
				{
					return vec_pObjectsToDraw[i];
				}
				else
				{
					continue;
				}
			}
		}
	}
	return nullptr;
}
