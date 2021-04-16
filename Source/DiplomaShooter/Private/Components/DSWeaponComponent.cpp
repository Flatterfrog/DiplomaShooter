// Diploma Shooter. Made by Viktor Polyakov IT-5

#include "Components/DSWeaponComponent.h"
#include "Weapon/DSBaseWeapon.h"
#include "GameFramework/Character.h"
#include "Animations/DSEquipFinishedAnimNotify.h"
#include "Animations/DSReloadFinishedAnimNotify.h"
#include "Animations/AnimUtils.h"

constexpr static int32 WeaponNum = 2;

UDSWeaponComponent::UDSWeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UDSWeaponComponent::BeginPlay()
{
    Super::BeginPlay();
    checkf(WeaponData.Num() == WeaponNum, TEXT("Our character can hold only %i weapon items"), WeaponNum);
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

    for (auto OneWeaponData : WeaponData)
    {
        auto Weapon = GetWorld()->SpawnActor<ADSBaseWeapon>(OneWeaponData.WeaponClass);  // Создаем оружие
        if (!Weapon) continue;

        Weapon->OnClipEmpty.AddUObject(this, &UDSWeaponComponent::OnEmptyClip);
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
    if (WeaponIndex < 0 || WeaponIndex >= Weapons.Num())
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid weapon index"));
        return;
    }
    ACharacter* Character = Cast<ACharacter>(GetOwner());  // указатель на персонажа
    if (!Character) return;

    if (CurrentWeapon)
    {
        CurrentWeapon->StopFire();
        AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
    }

    CurrentWeapon = Weapons[WeaponIndex];

    const auto CurrentWeaponData = WeaponData.FindByPredicate([&](const FWeaponData& Data) {  //
        return Data.WeaponClass == CurrentWeapon->GetClass();                                 //
    });
    CurrentReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr;

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
    auto EquipFinishedNotify = AnimUtils::FindNotifyByClass<UDSEquipFinishedAnimNotify>(EquipAnimMontage);
    if (EquipFinishedNotify)
    {
        EquipFinishedNotify->OnNotified.AddUObject(this, &UDSWeaponComponent::OnEquipFinished);
    }else
    {
        UE_LOG(LogTemp, Error, TEXT("Equip anim notify is forgotten to set"));
        checkNoEntry();
    }

    for (auto OneWeaponData : WeaponData)
    {
        auto ReloadFinishedNotify = AnimUtils::FindNotifyByClass<UDSReloadFinishedAnimNotify>(OneWeaponData.ReloadAnimMontage);

        if (!ReloadFinishedNotify)
        {
            UE_LOG(LogTemp, Error, TEXT("Reload anim notify is forgotten to set"));
            checkNoEntry();
        }

        ReloadFinishedNotify->OnNotified.AddUObject(this, &UDSWeaponComponent::OnReloadFinished);
    }
}
void UDSWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComponent)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());  // указатель на персонажа
    if (!Character || Character->GetMesh() != MeshComponent) return;
    EquipAnimInProgress = false;
}

void UDSWeaponComponent::OnReloadFinished(USkeletalMeshComponent* MeshComponent)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());  // указатель на персонажа
    if (!Character || Character->GetMesh() != MeshComponent) return;
    ReloadAnimInProgress = false;
}

bool UDSWeaponComponent::CanFire() const
{
    return CurrentWeapon && !EquipAnimInProgress && !ReloadAnimInProgress;
}
bool UDSWeaponComponent::CanEquip() const
{
    return !EquipAnimInProgress && !ReloadAnimInProgress;
}
bool UDSWeaponComponent::CanReload() const
{
    return CurrentWeapon && !EquipAnimInProgress && !ReloadAnimInProgress && CurrentWeapon->CanReload();
}

void UDSWeaponComponent::Reload()
{
    ChangeClip();
}

void UDSWeaponComponent::OnEmptyClip()
{
    ChangeClip();
}
void UDSWeaponComponent::ChangeClip()
{
    if (!CanReload()) return;
    CurrentWeapon->StopFire();
    CurrentWeapon->ChangeClip();

    ReloadAnimInProgress = true;
    PlayAnimMontage(CurrentReloadAnimMontage);
}