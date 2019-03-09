#include "cFlock.h"

#include <assert.h>
#include "HelpFuctions.h"
#include <math.h> 
#include "globalStuff.h"


int k = 0;
glm::vec3 getModelForward(cMeshObject* model)
{
	glm::vec4 vecForwardDirection_ModelSpace = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	glm::quat qRot = model->getQOrientation();
	glm::mat4 matRot = glm::mat4(qRot);
	glm::vec4 vecForwardDirection_WorldSpace = matRot * vecForwardDirection_ModelSpace;
	vecForwardDirection_WorldSpace = glm::normalize(vecForwardDirection_WorldSpace);
	return glm::vec3(vecForwardDirection_WorldSpace);

}

void moveToPos(cMeshObject* agent, glm::vec3 pos)
{
	glm::vec3 desired(0.f);
	desired = pos - agent->position;
	desired = glm::normalize(desired);
	float dist = glm::distance(pos, agent->position);
	if (dist > 0.3f) {
		agent->position += desired * (float)deltaTime * 10.0f;
	}
}


cFlock::cFlock(void)
	: cohesionWeight(1.0f / 3.0f)
	, separationWeight(1.0f / 3.0f)
{

}

cFlock::cFlock(float maxSpeed, float maxForce, cMeshObject* target)
	: mTarget(target)
	, mMaxForce(maxForce)
	, mMaxSpeed(maxSpeed)
{
	bIsStatic = true;
	mFormation = UNKNOWN;
	mCurTarget = glm::vec3(0.0f);
	bPathFollow = false;

	alingmentWeight = 1.0f;
	separationWeight = 1.0f;
	cohesionWeight = 1.0f;



	for(int i = 0; i < 5; i++)
	{
		glm::vec3 curPoint(RandomFloat(-100.0f, 100.0f), 0.0f, RandomFloat(-100.0f, 100.0f));
		m_vec_Path.push_back(curPoint);
	}

}

cFlock::~cFlock(void)
{
	
}


void cFlock::AddFlockMember(cMeshObject* entity)
{
	mFlockMembers.push_back(entity);
}




void cFlock::SwitchToLastFormation(void)
{
	mFormation = mLastFormation;
}

void cFlock::SwitchPathFollow()
{
	bPathFollow = !bPathFollow;
	this->bIsStatic = false;
}


void cFlock::ReversePath()
{
	if (bPathFollow)
	{
		std::reverse(m_vec_Path.begin(), m_vec_Path.end());
	}
}


