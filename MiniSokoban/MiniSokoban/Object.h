#pragma once
#include "EObjectTypes.h"

class Object
{
public:
	Object() = delete;
	Object(EObjectTypes objectType);
	~Object();

	bool hasObjectOnGoal();

	void SetObjectType(EObjectTypes objectType);
	EObjectTypes GetObjectType();

	void SetObjectOnGoal(Object* nextObject);
	Object* GetObjectOnGoal();

private:
	EObjectTypes mObjectType;
	Object* mObjectOnGoal;
};
