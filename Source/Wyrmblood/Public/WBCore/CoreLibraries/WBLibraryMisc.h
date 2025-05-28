// WBLibraryMisc.h - Advanced Print System
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Components/Widget.h"
#include "Components/SlateWrapperTypes.h"
#include "Engine/Engine.h"
#include "Engine/Texture2D.h"
#include "Components/Image.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "WBLibraryMisc.generated.h"

// Enhanced Log Levels
UENUM(BlueprintType)
enum class EWBLogLevel : uint8
{
    Trace       UMETA(DisplayName = "Trace"),
    Debug       UMETA(DisplayName = "Debug"), 
    Info        UMETA(DisplayName = "Info"),
    Notice      UMETA(DisplayName = "Notice"),
    Warning     UMETA(DisplayName = "Warning"),
    Error       UMETA(DisplayName = "Error"),
    Critical    UMETA(DisplayName = "Critical"),
    Fatal       UMETA(DisplayName = "Fatal")
};

// Log Categories for filtering
UENUM(BlueprintType)
enum class EWBLogCategory : uint8
{
    General     UMETA(DisplayName = "General"),
    Gameplay    UMETA(DisplayName = "Gameplay"),
    UI          UMETA(DisplayName = "UI"),
    Network     UMETA(DisplayName = "Network"),
    Audio       UMETA(DisplayName = "Audio"),
    Animation   UMETA(DisplayName = "Animation"),
    Physics     UMETA(DisplayName = "Physics"),
    AI          UMETA(DisplayName = "AI"),
    Performance UMETA(DisplayName = "Performance"),
    Memory      UMETA(DisplayName = "Memory"),
    Custom1     UMETA(DisplayName = "Custom1"),
    Custom2     UMETA(DisplayName = "Custom2"),
    Custom3     UMETA(DisplayName = "Custom3")
};

// Advanced Print Settings
USTRUCT(BlueprintType)
struct WYRMBLOOD_API FWBPrintSettings
{
    GENERATED_BODY()

    FWBPrintSettings()
    {
        bPrintToScreen = true;
        bPrintToLog = true;
        bPrintToFile = false;
        Duration = 5.0f;
        bShowTimestamp = true;
        bShowCategory = true;
        bShowCallstack = false;
        bDevelopmentOnly = true;
        FontSize = 12;
        bAutoColor = true;
        CustomColor = FLinearColor::White;
        MinLogLevel = EWBLogLevel::Debug;
    }

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Output")
    bool bPrintToScreen;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Output")
    bool bPrintToLog;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Output")
    bool bPrintToFile;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display")
    float Duration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display")
    bool bShowTimestamp;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display")
    bool bShowCategory;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display")
    bool bShowCallstack;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Build Settings")
    bool bDevelopmentOnly;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display")
    int32 FontSize;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color")
    bool bAutoColor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color")
    FLinearColor CustomColor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Filtering")
    EWBLogLevel MinLogLevel;
};

UCLASS(blueprintable, BlueprintType, meta=(DisplayName="Advanced Misc Library"))
class WYRMBLOOD_API UWBLibraryMisc : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    // ===================================== Core Utility Functions ===================================== //
    UFUNCTION(BlueprintCallable, Category="MiscLibrary|Widgets")
    static void SetWidgetVisibility(UWidget* TargetWidget, bool bVisible);

	UFUNCTION(BlueprintCallable, Category="BFL Misc Widgets Sh")
	static void SetIsIconSoftObject(UImage* Target, TSoftObjectPtr<UTexture2D> Texture2D);

    // ===================================== Advanced Print System ===================================== //
    
    /** 
     * Advanced print function with full customization 
     */
    UFUNCTION(BlueprintCallable, Category="MiscLibrary|Debug|Advanced", 
              meta=(CallInEditor = "true", DevelopmentOnly = "true"))
    static void PrintAdvanced(
        const FString& Message,
        EWBLogLevel LogLevel = EWBLogLevel::Info,
        EWBLogCategory Category = EWBLogCategory::General,
        const FString& Tag = TEXT(""),
        const FWBPrintSettings& Settings = FWBPrintSettings(),
        bool bActive = true
    );

    /** Quick print functions with smart defaults */
    UFUNCTION(BlueprintCallable, Category="MiscLibrary|Debug|Quick", 
              meta=(CallInEditor = "true", DevelopmentOnly = "true"))
    static void PrintError(const FString& Message, const FString& Tag = TEXT(""), bool bActive = true);

    UFUNCTION(BlueprintCallable, Category="MiscLibrary|Debug|Quick", 
              meta=(CallInEditor = "true", DevelopmentOnly = "true"))
    static void PrintWarning(const FString& Message, const FString& Tag = TEXT(""), bool bActive = true);

    UFUNCTION(BlueprintCallable, Category="MiscLibrary|Debug|Quick", 
              meta=(CallInEditor = "true", DevelopmentOnly = "true"))
    static void PrintSuccess(const FString& Message, const FString& Tag = TEXT(""), bool bActive = true);

    UFUNCTION(BlueprintCallable, Category="MiscLibrary|Debug|Quick", 
              meta=(CallInEditor = "true", DevelopmentOnly = "true"))
    static void PrintToDo(const FString& Message, const FString& Tag = TEXT(""), bool bActive = true);

    UFUNCTION(BlueprintCallable, Category="MiscLibrary|Debug|Quick", 
              meta=(CallInEditor = "true", DevelopmentOnly = "true"))
    static void PrintNotice(const FString& Message, const FString& Tag = TEXT(""), bool bActive = true);

    /** Performance-aware printing */
    UFUNCTION(BlueprintCallable, Category="MiscLibrary|Debug|Performance", 
              meta=(CallInEditor = "true", DevelopmentOnly = "true"))
    static void PrintWithPerformanceWarning(const FString& Message, bool bActive = true);

    /** Network-aware printing for multiplayer debugging */
    UFUNCTION(BlueprintCallable, Category="MiscLibrary|Debug|Network", 
              meta=(CallInEditor = "true", DevelopmentOnly = "true"))
    static void PrintNetworkDebug(const FString& Message, bool bServerOnly = false, bool bClientOnly = false, bool bActive = true);

    // ===================================== Settings & Configuration ===================================== //
    
    /** Get/Set global print settings */
    UFUNCTION(BlueprintCallable, Category="MiscLibrary|Debug|Settings")
    static FWBPrintSettings GetGlobalPrintSettings();

    UFUNCTION(BlueprintCallable, Category="MiscLibrary|Debug|Settings")
    static void SetGlobalPrintSettings(const FWBPrintSettings& NewSettings);

    /** Enable/Disable categories */
    UFUNCTION(BlueprintCallable, Category="MiscLibrary|Debug|Settings")
    static void SetCategoryEnabled(EWBLogCategory Category, bool bEnabled);

    UFUNCTION(BlueprintCallable, Category="MiscLibrary|Debug|Settings")
    static bool IsCategoryEnabled(EWBLogCategory Category);

    // ===================================== Utility Functions ===================================== //
    
    /** Format message with timestamp, category, etc. */
    static FString FormatMessage(const FString& Message, EWBLogLevel InLogLevel, EWBLogCategory Category, const FString& Tag, const FWBPrintSettings& Settings);
    
    /** Get color for log level */
    static FLinearColor GetColorForLogLevel(EWBLogLevel InLogLevel);
    
    /** Get prefix for log level */
    static FString GetPrefixForLogLevel(EWBLogLevel InLogLevel);
    
    /** Get current timestamp string */
    static FString GetTimestamp();

    /** Get calling function information */
    static FString GetCallerInfo();

