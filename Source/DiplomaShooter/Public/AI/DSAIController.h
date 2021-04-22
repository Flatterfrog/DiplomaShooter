// Diploma Shooter. Made by Viktor Polyakov IT-5

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DSAIController.generated.h"

UCLASS()
class DIPLOMASHOOTER_API ADSAIController : public AAIController
{
	GENERATED_BODY()

	protected:
    virtual void OnPossess(APawn* InPawn) override;
	
};
