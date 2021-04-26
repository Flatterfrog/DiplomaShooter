// Diploma Shooter. Made by Viktor Polyakov IT-5

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DSSpectatorWidget.generated.h"

UCLASS()
class DIPLOMASHOOTER_API UDSSpectatorWidget : public UUserWidget
{
	GENERATED_BODY()

		public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetRespawnTime(int32& CountDownTime) const;
};
