// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority()) {
		SetReplicates(true);
		SetReplicateMovement(true);
	}

	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);

}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		FVector Location = GetActorLocation();
		float Distance = (GlobalTargetLocation - GlobalStartLocation).Size();
		float DistanceTravelled = (Location - GlobalStartLocation).Size();
		if (DistanceTravelled >= Distance)
		{
			FVector Buffer;
			Buffer = GlobalStartLocation;
			GlobalStartLocation = GlobalTargetLocation;
			GlobalTargetLocation = Buffer;

			//SwapVectors(&GlobalStartLocation, &GlobalTargetLocation);
		}
		FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
		Location += Speed * DeltaTime * Direction;
		SetActorLocation(Location);
	}
}

void AMovingPlatform::SwapVectors(FVector* A, FVector* B)
{
	FVector Buffer;
	Buffer = *A;
	*A = *B;
	*B = Buffer;
}

