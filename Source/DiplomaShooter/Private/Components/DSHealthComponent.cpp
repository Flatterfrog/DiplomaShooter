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

    AActor* ComponentOwner = GetOwner();
    if (ComponentOwner)
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UDSHealthComponent::OnTakeAnyDamage);
    }
}

void UDSHealthComponent::OnTakeAnyDamage(
    AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
    Health -= Damage;
}