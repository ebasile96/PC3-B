// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Math/UnrealMathVectorCommon.h"



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

	
	NeutralGear = .0f;
	FirstGear = 6000.0f;
	SecondGear = 9000.0f;
	CruiseGear = 12000.0f;
	CurrentGear = NeutralGear;


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

float AMyPawn::ShiftGearUp()
{
	if (CurrentGear == NeutralGear) 
	{
		CurrentGear = FirstGear;
		return CurrentGear;
	}
	else if (CurrentGear == FirstGear) 
	{
		CurrentGear = SecondGear;
		return CurrentGear;
	}
	else if (CurrentGear == SecondGear) 
	{
		CurrentGear = CruiseGear;
		return CurrentGear;
	}
	else if (CurrentGear == CruiseGear) 
	{
		return CurrentGear;
	}
	return CurrentGear;
}

float AMyPawn::ShiftGearDown()
{
	if (CurrentGear == NeutralGear)
	{
		return CurrentGear;
	}
	else if (CurrentGear == FirstGear)
	{
		CurrentGear = NeutralGear;
		return CurrentGear;
	}
	else if (CurrentGear == SecondGear)
	{
		CurrentGear = FirstGear;
		return CurrentGear;
	}
	else if (CurrentGear == CruiseGear)
	{
		CurrentGear = SecondGear;
		return CurrentGear;
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





