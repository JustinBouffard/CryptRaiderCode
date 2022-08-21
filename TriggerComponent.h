// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Mover.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "TriggerComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CRYPTRAIDER_API UTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()

public:
	//constructor
	UTriggerComponent();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		void SetMover(UMover* NewMover);

protected:
	//begin play function
	virtual void BeginPlay() override;

	TArray<AActor*> Actors;	//list of AActor overlapping
	UPROPERTY(EditAnywhere)
		FName Tag;

	UMover* Mover{};

	AActor* GetAcceptableActor() const;
	void Moving();	//moving the Owner

private:
};
