// Diploma Shooter. Made by Viktor Polyakov IT-5

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DSRespawnComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DIPLOMASHOOTER_API UDSRespawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDSRespawnComponent();


		void Respawn(int32 RespawnTime);
    int32 GetRespawnCountDown() const { return RespawnCountDown; }
        bool IsRespawnInProgress() const;
		private:
        FTimerHandle RespawnTimerHandle;
            int32 RespawnCountDown = 0;

			void RespawnTimerUpdate();
};
