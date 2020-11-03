// Fill out your copyright notice in the Description page of Project Settings.

#include "TeaPawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Contructor Method that Sets default values
ATeaPawn::ATeaPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TeapotMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pawn Mesh"));
	TeapotMesh->SetupAttachment(RootComponent);

	//stretch**************
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	SpringArm->SetupAttachment(TeapotMesh);
	SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 20.0f));
	SpringArm->SetRelativeRotation(FRotator(-30.f, 0.f, 0.f));
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 5.0f;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->CameraRotationLagSpeed = 5.0f;
	//stretch***************


	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Actual Camera"));
	//Camera->SetupAttachment(TeapotMesh); //from pre-stretch
	Camera->SetupAttachment(SpringArm); //added post stretch

	//Camera->SetRelativeLocation(FVector(-400.0f, 0.0f, 350.0f)); //from pre-stretch
	//Camera->SetRelativeRotation(FRotator(-20.0f, 0.0f, 0.0f)); //from pre-stretch
	Camera->SetRelativeRotation(FRotator(20.0f, 0.0f, 0.0f)); //added post stretch

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ATeaPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATeaPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalOffset(DeltaLocation, true); //true is a sweep check (checks for collisions when the pawn is moving
	AddActorLocalRotation(DeltaRotation, true);
}

// Called to bind functionality to input
void ATeaPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Drive", this, &ATeaPawn::SetMoveAmount);
	PlayerInputComponent->BindAxis("Turn", this, &ATeaPawn::SetRotateAmount);
}

void ATeaPawn::SetMoveAmount(float Value){
	UE_LOG(LogTemp, Warning, TEXT("Drive Pressed: %f"), Value);
	DeltaLocation = FVector(Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0.0f, 0.0f);
}

void ATeaPawn::SetRotateAmount(float Value){
	UE_LOG(LogTemp, Warning, TEXT("Turn Pressed %f"), Value);

	float RotateAmount = Value * RotationSpeed * GetWorld()->DeltaTimeSeconds;
	FRotator Rotation = FRotator(0.0f, RotateAmount, 0.0f);
	DeltaRotation = FQuat(Rotation);
}

