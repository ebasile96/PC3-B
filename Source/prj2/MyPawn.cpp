// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Math/UnrealMathVectorCommon.h"

enum Gears{NEUTRAL = 0, FIRST = 1, SECOND = 2};

/*
GEARS LOGIC

- struct dati

GearUp(dati);
GearDown(dati);
*/
/*
ROLLING LOGIC
leftvalue= 0;
rightvalue = 1;
NeutralValue = 0.5;
current = 0; (default)

//Rolling(float _neutral, float _left, float _right)
Press left?
Lerp(_neutral, left, t) = current;
release?
Lerp(left, neutral, t) = current;

Press right?
Lerp(_neutral, right, t) = current;
release?
Lerp(right, neutral, t) = current;
*/

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	CurrentGear = 0;

	/*RollLeftValue = -2.0f;
	RollRightValue = 2.0f;
	LerpRollValue = 0.5f;*/
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	{
	}

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

int AMyPawn::ShiftGear()
{
	switch (CurrentGear)
	{
	case NEUTRAL:
		CurrentGear = 0;
		ShipSpeed = 0;
		NextGear = 1;
		break;
	case FIRST:
		CurrentGear = 1;
		ShipSpeed = 1500;
		NextGear = 2;
		PreviewsGear = 0;
		break;
	case SECOND:
		CurrentGear = 2;
		ShipSpeed = 3000;
		PreviewsGear = 1;
		break;
	default:
		break;
	}

	return CurrentGear;
}

//float AMyPawn::ShipRoller( float _lerpValue) 
//{
//	float _currentValue;
//	_currentValue = FMath::Lerp(RollLeftValue, RollRightValue, _lerpValue);
//	CurrentRollValue = FMath::Clamp(_currentValue, .0f, 1.0f);
//
//	return CurrentRollValue;
//}





