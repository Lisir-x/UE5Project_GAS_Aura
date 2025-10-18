

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "UObject/NoExportTypes.h"
#include "AuraWidgetController.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;

//控件控制器参数结构体
USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()

	//默认构造和带当前参数的构造函数
	FWidgetControllerParams() {}
	FWidgetControllerParams(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
	: PlayerController(PC), PlayerState(PS), AbilitySystemComponent(ASC), AttributeSet(AS) {}

	//玩家控制器
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController = nullptr;

	//玩家状态
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerState> PlayerState = nullptr;

	//能力系统组件
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

	//属性集
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;
};

UCLASS()
class A3_API UAuraWidgetController : public UObject
{
	GENERATED_BODY()

public:
	//设置控件控制器参数蓝图函数
	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParams (const FWidgetControllerParams& WCParams);
	
	//广播初始值
	UFUNCTION(BlueprintCallable)
	virtual void BroadcastInitialValues();
	
	//绑定回调到依赖项
	virtual void BindCallbacksToDependencies();
	
protected:
	//玩家控制器
	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<APlayerController> PlayerController;

	//玩家状态
	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<APlayerState> PlayerState;

	//能力系统组件
	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	//属性集
	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<UAttributeSet> AttributeSet;
};
