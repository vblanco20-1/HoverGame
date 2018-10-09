// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(LogGame, Log, All);


#define NETMODE_WORLD (((GEngine == nullptr) || (GetWorld() == nullptr)) ? TEXT("") \
        : (GEngine->GetNetMode(GetWorld()) == NM_Client) ? TEXT("[Client] ") \
        : (GEngine->GetNetMode(GetWorld()) == NM_ListenServer) ? TEXT("[ListenServer] ") \
        : (GEngine->GetNetMode(GetWorld()) == NM_DedicatedServer) ? TEXT("[DedicatedServer] ") \
        : TEXT("[Standalone] "))

//trace fix for PS4 clang compiler, it doesnt support the function in a macro
#if PLATFORM_PS4
#define FUNC_NAME TEXT(":")
#else
#if _MSC_VER
#define FUNC_NAME    TEXT(__FUNCTION__)
#else // FIXME - GCC?
#define FUNC_NAME    TEXT("_func_")
#endif
#endif



#define TRACE(Format, ...) \
{ \
    SET_WARN_COLOR(COLOR_CYAN);\
    const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
    if (Msg == "") \
    { \
        UE_LOG(LogGame, Log, TEXT("%s%s() : %s"), NETMODE_WORLD, FUNC_NAME, *GetNameSafe(this));\
    } \
    else \
    { \
        UE_LOG(LogGame, Log, TEXT("%s%s() : %s"), NETMODE_WORLD, FUNC_NAME, *Msg);\
    } \
    CLEAR_WARN_COLOR();\
}

#define TRACESTATIC(Format, ...) \
{ \
    SET_WARN_COLOR(COLOR_CYAN);\
    const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
    UE_LOG(LogGame, Log, TEXT("%s() : %s"), FUNC_NAME, *Msg);\
    CLEAR_WARN_COLOR();\
}

#define TRACEWARN(Format, ...) \
{ \
    SET_WARN_COLOR( COLOR_YELLOW );\
    const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
    UE_LOG(LogGame, Log, TEXT("**WARNING** %s%s() : %s"), NETMODE_WORLD, FUNC_NAME, *Msg);\
    CLEAR_WARN_COLOR();\
}

#define TRACEERROR(Format, ...) \
{ \
    SET_WARN_COLOR( COLOR_RED );\
    const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
    UE_LOG(LogGame, Log, TEXT("**ERROR** %s%s() : %s"), NETMODE_WORLD, FUNC_NAME, *Msg);\
    CLEAR_WARN_COLOR();\
}

#define SCREENDEBUG(Format, ...) \
{ \
    const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
    if (Msg == "") \
    { \
        TCHAR StdMsg[MAX_SPRINTF] = TEXT(""); \
        FCString::Sprintf(StdMsg, TEXT("%s%s() : %s"), NETMODE_WORLD, FUNC_NAME, *GetNameSafe(this)); \
        GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::White, StdMsg); \
    } \
    else \
    { \
        GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::White, Msg); \
    } \
}