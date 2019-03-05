#include "cFlock.h"

#include <assert.h>
#include "HelpFuctions.h"
// #define LOG_SYSTEMS

cFlock::cFlock(void)
	: cohesionWeight(1.0f / 3.0f)
	, separationWeight(1.0f / 3.0f)
	, alignmentWeight(1.0f / 3.0f)
{

}

cFlock::cFlock(float cohesionWeight, float separationWeight, float alignmentWeight)
	: cohesionWeight(cohesionWeight)
	, separationWeight(separationWeight)
	, alignmentWeight(alignmentWeight)
{

}

cFlock::~cFlock(void)
{
	
}


void cFlock::AddFlockMember(cMeshObject* entity)
{
	// TODO: Check if flock member exists

	//Transform* transform = entity->GetComponent<Transform>();
	//Velocity* velocity = entity->GetComponent<Velocity>();
	//assert(transform, "Error adding entity to flock. Entity does not have a Transform component attached.");
	//assert(velocity, "Error adding entity to flock. Entity does not have a Velocity component attached.");

	mFlockMembers.push_back(entity);
}

void cFlock::RemoveFlockMember(cMeshObject* entity)
{
}


void cFlock::CalculateVectors(void)
{
	glm::vec3 forward;

	// Calculate the cohesion for the flock. This is the average
	// position of all of the members of the flock.
	cohesion = glm::vec3(0.0f);
	separation = glm::vec3(0.0f);
	alignment = glm::vec3(0.0f);
	for (std::vector<cMeshObject*>::iterator itMember = mFlockMembers.begin();
		itMember != mFlockMembers.end(); itMember++)
	{
		cMeshObject* currMember = *itMember;
		forward = glm::normalize(currMember->velocity);

		cohesion += currMember->position;
		separation += currMember->position;
		alignment += forward;
	}
}

void cFlock::CalculateSteering(void)
{
	int i;
	cMeshObject* agent;
	glm::vec3 forceToApply(0.0f);
	//Calculate steering and flocking forces for all agents
	for (i = mFlockMembers.size() - 1; i >= 0; i--) {
		agent = mFlockMembers[i];

		//Work out our behaviours
		glm::vec3 seek = Seek(agent, glm::vec3(0.0f));
		glm::vec3 separation;
		GetSteeringFor(agent, separation);
		glm::vec3 curCohesion;
		GetCohesion(agent, curCohesion);
		glm::vec3 alignment;
		alingment(agent, alignment);
		

		//Combine them to come up with a total force to apply, decreasing the effect of cohesion
		forceToApply = seek + separation + curCohesion * 0.1f; //+ alignment;
		agent->accel = forceToApply;
	}

	//Move agents based on forces being applied (aka physics)
	//for (i = mFlockMembers.size() - 1; i >= 0; i--) {
	//	agent = mFlockMembers[i];
	//	agent->accel = forceToApply;
	//	//Apply the force
	//	//agent.velocity = agent.velocity.plus(agent.forceToApply.mul(dt));

	//	////Cap speed as required
	//	//var speed = agent.velocity.length();
	//	//if (speed > agent.maxSpeed) {
	//	//	agent.velocity = agent.velocity.mul(agent.maxSpeed / speed);
	//	//}

	//	////Calculate our new movement angle
	//	//agent.rotation = agent.velocity.angle();

	//	////Move a bit
	//	//agent.position = agent.position.plus(agent.velocity.mul(dt));
	//}
}

