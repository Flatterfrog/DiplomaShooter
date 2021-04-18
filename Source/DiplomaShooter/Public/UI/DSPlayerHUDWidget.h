// Diploma Shooter. Made by Viktor Polyakov IT-5

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DSCoreTypes.h"
#include "DSPlayerHUDWidget.generated.h"


UCLASS()
class DIPLOMASHOOTER_API UDSPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

		public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    float GetHealthPercent() const;
	
	UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const;

	UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const;

	UFUNCTION(BlueprintCallable, Category = "UI")
    bool IsPlayerAlive() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
    bool IsPlayerSpectating() const;

};
