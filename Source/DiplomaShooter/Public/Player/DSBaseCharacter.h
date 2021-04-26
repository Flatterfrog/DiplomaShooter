// Diploma Shooter. Made by Viktor Polyakov IT-5

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DSBaseCharacter.generated.h"


class UDSHealthComponent;
class UDSWeaponComponent;

UCLASS()
class DIPLOMASHOOTER_API ADSBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	ADSBaseCharacter(const FObjectInitializer& ObjInit);

protected:



	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UDSHealthComponent* HealthComponent;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UDSWeaponComponent* WeaponComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage* DeathAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
    float LifeSpanOnDeath = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
    FVector2D LandedDamageVelocity = FVector2D(900.0f, 1200.0f);

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
    FVector2D LandedDamage = FVector2D(10.0f, 100.0f);

	UPROPERTY(EditDefaultsOnly, Category = "Material")
    FName MaterialColorName = "Paint Color";

	virtual void BeginPlay() override;
    virtual void OnDeath();

public:	

	virtual void Tick(float DeltaTime) override;
	

	UFUNCTION(BlueprintCallable, Category = "Movement")
    virtual bool IsRunning() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
    float GetMovementDirection() const;

	void SetPlayerColor(const FLinearColor& Color);

	private:


	
    void OnHealthChanged(float Health, float HealthDelta);

    UFUNCTION()
    void OnGroundLanded(const FHitResult& Hit);

};
