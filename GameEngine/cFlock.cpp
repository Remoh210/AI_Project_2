#include "cFlock.h"

#include <assert.h>
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
	CalculateVectors();

	glm::vec3 steering;
	for (std::vector<cMeshObject*>::iterator itMember = mFlockMembers.begin();
		itMember != mFlockMembers.end(); itMember++)
	{
		GetSteeringFor(*itMember, steering);

		int breakpoint = 0;

		(*itMember)->accel = steering;
	}
}

void cFlock::GetSteeringFor(cMeshObject* member, glm::vec3 &flockSteering)
{
	glm::vec3 forward = glm::normalize(member->velocity);
	float sizeMinusOne = mFlockMembers.size() - 1;

	if (mFlockMembers.size() < 2)
	{
		flockSteering = forward;
	}

	// Calcuale cohesion vector
	glm::vec3 cohesionVec = glm::normalize((cohesion - member->position) / sizeMinusOne - member->position) * cohesionWeight;

	// Remove the current position from the separation vector to exclude the 
	// current flock member from the sum of positions.
	glm::vec3 separationVec = (separation - member->position);
	separationVec /= sizeMinusOne;
	separationVec = -glm::normalize(member->position - separationVec) * separationWeight;

	// Remove the current alignment from the separation vector to exclude the
	// current flock member from the sum of alignments;
	glm::vec3 alignmentVec = (alignment - forward);
	alignmentVec /= sizeMinusOne;
	alignmentVec = glm::normalize(alignmentVec) * alignmentWeight;

#ifdef LOG_SYSTEMS
	printf("CohesionVec Mag=%0.4f\n", glm::length(cohesionVec));
	printf("separationVec Mag=%0.4f\n", glm::length(separationVec));
	printf("alignmentVec Mag=%0.4f\n", glm::length(alignmentVec));
#endif

	// calculate the final steering direction
	// These three vectors should add up to a normalized vector, assuming
	// the weight values add up to 1.
	flockSteering = cohesionVec + separationVec + alignmentVec;

	if (glm::length(flockSteering) == 0)
	{
		flockSteering = forward;
	}
}

