// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FP_GAM415_McGuffeyProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UNiagaraSystem;

UCLASS(config=Game)
class AFP_GAM415_McGuffeyProjectile : public AActor
{
	GENERATED_BODY()

	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	USphereComponent* CollisionComp;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

	// Mesh and material
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* ballMesh;

	UPROPERTY(EditAnywhere)
		UMaterial* baseMat;

	// Random color and projectile materials
	UPROPERTY()
		FLinearColor randColor;

	UPROPERTY(EditAnywhere)
		UMaterialInterface* projMat;

	UPROPERTY()
		UMaterialInstanceDynamic* dmiMat;

	// Create projectile particle color
	UPROPERTY(EditAnywhere)
		UNiagaraSystem* colorP;

public:
	AFP_GAM415_McGuffeyProjectile();

protected:
	virtual void BeginPlay();

public:
	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Returns CollisionComp subobject **/
	USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** Returns ProjectileMovement subobject **/
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
};

