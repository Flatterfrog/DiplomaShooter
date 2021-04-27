// Diploma Shooter. Made by Viktor Polyakov IT-5

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DSCoreTypes.h"
#include "DSPlayerController.generated.h"

class UDSRespawnComponent;

UCLASS()
class DIPLOMASHOOTER_API ADSPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    ADSPlayerController();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UDSRespawnComponent* RespawnComponent;

    virtual void BeginPlay() override;
    virtual void OnPossess(APawn* InPawn) override;
    virtual void SetupInputComponent() override;

private:
    void OnPauseGame();
    void OnMatchStateChanged(EDSMatchState State);
};
