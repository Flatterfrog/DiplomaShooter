// Diploma Shooter. Made by Viktor Polyakov IT-5

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "DSChangeWeaponService.generated.h"

UCLASS()
class DIPLOMASHOOTER_API UDSChangeWeaponService : public UBTService
{
	GENERATED_BODY()
	

		public:
    UDSChangeWeaponService();

	protected:

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (ClampMin = "0.0", ClampMax = "1.0"))
        float Probability = 0.5f;
    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
