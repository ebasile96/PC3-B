// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "DrawDebugHelpers.h"
#include "ITargetable.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AMyPawn::AMyPawn()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComponent->SetupAttachment(RootComponent);
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	SpringArmComponent->SetupAttachment(StaticMeshComponent);
	SpringArmComponent->SetRelativeLocationAndRotation(FVector(-174.0f, -290.0f, 1391.0f),FRotator(.0f, 339.0f, .0f));
	SpringArmComponent->TargetArmLength = 562.0f;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
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
		Raycast();
		//CheckLock();
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

void AMyPawn::CheckLock()
{
	if(FocusedActor)
	{
		IITargetable* ITargetable = Cast<IITargetable>(FocusedActor);
		if(ITargetable)
		{
			//prendo la posizione del target e la mia
			FVector TargetLocation = FocusedActor->GetActorLocation();
			FVector CurrentLocation = CameraComponent->GetComponentLocation();
			//imposto la nuova rotazione della camera
			FRotator CurrentRotation = UKismetMathLibrary::FindLookAtRotation(CurrentLocation, TargetLocation);
			FRotator NewRotation = FMath::RInterpTo(CameraComponent->GetComponentRotation(), CurrentRotation, GetWorld()->GetDeltaSeconds(), 1.5f);
			CameraComponent->SetRelativeRotation(NewRotation);
		}
	}
}


void AMyPawn::LockAim()
{

	if(FocusedActor)
	{
		Raycast();
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
	FVector StartVector = CameraComponent->GetComponentLocation();
	FVector ForwardVector = CameraComponent->GetForwardVector();
	FVector EndVector = StartVector + (ForwardVector * RayLength);
	FCollisionQueryParams CQP;
	CQP.AddIgnoredActor(this);
	UWorld* const World = GetWorld();
	if(World != nullptr)
	{
		DrawDebugLine(World, StartVector, EndVector, FColor::Red, true);
		if(World->LineTraceSingleByChannel(HitResult, StartVector, EndVector, ECC_Visibility, CQP))
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
					IITargetable* ITargetable = Cast<IITargetable>(Targetable);
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






