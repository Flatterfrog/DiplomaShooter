// Diploma Shooter. Made by Viktor Polyakov IT-5

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DSCoreTypes.h"
#include "DSWeaponComponent.generated.h"

class ADSBaseWeapon;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DIPLOMASHOOTER_API UDSWeaponComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UDSWeaponComponent();

    virtual void StartFire();
    void StopFire();
    virtual void NextWeapon();
    void Reload();

    bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const;
    bool GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const;

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TArray<FWeaponData> WeaponData;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponEquipSocketName = "WeaponSocket";

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponArmorySocketName = "ArmorySocket";

    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage* EquipAnimMontage;

    UPROPERTY()
    ADSBaseWeapon* CurrentWeapon = nullptr;

    UPROPERTY()
    TArray<ADSBaseWeapon*> Weapons;

    int32 CurrentWeaponIndex = 0;

    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    bool CanFire() const;
    bool CanEquip() const;
    void EquipWeapon(int32 WeaponIndex);
    

private:
    UPROPERTY()
    UAnimMontage* CurrentReloadAnimMontage = nullptr;

    
    bool EquipAnimInProgress = false;
    bool ReloadAnimInProgress = false;

    void SpawnWeapons();
    void AttachWeaponToSocket(ADSBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);
    void PlayAnimMontage(UAnimMontage* Animation);

    void InitAnimations();
    void OnEquipFinished(USkeletalMeshComponent* MeshComponent);
    void OnReloadFinished(USkeletalMeshComponent* MeshComponent);

    bool CanReload() const;

    void OnEmptyClip();
    void ChangeClip();
};
