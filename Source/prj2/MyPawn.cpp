// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"

#include <string>

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

	Cannon1 = CreateDefaultSubobject<USceneComponent>(TEXT("Cannon1"));
	Cannon1->SetupAttachment(StaticMeshComponent);
	Cannon1->SetRelativeLocation(FVector(270.0f,-730.0f, 940.0f));

	Cannon2 = CreateDefaultSubobject<USceneComponent>(TEXT("Cannon2"));
	Cannon2->SetupAttachment(StaticMeshComponent);
	Cannon2->SetRelativeLocation(FVector(470.0f,-730.0f, 940.0f));

	Cannon3 = CreateDefaultSubobject<USceneComponent>(TEXT("Cannon3"));
	Cannon3->SetupAttachment(StaticMeshComponent);
	Cannon3->SetRelativeLocation(FVector(670.0f,-730.0f, 940.0f));

	Cannon4 = CreateDefaultSubobject<USceneComponent>(TEXT("Cannon4"));
	Cannon4->SetupAttachment(StaticMeshComponent);
	Cannon4->SetRelativeLocation(FVector(870.0f,-730.0f, 940.0f));
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	
	NeutralGear = .0f;
	FirstGear = 6000.0f;
	SecondGear = 9000.0f;
	CruiseGear = 12000.0f;
	CurrentGear = NeutralGear;

	ThresholdDistance = 5000.0f;
	
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

float AMyPawn::LookingDirection()
{
	FVector RightVector = GetActorRightVector();
	FVector CameraForward = CameraComponent->GetForwardVector();
	float DotProd = FVector::DotProduct(RightVector,CameraForward);

	/*if(DotProd > 0.0f)
	{
		//azione se sto guardando a destra
		GEngine->AddOnScreenDebugMessage(-1,15.0f,FColor::Yellow, TEXT("WATCHING RIGHT"));
	}
	else if(DotProd < 0.0f)
	{
		//azione se sto guardando a sinistra
		GEngine->AddOnScreenDebugMessage(-1,15.0f,FColor::Yellow, TEXT("WATCHING LEFT"));
	}*/
	return DotProd;
}

float AMyPawn::CheckTargetDistance()
{
	FVector SelfPos = GetActorLocation();
	FVector TargetLoc;
	if(FocusedActor)
	{
		TargetLoc = FocusedActor->GetActorLocation();
		float Distance = FVector::Distance(TargetLoc,SelfPos);
		FString DistString = FString::SanitizeFloat(Distance);
		if(Distance <= ThresholdDistance)
		{
			GEngine->AddOnScreenDebugMessage(-1 , 2.0f, FColor::Green, DistString);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1 , 2.0f, FColor::Red, DistString);
		}
		return Distance;
	}
	return .0f;
}



void AMyPawn::DrawAimLines(AActor* Objective)
{
	FVector ObjectivePos = Objective->GetActorLocation();
	FVector Cannon1Pos = Cannon1->GetComponentLocation();
	FVector Cannon2Pos = Cannon2->GetComponentLocation();
	FVector Cannon3Pos = Cannon3->GetComponentLocation();
	FVector Cannon4Pos = Cannon4->GetComponentLocation();
	
	UWorld* const World = GetWorld();
	DrawDebugLine(World, Cannon1Pos, ObjectivePos, FColor::Red, true);
	DrawDebugLine(World, Cannon2Pos, ObjectivePos, FColor::Red, true);
	DrawDebugLine(World, Cannon3Pos, ObjectivePos, FColor::Red, true);
	DrawDebugLine(World, Cannon4Pos, ObjectivePos, FColor::Red, true);
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
		//DrawDebugLine(World, StartVector, EndVector, FColor::Red, true);
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
							FlushPersistentDebugLines(World);
						}
					}
					IITargetable* ITargetable = Cast<IITargetable>(Targetable);
					if(ITargetable)
					{
						ITargetable->Execute_OnFocused(Targetable);
					}
					FocusedActor = Targetable;
					DrawAimLines(FocusedActor);
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
						FlushPersistentDebugLines(World);
					}
				}
				
				FocusedActor = nullptr;
			}
		}
		
	}
}






