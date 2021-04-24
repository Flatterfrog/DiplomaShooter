// Diploma Shooter. Made by Viktor Polyakov IT-5

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "DSEnemyEnvQueryContext.generated.h"


UCLASS()
class DIPLOMASHOOTER_API UDSEnemyEnvQueryContext : public UEnvQueryContext
{
	GENERATED_BODY()
	

		public:
    virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;

	protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FName EnemyActorKeyName = "EnemyActor";
};
