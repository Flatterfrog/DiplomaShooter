// Diploma Shooter. Made by Viktor Polyakov IT-5


#include "Player/DSBaseCharacter.h"
#include "Camera/CameraComponent.h"

// Sets default values
ADSBaseCharacter::ADSBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void ADSBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADSBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADSBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

