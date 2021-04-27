// Diploma Shooter. Made by Viktor Polyakov IT-5

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DSMenuHUD.generated.h"


UCLASS()
class DIPLOMASHOOTER_API ADSMenuHUD : public AHUD
{
	GENERATED_BODY()
	
		protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> MenuWidgetClass;

    virtual void BeginPlay() override;
};
