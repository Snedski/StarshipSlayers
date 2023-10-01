// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionSystem.h"
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "InteractableInterface.h"
#include "../../MainGameMode.h"
#include "../../../Widgets/MainHUD.h"

UInteractionSystem::UInteractionSystem()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

void UInteractionSystem::SetupSystem(UCameraComponent* camera)
{
	CameraOrigin = camera;
	SetComponentTickEnabled(true);
}

void UInteractionSystem::Interact()
{
	if(IsValid(FocusedInteractable))
	{
		IInteractableInterface::Execute_Interact(FocusedInteractable);
	}
}

void UInteractionSystem::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TArray<FHitResult> outHits = {};
	FVector start = CameraOrigin->GetComponentLocation();
	FVector end = start + (CameraOrigin->GetForwardVector() * InteractionDistance);
	bool bHit = UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), start, end, InteractionRadius, {EObjectTypeQuery::ObjectTypeQuery2}, false, {}, EDrawDebugTrace::None, outHits, true);

	if(bHit)
	{
		AActor* interactable = ChooseBestInteractable(outHits);

		if(IsValid(interactable))
		{
			if(IsValid(FocusedInteractable))
			{
				IInteractableInterface::Execute_Focus(FocusedInteractable, false);
			}

			FocusedInteractable = interactable;
			IInteractableInterface::Execute_Focus(FocusedInteractable, true);
			AMainGameMode::GetHUD()->ShowInteractionPopup(true);

			return;
		}
	}

	if(IsValid(FocusedInteractable))
	{
		IInteractableInterface::Execute_Focus(FocusedInteractable, false);
		FocusedInteractable = nullptr;
		AMainGameMode::GetHUD()->ShowInteractionPopup(false);
	}
}

AActor* UInteractionSystem::ChooseBestInteractable(TArray<FHitResult> hitResults)
{
	FHitResult pointAtResult = FHitResult();
	FVector start = CameraOrigin->GetComponentLocation();
	FVector end = start + (CameraOrigin->GetForwardVector() * 10000.f);
	bool bPointingAtSomething = UKismetSystemLibrary::LineTraceSingle(GetWorld(), start, end, ETraceTypeQuery::TraceTypeQuery1, false, {}, EDrawDebugTrace::None , pointAtResult, true);
	AActor* best = nullptr;

	for(FHitResult hitResult : hitResults)
	{
		AActor* hitActor = hitResult.GetActor();

		if(hitActor->GetClass()->ImplementsInterface(UInteractableInterface::StaticClass()))
		{
			// If an interactable is directly pointed at, choose this one
			if(bPointingAtSomething && pointAtResult.GetActor() == hitActor)
			{
				return hitActor;
			}
			// else check if each interactable are not hidden by something else, the closest to the camera that is not hidden will be chosen first
			else if(!IsValid(best))
			{
				FHitResult outHit = FHitResult();
				FVector actorLocation = hitActor->GetActorLocation();
				bool bHit = UKismetSystemLibrary::LineTraceSingle(GetWorld(), start, actorLocation, ETraceTypeQuery::TraceTypeQuery1, false, {}, EDrawDebugTrace::None, outHit, true);

				if(bHit && outHit.GetActor() == hitActor)
				{
					best = hitActor;
				}
			}
		}
	}

	return best;
}
