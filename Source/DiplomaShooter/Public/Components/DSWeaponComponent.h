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

protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponAttachPointName = "WeaponPoint";

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TSubclassOf<ADSBaseWeapon> WeaponClass;

	virtual void BeginPlay() override;

	private:

    UPROPERTY()
    ADSBaseWeapon* CurrentWeapon = nullptr;

	void SpawnWeapon();
};
