// Diploma Shooter. Made by Viktor Polyakov IT-5

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "DSFindEnemyService.generated.h"


UCLASS()
class DIPLOMASHOOTER_API UDSFindEnemyService : public UBTService
{
	GENERATED_BODY()
	

		public:
    UDSFindEnemyService();

	protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector EnemyActorKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
