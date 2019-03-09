#ifndef cFLOCK_H
#define cFLOCK_H

#include "cMeshObject.h"
#include <vector>

#include <glm/glm.hpp>

enum eFormations
{
	SQUERE,
	CIRCLE,
	LINE,
	ROWS,
	V,
	UNKNOWN

};


class cFlock
{
public:
	cFlock(void);
	cFlock(float maxSpeed, float maxForce, cMeshObject* target);
	virtual ~cFlock(void);

	void AddFlockMember(cMeshObject* entity);
	void setFormation(eFormations type);
	bool bIsStatic;
	void SwitchStaticFlock();
	void SwitchToLastFormation();
	void SwitchPathFollow();
	float cohesionWeight;
	float separationWeight;
	float alingmentWeight;
	void ReversePath();
	void CalculateSteering(void);

private:
	bool bPathFollow;
	
	void GetSeparation(cMeshObject* member, glm::vec3 &flockSeparation);
	void GetCohesion(cMeshObject* member, glm::vec3 &FlockCohesion);
	void alingment(cMeshObject* member, glm::vec3 &FlockAlingment);
	glm::vec3 Seek(cMeshObject* agent, glm::vec3 target);


	
	std::vector<cMeshObject*> mFlockMembers;

	glm::vec3 cohesion;
	glm::vec3 separation;
	glm::vec3 alignment;
	glm::vec3 mCurTarget; //for path following
	std::vector<glm::vec3> m_vec_Path;
	eFormations mFormation;
	eFormations mLastFormation;

	float mMaxForce;
	float mMaxSpeed;

	std::vector<glm::vec3> vec_positions;
	cMeshObject* mTarget;
};

#endif
