#include "Object.h"

Object::Object(EObjectTypes objectType)
	: mObjectType(objectType)
	, mObjectOnGoal(nullptr)
{
}

Object::~Object()
{
}

bool Object::hasObjectOnGoal()
{
	if (mObjectOnGoal != nullptr)
	{
		return true;
	}
	return false;
}

void Object::SetObjectType(EObjectTypes objectType)
{
	mObjectType = objectType;
}

EObjectTypes Object::GetObjectType()
{
	return mObjectType;
}

void Object::SetObjectOnGoal(Object * objectOnGoal)
{
	mObjectOnGoal = objectOnGoal;
}

Object* Object::GetObjectOnGoal()
{
	return mObjectOnGoal;
}
