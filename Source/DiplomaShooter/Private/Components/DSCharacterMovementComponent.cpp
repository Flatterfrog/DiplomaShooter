// Diploma Shooter. Made by Viktor Polyakov IT-5


#include "Components/DSCharacterMovementComponent.h"
#include "Player/DSBaseCharacter.h"

float UDSCharacterMovementComponent::GetMaxSpeed() const 
{
    const float MaxSpeed = Super::GetMaxSpeed();
    const ADSBaseCharacter* Player = Cast<ADSBaseCharacter>(GetPawnOwner());
    return Player && Player->IsRunning() ? MaxSpeed * RunModifier: MaxSpeed;
}