#include "globalStuff.h"
void shoot(cMeshObject* WhoIsShooting, float VelMult, glm::vec3 RelPos = glm::vec3(0.0f))
{
	//cMeshObject* beam = findObjectByFriendlyName("DebugSphere");
	//cMeshObject* leftWing = findObjectByFriendlyName("DebugSphereLeft");
	//cMeshObject* rightWing = findObjectByFriendlyName("DebugSphereLeft");
	//cMeshObject* xWing = findObjectByFriendlyName("player");
	glm::vec4 beam_ModelSpace = glm::vec4(0.0f, 0.0f, 5.0f, 1.0f) + glm::vec4(RelPos, 0.0f);
	glm::vec4 beam_ModelSpace2 = glm::vec4(-2.3692f, 0.0f, 5.0f, 1.0f);


	glm::mat4 matTransform = glm::mat4(1.0f);
	glm::mat4 matTranslation = glm::translate(glm::mat4(1.0f),
		WhoIsShooting->position);

	matTransform = matTransform * matTranslation;
	glm::quat qRotation = WhoIsShooting->getQOrientation();
	glm::mat4 matQrotation = glm::mat4(qRotation);
	matTransform = matTransform * matQrotation;

	glm::vec4 beam_WorldSpace = glm::vec4(0.0f);
	glm::vec4 beam_WorldSpace2 = glm::vec4(0.0f);

	beam_WorldSpace = matTransform * beam_ModelSpace;
	beam_WorldSpace2 = matTransform * beam_ModelSpace2;





	cMeshObject* pBeam = new cMeshObject();
	pBeam->setDiffuseColour(glm::vec3(0.0f, 1.0f, 0.0f));
	pBeam->friendlyName = "beam";
	pBeam->meshName = "beam.ply";
	pBeam->bIsWireFrame = false;
	pBeam->bDontLight = true;
	pBeam->bIsVisible = true;
	float scale = 1.3f;
	pBeam->nonUniformScale = glm::vec3(scale, scale, scale * 0.6f );
	pBeam->position = beam_WorldSpace;
	//pBeam->initPos = beam_WorldSpace;
	//pBeam->bIsProjectile = true;
	pBeam->bIsUpdatedByPhysics = true;
	pBeam->initPos = pBeam->position;
	pBeam->bIsDebug = false;
	pBeam->pTheShape = new sSphere(2.0f);
	pBeam->shapeType = cMeshObject::SPHERE;
	pBeam->setQOrientation(qRotation);
	vec_pObjectsToDraw.push_back(pBeam);


	//cMeshObject* pBeam2 = new cMeshObject();
	//pBeam2->setDiffuseColour(glm::vec3(1.0f, 0.0f, 0.0f));
	//pBeam2->friendlyName = "beam2";
	//pBeam2->meshName = "beam.ply";
	//pBeam2->bIsWireFrame = false;
	//pBeam2->bDontLight = true;
	//pBeam2->bIsVisible = true;
	//float scale2 = 0.7f;
	//pBeam2->nonUniformScale = glm::vec3(scale2, scale2, scale2 * 2);
	//pBeam2->position = beam_WorldSpace2;
	////pBeam2->initPos = beam_WorldSpace2;
	////pBeam2->bIsProjectile = true;
	//pBeam2->bIsUpdatedByPhysics = true;
	//pBeam2->bIsDebug = false;
	//pBeam2->pTheShape = new sSphere(2.0f);
	//pBeam2->shapeType = cMeshObject::SPHERE;
	//pBeam2->setQOrientation(qRotation);
	//vec_pObjectsToDraw.push_back(pBeam2);



	pBeam->bIsVisible = true;


	glm::vec4 vecForwardDirection_ModelSpace = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

	glm::quat qPlayer29Rotation = WhoIsShooting->getQOrientation();
	glm::mat4 matQPlayer29rotation = glm::mat4(qPlayer29Rotation);
	glm::vec4 vecForwardDirection_WorldSpace = matQPlayer29rotation * vecForwardDirection_ModelSpace;
	vecForwardDirection_WorldSpace = glm::normalize(vecForwardDirection_WorldSpace);
	float forwardSpeed = 40.5f;
	float forwardSpeedThisFrame = forwardSpeed * deltaTime;
	pBeam->velocity = vecForwardDirection_WorldSpace * forwardSpeed;


	//pBeam2->velocity = xWing->velocity * 15.0f;
	//pBeam->velocity = WhoIsShooting->velocity * 3.0f;
}


