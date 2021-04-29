// Diploma Shooter. Made by Viktor Polyakov IT-5

#pragma once

#include "CoreMinimal.h"
#include "Weapon/DSBaseWeapon.h"
#include "DSLauncherWeapon.generated.h"

class ADSProjectile;
class USoundCue;

UCLASS()
class DIPLOMASHOOTER_API ADSLauncherWeapon : public ADSBaseWeapon
{
	GENERATED_BODY()
	
		public:
    virtual void StartFire() override;

	protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<ADSProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
    USoundCue* NoAmmoSound;

    virtual void MakeShot() override;
};
