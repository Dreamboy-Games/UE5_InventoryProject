// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Inv_PlayerController.generated.h"

/**
 * 
 */

class UInv_HUDWidget;
class UInputAction;
class UInputMappingContext;

UCLASS()
class INVENTORY_API AInv_PlayerController : public APlayerController {
	GENERATED_BODY()
	
public:
	AInv_PlayerController();
	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
private:
	void PrimaryInteract();
	void CreateHudWidget();
	void TraceForItem();
	
	UPROPERTY(EditDefaultsOnly, Category="Inventory")
	TArray<TObjectPtr<UInputMappingContext>> DefaultIMCs;    // UE5.6 uses array of IMCs
	//TObjectPtr<UInputMappingContext> DefaultIMC;
	
	UPROPERTY(EditDefaultsOnly, Category="Inventory")
	TObjectPtr<UInputAction> PrimaryInteractionAction;
	
	UPROPERTY(EditDefaultsOnly, Category="Inventory")
	TSubclassOf<UInv_HUDWidget> HUDWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UInv_HUDWidget> HUDWidget;
	
	UPROPERTY(EditDefaultsOnly, Category="Inventory")
	double TraceLenght;
	
	UPROPERTY(EditDefaultsOnly, Category="Inventory")
	TEnumAsByte<ECollisionChannel> ItemTraceChannel; 
	
	// Line Trace Hit Actors
	TWeakObjectPtr<AActor> ThisActor;
	TWeakObjectPtr<AActor> LastActor;
};
