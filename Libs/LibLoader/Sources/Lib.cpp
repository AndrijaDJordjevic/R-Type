/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** Lib
*/

#include <dlfcn.h>
#include <utility>
#include "Lib.hpp"
#include "Exceptions/FileNotFound.hpp"
#include "Exceptions/DlError.hpp"
#include "Exceptions/NullReference.hpp"

namespace LL
{
    Lib::Lib(const char *&&path) : Lib(path) { }
    Lib::Lib(std::filesystem::path path) : _path(std::move(path)) { }

    const std::filesystem::path & Lib::getPath() const noexcept
    {
        return _path;
    }

    void Lib::DL::CheckDLError()
    {
        char const *err = dlerror();

        if (err == nullptr)
            return;

        throw Exceptions::DLError(err);
    }

    void Lib::DL::ClearDLError() noexcept
    {
        dlerror();
    }

    void *Lib::operator[](const std::string &name) const
    {
        return GetSymbol<void>(name);
    }

    DLHandle const &Lib::GetHandle() const noexcept
    {
        return _handle;
    }

    bool Lib::IsLoaded(std::string const &name)
    {
        DL::ClearDLError();
        void* handle = dlopen(name.c_str(), RTLD_NOLOAD);
        DL::CheckDLError();

        return handle != nullptr;
    }

    void Lib::Unload()
    {
        if (dlclose(_handle) == 0)
            _handle = nullptr;
        else
            throw Exceptions::DLError("Could not unload library.");
    }

    void Lib::Load(const Lib::Binding &binding, const Lib::Scope &scope, const bool &deepBind)
    {
        if (!std::filesystem::exists(getPath()))
            throw Exceptions::FileNotFound(getPath());

        int flags = ((int)binding) | ((int)scope);

        if (IsLoaded())
            flags |= RTLD_NOLOAD;

        if (deepBind)
            flags |= RTLD_DEEPBIND;

        DL::ClearDLError();
        _handle = dlopen(_path.c_str(), (int)binding);
        DL::CheckDLError();
    }

    bool Lib::IsLoaded() const
    {
        return IsLoaded(getPath());
    }

    template<typename TValue>
    TValue &Lib::GetValue(const std::string &name) const
    {
        TValue *ptr = GetSymbol<TValue>(name);

        if (ptr == nullptr)
            throw Exceptions::NullReference();
        return *ptr;
    }

    template<typename TSymbol>
    TSymbol *Lib::GetSymbol(std::string const &name) const
    {
        DL::ClearDLError();

        TSymbol *val = reinterpret_cast<TSymbol*>(dlsym(_handle, name.c_str()));
        DL::CheckDLError();

        return val;
    }

    template<typename TFunction, typename ...TArgs>
    std::invoke_result<TFunction, TArgs...>::type Lib::Call(const std::string &function, TArgs... args) const
    {
        TFunction* func = GetSymbol<TFunction>(function);

        if (func == nullptr)
            throw Exceptions::NullReference();

        return func(args...);
    }
} // LL
