#include "Object.h"

Object::Object(EObjectTypes objectType)
	: mObjectType(objectType)
	,mNext(nullptr)
{
}

Object::~Object()
{
}

bool Object::hasNext()
{
	if (mNext != nullptr)
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

void Object::SetNextObject(Object * nextObject)
{
	mNext = nextObject;
}

Object* Object::GetNextObject()
{
	return mNext;
}
