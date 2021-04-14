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

    ACharacter* Character = Cast<ACharacter>(GetOwner()); // ��������� �� ���������
    if (!Character) return;

    CurrentWeapon = GetWorld()->SpawnActor<ADSBaseWeapon>(WeaponClass); // ������� ������
    if (!CurrentWeapon) return;
    
    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);  // ����������� ������ � ���� ���������
    CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponAttachPointName);
    CurrentWeapon->SetOwner(Character);
}

void UDSWeaponComponent::StartFire()
{
    if (!CurrentWeapon) return;
    CurrentWeapon->StartFire();
}

void UDSWeaponComponent::StopFire()
{
    if (!CurrentWeapon) return;
    CurrentWeapon->StopFire();
}