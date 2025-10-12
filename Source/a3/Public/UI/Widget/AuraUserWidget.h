

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class A3_API UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//设置控件控制器函数
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

	//控件控制器
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;
	
protected:
	//控件控制器设置事件
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
};
