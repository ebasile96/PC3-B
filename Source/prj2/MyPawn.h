// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USpringArmComponent* SpringArmComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* CameraComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* Cannon1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* Cannon2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* Cannon3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* Cannon4;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* Cannon5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* Cannon6;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* Cannon7;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* Cannon8;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<USceneComponent*> CannonsLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<USceneComponent*> CannonsRight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* HarpoonCannon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* HarpoonProjectile;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCableComponent* Rope;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* BoxCollider;
	
	
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	float RayLength = 15000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	float ThresholdDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	FString CurrentGearName = "";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Threshold")
	float RopeTension = 49.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Threshold")
	float WhaleDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Threshold")
	TArray<AActor*> WhaleReference;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Threshold")
	float CurrentDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Threshold")
	float NextDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Threshold")
	float ThresholdMultiplier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Threshold")
	bool IsShipApproachingBool;
	

	UFUNCTION(BlueprintCallable)
	float ShiftGearUp();
	UFUNCTION(BlueprintCallable)
	float ShiftGearDown();
	
	UFUNCTION(BlueprintCallable)
    void LockAim();
	UFUNCTION(BlueprintCallable)
    void CheckLock();
	UFUNCTION(BlueprintCallable)
	void DrawAimLines(AActor* Objective);
	UFUNCTION(BlueprintCallable)
	float LookingDirection();
	UFUNCTION(BlueprintCallable)
	float CheckTargetDistance();
	UFUNCTION(BlueprintCallable)
	TArray<USceneComponent*> SetCannonsToShoot(TArray<USceneComponent*> cannonArrayInput);
	UFUNCTION(BlueprintCallable)
	void Raycast();

	UFUNCTION(BlueprintCallable)
	FRotator Fire(TArray<USceneComponent*> Cannons, FVector& cannonLoc);
	UFUNCTION(BlueprintCallable)
	float CheckWhaleDistance();
	UFUNCTION(BlueprintCallable)
	float RopeTensionSetter(float multiplier, float _ropeTension);
	UFUNCTION(BlueprintCallable)
	void GetWhaleReference();
	/*UFUNCTION(BlueprintCallable)
	void IsShipApproaching();*/
	UFUNCTION(BlueprintCallable)
	void SetThresholdMultiplier();
	
	
	
	 AActor* FocusedActor;

}
;