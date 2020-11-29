// Fill out your copyright notice in the Description page of Project Settings.


#include "CannonBall.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ACannonBall::ACannonBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	RootComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComponent-> SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ACannonBall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACannonBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

