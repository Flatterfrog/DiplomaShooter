// Diploma Shooter. Made by Viktor Polyakov IT-5

#pragma once

#include "CoreMinimal.h"
#include "Player/DSBaseCharacter.h"
#include "DSAICharacter.generated.h"

class UBehaviorTree;
class UWidgetComponent;

UCLASS()
class DIPLOMASHOOTER_API ADSAICharacter : public ADSBaseCharacter
{
	GENERATED_BODY()

		public:
    ADSAICharacter(const FObjectInitializer& ObjInit);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
    UBehaviorTree* BehaviorTreeAsset;

	virtual void Tick(float DeltaTime) override;

	protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UWidgetComponent* HealthWidgetComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
    float HealthVisibilityDistance = 1000.0f;

    virtual void BeginPlay() override;

	virtual void OnDeath() override;

	virtual void OnHealthChanged(float Health, float HealthDelta) override;

private:
    void UpdateHealthWidgetVisibility();
	
};
