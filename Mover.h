// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Mover.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UMover : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMover();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetMove(bool SetMove);

private:
	UPROPERTY(EditAnywhere)
		FVector MovingOffset;	//moving distance 
	UPROPERTY(EditAnywhere)
		int32 MovingTime;	//time for the owner to move

	bool Move{};	//owner moving if true

	FVector OriginalLocation;	//original location of the owner
};
