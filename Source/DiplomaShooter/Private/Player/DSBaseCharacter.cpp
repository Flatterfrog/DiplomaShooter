// Diploma Shooter. Made by Viktor Polyakov IT-5

#include "Player/DSBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "..\..\Public\Player\DSBaseCharacter.h"
#include "Components/DSCharacterMovementComponent.h"

// Sets default values
ADSBaseCharacter::ADSBaseCharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<UDSCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;


    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);
}

// Called when the game starts or when spawned
void ADSBaseCharacter::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ADSBaseCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ADSBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("MoveForward", this, &ADSBaseCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ADSBaseCharacter::MoveRight);
    PlayerInputComponent->BindAxis("LookUp", this, &ADSBaseCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("TurnAround", this, &ADSBaseCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ADSBaseCharacter::Jump);
    PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ADSBaseCharacter::OnStartRunning);
    PlayerInputComponent->BindAction("Run", IE_Released, this, &ADSBaseCharacter::OnStopRunning);
}

bool ADSBaseCharacter::IsRunning() const
{
    return WantsToRun && IsMovingForward && !GetVelocity().IsZero();
}

void ADSBaseCharacter::MoveForward(float Amount) 
{
    IsMovingForward = Amount > 0.0f;
    AddMovementInput(GetActorForwardVector(), Amount);
}

void ADSBaseCharacter::MoveRight(float Amount) 
{
    AddMovementInput(GetActorRightVector(), Amount);
}

void ADSBaseCharacter::OnStartRunning() 
{
    WantsToRun = true;
}

void ADSBaseCharacter::OnStopRunning() 
{
    WantsToRun = false;
}
