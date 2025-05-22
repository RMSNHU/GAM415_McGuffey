// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "CubeDMIMod.generated.h"

class UNiagaraSystem;

UCLASS()
class FP_GAM415_MCGUFFEY_API ACubeDMIMod : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACubeDMIMod();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Create mesh and materials

	UPROPERTY(EditAnywhere)
		UBoxComponent* boxComp;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* cubeMesh;

	UPROPERTY(EditAnywhere)
		UMaterialInterface* baseMat;

	UPROPERTY()
		UMaterialInstanceDynamic* dmiMat;

	// Create Niagara confetti color
	UPROPERTY(EditAnywhere)
		UNiagaraSystem* colorP;


	// Create overlap trigger
	UFUNCTION()
		void onOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