private:
    // Global settings
    static FWBPrintSettings GlobalSettings;
    static TMap<EWBLogCategory, bool> CategoryEnabledMap;
    
    // Rate limiting for performance
    static TMap<FString, double> LastPrintTimeMap;
    static constexpr double MinTimeBetweenSamePrints = 0.1; // 100ms
};

// ===================================== Convenience Macros ===================================== //

#if !UE_BUILD_SHIPPING
    #define WB_PRINT_ERROR(Message, ...) UWBLibraryMisc::PrintError(FString::Printf(TEXT(Message), ##__VA_ARGS__), TEXT(__FUNCTION__))
    #define WB_PRINT_WARNING(Message, ...) UWBLibraryMisc::PrintWarning(FString::Printf(TEXT(Message), ##__VA_ARGS__), TEXT(__FUNCTION__))
    #define WB_PRINT_SUCCESS(Message, ...) UWBLibraryMisc::PrintSuccess(FString::Printf(TEXT(Message), ##__VA_ARGS__), TEXT(__FUNCTION__))
    #define WB_PRINT_TODO(Message, ...) UWBLibraryMisc::PrintToDo(FString::Printf(TEXT(Message), ##__VA_ARGS__), TEXT(__FUNCTION__))
    
    // Conditional printing
    #define WB_PRINT_ERROR_IF(Condition, Message, ...) if(Condition) { WB_PRINT_ERROR(Message, ##__VA_ARGS__); }
    #define WB_PRINT_WARNING_IF(Condition, Message, ...) if(Condition) { WB_PRINT_WARNING(Message, ##__VA_ARGS__); }
    
    // Category-specific printing
    #define WB_PRINT_GAMEPLAY(Message, ...) UWBLibraryMisc::PrintAdvanced(FString::Printf(TEXT(Message), ##__VA_ARGS__), EWBLogLevel::Info, EWBLogCategory::Gameplay, TEXT(__FUNCTION__))
    #define WB_PRINT_UI(Message, ...) UWBLibraryMisc::PrintAdvanced(FString::Printf(TEXT(Message), ##__VA_ARGS__), EWBLogLevel::Info, EWBLogCategory::UI, TEXT(__FUNCTION__))
    #define WB_PRINT_NETWORK(Message, ...) UWBLibraryMisc::PrintAdvanced(FString::Printf(TEXT(Message), ##__VA_ARGS__), EWBLogLevel::Info, EWBLogCategory::Network, TEXT(__FUNCTION__))
#else
    #define WB_PRINT_ERROR(Message, ...)
    #define WB_PRINT_WARNING(Message, ...)
    #define WB_PRINT_SUCCESS(Message, ...)
    #define WB_PRINT_TODO(Message, ...)
    #define WB_PRINT_ERROR_IF(Condition, Message, ...)
    #define WB_PRINT_WARNING_IF(Condition, Message, ...)
    #define WB_PRINT_GAMEPLAY(Message, ...)
    #define WB_PRINT_UI(Message, ...)
    #define WB_PRINT_NETWORK(Message, ...)
#endif