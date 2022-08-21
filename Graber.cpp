// Fill out your copyright notice in the Description page of Project Settings.


#include "Graber.h"
#include "Engine/World.h"
#include"DrawDebugHelpers.h"

// Sets default values for this component's properties
UGraber::UGraber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGraber::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UGraber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetPhysicsHandle() && GetPhysicsHandle() != nullptr)
	{
		FVector TargetLocation{ GetComponentLocation() + GetForwardVector() * HoldDistance };	//hold target location
		GetPhysicsHandle()->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}
}

bool UGraber::CheckGrab(FHitResult& OutHitResults) const
{
	FVector Start = GetComponentLocation();	//start of the sweep
	FVector End = Start + GetForwardVector() * MaxGrabDistance;	//end of the sweep

	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);	//sphere sweeping 

	return GetWorld()->SweepSingleByChannel(	//doing sweep
		OutHitResults,
		Start,
		End,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		Sphere
	);
}

void UGraber::Grab()
{
	FHitResult HitResults;
	bool Hashit{ CheckGrab(HitResults) };
	UPrimitiveComponent* HitComponent{ HitResults.GetComponent() };
		
	if (HitComponent != nullptr && GetPhysicsHandle() != nullptr)
	{
		HitComponent->WakeAllRigidBodies();	//wake physics on the grabbed component

		GetPhysicsHandle()->GrabComponentAtLocationWithRotation(	//grabs component with physics
			HitComponent,
			NAME_None,
			HitResults.ImpactPoint,
			GetComponentRotation()
		);

		UE_LOG(LogTemp, Display, TEXT("Grabbing"));
	}
}

void UGraber::Release()
{
	if (GetPhysicsHandle()->GetGrabbedComponent() && GetPhysicsHandle() != nullptr)	//check if grabbing if true release
	{
		GetPhysicsHandle()->ReleaseComponent();

		UE_LOG(LogTemp, Display, TEXT("Released Graber"))
	}
}

UPhysicsHandleComponent* UGraber::GetPhysicsHandle() const
{
	UPhysicsHandleComponent* Handle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (Handle == nullptr)
		UE_LOG(LogTemp, Warning, TEXT("Grabber requires a UPhysicsHandleComponent"));

	return Handle;
}
