// Fill out your copyright notice in the Description page of Project Settings.


#include "PerlinProc.h"
#include "ProceduralMeshComponent.h"
#include "KismetProceduralMeshLibrary.h"

// Sets default values  
APerlinProc::APerlinProc()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setup procedural mesh
	ProcMesh = CreateDefaultSubobject<UProceduralMeshComponent>("Procedural Mesh");
	ProcMesh->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void APerlinProc::BeginPlay()
{
	Super::BeginPlay();
	
	// Call functions and create mesh section
	CreateVertices();
	CreateTriangles();
	ProcMesh->CreateMeshSection(sectionID, Vertices, Triangles, Normals, UV0, UpVertexColors, TArray<FProcMeshTangent>(), true);
	ProcMesh->SetMaterial(0, Mat);
}

// Called every frame
void APerlinProc::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APerlinProc::AlterMesh(FVector impactPoint)
{
	// Cycle through vertices
	for (int i = 0; i < Vertices.Num(); i++)
	{
		// Create temporary vector relative to actor location
		FVector tempVector = impactPoint - this->GetActorLocation();

		// Check if our vertice size is less than the given radius
		if (FVector(Vertices[i] - tempVector).Size() < radius)
		{
			// Subtract depth to vertices and update mesh section
			Vertices[i] = Vertices[i] - Depth;
			ProcMesh->UpdateMeshSection(sectionID, Vertices, Normals, UV0, UpVertexColors, TArray<FProcMeshTangent>());
		}
	}
}

void APerlinProc::CreateVertices()
{
	// Create X and Y values and loop through them
	for (int X = 0; X <= XSize; X++)
	{
		for (int Y = 0; Y <= YSize; Y++)
		{
			// Create Z value with Perlin Noise and add vertices / UV indexes
			float Z = FMath::PerlinNoise2D(FVector2D(X * NoiseScale + 0.1, Y * NoiseScale + 0.1)) * ZMultiplier;
			GEngine->AddOnScreenDebugMessage(-1, 999.0f, FColor::Yellow, FString::Printf(TEXT("Z %f"), Z)); // Debug
			Vertices.Add(FVector(X * Scale, Y * Scale, Z));
			UV0.Add(FVector2D(X * UVScale, Y * UVScale));
		}
	}
}

void APerlinProc::CreateTriangles()
{
	// Create vertex variable, add 1 to it after each loop
	int Vertex = 0;

	for (int X = 0; X < XSize; X++)
	{
		for (int Y = 0; Y < YSize; Y++)
		{
			// Add triangle indexes
			Triangles.Add(Vertex);
			Triangles.Add(Vertex + 1);
			Triangles.Add(Vertex + YSize + 1);
			Triangles.Add(Vertex + 1);
			Triangles.Add(Vertex + YSize + 2);
			Triangles.Add(Vertex + YSize + 1);

			Vertex++;
		}

		Vertex++;
	}
}