void cFlock::CalculateSteering(void)
{
	int i;
	
	cMeshObject* agent;
	cMeshObject* leader;
	glm::vec3 forceToApply(0.0f);


	
	for (i = mFlockMembers.size() - 1; i >= 0; i--) {

		agent = mFlockMembers[i];
		leader = mFlockMembers[11];
		glm::vec3 seek = glm::vec3(0.f);
		glm::vec3 separation = glm::vec3(0.f);
		glm::vec3 curCohesion = glm::vec3(0.f);
		glm::vec3 alignment = glm::vec3(0.f);

		if(bIsStatic)
		{
			if (mFormation != UNKNOWN) {
				if (i != 11) {
					moveToPos(agent, vec_positions[i]);
				}
				else if (i == 11)
				{
					moveToPos(agent, glm::vec3(0.f));
				}
			}
		}
		else {

			switch (mFormation)
			{
			case SQUERE:
				if (i != 11) {
					seek = Seek(agent, leader->position + vec_positions[i]);
				}

				if(bPathFollow)
				{
					seek += Seek(agent, mCurTarget);
				}
				else
				{
					seek += Seek(agent, mTarget->position);
				}

				break;
			case CIRCLE:
				if (i != 11) {
					seek = Seek(agent, leader->position + vec_positions[i]);
				}
				if (bPathFollow)
				{
					seek += Seek(agent, mCurTarget);
				}
				else
				{
					seek += Seek(agent, mTarget->position);
				}
				break;
			case LINE:
				if (i != 11) {
					seek = Seek(agent, getModelForward(leader) - vec_positions[i]);
				}
				else if (i == 11)
				{
					if (bPathFollow)
					{
						seek += Seek(agent, mCurTarget);
					}
					else
					{
						seek += Seek(agent, mTarget->position);
					}
				}

				break;
			case ROWS:
				if (i != 11) {
					seek = Seek(agent, leader->position + vec_positions[i]);
				}

				if (bPathFollow)
				{
					seek += Seek(agent, mCurTarget);
				}
				else
				{
					seek += Seek(agent, mTarget->position);
				}
				break;
			case V:
				if (i != 11) {
					seek = Seek(agent, leader->position + vec_positions[i]);
				}
				if (bPathFollow)
				{
					seek += Seek(agent, mCurTarget);
				}
				else
				{
					seek += Seek(agent, mTarget->position);
				}
				break;
			case UNKNOWN:
				if (bPathFollow)
				{
					seek += Seek(agent, mCurTarget) * 1.5f;
				}
				else
				{
					seek += Seek(agent, mTarget->position);
				}

				//seek = Seek(agent, mTarget->position);
				separation;
				GetSeparation(agent, separation);
				curCohesion;
				GetCohesion(agent, curCohesion);
				alingment(agent, alignment);


				break;
			default:
				break;
			}

			
			if (bPathFollow) {

				glm::vec3 av = glm::vec3(0.0f);
				for (int j = 0; j < mFlockMembers.size(); j++)
				{
					av += mFlockMembers[j]->position;
				}
				float quntity = (float)mFlockMembers.size();
				av = av / quntity;
				if (glm::distance(av, mCurTarget) < 15.0f)
				{
					if(k < m_vec_Path.size())
					{
						mCurTarget = m_vec_Path[k];
						k++;
					}
					else
					{
						k = 0;
					}
				}

				for (int c = 0; c < m_vec_Path.size(); c++)
				{
					
					cMeshObject* pDebugSph = findObjectByFriendlyName("DebugSphere");
					pDebugSph->position = m_vec_Path[c];
					pDebugSph->bIsVisible = true;
					pDebugSph->setUniformScale(2.0f);
					//if (c = k) { pDebugSph->setDiffuseColour(glm::vec3(0.0f, 1.0f, 0.0f)); }
					pDebugSph->setDiffuseColour(glm::vec3(1.0f, 0.0f, 0.0f)); 

					glm::mat4 iden = glm::mat4(1.0f);
					DrawObject(pDebugSph, iden, program);
				}

			}
			separation *= separationWeight;
			curCohesion *= cohesionWeight;
			alignment *= alingmentWeight;

			forceToApply = seek + separation + curCohesion  + alignment;
			agent->accel = forceToApply;
			glm::mat4 rot = glm::inverse(glm::lookAt(agent->position, agent->position + agent->velocity, glm::vec3(0.0f, 1.0f, 0.0f)));
			agent->m_meshQOrientation = glm::quat(rot);
		}
	}


}

void cFlock::GetSeparation(cMeshObject* member, glm::vec3 &flockSeparation)
{
	glm::vec3 totalForce = glm::vec3(0.0f);
	int neighboursCount = 0;
	glm::vec3 memPos = member->position;
	for (int i = 0; i < mFlockMembers.size(); i++) {
		cMeshObject* a = mFlockMembers[i];
		if (a != member) {
			float distance = glm::distance(member->position, a->position);
			if (distance < 7.0f && distance > 0) {
				glm::vec3 pushForce = member->position - a->position;
				pushForce = glm::normalize(pushForce);
				totalForce = totalForce + pushForce;
				neighboursCount++;
			}
		}
	}

	if (neighboursCount == 0) {
		flockSeparation = glm::vec3(0.0f);
		return;
	}
	if (totalForce == glm::vec3(0.0f))
	{
		flockSeparation = glm::vec3(0.0f);
		return;
	}

	totalForce = glm::normalize(totalForce);
	totalForce = totalForce * (float)neighboursCount;
	
	flockSeparation = totalForce * mMaxForce;
}


glm::vec3 cFlock::Seek(cMeshObject* agent, glm::vec3 target)
{

	glm::vec3 desired = target - agent->position;
	desired = glm::normalize(desired) * 2.0f;
	float d = glm::length(desired);
	if (d < 50.0f) {
		float m = map(d, 0, 10, 0, mMaxSpeed);
		desired = glm::normalize(desired) * m;
	}
	else {
		desired = glm::normalize(desired) * mMaxSpeed;
	}

	glm::vec3 steering = desired - agent->velocity;

	if (glm::length(steering) > mMaxForce ) {
		steering = glm::normalize(steering) * mMaxForce ;
	}
	return steering;

}



