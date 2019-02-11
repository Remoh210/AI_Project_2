#include "SeekAndFleeBehaviour.h"
#include "HelpFuctions.h"


SeekAndFleeBehaviour::SeekAndFleeBehaviour(cMeshObject* agent, cMeshObject* target, float maxSpeed, float maxForce, float seekDist, float angle, float fleeDist)
	: mAgent(agent)
	, mTarget(target)
	, mMaxSpeed(maxSpeed)
	, mMaxForce(maxForce)
	, mAngle(angle)
	, mSeekDist(seekDist)
	, mFleeDist(fleeDist)
{
	
}

SeekAndFleeBehaviour::~SeekAndFleeBehaviour(void)
{
}

void SeekAndFleeBehaviour::update(float dt)
{
	if (mAgent == 0 || mTarget == 0) return;

	glm::vec3 ToPlayer = mAgent->position - mTarget->position;



	glm::vec4 vecForwardDirection_ModelSpace = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

	glm::quat qPlayer29Rotation = mTarget->getQOrientation();
	glm::mat4 matQPlayer29rotation = glm::mat4(qPlayer29Rotation);
	glm::vec4 vecForwardDirection_WorldSpace = matQPlayer29rotation * vecForwardDirection_ModelSpace;
	vecForwardDirection_WorldSpace = glm::normalize(vecForwardDirection_WorldSpace);









	glm::vec3 playerLook = vecForwardDirection_WorldSpace;
	float dist = glm::distance(mAgent->position, mTarget->position);
	float dot = glm::dot(ToPlayer, playerLook);
	float angle = glm::acos(dot / (glm::length(ToPlayer)*glm::length(playerLook)));
	angle = angle * (180.0 / 3.14);

	if (angle < mAngle && dist < mFleeDist) {
		//std::cout << angle << std::endl;
		//normalize it and scale by mMaxSpeed
		ToPlayer = glm::normalize(ToPlayer) * mMaxSpeed;
		ToPlayer *= -1;

		glm::vec3 steering = ToPlayer - mAgent->velocity;

		if (glm::length(steering) > mMaxForce) {
			steering = glm::normalize(steering) * mMaxForce;
		}
		//steering = glm::normalize(desired) * mMaxForce;
		mAgent->accel = -steering * 1.8f;

		glm::mat4 rot = glm::inverse(glm::lookAt(mAgent->position, mAgent->position + mAgent->velocity, glm::vec3(0.0f, 1.0f, 0.0f)));
		mAgent->m_meshQOrientation = glm::quat(rot);
	}
	else
	{
		glm::vec3 desired = mTarget->position - mAgent->position;
		//normalize it and scale by mMaxSpeed
		desired = glm::normalize(desired) * mMaxSpeed;
		float d = glm::length(desired);
		if (d < mSeekDist) {
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
}

