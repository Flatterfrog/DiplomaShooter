// Diploma Shooter. Made by Viktor Polyakov IT-5

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DSMenuPlayerController.generated.h"


UCLASS()
class DIPLOMASHOOTER_API ADSMenuPlayerController : public APlayerController
{
    GENERATED_BODY()

    protected:
    virtual void BeginPlay() override;
};
