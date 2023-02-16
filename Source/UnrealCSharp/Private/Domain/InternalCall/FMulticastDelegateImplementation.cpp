﻿#include "Domain/InternalCall/FMulticastDelegateImplementation.h"
#include "Binding/Class/FBindingClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Delegate/FMulticastDelegateHelper.h"
#include "Macro/NamespaceMacro.h"

struct FRegisterMulticastDelegate
{
	FRegisterMulticastDelegate()
	{
		FBindingClassBuilder(TEXT("MulticastDelegate"), NAMESPACE_DELEGATE)
			.Function("IsBound",
			          static_cast<void*>(FMulticastDelegateImplementation::MulticastDelegate_IsBoundImplementation))
			.Function("Contains",
			          static_cast<void*>(FMulticastDelegateImplementation::MulticastDelegate_ContainsImplementation))
			.Function("Add",
			          static_cast<void*>(FMulticastDelegateImplementation::MulticastDelegate_AddImplementation))
			.Function("AddUnique",
			          static_cast<void*>(FMulticastDelegateImplementation::MulticastDelegate_AddUniqueImplementation))
			.Function("Remove",
			          static_cast<void*>(FMulticastDelegateImplementation::MulticastDelegate_RemoveImplementation))
			.Function("RemoveAll",
			          static_cast<void*>(FMulticastDelegateImplementation::MulticastDelegate_RemoveAllImplementation))
			.Function("Clear",
			          static_cast<void*>(FMulticastDelegateImplementation::MulticastDelegate_ClearImplementation))
			.Function("Broadcast",
			          static_cast<void*>(FMulticastDelegateImplementation::MulticastDelegate_BroadcastImplementation))
			.Register();
	}
};

static FRegisterMulticastDelegate RegisterMulticastDelegate;

bool FMulticastDelegateImplementation::MulticastDelegate_IsBoundImplementation(const void* InAddress)
{
	if (const auto MulticastDelegateHelper = FCSharpEnvironment::GetEnvironment()->GetDelegate<
		FMulticastDelegateHelper>(InAddress))
	{
		return MulticastDelegateHelper->IsBound();
	}

	return false;
}

bool FMulticastDelegateImplementation::MulticastDelegate_ContainsImplementation(
	const void* InAddress, MonoObject* InDelegate)
{
	if (const auto MulticastDelegateHelper = FCSharpEnvironment::GetEnvironment()->GetDelegate<
		FMulticastDelegateHelper>(InAddress))
	{
		return MulticastDelegateHelper->Contains(InDelegate);
	}

	return false;
}

void FMulticastDelegateImplementation::MulticastDelegate_AddImplementation(
	const void* InAddress, MonoObject* InDelegate)
{
	if (const auto MulticastDelegateHelper = FCSharpEnvironment::GetEnvironment()->GetDelegate<
		FMulticastDelegateHelper>(InAddress))
	{
		return MulticastDelegateHelper->Add(InDelegate);
	}
}

void FMulticastDelegateImplementation::MulticastDelegate_AddUniqueImplementation(
	const void* InAddress, MonoObject* InDelegate)
{
	if (const auto MulticastDelegateHelper = FCSharpEnvironment::GetEnvironment()->GetDelegate<
		FMulticastDelegateHelper>(InAddress))
	{
		return MulticastDelegateHelper->AddUnique(InDelegate);
	}
}

void FMulticastDelegateImplementation::MulticastDelegate_RemoveImplementation(
	const void* InAddress, MonoObject* InDelegate)
{
	if (const auto MulticastDelegateHelper = FCSharpEnvironment::GetEnvironment()->GetDelegate<
		FMulticastDelegateHelper>(InAddress))
	{
		return MulticastDelegateHelper->Remove(InDelegate);
	}
}

void FMulticastDelegateImplementation::MulticastDelegate_RemoveAllImplementation(
	const void* InAddress, MonoObject* InMonoObject)
{
	if (const auto MulticastDelegateHelper = FCSharpEnvironment::GetEnvironment()->GetDelegate<
		FMulticastDelegateHelper>(InAddress))
	{
		return MulticastDelegateHelper->RemoveAll(InMonoObject);
	}
}

void FMulticastDelegateImplementation::MulticastDelegate_ClearImplementation(const void* InAddress)
{
	if (const auto MulticastDelegateHelper = FCSharpEnvironment::GetEnvironment()->GetDelegate<
		FMulticastDelegateHelper>(InAddress))
	{
		return MulticastDelegateHelper->Clear();
	}
}

void FMulticastDelegateImplementation::MulticastDelegate_BroadcastImplementation(
	const void* InAddress, MonoObject** OutValue, MonoArray* InValue)
{
	if (const auto MulticastDelegateHelper = FCSharpEnvironment::GetEnvironment()->GetDelegate<
		FMulticastDelegateHelper>(InAddress))
	{
		return MulticastDelegateHelper->Broadcast(OutValue, InValue);
	}
}
