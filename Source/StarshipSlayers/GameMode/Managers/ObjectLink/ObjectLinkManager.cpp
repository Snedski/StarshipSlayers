// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectLinkManager.h"
#include "../../MainGameMode.h"

void UObjectLinkManager::AddObjectToGUID(FGuid GUID, UObject* obj)
{
	UObjectLinkManager* inst = GetInstace();

	if(inst->bEnable)
	{
		if(!GUID.IsValid())
		{
			return;
		}

		if(!inst->LinkedObjectsFromGUID.Contains(GUID))
		{
			inst->LinkedObjectsFromGUID.Add(GUID, FObjectLinkInfo());
		}

		inst->LinkedObjectsFromGUID[GUID].LinkedObjects.AddUnique(obj);
	}
}

void UObjectLinkManager::RemoveObjectToGIUD(FGuid GUID, UObject* obj)
{
	UObjectLinkManager* inst = GetInstace();

	if(inst->bEnable)
	{
		if(inst->LinkedObjectsFromGUID.Contains(GUID))
		{
			inst->LinkedObjectsFromGUID[GUID].LinkedObjects.Remove(obj);

			if(inst->LinkedObjectsFromGUID[GUID].LinkedObjects.Num() == 0)
			{
				inst->LinkedObjectsFromGUID.Remove(GUID);
			}
		}
	}
}

UObjectLinkManager* UObjectLinkManager::GetInstace()
{
	return AMainGameMode::MainGameModeInstance->ObjectLinkManager;
}
