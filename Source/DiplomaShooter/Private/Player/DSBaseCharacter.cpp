// Diploma Shooter. Made by Viktor Polyakov IT-5

#include "Player/DSBaseCharacter.h"
#include "..\..\Public\Player\DSBaseCharacter.h"
#include "Components/DSCharacterMovementComponent.h"
#include "Components/DSHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Controller.h"
#include "Components/CapsuleComponent.h"
#include "Components/DSWeaponComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

DEFINE_LOG_CATEGORY_STATIC(BaseCharacterLog, All, All);

ADSBaseCharacter::ADSBaseCharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<UDSCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
    PrimaryActorTick.bCanEverTick = true;

    HealthComponent = CreateDefaultSubobject<UDSHealthComponent>("HealthComponent");
    WeaponComponent = CreateDefaultSubobject<UDSWeaponComponent>("WeaponComponent");
}

void ADSBaseCharacter::BeginPlay()
{
    Super::BeginPlay();

    check(HealthComponent);
    check(GetCharacterMovement());
    check(GetMesh());

    OnHealthChanged(HealthComponent->GetHealth(), 0.0f);
    HealthComponent->OnDeath.AddUObject(this, &ADSBaseCharacter::OnDeath);
    HealthComponent->OnHealthChanged.AddUObject(this, &ADSBaseCharacter::OnHealthChanged);

    LandedDelegate.AddDynamic(this, &ADSBaseCharacter::OnGroundLanded);
}

void ADSBaseCharacter::OnHealthChanged(float Health, float HealthDelta)
{

}

void ADSBaseCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
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

bool ADSBaseCharacter::IsRunning() const
{
    return false;
}

void ADSBaseCharacter::OnDeath() 
{
    UE_LOG(BaseCharacterLog, Display, TEXT("Player %s is dead"), *GetName());

    GetCharacterMovement()->DisableMovement();

    SetLifeSpan(LifeSpanOnDeath);
    GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    WeaponComponent->StopFire();

    GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    GetMesh()->SetSimulatePhysics(true);

    UGameplayStatics::PlaySoundAtLocation(GetWorld(), DeathSound, GetActorLocation());
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