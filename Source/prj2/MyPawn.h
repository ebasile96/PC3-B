// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

UCLASS()
class PRJ2_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	int CurrentGear;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	int FirstGear;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	int SecondGear;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	int NeutralGear;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	int ShipSpeed;

	//rolling values
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
		float RollLeftValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
		float RollRightValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
		float CurrentRollValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
		float LerpRollValue;*/

	UFUNCTION(BlueprintCallable)
	int ShiftGearUp();
	UFUNCTION(BlueprintCallable)
	int ShiftGearDown();

	//rolling function
	/*UFUNCTION(BlueprintCallable)
	float ShipRoller(float _lerpValue);*/
}
;