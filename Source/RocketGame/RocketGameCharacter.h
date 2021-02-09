// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RocketGameCharacter.generated.h"

UCLASS(config=Game)
class ARocketGameCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void LaunchRocket();

	void LaunchRocketReleased();

	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

	bool bTapActive = false;

	UPROPERTY()
	FTimerHandle TapTimerHandle;

	void OnTapTimerTick();

public:
	ARocketGameCharacter();

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	int32 StartingRockets = 3;
	
	int32 Rockets;
	
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	int32 StartingHealth = 3;

	int32 Health;

	UPROPERTY(Category = "Config", EditAnywhere, BlueprintReadWrite)
	float ImpulseZ = 2000.f;

	UPROPERTY(Category = "Config", EditAnywhere, BlueprintReadWrite)
	float ImpulseY = -1000.f;

	UPROPERTY(Category = "Config", EditAnywhere, BlueprintReadWrite)
	float CorrectZ = -20.f;

	UPROPERTY(Category = "Config", EditAnywhere, BlueprintReadWrite)
	float CorrectY = -20.f;

	UPROPERTY(Category = "Config", EditAnywhere, BlueprintReadWrite)
	float CorrectionTickDuration = .01f;

	UFUNCTION(BlueprintImplementableEvent, Category = "RocketGameCharacter")
	void OnCrash();

	void Die();

	virtual void Landed(const FHitResult& Hit) override;
};
