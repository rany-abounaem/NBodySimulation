// Fill out your copyright notice in the Description page of Project Settings.


#include "Test.h"

// Sets default values
ATest::ATest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    GravitationalConstant = 1;
}

// Called when the game starts or when spawned
void ATest::BeginPlay()
{
    Super::BeginPlay();
    auto SceneComponent = NewObject<USceneComponent>(this);
    RootComponent = SceneComponent;
    Bodies.SetNum(1000);

    for (int i = 0; i < 1000; i++)
    {
        auto randX = FMath::RandRange(-500, 500);
        auto randY = FMath::RandRange(-500, 500);
        Bodies[i] = GetWorld()->SpawnActor<ACPP_BodyV2>(FVector(0,0,0), FRotator(0,0,0));
        Bodies[i]->SetActorLocation(FVector(randX, 0, randY));
        if (!Bodies[i])
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to spawn actor"));
            return;
        }
    }

    NewPositions.Init(FVector::ZeroVector, Bodies.Num());
    for (int i = 0; i < NewPositions.Num(); i++)
    {
        NewPositions[i] = Bodies[i]->GetActorLocation();
    }
}

void ATest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    ParallelFor(Bodies.Num(), [&](int i) {
        auto BodyLocation = NewPositions[i];
        for (int j = 0; j < Bodies.Num(); j++) {
            if (Bodies[i] == Bodies[j]) continue;
            auto OtherBodyLocation = NewPositions[j];
            float Distance = FVector::Distance(BodyLocation, OtherBodyLocation);
            Distance = FMath::Clamp(10, Distance, 100);
            auto ForceValue = GravitationalConstant * (Bodies[i]->Mass * Bodies[j]->Mass) / (Distance * Distance);
            auto Direction = (BodyLocation - OtherBodyLocation);
            Direction.Normalize();
            auto FinalPosition = Direction * ForceValue * DeltaTime;
            NewPositions[i] += FinalPosition;
        }
    });

    for (int i = 0; i < Bodies.Num(); i++) {
        Bodies[i]->SetActorLocation(NewPositions[i]);
    }
}

