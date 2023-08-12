﻿#include "Registry/FBindingRegistry.h"

FBindingRegistry::FBindingRegistry()
{
	Initialize();
}

FBindingRegistry::~FBindingRegistry()
{
	Deinitialize();
}

void FBindingRegistry::Initialize()
{
}

void FBindingRegistry::Deinitialize()
{
	for (auto& Pair : GarbageCollectionHandle2BindingAddress.Get())
	{
		FGarbageCollectionHandle::Free(Pair.Key);

		if (Pair.Value.bNeedFree)
		{
			FMemory::Free(Pair.Value.Address);

			Pair.Value.Address = nullptr;
		}
	}

	GarbageCollectionHandle2BindingAddress.Empty();

	BindingAddress2GarbageCollectionHandle.Empty();

	MonoObject2GarbageCollectionHandleMap.Empty();
}

MonoObject* FBindingRegistry::GetObject(const void* InObject)
{
	const auto FoundGarbageCollectionHandle = BindingAddress2GarbageCollectionHandle.Find({
		const_cast<void*>(InObject)
	});

	return FoundGarbageCollectionHandle != nullptr ? static_cast<MonoObject*>(*FoundGarbageCollectionHandle) : nullptr;
}

void* FBindingRegistry::GetObject(const FGarbageCollectionHandle& InGarbageCollectionHandle)
{
	const auto FoundStructAddress = GarbageCollectionHandle2BindingAddress.Find(InGarbageCollectionHandle);

	return FoundStructAddress != nullptr ? FoundStructAddress->Address : nullptr;
}

bool FBindingRegistry::AddReference(const void* InObject, MonoObject* InMonoObject, bool bNeedFree)
{
	const auto GarbageCollectionHandle = FGarbageCollectionHandle::NewWeakRef(InMonoObject, true);

	BindingAddress2GarbageCollectionHandle.Add(FBindingAddress{const_cast<void*>(InObject), bNeedFree},
	                                           GarbageCollectionHandle);

	GarbageCollectionHandle2BindingAddress.Add(GarbageCollectionHandle,
	                                           {const_cast<void*>(InObject), bNeedFree});

	MonoObject2GarbageCollectionHandleMap.Add(InMonoObject, GarbageCollectionHandle);

	return true;
}

bool FBindingRegistry::RemoveReference(const MonoObject* InMonoObject)
{
	if (const auto FoundGarbageCollectionHandle = MonoObject2GarbageCollectionHandleMap.Find(InMonoObject))
	{
		FGarbageCollectionHandle::Free(*FoundGarbageCollectionHandle, false);

		if (const auto FoundObject = GarbageCollectionHandle2BindingAddress.Find(
			MonoObject2GarbageCollectionHandleMap[InMonoObject]))
		{
			MonoObject2GarbageCollectionHandleMap.Remove(InMonoObject);

			GarbageCollectionHandle2BindingAddress.Remove(*FoundGarbageCollectionHandle);

			BindingAddress2GarbageCollectionHandle.Remove(*FoundObject);

			return true;
		}
	}

	return false;
}
