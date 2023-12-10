// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Main/MainManager.h"
#include "ObjectLinkManager.generated.h"

USTRUCT()
struct FObjectLinkInfo
{
	GENERATED_USTRUCT_BODY()

public:
	TArray<TWeakObjectPtr<UObject>> LinkedObjects = {};
};

UCLASS()
class STARSHIPSLAYERS_API UObjectLinkManager : public UMainManager
{
	GENERATED_BODY()
	
protected:
	TMap<FGuid, FObjectLinkInfo> LinkedObjectsFromGUID = {};

public:
	static void AddObjectToGUID(FGuid GUID, UObject* obj);

	static void RemoveObjectToGIUD(FGuid GUID, UObject* obj);

	template<class T = UObject>
	static TArray<T*> GetObjectListFromGUID(FGuid GUID)
	{
		UObjectLinkManager* inst = GetInstace();
		TArray<T*> linkedObj = {};

		if(inst->bEnable)
		{
			if(inst->LinkedObjectsFromGUID.Contains(GUID))
			{
				for(TWeakObjectPtr<UObject> weakObj : inst->LinkedObjectsFromGUID[GUID].LinkedObjects)
				{
					if(weakObj.IsValid() && weakObj->GetClass()->IsChildOf(T::StaticClass()))
					{
						T* obj = Cast<T>(weakObj.Get());
						linkedObj.Add(obj);
					}
				}
			}
		}

		return linkedObj;
	}

protected:
	static UObjectLinkManager* GetInstace();
};