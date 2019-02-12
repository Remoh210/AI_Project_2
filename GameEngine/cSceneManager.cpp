#include "cSceneManager.h"
#include "globalStuff.h"
#include <cstdio>
#include <fstream>
#include <iostream>

#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/writer.h>
#include <rapidjson/prettywriter.h>
#include <cstdio>


cSceneManager::cSceneManager() {};


void cSceneManager::setBasePath(std::string basepath)
{
	this->m_basePath = basepath;
	return;
}


bool cSceneManager::saveScene(std::string filename) {

	rapidjson::Document doc;
	rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
	doc.SetObject();
	rapidjson::Value MeshArray(rapidjson::kArrayType);
	
	//Camera Output
	rapidjson::Value CameraObj(rapidjson::kObjectType);
	rapidjson::Value CameraSpeed(camera.MovementSpeed);
	rapidjson::Value CameraPosArray(rapidjson::kArrayType);

	for (int i = 0; i < 3; i++)
	{
		rapidjson::Value temp(camera.Position[i]);
		CameraPosArray.PushBack(temp, allocator);
	}
	CameraObj.AddMember("Speed", CameraSpeed, allocator);
	CameraObj.AddMember("Position", CameraPosArray, allocator);


	//GameObjects
	/*or rapidjson::Value myArray; ;
	     myArray.SetArray() */
	for (std::vector<cMeshObject*>::iterator it = vec_pObjectsToDraw.begin(); it != vec_pObjectsToDraw.end(); ++it) {
		cMeshObject* CurModel = *it;
		if (!CurModel->bIsDebug) {
			rapidjson::Value ObjValue(rapidjson::kObjectType);
			rapidjson::Value FriendlyName(CurModel->friendlyName.c_str(), allocator);
			rapidjson::Value MeshName(CurModel->meshName.c_str(), allocator);
			rapidjson::Value PositionArray(rapidjson::kArrayType);
			rapidjson::Value DiffuseRGBArray(rapidjson::kArrayType);
			rapidjson::Value SpecularRGBArray(rapidjson::kArrayType);
			rapidjson::Value Rotation(rapidjson::kArrayType);
			rapidjson::Value Scale(rapidjson::kArrayType);
			rapidjson::Value Visible(CurModel->bIsVisible);
			rapidjson::Value DontLight(CurModel->bDontLight);
			rapidjson::Value UsePhysics(CurModel->bIsUpdatedByPhysics);
			rapidjson::Value WireFrame(CurModel->bIsWireFrame);
			



			for (int i = 0; i < 3; i++) {
				rapidjson::Value temp(CurModel->position[i]);
				PositionArray.PushBack(temp, allocator);
			}

			for (int i = 0; i < 4; i++) {
				rapidjson::Value temp(CurModel->materialDiffuse[i]);
				DiffuseRGBArray.PushBack(temp, allocator);
			}

			for (int i = 0; i < 4; i++) {
				rapidjson::Value temp(CurModel->materialSpecular[i]);
				SpecularRGBArray.PushBack(temp, allocator);
			}

			for (int i = 0; i < 4; i++) {
				rapidjson::Value temp(CurModel->m_meshQOrientation[i]);
				Rotation.PushBack(temp, allocator);
			}
			for (int i = 0; i < 3; i++) {
				rapidjson::Value temp(CurModel->nonUniformScale[i]);
				Scale.PushBack(temp, allocator);
			}

			ObjValue.AddMember("Name", FriendlyName, allocator);
			ObjValue.AddMember("Mesh", MeshName, allocator);
			ObjValue.AddMember("Visible", Visible, allocator);
			ObjValue.AddMember("Use_Physics", UsePhysics, allocator);
			ObjValue.AddMember("Dont_light", DontLight, allocator);
			ObjValue.AddMember("Wireframe", WireFrame, allocator);
			ObjValue.AddMember("Position", PositionArray, allocator);
			ObjValue.AddMember("DiffuseRGB_Alpha", DiffuseRGBArray, allocator);
			ObjValue.AddMember("SpecularRGB_Alpha", SpecularRGBArray, allocator);
			ObjValue.AddMember("Rotation", Rotation, allocator);
			ObjValue.AddMember("Scale", Scale, allocator);
			if (CurModel->shapeType == cMeshObject::SPHERE)
			{
				sSphere* sphere = (sSphere*)(CurModel->pTheShape);
				rapidjson::Value temp(sphere->radius);
				ObjValue.AddMember("Collider_Radius", temp, allocator);
			}

			//Textures
			if (CurModel->vecTextures.size() > 0) {
				rapidjson::Value TexArray(rapidjson::kArrayType);
				for (int i = 0; i < CurModel->vecTextures.size(); i++) {
					rapidjson::Value TexObjValue(rapidjson::kObjectType);
					rapidjson::Value TexName(CurModel->vecTextures[i].name.c_str(), allocator);
					rapidjson::Value TexStrength(CurModel->vecTextures[i].strength);
					TexObjValue.AddMember("Name", TexName, allocator);
					TexObjValue.AddMember("Strength", TexStrength, allocator);
					TexArray.PushBack(TexObjValue, allocator);
				}
				ObjValue.AddMember("Textures", TexArray, allocator);
			}



			MeshArray.PushBack(ObjValue, allocator);

		}
	}



	//Lights
	rapidjson::Value LightsArray(rapidjson::kArrayType);
	for (std::vector<sLight*>::iterator it = LightManager->vecLights.begin(); it != LightManager->vecLights.end(); ++it) {
		sLight* CurLight = *it;
		rapidjson::Value ObjValue(rapidjson::kObjectType);
		rapidjson::Value FriendlyName(CurLight->lightName.c_str(), allocator);
		rapidjson::Value LightType(CurLight->GetLightType_str().c_str(), allocator);
		rapidjson::Value PositionArray(rapidjson::kArrayType);
		rapidjson::Value AttenArray(rapidjson::kArrayType);
		rapidjson::Value DiffuseArray(rapidjson::kArrayType);
		rapidjson::Value DirectionArray(rapidjson::kArrayType);
		rapidjson::Value Turned("OFF");
		
	

		//cone Angles
		

		//light position

		for (int i = 0; i < 3; i++) {
			rapidjson::Value temp(CurLight->position[i]);
			PositionArray.PushBack(temp, allocator);
		}
		for (int i = 0; i < 4; i++) {
			rapidjson::Value temp(CurLight->diffuse[i]);
			DiffuseArray.PushBack(temp, allocator);
		}
		for (int i = 0; i < 4; i++) {
			rapidjson::Value temp(CurLight->atten[i]);
			AttenArray.PushBack(temp, allocator);
		}
		

		if (CurLight->param2.x == 1.0f) {
			rapidjson::Value temp("ON");
			Turned = temp;
		}
	

		ObjValue.AddMember("Name", FriendlyName, allocator);
		ObjValue.AddMember("Type", LightType, allocator);

		if (CurLight->GetLightType_str() != "POINT_LIGHT") {
			rapidjson::Value AnglesArray(rapidjson::kArrayType);
			for (int i = 1; i < 3; i++) {
				rapidjson::Value temp(CurLight->param1[i]);
				AnglesArray.PushBack(temp, allocator);
			}
			ObjValue.AddMember("Angles", AnglesArray, allocator);

			// Direction Or LookAt object
			if (CurLight->ObjectLookAt == NULL ) {
				for (int i = 0; i < 3; i++) {
					rapidjson::Value temp(CurLight->direction[i]);
					DirectionArray.PushBack(temp, allocator);
				}
				ObjValue.AddMember("Direction", DirectionArray, allocator);
			}
			else {
				rapidjson::Value temp(CurLight->ObjectLookAt->friendlyName.c_str(), allocator);
				ObjValue.AddMember("ObjectLookAt", temp, allocator);
			}
		}
		ObjValue.AddMember("Position", PositionArray, allocator);
		ObjValue.AddMember("Attenuation", AttenArray, allocator);
		ObjValue.AddMember("DiffuseRGB_Alpha", DiffuseArray, allocator);
		ObjValue.AddMember("Turned", Turned, allocator);

		LightsArray.PushBack(ObjValue, allocator);

	}











	doc.AddMember("Camera", CameraObj, allocator);
	doc.AddMember("GameObjects", MeshArray, allocator);
	doc.AddMember("Lights", LightsArray, allocator);

	
	
	std::string fileToLoadFullPath = this->m_basePath + "/" + filename;

	FILE* fp = fopen(fileToLoadFullPath.c_str(), "wb"); // non-Windows use "w"
	char writeBuffer[65536];
	rapidjson::FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
	rapidjson::PrettyWriter<rapidjson::FileWriteStream> writer(os);
	doc.Accept(writer);
	fclose(fp);
	return true;
}




