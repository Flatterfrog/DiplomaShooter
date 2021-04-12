// Diploma Shooter. Made by Viktor Polyakov IT-5

#include "Components/DSHealthComponent.h"
#include "GameFramework/Actor.h"

UDSHealthComponent::UDSHealthComponent()
{

    PrimaryComponentTick.bCanEverTick = false;
}

void UDSHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    Health = MaxHealth;
    OnHealthChanged.Broadcast(Health);

    AActor* ComponentOwner = GetOwner();
    if (ComponentOwner)
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UDSHealthComponent::OnTakeAnyDamage);
    }
}

void UDSHealthComponent::OnTakeAnyDamage(
    AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{

    if (Damage <= 0.0f || IsDead()) return;

    Health =FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
    OnHealthChanged.Broadcast(Health);

    if (IsDead())
    {
        OnDeath.Broadcast();
    }
}