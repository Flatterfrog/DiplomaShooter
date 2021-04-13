// Diploma Shooter. Made by Viktor Polyakov IT-5

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DSBaseWeapon.generated.h"

class USkeletalMeshComponent;

UCLASS()
class DIPLOMASHOOTER_API ADSBaseWeapon : public AActor
{
    GENERATED_BODY()

public:
    ADSBaseWeapon();

protected:

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent* WeaponMesh;

    virtual void BeginPlay() override;
};
