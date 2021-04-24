// Diploma Shooter. Made by Viktor Polyakov IT-5

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "DSAIPerceptionComponent.generated.h"


UCLASS()
class DIPLOMASHOOTER_API UDSAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()
	
		public:
    AActor* GetClosestEnemy() const;
};
