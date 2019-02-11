#pragma once
#include "cMeshObject.h"
void shoot(cMeshObject* WhoIsShooting, float VelMult, glm::vec3 RelPos = glm::vec3(0.0f));

void shoot(cMeshObject* WhoIsShooting, cMeshObject* Target, float speed, glm::vec3 RelPos = glm::vec3(0.0f));
