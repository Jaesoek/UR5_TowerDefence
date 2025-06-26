// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/TDLogChannel.h"

DEFINE_LOG_CATEGORY(LogTD);

FString GetNetModeString(UObject* InObject)
{
	ENetRole NetRole = ROLE_None;

	if (InObject->IsA(AActor::StaticClass()))
	{
		NetRole = Cast<AActor>(InObject)->GetLocalRole();
	}
	else if (InObject->IsA(UActorComponent::StaticClass()))
	{
		UActorComponent* DesiredActorComponent = Cast<UActorComponent>(InObject);
		if (IsValid(DesiredActorComponent) && IsValid(DesiredActorComponent->GetOwner()))
		{
			NetRole = DesiredActorComponent->GetOwner()->GetLocalRole();
		}
	}

	switch (NetRole)
	{
	case ROLE_SimulatedProxy:
		return TEXT("[SimulatedProxy]");
	case ROLE_AutonomousProxy:
		return TEXT("[AutonomousProxy]");
	case ROLE_Authority:
		return TEXT("[Authority]");
	default:
		break;
	}

	return TEXT("[]");
}

FString GetRoleString(UObject* InObject)
{
	ENetMode NetMode = NM_MAX;

	if (InObject->IsA(AActor::StaticClass()))
	{
		NetMode = Cast<AActor>(InObject)->GetWorld()->GetNetMode();
	}
	else if (InObject->IsA(UActorComponent::StaticClass()))
	{
		UActorComponent* DesiredActorComponent = Cast<UActorComponent>(InObject);
		if (IsValid(DesiredActorComponent) && IsValid(DesiredActorComponent->GetOwner()))
		{
			NetMode = DesiredActorComponent->GetOwner()->GetWorld()->GetNetMode();
		}
	}

	switch (NetMode)
	{
	case NM_Standalone:
		return TEXT("[Standalone]");
	case NM_DedicatedServer:
		return TEXT("[DedicatedServer]");
	case NM_ListenServer:
		return TEXT("[ListenServe]");
	case NM_Client:
		return TEXT("[Client]");
	default:
		break;
	}

	return TEXT("[]");
}
