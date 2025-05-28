// WBLibraryMisc.cpp - Advanced Print System Implementation
#include "WBCore/CoreLibraries/WBLibraryMisc.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "HAL/PlatformFilemanager.h"
#include "Misc/FileHelper.h"
#include "Misc/DateTime.h"
#include "Stats/Stats.h"

// Initialize static members
FWBPrintSettings UWBLibraryMisc::GlobalSettings;
TMap<EWBLogCategory, bool> UWBLibraryMisc::CategoryEnabledMap;
TMap<FString, double> UWBLibraryMisc::LastPrintTimeMap;

void UWBLibraryMisc::SetWidgetVisibility(UWidget* TargetWidget, bool bVisible)
{
    if (!TargetWidget)
    {
        return;
    }

    ESlateVisibility NewVisibility = bVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
    TargetWidget->SetVisibility(NewVisibility);
}

void UWBLibraryMisc::SetIsIconSoftObject(UImage* Target, TSoftObjectPtr<UTexture2D> Texture2D)
{
    // Local variable TextureParamName
    FName TextureParamName = FName("T_UI_Empty");
    
    // Get Dynamic Material from Target
    UMaterialInstanceDynamic* DynamicMaterial = Target->GetDynamicMaterial();
    
    // Is Valid Soft Object Reference (Branch condition)
    bool bIsValidSoftObjectReference = !Texture2D.IsNull();
    
    // Branch
    if (bIsValidSoftObjectReference)
    {
        // True branch: Load Asset Blocking
        UObject* LoadedAsset = Texture2D.LoadSynchronous();
        
        // Cast to Texture2D
        UTexture2D* CastTexture = Cast<UTexture2D>(LoadedAsset);
        
        // Set Texture Parameter Value
        DynamicMaterial->SetTextureParameterValue(TextureParamName, CastTexture);
    }
    else
    {
        // False branch: Print Error
        PrintError(TEXT("Cant cast Icon Soft Object Texture 2D"), TEXT(""), true);
    }
}



// ===================================== Advanced Print System ===================================== //

void UWBLibraryMisc::PrintAdvanced(const FString& Message, EWBLogLevel InLogLevel, EWBLogCategory Category, 
                                   const FString& Tag, const FWBPrintSettings& Settings, bool bActive)
{
    // Early exit conditions
    if (!bActive) return;
    
#if UE_BUILD_SHIPPING
    if (Settings.bDevelopmentOnly) return;
#endif

    // Check if category is enabled
    if (!IsCategoryEnabled(Category)) return;
    
    // Check log level filtering
    if (InLogLevel < Settings.MinLogLevel) return;

    // Rate limiting to prevent spam
    FString RateLimitKey = Message + Tag;
    double CurrentTime = FPlatformTime::Seconds();
    if (LastPrintTimeMap.Contains(RateLimitKey))
    {
        if (CurrentTime - LastPrintTimeMap[RateLimitKey] < MinTimeBetweenSamePrints)
        {
            return; // Skip this print to prevent spam
        }
    }
    LastPrintTimeMap.Add(RateLimitKey, CurrentTime);

    // Format the message
    FString FormattedMessage = FormatMessage(Message, InLogLevel, Category, Tag, Settings);
    
    // Get color
    FLinearColor PrintColor = Settings.bAutoColor ? GetColorForLogLevel(InLogLevel) : Settings.CustomColor;

    // Print to screen
    if (Settings.bPrintToScreen && GEngine)
    {
        UWorld* World = nullptr;
        if (GEngine->GetWorldContexts().Num() > 0)
        {
            World = GEngine->GetWorldContexts()[0].World();
        }

        UKismetSystemLibrary::PrintString(
            World,
            FormattedMessage,
            true,                    // Print to Screen
            Settings.bPrintToLog,    // Print to Log
            PrintColor,              // Text Color
            Settings.Duration        // Duration
        );
    }

    // Print to UE Log
    if (Settings.bPrintToLog)
    {
        switch (InLogLevel)
        {
            case EWBLogLevel::Trace:
            case EWBLogLevel::Debug:
                UE_LOG(LogTemp, Log, TEXT("%s"), *FormattedMessage);
                break;
            case EWBLogLevel::Info:
            case EWBLogLevel::Notice:
                UE_LOG(LogTemp, Display, TEXT("%s"), *FormattedMessage);
                break;
            case EWBLogLevel::Warning:
                UE_LOG(LogTemp, Warning, TEXT("%s"), *FormattedMessage);
                break;
            case EWBLogLevel::Error:
            case EWBLogLevel::Critical:
            case EWBLogLevel::Fatal:
                UE_LOG(LogTemp, Error, TEXT("%s"), *FormattedMessage);
                break;
        }
    }

    // Print to file
    if (Settings.bPrintToFile)
    {
        FString LogFilePath = FPaths::ProjectLogDir() / TEXT("WyrmbloodDebug.log");
        FString FileMessage = FString::Printf(TEXT("[%s] %s\n"), *GetTimestamp(), *FormattedMessage);
        FFileHelper::SaveStringToFile(FileMessage, *LogFilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), FILEWRITE_Append);
    }
}

