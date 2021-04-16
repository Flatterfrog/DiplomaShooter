// Diploma Shooter. Made by Viktor Polyakov IT-5

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DSWeaponComponent.generated.h"

class ADSBaseWeapon;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DIPLOMASHOOTER_API UDSWeaponComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UDSWeaponComponent();

    void StartFire();
    void StopFire();
    void NextWeapon();

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponEquipSocketName = "WeaponSocket";

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponArmorySocketName = "ArmorySocket";

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TArray<TSubclassOf<ADSBaseWeapon>> WeaponClasses;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    UAnimMontage* EquipAnimMontage;

    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
    UPROPERTY()
    ADSBaseWeapon* CurrentWeapon = nullptr;

    UPROPERTY()
    TArray<ADSBaseWeapon*> Weapons;

    int32 CurrentWeaponIndex = 0;
    bool EquipAnimInProgress = false;

    void EquipWeapon(int32 WeaponIndex);
    void SpawnWeapons();
    void AttachWeaponToSocket(ADSBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);
    void PlayAnimMontage(UAnimMontage* Animation);

    void InitAnimations();
    void OnEquipFinished(USkeletalMeshComponent* MeshComponent);
    
    bool CanFire() const;
    bool CanEquip() const;

};