bool cSceneManager::loadScene(std::string filename) {


	std::string fileToLoadFullPath = this->m_basePath + "/" + filename;

	vec_pObjectsToDraw.clear();
	//LightManager->vecLights.clear();
	::g_pTheTextureManager->SetBasePath("assets/textures");
	::g_pTheVAOMeshManager->SetBasePath("assets/models");
	rapidjson::Document doc;
	FILE* fp = fopen(fileToLoadFullPath.c_str(), "rb"); // non-Windows use "r"
	char readBuffer[65536];
	rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	doc.ParseStream(is);
	fclose(fp);


	//Camera
	float Speed;
	glm::vec3 CameraPos;
	rapidjson::Value& CameraPosArray = doc["Camera"]["Position"];

	camera.MovementSpeed = doc["Camera"]["Speed"].GetFloat();
	for (rapidjson::SizeType i = 0; i < CameraPosArray.Size(); i++) {
		CameraPos[i] = CameraPosArray[i].GetFloat();
		std::cout << "CameraPos: [ " << CameraPos[i] << " ]" << std::endl;
	}
	camera.Position = CameraPos;

	

	//Game Objects
	const rapidjson::Value& GameObject = doc["GameObjects"];
	const rapidjson::Value& LightObject = doc["Lights"];


	for (rapidjson::SizeType i = 0; i < GameObject.Size(); i++) {

		cMeshObject *CurModel = new cMeshObject();
		sModelDrawInfo curModelInfo;

		CurModel->friendlyName = GameObject[i]["Name"].GetString();
		CurModel->meshName = GameObject[i]["Mesh"].GetString();
		CurModel->bIsVisible = GameObject[i]["Visible"].GetBool();
		CurModel->bIsUpdatedByPhysics = GameObject[i]["Use_Physics"].GetBool();
		CurModel->bDontLight = GameObject[i]["Dont_light"].GetBool();
		CurModel->bIsWireFrame = GameObject[i]["Wireframe"].GetBool();
		curModelInfo.meshFileName = GameObject[i]["Mesh"].GetString();
		

		const rapidjson::Value& PositionArray = GameObject[i]["Position"];
		for (rapidjson::SizeType i = 0; i < PositionArray.Size(); i++) {

			CurModel->position[i] = PositionArray[i].GetFloat();
			
		}

		const rapidjson::Value& DiffuseArray = GameObject[i]["DiffuseRGB_Alpha"];
		for (rapidjson::SizeType i = 0; i < DiffuseArray.Size(); i++) {

			CurModel->materialDiffuse[i] = DiffuseArray[i].GetFloat();

		}

		const rapidjson::Value& SpecularArray = GameObject[i]["SpecularRGB_Alpha"];
		for (rapidjson::SizeType i = 0; i < SpecularArray.Size(); i++) {

			CurModel->materialSpecular[i] = SpecularArray[i].GetFloat();

		}

		const rapidjson::Value& RotationArray = GameObject[i]["Rotation"];
		for (rapidjson::SizeType i = 0; i < RotationArray.Size(); i++) {

			CurModel->m_meshQOrientation[i] = RotationArray[i].GetFloat();

		}

		const rapidjson::Value& ScaleArray = GameObject[i]["Scale"];
		for (rapidjson::SizeType i = 0; i < ScaleArray.Size(); i++) {

			CurModel->nonUniformScale[i] = ScaleArray[i].GetFloat();

		}

		if (GameObject[i].HasMember("Collider_Radius"))
		{
			CurModel->shapeType = cMeshObject::SPHERE;
			CurModel->pTheShape = new sSphere(GameObject[i]["Collider_Radius"].GetFloat());
		}

		if (GameObject[i].HasMember("Textures")) {
			const rapidjson::Value& TexArray = GameObject[i]["Textures"];
			for (rapidjson::SizeType i = 0; i < TexArray.Size(); i++)
			{
				sTextureInfo CurModelTex;
				CurModelTex.name = TexArray[i]["Name"].GetString();
				CurModelTex.strength = TexArray[i]["Strength"].GetFloat();
				CurModel->vecTextures.push_back(CurModelTex);
				//Creating Texture even if there is alreade same textue NEED FIX
				::g_pTheTextureManager->Create2DTextureFromBMPFile(CurModelTex.name, true);
			}
		}

		vec_pObjectsToDraw.push_back(CurModel);
		g_pTheVAOMeshManager->LoadModelIntoVAO(curModelInfo, program);
	
	}



	for (rapidjson::SizeType i = 0; i < LightObject.Size(); i++) {

		sLight* CurLight = new sLight();

		CurLight->lightName = LightObject[i]["Name"].GetString();
		CurLight->SetLightType(LightObject[i]["Type"].GetString());
		if (LightObject[i].HasMember("Angles"))	{
			const rapidjson::Value& AngleArray = LightObject[i]["Angles"];
			CurLight->SetSpotConeAngles(AngleArray[0].GetFloat(), AngleArray[1].GetFloat());
		}

		if (LightObject[i].HasMember("Direction")) {
			const rapidjson::Value& DirectionArray = LightObject[i]["Direction"];
			for (rapidjson::SizeType i = 0; i < DirectionArray.Size(); i++) {
				CurLight->direction[i] = DirectionArray[i].GetFloat();
			}
		}

		
		const rapidjson::Value& PositionArray = LightObject[i]["Position"];
		for (rapidjson::SizeType i = 0; i < PositionArray.Size(); i++) {
			CurLight->position[i] = PositionArray[i].GetFloat();
		}
		if (LightObject[i].HasMember("ObjectLookAt")) {
			cMeshObject* LookAtObj = findObjectByFriendlyName(LightObject[i]["ObjectLookAt"].GetString());
			if (LookAtObj != NULL) {
				CurLight->SetRelativeDirectionByLookAt(LookAtObj);
			}
			else {
				std::cout << "LookAt obj not found: " << LightObject[i]["ObjectLookAt"].GetString() << std::endl;
			}
		}
		const rapidjson::Value& AttenArray = LightObject[i]["Attenuation"];
		for (rapidjson::SizeType i = 0; i < AttenArray.Size(); i++) {
			CurLight->atten[i] = AttenArray[i].GetFloat();
		}
		const rapidjson::Value& DiffuseArray = LightObject[i]["DiffuseRGB_Alpha"];
		for (rapidjson::SizeType i = 0; i < DiffuseArray.Size(); i++) {
			CurLight->diffuse[i] = DiffuseArray[i].GetFloat();
		}
		std::string turn = LightObject[i]["Turned"].GetString();
		if (turn == "ON") {
			CurLight->param2.x = 1.0f;
		}
		else{
			CurLight->param2.x = 0.0f;
		}

		LightManager->vecLights.push_back(CurLight);
		
	}

	


	return true;
}