void shoot(cMeshObject* WhoIsShooting, cMeshObject* Target, float speed, glm::vec3 RelPos = glm::vec3(0.0f))
{
	//cMeshObject* beam = findObjectByFriendlyName("DebugSphere");
	//cMeshObject* leftWing = findObjectByFriendlyName("DebugSphereLeft");
	//cMeshObject* rightWing = findObjectByFriendlyName("DebugSphereLeft");
	//cMeshObject* xWing = findObjectByFriendlyName("player");
	glm::vec4 beam_ModelSpace = glm::vec4(RelPos, 1.0f);
	glm::vec4 beam_ModelSpace2 = glm::vec4(-2.3692f, 0.0f, 5.0f, 1.0f);


	glm::mat4 matTransform = glm::mat4(1.0f);
	glm::mat4 matTranslation = glm::translate(glm::mat4(1.0f),
		WhoIsShooting->position);

	matTransform = matTransform * matTranslation;
	glm::quat qRotation = WhoIsShooting->getQOrientation();
	glm::mat4 matQrotation = glm::mat4(qRotation);
	matTransform = matTransform * matQrotation;

	glm::vec4 beam_WorldSpace = glm::vec4(0.0f);
	glm::vec4 beam_WorldSpace2 = glm::vec4(0.0f);

	beam_WorldSpace = matTransform * beam_ModelSpace;
	beam_WorldSpace2 = matTransform * beam_ModelSpace2;





	cMeshObject* pBeam = new cMeshObject();
	pBeam->setDiffuseColour(glm::vec3(1.0f, 0.0f, 0.0f));
	pBeam->friendlyName = "beam";
	pBeam->meshName = "beam.ply";
	pBeam->bIsWireFrame = false;
	pBeam->bDontLight = true;
	pBeam->bIsVisible = true;
	float scale = 1.3f;
	pBeam->nonUniformScale = glm::vec3(scale, scale, scale * 0.6f);
	pBeam->position = beam_WorldSpace;
	//pBeam->initPos = beam_WorldSpace;
	//pBeam->bIsProjectile = true;
	pBeam->bIsUpdatedByPhysics = true;
	pBeam->initPos = pBeam->position;
	pBeam->bIsDebug = false;
	pBeam->pTheShape = new sSphere(2.0f);
	pBeam->shapeType = cMeshObject::SPHERE;
	pBeam->setQOrientation(qRotation);
	vec_pObjectsToDraw.push_back(pBeam);


	//cMeshObject* pBeam2 = new cMeshObject();
	//pBeam2->setDiffuseColour(glm::vec3(1.0f, 0.0f, 0.0f));
	//pBeam2->friendlyName = "beam2";
	//pBeam2->meshName = "beam.ply";
	//pBeam2->bIsWireFrame = false;
	//pBeam2->bDontLight = true;
	//pBeam2->bIsVisible = true;
	//float scale2 = 0.7f;
	//pBeam2->nonUniformScale = glm::vec3(scale2, scale2, scale2 * 2);
	//pBeam2->position = beam_WorldSpace2;
	////pBeam2->initPos = beam_WorldSpace2;
	////pBeam2->bIsProjectile = true;
	//pBeam2->bIsUpdatedByPhysics = true;
	//pBeam2->bIsDebug = false;
	//pBeam2->pTheShape = new sSphere(2.0f);
	//pBeam2->shapeType = cMeshObject::SPHERE;
	//pBeam2->setQOrientation(qRotation);
	//vec_pObjectsToDraw.push_back(pBeam2);

	glm::vec3 direction = Target->position - WhoIsShooting->position;
	direction = glm::normalize(direction);
	pBeam->bIsVisible = true;
	//pBeam2->velocity = xWing->velocity * 15.0f;
	pBeam->velocity = direction * speed;
}