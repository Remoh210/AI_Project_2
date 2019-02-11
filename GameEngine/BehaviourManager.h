#ifndef BEHAVIOUR_MANAGER_H
#define BEHAVIOUR_MANAGER_H

#include <map>
#include "cMeshObject.h"
#include "Behaviour.h"

class BehaviourManager {
public:
	BehaviourManager(void);
	~BehaviourManager(void);

	void SetBehaviour(cMeshObject* agent, Behaviour* behaviour);
	void RemoveAgent(cMeshObject* agent);

	void update(float dt);

private:
	std::map<cMeshObject*, Behaviour*> mBehaviourMap;
};

typedef std::map<cMeshObject*, Behaviour*>::iterator behaviour_iterator;


#endif
