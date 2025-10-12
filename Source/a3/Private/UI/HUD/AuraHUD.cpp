


#include "UI/HUD/AuraHUD.h"

#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

//获取覆层控件控制器
UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	//如果覆层控件控制器尚未初始化
	if (OverlayWidgetController == nullptr)
	{
		//使用指定的类创建一个新的覆层控件控制器实例
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		//设置覆层控件控制器参数
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		//控件控制器绑定回调到依赖项
		OverlayWidgetController->BindCallbacksToDependencies();

		//返回新创建的覆层控件控制器
		return OverlayWidgetController;
	}
	//如果覆层控件控制器已经存在，直接返回它
	return OverlayWidgetController;
}

//初始化覆层 
void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	//确保覆层用户控件类和覆层控件控制器类已设置
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized, please fill out BP_AuraHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class uninitialized, please fill out BP_AuraHUD"));

	//创建用户控件并转换成Aura用户控件作为覆层
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UAuraUserWidget>(Widget);

	//创建覆层控件控制器参数
	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	//获取或创建覆层控件控制器
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	//将覆层控件控制器设置给覆层控件
	OverlayWidget->SetWidgetController(WidgetController);
	//控件控制器广播初始值
	WidgetController->BroadcastInitialValues();
	//将用户控件添加到视口
	Widget->AddToViewport();
}
