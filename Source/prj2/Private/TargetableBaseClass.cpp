// Fill out your copyright notice in the Description page of Project Settings.



#include "prj2/Public/TargetableBaseClass.h"

// Sets default values
ATargetableBaseClass::ATargetableBaseClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATargetableBaseClass::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATargetableBaseClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATargetableBaseClass::OnFocused_Implementation()
{
	
}

void ATargetableBaseClass::OffFocused_Implementation()
{
	
}

void ATargetableBaseClass::Interact_Implementation(APawn* Caller)
{
	
}