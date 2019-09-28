#pragma once
#include "EObjectTypes.h"

class Object
{
public:
	Object() = delete;
	Object(EObjectTypes objectType);
	~Object();

	bool hasNext();

	void SetObjectType(EObjectTypes objectType);
	EObjectTypes GetObjectType();

	void SetNextObject(Object* nextObject);
	Object* GetNextObject();

private:
	EObjectTypes mObjectType;
	Object* mNext;
};
