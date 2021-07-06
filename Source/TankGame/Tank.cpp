// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "Math/UnitConversion.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Body = CreateDefaultSubobject<UStaticMeshComponent>("Body");
	GunStand = CreateDefaultSubobject<UStaticMeshComponent>("GunStand");
	GunStand->SetupAttachment(Body);
	Gun = CreateDefaultSubobject<UStaticMeshComponent>("Gun");
	Gun->SetupAttachment(GunStand);
	Arrow = CreateDefaultSubobject<UArrowComponent>("Arrow");
	Arrow->SetupAttachment(Gun);

	PawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>("Pawn Movement");

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	ForwardVector = GetActorForwardVector();
	RightVector = GetActorRightVector();
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Rotate tank to move direction smoothly
	if(!GetLastMovementInputVector().IsZero())
	{
		FRotator MoveDirection = GetLastMovementInputVector().Rotation();
		TargetRotation = MoveDirection;
	}
	SetActorRotation(FMath::RInterpTo(GetActorRotation(), TargetRotation, DeltaTime , RotationSpeed));
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Vertical", this, &ATank::MoveVertical);
	PlayerInputComponent->BindAxis("Horizontal", this, &ATank::MoveHorizontal);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &ATank::Shoot);
}

void ATank::MoveVertical(float Axis)
{
	AddMovementInput(ForwardVector, Axis, false);
	
}

void ATank::MoveHorizontal(float Axis)
{
	AddMovementInput(RightVector, Axis, false);
}

void ATank::Shoot()
{
	//UE_LOG(LogTemp, Warning, TEXT("SHOOT"));
	SpawnBullet();
	
}

void ATank::SpawnBullet()
{
	if(ActorToSpawn)
	{
		UWorld* world = GetWorld();
		if(world)
		{
			world->SpawnActor<AActor>(ActorToSpawn, Arrow->GetComponentLocation(), Arrow->GetComponentRotation());
		}
	}
}

