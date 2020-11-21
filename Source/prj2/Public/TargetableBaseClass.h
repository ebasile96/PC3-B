// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "prj2/ITargetable.h"
#include "TargetableBaseClass.generated.h"


UCLASS()
class PRJ2_API ATargetableBaseClass : public AActor, public IITargetable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATargetableBaseClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Targetable")
    void OnFocused();
	virtual  void OnFocused_Implementation();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Targetable")
    void OffFocused();
	virtual void OffFocused_Implementation();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Targetable")
    void Interact(APawn* Caller);
	virtual void Interact_Implementation(APawn* Caller);

};
