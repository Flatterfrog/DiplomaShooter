// Diploma Shooter. Made by Viktor Polyakov IT-5

#include "Player/DSBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "..\..\Public\Player\DSBaseCharacter.h"
#include "Components/DSCharacterMovementComponent.h"
#include "Components/DSHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Controller.h"
#include "Components/CapsuleComponent.h"
#include "Components/DSWeaponComponent.h"

DEFINE_LOG_CATEGORY_STATIC(BaseCharacterLog, All, All);

ADSBaseCharacter::ADSBaseCharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<UDSCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;
    SpringArmComponent->SocketOffset = FVector(0.0f, 100.0f, 80.0f); // настройка расстояния от камеры до персонажа

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);

    HealthComponent = CreateDefaultSubobject<UDSHealthComponent>("HealthComponent");
    
    HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
    HealthTextComponent->SetupAttachment(GetRootComponent());
    HealthTextComponent->SetOwnerNoSee(true);

    WeaponComponent = CreateDefaultSubobject<UDSWeaponComponent>("WeaponComponent");
}

void ADSBaseCharacter::BeginPlay()
{
    Super::BeginPlay();

    check(HealthComponent);
    check(HealthTextComponent);
    check(GetCharacterMovement());
    check(GetMesh());

    OnHealthChanged(HealthComponent->GetHealth(), 0.0f);
    HealthComponent->OnDeath.AddUObject(this, &ADSBaseCharacter::OnDeath);
    HealthComponent->OnHealthChanged.AddUObject(this, &ADSBaseCharacter::OnHealthChanged);

    LandedDelegate.AddDynamic(this, &ADSBaseCharacter::OnGroundLanded);
}

void ADSBaseCharacter::OnHealthChanged(float Health, float HealthDelta)
{
    HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}

void ADSBaseCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ADSBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    check(PlayerInputComponent);
    check(WeaponComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &ADSBaseCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ADSBaseCharacter::MoveRight);
    PlayerInputComponent->BindAxis("LookUp", this, &ADSBaseCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("TurnAround", this, &ADSBaseCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ADSBaseCharacter::Jump);
    PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ADSBaseCharacter::OnStartRunning);
    PlayerInputComponent->BindAction("Run", IE_Released, this, &ADSBaseCharacter::OnStopRunning);
    PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &UDSWeaponComponent::StartFire);
    PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &UDSWeaponComponent::StopFire);
    PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &UDSWeaponComponent::NextWeapon);
    PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &UDSWeaponComponent::Reload);
}

bool ADSBaseCharacter::IsRunning() const
{
    return WantsToRun && IsMovingForward && !GetVelocity().IsZero();
}

float ADSBaseCharacter::GetMovementDirection() const
{
    if (GetVelocity().IsZero()) return 0.0f;
    const auto VelocityNormal = GetVelocity().GetSafeNormal();
    const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
    const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
    const auto Degrees = FMath::RadiansToDegrees(AngleBetween);
    return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

void ADSBaseCharacter::MoveForward(float Amount) 
{
    IsMovingForward = Amount > 0.0f;
    if (Amount == 0.0f) return;
    AddMovementInput(GetActorForwardVector(), Amount);
}

void ADSBaseCharacter::MoveRight(float Amount) 
{
    if (Amount == 0.0f) return;
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

void ADSBaseCharacter::OnDeath() 
{
    UE_LOG(BaseCharacterLog, Display, TEXT("Player %s is dead"), *GetName());

    GetCharacterMovement()->DisableMovement();

    SetLifeSpan(LifeSpanOnDeath);
    if (Controller)
    {
        Controller->ChangeState(NAME_Spectating);
    }
    GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    WeaponComponent->StopFire();

    GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    GetMesh()->SetSimulatePhysics(true);
}

void ADSBaseCharacter::OnGroundLanded(const FHitResult& Hit)
{
    const auto FallVelocityZ = -GetVelocity().Z;
    if (FallVelocityZ < LandedDamageVelocity.X) return;
    const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);
    TakeDamage(FinalDamage, FDamageEvent{}, nullptr, nullptr);
}

void ADSBaseCharacter::SetPlayerColor(const FLinearColor& Color) {
    const auto MaterialInst = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);
    if(!MaterialInst) return;
    MaterialInst->SetVectorParameterValue(MaterialColorName, Color);
}