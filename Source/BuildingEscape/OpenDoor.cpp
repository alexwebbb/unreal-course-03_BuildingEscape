// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"



// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	TriggerActor = GetWorld()->GetFirstPlayerController()->GetPawn();

}

void UOpenDoor::OpenDoor()
{
	if (IsDoorOpen == false)
	{
	AActor* Owner = GetOwner();
	FRotator OpenRotation = FRotator(0.0f, Owner->GetActorRotation().Yaw - OpenAngle, 0.0f);
	Owner->SetActorRotation(OpenRotation);
	IsDoorOpen = true;
	}
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate && PressurePlate->IsOverlappingActor(TriggerActor))
	{
		OpenDoor();
	}
	else
	{
		CloseDoor();
	}
}

void UOpenDoor::CloseDoor()
{
	if(IsDoorOpen == true)
	{
	AActor* Owner = GetOwner();
	FRotator OpenRotation = FRotator(0.0f, Owner->GetActorRotation().Yaw + OpenAngle, 0.0f);
	Owner->SetActorRotation(OpenRotation);
	IsDoorOpen = false;
	}
}

