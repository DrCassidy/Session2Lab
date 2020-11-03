// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TeaPawn.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class SESSION2LAB_API ATeaPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATeaPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* TeapotMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		USceneComponent* ProjectileSpawnPoint;
	UPROPERTY(EditAnywhere)
		UCameraComponent* Camera;
	UPROPERTY(EditAnywhere)
		USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere)
		float MoveSpeed = 500.0f;
	UPROPERTY(EditAnywhere)
		float RotationSpeed = 200.0f;

	FVector DeltaLocation;
	FQuat DeltaRotation;
	void SetMoveAmount(float Value);
	void SetRotateAmount(float Value);

	/*UPROPERTY(EditAnywhere)
		float EditAnywhereFloat;
	UPROPERTY(EditDefaultsOnly)
		float EditDefaultFloat;
	UPROPERTY(EditInstanceOnly)
		float EditInstanceFloat;
	UPROPERTY(VisibleAnywhere)
		float VisibleAnywhereFloat;
	UPROPERTY(VisibleDefaultsOnly)
		float VisibleDefaultsFloat;
	UPROPERTY(VisibleInstanceOnly)
		float VisibleInstanceFloat;*/
};
