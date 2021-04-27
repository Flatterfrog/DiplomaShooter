// Diploma Shooter. Made by Viktor Polyakov IT-5

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DSGameInstance.generated.h"

UCLASS()
class DIPLOMASHOOTER_API UDSGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
		public:
    FName GetStartupLevelName() const { return StartupLevelName; }
            FName GetMenuLevelName() const { return MenuLevelName; }

		protected:
    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FName StartupLevelName = NAME_None;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
    FName MenuLevelName = NAME_None;
};
