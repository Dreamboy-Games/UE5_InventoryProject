// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inv_InventoryComponent.generated.h"

class UInv_InventoryItem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInventoryitemChange, UInv_InventoryItem*, Item);

class UInv_InventoryBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class INVENTORY_API UInv_InventoryComponent : public UActorComponent {
	GENERATED_BODY()

public:
	UInv_InventoryComponent();
	
	void ToggleInventoryMenu();
	
	FInventoryitemChange OnItemAdded;
	FInventoryitemChange OnItemRemoved;

protected:
	virtual void BeginPlay() override;

private:
	void ConstructInventory();
	
	TWeakObjectPtr<APlayerController> OwningController;
	
	UPROPERTY(EditAnywhere, Category="Inventory")
	TSubclassOf<UInv_InventoryBase> InventoryMenuClass;
	
	UPROPERTY()
	TObjectPtr<UInv_InventoryBase> InventoryMenu;
	
	bool bInventoryMenuOpen;
	void OpenInventoryMenu();
	void CloseInventoryMenu();
};
