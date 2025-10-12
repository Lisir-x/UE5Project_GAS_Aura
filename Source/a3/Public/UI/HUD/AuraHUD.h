

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
class UOverlayWidgetController;
class UAuraUserWidget;
struct FWidgetControllerParams;

UCLASS()
class A3_API AAuraHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	//覆层控件
	UPROPERTY()
	TObjectPtr<UAuraUserWidget>  OverlayWidget;

	//获取覆层控件控制器
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);

	//初始化覆层
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

protected:

private:
	//覆层控件类
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass;

	//覆层控件控制器
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	//覆层控件控制器类
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
};