// Quick print functions
void UWBLibraryMisc::PrintError(const FString& Message, const FString& Tag, bool bActive)
{
    FWBPrintSettings Settings = GetGlobalPrintSettings();
    Settings.Duration = 8.0f; // Errors stay longer
    PrintAdvanced(Message, EWBLogLevel::Error, EWBLogCategory::General, Tag, Settings, bActive);
}

void UWBLibraryMisc::PrintWarning(const FString& Message, const FString& Tag, bool bActive)
{
    FWBPrintSettings Settings = GetGlobalPrintSettings();
    Settings.Duration = 6.0f;
    PrintAdvanced(Message, EWBLogLevel::Warning, EWBLogCategory::General, Tag, Settings, bActive);
}

void UWBLibraryMisc::PrintSuccess(const FString& Message, const FString& Tag, bool bActive)
{
    FWBPrintSettings Settings = GetGlobalPrintSettings();
    Settings.CustomColor = FLinearColor::Green;
    Settings.bAutoColor = false;
    PrintAdvanced(Message, EWBLogLevel::Info, EWBLogCategory::General, Tag, Settings, bActive);
}

void UWBLibraryMisc::PrintToDo(const FString& Message, const FString& Tag, bool bActive)
{
    FWBPrintSettings Settings = GetGlobalPrintSettings();
    Settings.Duration = 10.0f; // TODOs stay longer
    PrintAdvanced(FString::Printf(TEXT("TODO: %s"), *Message), EWBLogLevel::Notice, EWBLogCategory::General, Tag, Settings, bActive);
}

void UWBLibraryMisc::PrintNotice(const FString& Message, const FString& Tag, bool bActive)
{
    PrintAdvanced(Message, EWBLogLevel::Notice, EWBLogCategory::General, Tag, GetGlobalPrintSettings(), bActive);
}

void UWBLibraryMisc::PrintWithPerformanceWarning(const FString& Message, bool bActive)
{
    if (!bActive) return;

    // Get current FPS
    float CurrentFPS = 1.0f / FApp::GetDeltaTime();
    FString PerformanceInfo = FString::Printf(TEXT("[FPS: %.1f] %s"), CurrentFPS, *Message);
    
    // Warn if FPS is low
    EWBLogLevel CurrentLogLevel = (CurrentFPS < 30.0f) ? EWBLogLevel::Warning : EWBLogLevel::Info;
    
    PrintAdvanced(PerformanceInfo, CurrentLogLevel, EWBLogCategory::Performance, TEXT("Performance"), GetGlobalPrintSettings(), true);
}

void UWBLibraryMisc::PrintNetworkDebug(const FString& Message, bool bServerOnly, bool bClientOnly, bool bActive)
{
    if (!bActive) return;

    UWorld* World = nullptr;
    if (GEngine && GEngine->GetWorldContexts().Num() > 0)
    {
        World = GEngine->GetWorldContexts()[0].World();
    }

    if (!World) return;

    // Check network role restrictions
    bool bShouldPrint = true;
    if (bServerOnly && World->GetNetMode() != NM_DedicatedServer && World->GetNetMode() != NM_ListenServer)
    {
        bShouldPrint = false;
    }
    if (bClientOnly && World->GetNetMode() == NM_DedicatedServer)
    {
        bShouldPrint = false;
    }

    if (bShouldPrint)
    {
        FString NetworkInfo = World->GetNetMode() == NM_DedicatedServer ? TEXT("[SERVER]") : 
                             World->GetNetMode() == NM_ListenServer ? TEXT("[LISTEN]") : TEXT("[CLIENT]");
        FString FullMessage = FString::Printf(TEXT("%s %s"), *NetworkInfo, *Message);
        
        PrintAdvanced(FullMessage, EWBLogLevel::Info, EWBLogCategory::Network, TEXT("Network"), GetGlobalPrintSettings(), true);
    }
}

