#include "globalStuff.h"
#include "BehaviourManager.h"
#include "SeekBehaviour.h"
#include "FleeBehaviour.h"
#include "SeekAndFleeBehaviour.h"
#include "ApproachBehaviour.h"
#include "PursueAndEvadeBehaviour.h"
#include "WanderBehaviour.h"
#include "cFlock.h"
#include <iostream>

// These are for the transformation glm stuff
#include <glm/glm.hpp> 
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
cMeshObject* pDebugSphere;
cMeshObject* pEarth;
cMeshObject* pMars;
cMeshObject* pPlayer;
std::vector <cMeshObject*> vec_Enemies;
extern cFlock* pFlock;
int stage;
int enemyCount;
float timer;
bool respawnEnemies;
extern bool game_is_over;
bool checkIsAllDead(std::vector<cMeshObject*> enemies);
char answer;


void InitGame() {
	//behavManager = new BehaviourManager();


	pPlayer = findObjectByFriendlyName("player");
	pEarth = findObjectByFriendlyName("earth");
	pMars = findObjectByFriendlyName("mars");

	pFlock = new cFlock(40.0f, 30.0f, pPlayer);

	cMeshObject* pEnemey1 = findObjectByFriendlyName("enemy1");
	vec_Enemies.push_back(pEnemey1);
	cMeshObject* pEnemey2 = findObjectByFriendlyName("enemy2");
	vec_Enemies.push_back(pEnemey2);
	cMeshObject* pEnemey3 = findObjectByFriendlyName("enemy3");
	vec_Enemies.push_back(pEnemey3);
	cMeshObject* pEnemey4 = findObjectByFriendlyName("enemy4");
	vec_Enemies.push_back(pEnemey4);
	cMeshObject* pEnemey5 = findObjectByFriendlyName("enemy5");
	vec_Enemies.push_back(pEnemey5);
	cMeshObject* pEnemey6 = findObjectByFriendlyName("enemy6");
	vec_Enemies.push_back(pEnemey6);
	cMeshObject* pEnemey7 = findObjectByFriendlyName("enemy7");
	vec_Enemies.push_back(pEnemey7);
	cMeshObject* pEnemey8 = findObjectByFriendlyName("enemy8");
	vec_Enemies.push_back(pEnemey8);
	cMeshObject* pEnemey9 = findObjectByFriendlyName("enemy9");
	vec_Enemies.push_back(pEnemey9);
	cMeshObject* pEnemey10 = findObjectByFriendlyName("enemy10");
	vec_Enemies.push_back(pEnemey10);
	cMeshObject* pEnemey11 = findObjectByFriendlyName("enemy11");
	vec_Enemies.push_back(pEnemey11);
	cMeshObject* pEnemey12 = findObjectByFriendlyName("enemy12");
	vec_Enemies.push_back(pEnemey12);

	
	for (int i = 0; i < vec_Enemies.size(); i++) {
		//vec_Enemies[i]->velocity = glm::vec3(0.0f, 0.0, 5.1f);
		vec_Enemies[i]->bIsUpdatedByPhysics = false;
		pFlock->AddFlockMember(vec_Enemies[i]);
	}

	


	camera.b_controlledByScript = true;
	camera.SetViewMatrix(glm::lookAt(camera.Position, pEarth->position, glm::vec3(0.0f, 1.0f, 0.0f)));


	//hide debug models
	for (int i = 0; i < vec_pObjectsToDraw.size(); i++)
	{
		if (vec_pObjectsToDraw[i]->bIsDebug) {
			vec_pObjectsToDraw[i]->bIsVisible = false;
		}

	}
	
}

