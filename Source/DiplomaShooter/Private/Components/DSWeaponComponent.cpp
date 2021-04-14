// Diploma Shooter. Made by Viktor Polyakov IT-5

#include "Components/DSWeaponComponent.h"
#include "Weapon/DSBaseWeapon.h"
#include "GameFramework/Character.h"

UDSWeaponComponent::UDSWeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UDSWeaponComponent::BeginPlay()
{
    Super::BeginPlay();
    SpawnWeapon();
}

void UDSWeaponComponent::SpawnWeapon()
{
    if (!GetWorld()) return;

    ACharacter* Character = Cast<ACharacter>(GetOwner()); // указатель на персонажа
    if (!Character) return;

    CurrentWeapon = GetWorld()->SpawnActor<ADSBaseWeapon>(WeaponClass); // Создаем оружие
    if (!CurrentWeapon) return;
    
    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);  // привязываем оружие к мешу персонажа
    CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponAttachPointName);
    CurrentWeapon->SetOwner(Character);
}

void UDSWeaponComponent::Fire()
{
    if (!CurrentWeapon) return;
    CurrentWeapon->Fire();
}