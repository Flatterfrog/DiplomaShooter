// Diploma Shooter. Made by Viktor Polyakov IT-5

#pragma once

#include "CoreMinimal.h"
#include "Components/DSWeaponComponent.h"
#include "DSAIWeaponComponent.generated.h"

UCLASS()
class DIPLOMASHOOTER_API UDSAIWeaponComponent : public UDSWeaponComponent
{
    GENERATED_BODY()

public:
    virtual void StartFire() override;
    virtual void NextWeapon() override;
};