void cFlock::GetCohesion(cMeshObject* member, glm::vec3 &FlockCohesion)
{
	glm::vec3 centerOfMass = member->position;
	int neighboursCount = 1;

	for (int i = 0; i < mFlockMembers.size(); i++) {
		cMeshObject* a = mFlockMembers[i];
		if (a != member) {
			float distance = glm::distance(member->position, a->position);
			if (distance < 10.0f) {
				centerOfMass = centerOfMass + a->position;
				neighboursCount++;
			}
		}
	}

	if (neighboursCount == 1) {
		FlockCohesion = glm::vec3(0.0f);
		return;
	}


	centerOfMass = glm::normalize(centerOfMass);
	centerOfMass = centerOfMass * (float)neighboursCount;
	FlockCohesion = Seek(member, centerOfMass);
	return;
}



void cFlock::alingment(cMeshObject* member, glm::vec3 &FlockAlingment)
{
		glm::vec3 averageHeading(0.0f);
		int neighboursCount = 0;

		for (int i = 0; i < mFlockMembers.size(); i++) {
			cMeshObject* a = mFlockMembers[i];
			float distance = glm::distance(member->position, a->position);
			if (distance < 5.0f && glm::length(a->velocity) > 0) {
				averageHeading = averageHeading + glm::normalize(a->velocity);
				neighboursCount++;
			}
		}

		if (neighboursCount == 0) {
			FlockAlingment = glm::vec3(0.f);
			return;
		}


		averageHeading = averageHeading / (float)neighboursCount;
		glm::vec3 desired = glm::normalize(averageHeading) * mMaxSpeed;
		glm::vec3 force = desired - member->velocity;
		float idk = mMaxForce / mMaxSpeed;
		FlockAlingment =  force * idk;
		return;
}

void cFlock::SwitchStaticFlock()
{
	bIsStatic = !bIsStatic;
	for(int i = 0; i < mFlockMembers.size(); i++)
	{
		cMeshObject* agent = mFlockMembers[i];
		agent->bIsUpdatedByPhysics = !agent->bIsUpdatedByPhysics;
	}
}

void cFlock::setFormation(eFormations type)
{
	glm::vec3 curPos(0.0f);
	float radius = 20;
	if (mFormation != UNKNOWN) {
		vec_positions.clear();
	}
	switch (type)
	{
	case SQUERE:
		mFormation = SQUERE;
		mLastFormation = mFormation;
		vec_positions.clear();
		curPos = glm::vec3(0.f);
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 4; j++) {
				if (i == 0 && j == 0) 
				{
					continue;
				}
				else
				{
					curPos.x += 10.0f;
					vec_positions.push_back(curPos);
					
				}

			}
			curPos.x = -10.0f;
			curPos.z -= 10.0f;

		}
		break;
	case CIRCLE:
		mFormation = CIRCLE;
		mLastFormation = mFormation;
		vec_positions.clear();
		for (int i = 0; i < mFlockMembers.size() - 1; i++) {
			float angle = i * 3.14f * 2 / (mFlockMembers.size() - 1);
			glm::vec3 pos = glm::vec3(cos(angle), 0, sin(angle)) * radius;
			vec_positions.push_back(pos);
		}
		break;
	case LINE:
		mFormation = LINE;
		mLastFormation = mFormation;
		vec_positions.clear();
		curPos = glm::vec3(0.0f);
		for (int i = 0; i < mFlockMembers.size() - 1; i++) {
			curPos.z -= 10.0f;
			vec_positions.push_back(curPos);
		}
		break;
	case ROWS:
		mFormation = ROWS;
		mLastFormation = mFormation;
		vec_positions.clear();
		vec_positions.clear();
		curPos = glm::vec3(0.0f);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 6; j++) {
				if (i == 0 && j == 0)
				{
					continue;
				}
				else
				{
					curPos.x += 10.0f;
					vec_positions.push_back(curPos);

				}

			}
			curPos.x = -10.0f;
			curPos.z -= 10.0f;

		}
		break;
	case V:
		mFormation = V;
		mLastFormation = mFormation;
		vec_positions.clear();
		curPos = glm::vec3(0.0f);
		for(int i = 1; i < mFlockMembers.size(); i++)
		{
			if (i <= mFlockMembers.size() / 2) {
				curPos.z -= 10.0f;
				curPos.x += 10.0f;
				vec_positions.push_back(curPos);
			}
			else
			{
				curPos.z -= 10.0f;
				curPos.x -= 10.0f;
				vec_positions.push_back(curPos);
			}
		}
	
		
		break;
	case UNKNOWN:
		mFormation = UNKNOWN;
		mMaxForce /= 2.0f;
		break;
	default:
		break;
	}
}