void cFlock::GetSteeringFor(cMeshObject* member, glm::vec3 &flockSteering)
{
	glm::vec3 totalForce = glm::vec3(0.0f);
	int neighboursCount = 0;
	glm::vec3 memPos = member->position;
	//for each agent
	for (int i = 0; i < mFlockMembers.size(); i++) {
		cMeshObject* a = mFlockMembers[i];
		//that is not us
		if (a != member) {
			float distance = glm::distance(member->position, a->position);
			//that is within the distance we want to separate from
			if (distance < separationWeight && distance > 0) {
				//Calculate a Vector from the other agent to us
				glm::vec3 pushForce = member->position - a->position;
				//Scale it based on how close they are compared to our radius
				// and add it to the sum
				pushForce = glm::normalize(pushForce);
				totalForce = totalForce + pushForce * 2.0f;
				neighboursCount++;
			}
		}
	}

	if (neighboursCount == 0) {
		flockSteering = glm::vec3(0.0f);
		return;
	}
	if (totalForce == glm::vec3(0.0f))
	{
		flockSteering = glm::vec3(0.0f);
		return;
	}

	//Normalise the force back down and then back up based on the maximum force
	totalForce = glm::normalize(totalForce);
	totalForce = totalForce * (float)neighboursCount;
	//mul(agent.maxForce);
	
	flockSteering = totalForce * 3.0f;
}


glm::vec3 cFlock::Seek(cMeshObject* agent, glm::vec3 target)
{



	glm::vec3 desired = target - agent->position;
	//normalize it and scale by mMaxSpeed
	desired = glm::normalize(desired) * 2.0f;
	float d = glm::length(desired);
	if (d < 20.0f) {
		float m = map(d, 0, 10, 0, 6.0f);
		desired = glm::normalize(desired) * m;
	}
	else {
		desired = glm::normalize(desired) * 6.0f /*mMaxSpeed*/;
	}

	glm::vec3 steering = desired - agent->velocity;

	if (glm::length(steering) > 5.0f /*mMaxForce*/) {
		steering = glm::normalize(steering) * 5.0f /*mMaxForce*/;
	}
	//steering = glm::normalize(desired) * mMaxForce;
	return steering;

	//glm::mat4 rot = glm::inverse(glm::lookAt(agent->position, agent->position + agent->velocity, glm::vec3(0.0f, 1.0f, 0.0f)));
	//agent->m_meshQOrientation = glm::quat(rot);

}



void cFlock::GetCohesion(cMeshObject* member, glm::vec3 &FlockCohesion)
{
	//Start with just our position
	glm::vec3 centerOfMass = member->position;
	int neighboursCount = 1;

	for (int i = 0; i < mFlockMembers.size(); i++) {
		cMeshObject* a = mFlockMembers[i];
		if (a != member) {
			float distance = glm::distance(member->position, a->position);
			if (distance < cohesionWeight) {
				//sum up the position of our neighbours
				centerOfMass = centerOfMass + a->position;
				neighboursCount++;
			}
		}
	}

	if (neighboursCount == 1) {
		FlockCohesion = glm::vec3(0.0f);
		return;
	}

	//Get the average position of ourself and our neighbours

	centerOfMass = glm::normalize(centerOfMass);
	centerOfMass = centerOfMass * (float)neighboursCount;
	//seek that position
	FlockCohesion = Seek(member, centerOfMass);
	return;
}



void cFlock::alingment(cMeshObject* member, glm::vec3 &FlockAlingment)
{
		glm::vec3 averageHeading(0.0f);
		int neighboursCount = 0;

		//for each of our neighbours (including ourself)
		for (int i = 0; i < mFlockMembers.size(); i++) {
			cMeshObject* a = mFlockMembers[i];
			float distance = glm::distance(member->position, a->position);
			//That are within the max distance and are moving
			if (distance < cohesionWeight && glm::length(a->velocity) > 0) {
				//Sum up our headings
				averageHeading = averageHeading + glm::normalize(a->velocity);
				neighboursCount++;
			}
		}

		if (neighboursCount == 0) {
			FlockAlingment = glm::vec3(0.f);
			return;
		}

		//Divide to get the average heading
		averageHeading = glm::normalize(averageHeading);
		averageHeading = averageHeading * (float)neighboursCount;

		//Steer towards that heading
		glm::vec3 desired = averageHeading * 6.0f;
		glm::vec3 force = desired - member->velocity;
		float idk = 5.0f / 6.0f;
		FlockAlingment =  force * idk;
		return;
}

