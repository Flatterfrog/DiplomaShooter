// Diploma Shooter. Made by Viktor Polyakov IT-5

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "DSPlayerState.generated.h"

UCLASS()
class DIPLOMASHOOTER_API ADSPlayerState : public APlayerState
{
    GENERATED_BODY()

public:
    void SetTeamID(int32 ID) { TeamID = ID; }
    int32 GetTeamID() const { return TeamID; }

    void SetTeamColor(const FLinearColor& Color) { TeamColor = Color; }
    FLinearColor GetTeamColor() const { return TeamColor; }

    void AddKill() {++KillsNum;}
    int32 GetKillsNum() const {return KillsNum;}

    void AddDeath() {++DeathsNum;}
    int32 GetDeathsNum() const {return DeathsNum;}

private:
    int32 TeamID;
    FLinearColor TeamColor;

    int32 KillsNum = 0;
    int32 DeathsNum = 0;
};
