#include "CPP_BodyV2.h"

ACPP_BodyV2::ACPP_BodyV2()
{
	PrimaryActorTick.bCanEverTick = true;
    Mass = FMath::RandRange(20, 100);
}

void ACPP_BodyV2::BeginPlay()
{
    Super::BeginPlay();

    auto PaperSprite = LoadObject<UPaperSprite>(nullptr, TEXT("/Game/Sprites/Circle_Sprite"));
    auto SceneComponent = NewObject<USceneComponent>(this);
    RootComponent = SceneComponent;
    auto SpriteComponent = NewObject<UPaperSpriteComponent>(this);
    SpriteComponent->SetSprite(PaperSprite);
    SpriteComponent->SetupAttachment(SceneComponent);
    SpriteComponent->RegisterComponent();
    SpriteComponent->SetWorldScale3D(FVector(0.025, 0.025, 0.025));
    //SpriteComponent->SetSimulatePhysics(true);
    //SpriteComponent->SetEnableGravity(false);
    AddInstanceComponent(SpriteComponent);
}

void ACPP_BodyV2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

