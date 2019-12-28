#pragma once

#include "Common.h"
#include "EObjectTypes.h"

class Object
{
public:
	Object() = delete;
	Object(EObjectTypes objectType);
	~Object();

	bool IsThereObjectOnGoal() const;

	EObjectTypes GetObjectType() const;
	EObjectColors GetObjectColor() const;
	Object* GetObjectOnGoal() const;

	void SetObjectType(EObjectTypes objectType);
	void SetObjectOnGoal(Object* nextObject);

private:
	void setObjectColorByObjectType();

	EObjectTypes mObjectType;
	EObjectColors mObjectColor;
	Object* mObjectOnGoal;
};
