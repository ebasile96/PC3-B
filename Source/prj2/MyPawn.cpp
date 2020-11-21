// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"


#include "DrawDebugHelpers.h"
#include "ITargetable.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"




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

void AMyPawn::LockAim()
{
	Raycast();
	if(FocusedActor)
	{
		IITargetable* ITargetable = Cast<IITargetable>(FocusedActor);
		if(ITargetable)
		{
			ITargetable->Execute_Interact(FocusedActor, this);
		}
	}
	
}


void AMyPawn::Raycast()
{
	FHitResult HitResult;
	//UCameraComponent* Camera;
	FVector StartVector = CameraComponent->GetComponentLocation();
	FVector ForwardVector = CameraComponent->GetForwardVector();
	FVector EndVector = StartVector + (ForwardVector * RayLength);
	FCollisionQueryParams CQP;
	CQP.AddIgnoredActor(this);
	UWorld* const World = GetWorld();
	if(World != nullptr)
	{
		DrawDebugLine(World, StartVector, EndVector, FColor::Red, true);
		if(World->LineTraceSingleByChannel(HitResult, StartVector, EndVector, ECC_Visibility))
		{
			AActor* Targetable = HitResult.GetActor();
			if(Targetable)
			{
				if(Targetable != FocusedActor)
				{
					if(FocusedActor)
					{
						IITargetable* ITargetable = Cast<IITargetable>(FocusedActor);
						if(ITargetable)
						{
							ITargetable->Execute_OffFocused(FocusedActor);
						}
					}
					IITargetable* ITargetable = Cast<IITargetable>(FocusedActor);
					if(ITargetable)
					{
						ITargetable->Execute_OnFocused(Targetable);
					}
					FocusedActor = Targetable;
				}
			}
			else
			{
				if (FocusedActor)
				{
					IITargetable* ITargetable = Cast<IITargetable>(FocusedActor);
					if(ITargetable)
					{
						ITargetable->Execute_OffFocused(FocusedActor);
					}
				}
				
				FocusedActor = nullptr;
			}
		}
		
	}
}






