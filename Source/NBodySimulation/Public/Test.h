// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_BodyV2.h"
#include "Test.generated.h"

UCLASS()
class NBODYSIMULATION_API ATest : public AActor
{
	GENERATED_BODY()
	
public:	

	TArray<ACPP_BodyV2*> Bodies;
	TArray<FVector> NewPositions;
	float GravitationalConstant;
	ATest();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

};
