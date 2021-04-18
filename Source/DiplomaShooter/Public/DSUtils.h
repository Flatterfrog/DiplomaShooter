#pragma once

class DSUtils
{
public:
	template<typename T>
    static T* GetDSPlayerComponent(APawn* PlayerPawn)
    {
        if (!PlayerPawn) return nullptr;

        const auto Component = PlayerPawn->GetComponentByClass(T::StaticClass());
        return Cast<T>(Component);
    }
};