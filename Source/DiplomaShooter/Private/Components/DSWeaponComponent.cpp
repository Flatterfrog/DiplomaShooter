// Diploma Shooter. Made by Viktor Polyakov IT-5

#include "Components/DSWeaponComponent.h"
#include "Weapon/DSBaseWeapon.h"
#include "GameFramework/Character.h"
#include "Animations/DSEquipFinishedAnimNotify.h"

UDSWeaponComponent::UDSWeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UDSWeaponComponent::BeginPlay()
{
    Super::BeginPlay();
    CurrentWeaponIndex = 0;
    InitAnimations(); 
    SpawnWeapons();
    EquipWeapon(CurrentWeaponIndex);
}

void UDSWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    CurrentWeapon = nullptr;
    for (auto Weapon : Weapons)
    {
        Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
        Weapon->Destroy();
    }
    Weapons.Empty();

    Super::EndPlay(EndPlayReason);
}

void UDSWeaponComponent::SpawnWeapons()
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());  // указатель на персонажа
    if (!GetWorld() || !Character) return;

    for (auto WeaponClass : WeaponClasses)
    {
        auto Weapon = GetWorld()->SpawnActor<ADSBaseWeapon>(WeaponClass);  // Создаем оружие
        if (!Weapon) continue;

        Weapon->SetOwner(Character);
        Weapons.Add(Weapon);

        AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
    }
}

void UDSWeaponComponent::AttachWeaponToSocket(ADSBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName)
{
    if (!Weapon || !SceneComponent) return;
    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);  // привязываем оружие к мешу персонажа
    Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}

void UDSWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());  // указатель на персонажа
    if (!Character) return;

    if (CurrentWeapon)
    {
        CurrentWeapon->StopFire();
        AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
    }

    CurrentWeapon = Weapons[WeaponIndex];
    AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
    EquipAnimInProgress = true;
    PlayAnimMontage(EquipAnimMontage);
}

void UDSWeaponComponent::StartFire()
{
    if (!CanFire()) return;
    CurrentWeapon->StartFire();
}

void UDSWeaponComponent::StopFire()
{
    if (!CurrentWeapon) return;
    CurrentWeapon->StopFire();
}

void UDSWeaponComponent::NextWeapon()
{
    if (!CanEquip()) return;
    CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
    EquipWeapon(CurrentWeaponIndex);
}

void UDSWeaponComponent::PlayAnimMontage(UAnimMontage* Animation) 
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());  // указатель на персонажа
    if (!Character) return;

    Character->PlayAnimMontage(Animation);
}



void UDSWeaponComponent::InitAnimations() 
{
    if (!EquipAnimMontage) return;
    const auto NotifyEvents = EquipAnimMontage->Notifies;
    for (auto NotifyEvent : NotifyEvents)
    {
        auto EquipFinishedNotify = Cast<UDSEquipFinishedAnimNotify>(NotifyEvent.Notify);
        if (EquipFinishedNotify)
        {
            EquipFinishedNotify->OnNotified.AddUObject(this, &UDSWeaponComponent::OnEquipFinished);
            break;

        }
    }
}
void UDSWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComponent) 
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());  // указатель на персонажа
    if (!Character || Character->GetMesh() != MeshComponent) return;
    EquipAnimInProgress = false;

}

bool UDSWeaponComponent::CanFire() const 
{
    return CurrentWeapon && !EquipAnimInProgress;
}
bool UDSWeaponComponent::CanEquip() const 
{
    return !EquipAnimInProgress;
}