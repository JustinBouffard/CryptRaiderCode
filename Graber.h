// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Graber.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UGraber : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGraber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
		void Release();
	UFUNCTION(BlueprintCallable)
		void Grab();

	bool CheckGrab(FHitResult& OutHitResults) const;

	UPROPERTY(EditAnywhere)
		float MaxGrabDistance{ 250 };
	UPROPERTY(EditAnywhere)
		float GrabRadius{ 50 };
	UPROPERTY(EditAnywhere)
		float HoldDistance{ 200 };

	UPhysicsHandleComponent* GetPhysicsHandle() const;	//get the physics handle in the blueprint


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

};