void GameLoop(double deltaTime, GLuint shaderProgramID)
{
	pFlock->CalculateSteering();
	//behavManager->update(deltaTime);

	//draw Debug Info
	//for (int i = 0; i < vec_pObjectsToDraw.size(); i++)
	//{
	//	if (vec_pObjectsToDraw[i]->shapeType == cMeshObject::SPHERE)
	//	{
	//		if(vec_pObjectsToDraw[i]->bIsVisible)
	//		{
	//			sSphere* sphere = (sSphere*)(vec_pObjectsToDraw[i]->pTheShape);
	//			pDebugSphere->position = vec_pObjectsToDraw[i]->position;
	//			pDebugSphere->setUniformScale(sphere->radius);
	//			pDebugSphere->setDiffuseColour(glm::vec3(0.0f, 1.0f, 0.0f));
	//			glm::mat4 matIdentity = glm::mat4(1.0f);
	//			DrawObject(pDebugSphere, matIdentity, program);
	//		}
	//		//pDebugSphere->bIsVisible = false;
	//	}
	//}

	//
	//if (game_is_over)
	//{
	//	pPlayer->adjMeshOrientationEulerAngles(0.3f * deltaTime, 0.0f, 0.0f);
	//	glm::vec4 vecForwardDirection_ModelSpace = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	//	
	//	glm::quat qPlayer29Rotation = pPlayer->getQOrientation();
	//	glm::mat4 matQPlayer29rotation = glm::mat4(qPlayer29Rotation);
	//	glm::vec4 vecForwardDirection_WorldSpace = matQPlayer29rotation * vecForwardDirection_ModelSpace;
	//	vecForwardDirection_WorldSpace = glm::normalize(vecForwardDirection_WorldSpace);
	//	float forwardSpeed = 20.5f;
	//	float forwardSpeedThisFrame = forwardSpeed * deltaTime;
	//	pPlayer->velocity = vecForwardDirection_WorldSpace * forwardSpeed;
	//}



	//
	////increase timer

	////timer += (float)deltaTime; timer > 10.0f && 
	//if (vec_Enemies[enemyCount]->bIsVisible == false  && respawnEnemies != true)
	//{
	//	stage = 1;
	//	if (enemyCount < vec_Enemies.size() - 1) 

	//	{
	//		enemyCount++;
	//		vec_Enemies[enemyCount]->bIsVisible = true;
	//		vec_Enemies[enemyCount]->bIsUpdatedByPhysics = true;
	//		std::cout << vec_Enemies[enemyCount]->friendlyName << " has appeared!" << std::endl;;
	//		if (vec_Enemies[enemyCount]->friendlyName == "wanderEnemy") 
	//		{
	//			std::cout << "He is not aggresive, he only protects the area!";
	//			std::cout << std::endl;
	//			std::cout << std::endl;
	//		}
	//		if (vec_Enemies[enemyCount]->friendlyName == "wanderWaitEnemy")
	//		{
	//			std::cout << "He is not aggresive, he only protects the area, stopping for 3 seconds!";
	//			std::cout << std::endl;
	//			std::cout << std::endl;
	//		}
	//		if (vec_Enemies[enemyCount]->friendlyName == "pursueEnemy")
	//		{
	//			std::cout << "Careful! He will pursue your future position and evade from lasers!";
	//			std::cout << std::endl;
	//			std::cout << std::endl;
	//		}
	//		if (vec_Enemies[enemyCount]->friendlyName == "seekEnemy")
	//		{
	//			std::cout << "Careful! He will seek your position and flee if you look at him!";
	//			std::cout << std::endl;
	//			std::cout << std::endl;
	//		}
	//		
	//	}
	//	else
	//	{
	//		std::cout << "Good Job! Now try to kill all enemies in 10 seconds, either way they will respawn!";
	//		std::cout << std::endl;
	//		std::cout << std::endl;
	//		respawnEnemies = true;
	//	}

	//}
	//else if(respawnEnemies && !game_is_over)//respawn all together! Its a Second Phase!
	//{
	//	
	//	//increase timer if enemy is "dead"
	//	for (int i = 0; i < vec_Enemies.size(); i++)
	//	{
	//		if (!vec_Enemies[i]->bIsVisible  && vec_Enemies[i]->friendlyName != "wanderWaitEnemy")
	//		{
	//			vec_Enemies[i]->time_dead += (float)deltaTime;
	//			if (vec_Enemies[i]->time_dead > 5.0f)
	//			{
	//				stage = 2;
	//				vec_Enemies[i]->position = vec_Enemies[i]->initPos;
	//				vec_Enemies[i]->bIsUpdatedByPhysics = true;
	//				vec_Enemies[i]->bIsVisible = true;

	//				vec_Enemies[i]->time_dead = 0.0f;

	//			}
	//		}

	//	}
	//}

	//if (checkIsAllDead(vec_Enemies) && stage == 2 && game_is_over == false)
	//{
	//	game_is_over = true;
	//	std::cout << "Congradulations! You Win!" << std::endl;
	////	std::cout << "Continue?(y/n): ";
	//	
	////	std::cin >> answer;
	////	if(answer == 'y')
	////	{
	////		stage = 1;
	////		game_is_over = false;
	////		respawnEnemies = false;
	////	}
	////	else
	////	{
 //   //
	////	}
	//	
	//}

	

	////increase timer if enemy is "dead"
	//for (int i = 0; i < vec_Enemies.size(); i++)
	//{
	//	if (!vec_Enemies[i]->bIsVisible)
	//	{
	//		vec_Enemies[i]->time_dead += (float)deltaTime;
	//		if (vec_Enemies[i]->time_dead > 4.0f)
	//		{
	//			vec_Enemies[i]->position = vec_Enemies[i]->initPos;
	//			vec_Enemies[i]->bIsUpdatedByPhysics = true;
	//			vec_Enemies[i]->bIsVisible = true;

	//			vec_Enemies[i]->time_dead = 0.0f;
	//		}
	//	}

	//}


	
	for (int i = 0; i < vec_pObjectsToDraw.size(); i++)
	{
		if (vec_pObjectsToDraw[i]->friendlyName == "beam")
		{
			if (glm::distance(vec_pObjectsToDraw[i]->initPos, vec_pObjectsToDraw[i]->position) > 300.0f)
			{
				//vec_pObjectsToDraw[i].
				delete vec_pObjectsToDraw[i];
				vec_pObjectsToDraw.erase(vec_pObjectsToDraw.begin() + i);
			}
		}
	}



	////Respawn Dead Enemies
	//for (int i; i < vec_Enemies.size(); i++)
	//{
	//	mTimeWaitedSoFar += (float)dt;
	//	if (mTimeWaitedSoFar > mTimeToWait)
	//	{
	//		mCurTarget = glm::vec3(mRelPos.x + RandomFloat(mDwnLim, mUpLim), 0.0f, mRelPos.z + RandomFloat(mDwnLim, mUpLim));
	//		mStart = true;
	//	}
	//	//Ressurect!
	//}
	//Animate Earth
	pEarth->adjMeshOrientationEulerAngles(0.0f, -0.1f * deltaTime, 0.0f, false);
	pMars->adjMeshOrientationEulerAngles(0.0f, 0.1f * deltaTime , 0.0f, false);
	return;
}



bool checkIsAllDead(std::vector<cMeshObject*> enemies)
{
	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i]->bIsVisible == true)
		{
			return false;
		}
	}
	//Yup they're all dead
	return true;
}