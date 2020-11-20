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
	float CurrentGear;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	float FirstGear;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	float SecondGear;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
    float NeutralGear;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	float CruiseGear;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	float ShipSpeed;

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
	float ShiftGearUp();
	UFUNCTION(BlueprintCallable)
	float ShiftGearDown();

	//rolling function
	/*UFUNCTION(BlueprintCallable)
	float ShipRoller(float _lerpValue);*/
}
;