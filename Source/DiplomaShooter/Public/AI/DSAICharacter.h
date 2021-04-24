// Diploma Shooter. Made by Viktor Polyakov IT-5

#pragma once

#include "CoreMinimal.h"
#include "Player/DSBaseCharacter.h"
#include "DSAICharacter.generated.h"

class UBehaviorTree;

UCLASS()
class DIPLOMASHOOTER_API ADSAICharacter : public ADSBaseCharacter
{
	GENERATED_BODY()

		public:
    ADSAICharacter(const FObjectInitializer& ObjInit);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
    UBehaviorTree* BehaviorTreeAsset;


	protected:
	virtual void OnDeath() override;
	
};
