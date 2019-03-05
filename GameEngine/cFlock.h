#ifndef cFLOCK_H
#define cFLOCK_H

#include "cMeshObject.h"
#include <vector>

#include <glm/glm.hpp>

class cFlock
{
public:
	cFlock(void);
	cFlock(float cohesionWeight, float separationWeight, float alignmentWeight);
	virtual ~cFlock(void);

	void AddFlockMember(cMeshObject* entity);
	void RemoveFlockMember(cMeshObject* entity);

	void CalculateSteering(void);

private:

	void CalculateVectors(void);
	void GetSteeringFor(cMeshObject* member, glm::vec3 &flockSteering);
	void GetCohesion(cMeshObject* member, glm::vec3 &FlockCohesion);
	glm::vec3 Seek(cMeshObject* agent, glm::vec3 target);
	void alingment(cMeshObject* member, glm::vec3 &FlockAlingment);

	std::vector<cMeshObject*> mFlockMembers;

	glm::vec3 cohesion;
	glm::vec3 separation;
	glm::vec3 alignment;

	float cohesionWeight;
	float alignmentWeight;
	float separationWeight;
};

#endif
