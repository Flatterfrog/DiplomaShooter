// Diploma Shooter. Made by Viktor Polyakov IT-5

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DSGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class DIPLOMASHOOTER_API ADSGameHUD : public AHUD
{
	GENERATED_BODY()

		public:

    virtual void DrawHUD() override;

	private:
    void DrawCrossHair();
	
};
