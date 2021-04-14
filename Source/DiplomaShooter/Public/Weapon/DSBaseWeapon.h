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

    virtual void Fire();

protected:

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent* WeaponMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    FName MuzzleSocketName = "MuzzleSocket";

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    float TraceMaxDistance = 1500.0f;

    virtual void BeginPlay() override;

    void MakeShot();
};
