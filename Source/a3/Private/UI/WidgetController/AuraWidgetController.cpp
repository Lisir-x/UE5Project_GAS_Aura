


#include "UI/WidgetController/AuraWidgetController.h"

//设置控件控制器参数蓝图函数
void UAuraWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void UAuraWidgetController::BroadcastInitialValues()
{
}

void UAuraWidgetController::BindCallbacksToDependencies()
{
}
