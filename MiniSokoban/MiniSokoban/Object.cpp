#include "Object.h"

Object::Object(EObjectTypes objectType)
	: mObjectType(objectType)
	, mObjectOnGoal(nullptr)
	, mObjectColor(EObjectColors::BLACK_WHITE)
{
	setObjectColorByObjectType();
}

Object::~Object()
{
}

bool Object::IsThereObjectOnGoal() const
{
	if (mObjectOnGoal != nullptr)
	{
		return true;
	}
	return false;
}

EObjectTypes Object::GetObjectType() const
{
	return mObjectType;
}

EObjectColors Object::GetObjectColor() const
{
	return mObjectColor;
}

Object* Object::GetObjectOnGoal() const
{
	return mObjectOnGoal;
}

void Object::SetObjectType(EObjectTypes objectType)
{
	mObjectType = objectType;
	setObjectColorByObjectType();
}

void Object::SetObjectOnGoal(Object* objectOnGoal)
{
	mObjectOnGoal = objectOnGoal;
}

void Object::setObjectColorByObjectType()
{
	switch (mObjectType)
	{
	case EObjectTypes::PLAYER:
		mObjectColor = EObjectColors::CYANBLUE_WHITE;
		break;
	case EObjectTypes::BOX:
		mObjectColor = EObjectColors::RED_WHITE;
		break;
	case EObjectTypes::GOAL:
		mObjectColor = EObjectColors::YELLOW_WHITE;
		break;
	case EObjectTypes::WALL:
		mObjectColor = EObjectColors::WHITE_BLACK;
		break;
	case EObjectTypes::WAY:
		mObjectColor = EObjectColors::BLACK_WHITE;
		break;
	default:
		break;
	}
}
