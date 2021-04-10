// Diploma Shooter. Made by Viktor Polyakov IT-5

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DSCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class DIPLOMASHOOTER_API UDSCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement", meta = (ClampMin = "1.5", ClampMax = "10.0"))
    float RunModifier = 2.0f;

    virtual float GetMaxSpeed() const override;
};