// ===================================== Settings & Configuration ===================================== //

FWBPrintSettings UWBLibraryMisc::GetGlobalPrintSettings()
{
    return GlobalSettings;
}

void UWBLibraryMisc::SetGlobalPrintSettings(const FWBPrintSettings& NewSettings)
{
    GlobalSettings = NewSettings;
}

void UWBLibraryMisc::SetCategoryEnabled(EWBLogCategory Category, bool bEnabled)
{
    CategoryEnabledMap.Add(Category, bEnabled);
}

bool UWBLibraryMisc::IsCategoryEnabled(EWBLogCategory Category)
{
    // Default to enabled if not found
    return CategoryEnabledMap.FindRef(Category) != false;
}

// ===================================== Utility Functions ===================================== //

FString UWBLibraryMisc::FormatMessage(const FString& Message, EWBLogLevel InLogLevel, EWBLogCategory Category, 
                                     const FString& Tag, const FWBPrintSettings& Settings)
{
    FString FormattedMessage;

    // Add timestamp
    if (Settings.bShowTimestamp)
    {
        FormattedMessage += FString::Printf(TEXT("[%s] "), *GetTimestamp());
    }

    // Add log level prefix
    FormattedMessage += GetPrefixForLogLevel(InLogLevel);

    // Add category
    if (Settings.bShowCategory)
    {
        FString CategoryName = UEnum::GetValueAsString(Category);
        CategoryName = CategoryName.Replace(TEXT("EWBLogCategory::"), TEXT(""));
        FormattedMessage += FString::Printf(TEXT("[%s] "), *CategoryName);
    }

    // Add tag if provided
    if (!Tag.IsEmpty())
    {
        FormattedMessage += FString::Printf(TEXT("[%s] "), *Tag);
    }

    // Add the actual message
    FormattedMessage += Message;

    // Add callstack if requested
    if (Settings.bShowCallstack && (InLogLevel == EWBLogLevel::Error || InLogLevel == EWBLogLevel::Critical || InLogLevel == EWBLogLevel::Fatal))
    {
        FormattedMessage += TEXT("\nCallstack: ") + GetCallerInfo();
    }

    return FormattedMessage;
}

FLinearColor UWBLibraryMisc::GetColorForLogLevel(EWBLogLevel InLogLevel)
{
    switch (InLogLevel)
    {
        case EWBLogLevel::Trace:     return FLinearColor::Gray;
        case EWBLogLevel::Debug:     return FLinearColor::White;
        case EWBLogLevel::Info:      return FLinearColor::Blue;
        case EWBLogLevel::Notice:    return FLinearColor(0.0f, 0.8f, 1.0f); // Light Blue
        case EWBLogLevel::Warning:   return FLinearColor::Yellow;
        case EWBLogLevel::Error:     return FLinearColor::Red;
        case EWBLogLevel::Critical:  return FLinearColor(1.0f, 0.2f, 0.0f); // Dark Red
        case EWBLogLevel::Fatal:     return FLinearColor(0.8f, 0.0f, 0.8f); // Magenta
        default:                     return FLinearColor::White;
    }
}

FString UWBLibraryMisc::GetPrefixForLogLevel(EWBLogLevel InLogLevel)
{
    switch (InLogLevel)
    {
        case EWBLogLevel::Trace:     return TEXT("[TRACE] ");
        case EWBLogLevel::Debug:     return TEXT("[DEBUG] ");
        case EWBLogLevel::Info:      return TEXT("[INFO] ");
        case EWBLogLevel::Notice:    return TEXT("[NOTICE] ");
        case EWBLogLevel::Warning:   return TEXT("[WARNING] ");
        case EWBLogLevel::Error:     return TEXT("[ERROR] ");
        case EWBLogLevel::Critical:  return TEXT("[CRITICAL] ");
        case EWBLogLevel::Fatal:     return TEXT("[FATAL] ");
        default:                     return TEXT("[UNKNOWN] ");
    }
}

FString UWBLibraryMisc::GetTimestamp()
{
    return FDateTime::Now().ToString(TEXT("%H:%M:%S.%f"));
}

FString UWBLibraryMisc::GetCallerInfo()
{
    // This is a simplified version - for full callstack you'd need platform-specific code
    return TEXT("(Callstack information requires platform-specific implementation)");
}