// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterMovTest.h"

// Sets default values
ACharacterMovTest::ACharacterMovTest()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts or when spawned
void ACharacterMovTest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACharacterMovTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

}

// Called to bind functionality to input
void ACharacterMovTest::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

}


