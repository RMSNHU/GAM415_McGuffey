// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeDMIMod.h"
#include "FP_GAM415_McGuffeyCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

// Sets default values
ACubeDMIMod::ACubeDMIMod()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 
	boxComp = CreateDefaultSubobject<UBoxComponent>("Box Component");
	cubeMesh = CreateDefaultSubobject<UStaticMeshComponent>("Cube Mesh");

	// Set root component
	RootComponent = boxComp;
	cubeMesh->SetupAttachment(boxComp);
}

// Called when the game starts or when spawned
void ACubeDMIMod::BeginPlay()
{
	Super::BeginPlay();
	 
	// Set overlap trigger
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &ACubeDMIMod::onOverlapBegin);

	// Set materials
	if (baseMat)
	{
		dmiMat = UMaterialInstanceDynamic::Create(baseMat, this);
	}

	if (cubeMesh)
	{
		cubeMesh->SetMaterial(0, dmiMat);
	}
	
}

// Called every frame
void ACubeDMIMod::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACubeDMIMod::onOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AFP_GAM415_McGuffeyCharacter* OverlappedActor = Cast< AFP_GAM415_McGuffeyCharacter>(OtherActor);

	// If actor is overlapped
	if (OverlappedActor)
	{
		// Set random values
		float ranNumX = UKismetMathLibrary::RandomFloatInRange(0.1f, 1.f);
		float ranNumY = UKismetMathLibrary::RandomFloatInRange(0.1f, 1.f);
		float ranNumZ = UKismetMathLibrary::RandomFloatInRange(0.1f, 1.f);

		// Create random color and apply it to the materials
		FLinearColor randColor = FLinearColor(ranNumX, ranNumY, ranNumZ, 1.f);
		if (dmiMat)
		{
			dmiMat->SetVectorParameterValue("Color", randColor);
			dmiMat->SetScalarParameterValue("Darkness", ranNumX);

			// Check if colorP is valid
			if (colorP)
			{
				// Create new confetti component and set it to RandColor
				UNiagaraComponent* particleComp = UNiagaraFunctionLibrary::SpawnSystemAttached(colorP, OtherComp, NAME_None, FVector(0.f), FRotator(0.f), EAttachLocation::KeepRelativeOffset, true);
				particleComp->SetNiagaraVariableLinearColor(FString("RandColor"), randColor);
			}
		}
	}
}