// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/ArrowComponent.h"


#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class TANKGAME_API ATank : public APawn
{
	GENERATED_BODY()	

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UStaticMeshComponent* Body;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UStaticMeshComponent* GunStand;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UStaticMeshComponent* Gun;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UArrowComponent* Arrow;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UFloatingPawnMovement* PawnMovement;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ActorToSpawn;

	UPROPERTY(EditAnywhere)
	float RotationSpeed;
	
private:
	void MoveVertical(float Axis);
	void MoveHorizontal(float Axis);
	void Shoot();
	void SpawnBullet();
	FRotator TargetRotation;
	FVector ForwardVector;
	FVector RightVector;
};
