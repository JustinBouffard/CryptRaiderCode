// Fill out your copyright notice in the Description page of Project Settings.

#include "TriggerComponent.h"


// Sets default values for this component's properties
UTriggerComponent::UTriggerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
}

//repeats every frames
void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	GetOverlappingActors(Actors);

	//DelayMoving
	FTimerHandle TimerHandle{};
	AActor* Actor = GetAcceptableActor();
	if (Actor != nullptr)
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UTriggerComponent::Moving, 1.0f, false);
}

AActor* UTriggerComponent::GetAcceptableActor() const
{
	for (AActor* Actor : Actors)
	{
		if (Actor->ActorHasTag(Tag))
		{
			return Actor;
		}
	}

	return nullptr;
}

void UTriggerComponent::SetMover(UMover* NewMover)
{
	Mover = NewMover;
}

void UTriggerComponent::Moving()	//gets called in blueprints
{
	AActor* Actor = GetAcceptableActor();	//no need to check if nullptr already did in tick

	UPrimitiveComponent* RootComponent = Cast<UPrimitiveComponent>(Actor->GetRootComponent());	//access root component

	if (RootComponent != nullptr)
		RootComponent->SetSimulatePhysics(false);	//disable physics so that the statue doesn't block the wall

	Actor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);	//attach statue so it goes down with the wall
	Mover->SetMove(true);
}