// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProcPlane.generated.h"

class UProceduralMeshComponent;

UCLASS()
class FP_GAM415_MCGUFFEY_API AProcPlane : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProcPlane();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostActorCreated() override;

	virtual void PostLoad() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Create arrays of vertices, triangles, and UVs
	UPROPERTY(EditAnywhere)
		TArray<FVector> Vertices;

	UPROPERTY(EditAnywhere)
		TArray<int> Triangles;

	UPROPERTY(EditAnywhere)
		TArray<FVector2D> UV0;

	// Create plane material
	UPROPERTY(EditAnywhere)
		UMaterialInterface* PlaneMat;

	// Create mesh function
	UFUNCTION()
		void CreateMesh();

private:
	// Create procedual mesh
	UProceduralMeshComponent* procMesh;
};

