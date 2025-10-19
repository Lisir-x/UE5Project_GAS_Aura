

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

class UAttributeInfo;
struct FAuraAttributeInfo;

//创建动态多播委托(签名)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAuraAttributeInfoSignature, const FAuraAttributeInfo&, Info);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class A3_API UAttributeMenuWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
	
public:
	//广播初始值
	virtual void BroadcastInitialValues() override;
	//绑定回调到依赖项
	virtual void BindCallbacksToDependencies() override;

	/*----------动态多播委托----------*/
	//属性信息委托
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FAuraAttributeInfoSignature AttributeInfoDelegate;
	/*------------------------------*/

protected:
	//属性信息
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAttributeInfo> AttributeInfo;
	
private:
	//广播属性信息
	void BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const;
};
