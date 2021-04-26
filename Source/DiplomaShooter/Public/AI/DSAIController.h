// Diploma Shooter. Made by Viktor Polyakov IT-5

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DSAIController.generated.h"

class UDSAIPerceptionComponent;
class UDSRespawnComponent;

UCLASS()
class DIPLOMASHOOTER_API ADSAIController : public AAIController
{
	GENERATED_BODY()

		public:
    ADSAIController();

	protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UDSAIPerceptionComponent* DSAIPerceptionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UDSRespawnComponent* RespawnComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FName FocusOnKeyName = "EnemyActor";


	virtual void Tick(float DeltaTime) override;
    virtual void OnPossess(APawn* InPawn) override;
	

	private:
    AActor* GetFocusOnActor() const;
};
