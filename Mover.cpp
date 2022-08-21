// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	OriginalLocation = GetOwner()->GetActorLocation();
}

// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Move)
	{
		FVector CurrentLocation{ GetOwner()->GetActorLocation() };	//updates owner location
		FVector TargetLocation{ OriginalLocation + MovingOffset };	//targeted location for the owner when moving 
		float speed = FVector::Distance(OriginalLocation, TargetLocation) / MovingTime;	//speed of the movment

		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, speed);	//calculates new location
		GetOwner()->SetActorLocation(NewLocation);	//sets new location
	}
}

void UMover::SetMove(bool SetMove)
{
	Move = SetMove;
}

