//
// Created by nperreau on 7/28/23.
//

#ifndef LIBLOADER_LIB_HPP
#define LIBLOADER_LIB_HPP

#include <string>
#include <filesystem>
#include <bits/dlfcn.h>

namespace LL
{
    using DLHandle = void*;

    class Lib
    {
        public:
            enum class Binding
            {
                /** Perform lazy binding.
                 * Only resolve symbols as the code that references them is executed. If the symbol is never referenced, then it is never resolved. (Lazy binding is only performed for function references; references to variables are always immediately bound when the library is loaded.)
                 */
                Lazy = RTLD_LAZY,
                /** Bind when the library is loaded.
                 * If this value is specified, or the environment variable LD_BIND_NOW is set to a nonempty string, all undefined symbols in the library are resolved as soon as the library is loaded.
                 */
                Now = RTLD_NOW,
            };

            enum class Scope
            {
                /**
                 * This is the converse of Scope::Global, and the default if neither flag is specified. Symbols defined in this library are not made available to resolve references in subsequently loaded libraries.
                 */
                Local = RTLD_LOCAL,
                /**
                 * The symbols defined by this library will be made available for symbol resolution of subsequently loaded libraries.
                 */
                Global = RTLD_GLOBAL,
            };

            Lib(nullptr_t) = delete; // NOLINT(*-explicit-constructor)
            Lib(char const *&&path); // NOLINT(*-explicit-constructor)
            Lib(std::filesystem::path path); // NOLINT(*-explicit-constructor)

            /// @returns The path of this library.
            [[nodiscard]] const std::filesystem::path &getPath() const noexcept;

            /// @brief Calls the function associated with this symbol.
            /// @returns The value returned by this function call, if non-void.
            template<typename TFunction, typename ...TArgs>
            std::invoke_result<TFunction, TArgs...>::type Call(const std::string &function, TArgs... args) const;

            /// @returns The address of this symbol.
            [[nodiscard]] void *operator[](std::string const &name) const;

            /// @returns The address of this symbol.
            template<typename T>
            [[nodiscard]] T *GetSymbol(std::string const &name) const;

            /// @returns A reference to the value contained in the address of this symbol.
            template<typename T>
            [[nodiscard]] T &GetValue(std::string const &name) const;

            /// @returns The handle of this library. Take care of it!
            [[nodiscard]] DLHandle const &GetHandle() const noexcept;

            /// @brief Loads the library with the given flags.
            void Load(Binding const &binding = Binding::Lazy, Scope const &scope = Scope::Local, bool const &deepBind = false);
            /// @brief Unloads the library.
            void Unload();

            [[nodiscard]] bool IsLoaded() const;
            static bool IsLoaded(std::string const &name);

        class DL
        {
            public:
                static void CheckDLError();
                static void ClearDLError() noexcept;

            private:
                virtual void PreventInheritance() = 0;
        };

        protected:
            std::filesystem::path _path;
            void *_handle = nullptr;
    };
} // LL

#endif //LIBLOADER_LIB_HPP
