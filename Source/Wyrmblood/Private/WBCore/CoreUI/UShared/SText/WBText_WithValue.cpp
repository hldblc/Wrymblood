// © 2025 Hephaestus Studios. All rights reserved.


#include "WBCore/CoreUI/UShared/SText/WBText_WithValue.h"


UWBText_WithValue::UWBText_WithValue(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Name = FText::FromString("{Name}");
	StatValue = FText::FromString("{Value}");
}
