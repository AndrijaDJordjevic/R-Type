/*
** EPITECH PROJECT, 2023
** GameEngine [WSL: Ubuntu]
** File description:
** Registry
*/


#ifndef REGISTRY_HPP_
    #define REGISTRY_HPP_

#include <stdexcept>
#include <unordered_map>
#include <typeindex>
#include <type_traits>
#include <vector>
#include <any>
#include <functional>
#include "SparseArray.hpp"
#include <iostream>

class Registry
{
    public:
        Registry();
        static Registry &getCurrentRegitry();

        // Enregistrez les composants dans le Registry.
        template <class Component>
        SparseArray<Component>& registerComponent();

        // Récupérez les composants à partir de std::type_index.
        template <class Component>
        SparseArray<Component>& getComponents();

        // Récupérez les composants (const) à partir de std::type_index.
        template <class Component>
        const SparseArray<Component>& getComponents() const;

        // Créez une nouvelle entité.
        size_t &spawnEntity();

        // Supprime une entité et tous ses composants.
        void killEntity(size_t const& e);

        // Ajoute un composant à une entité.
        template <typename Component>
        typename SparseArray<Component>::reference_type addComponent(size_t const& to, Component&& c);

        // Ajoute un composant à une entité en utilisant emplace.
        template <typename TComponent, typename... TParams>
        typename SparseArray<TComponent>::reference_type emplaceComponent(size_t const& to, TParams... p);

        // Supprime un composant d'une entité.
        template <typename TComponent>
        void removeComponent(size_t const& from);

        template<class TComponent>
        inline TComponent &GetComponentByEntity(size_t const &id)
        {
            return std::any_cast<SparseArray<TComponent>&>(_components_arrays[typeid(TComponent)])[id];
        }

        /// @brief Executes a system on the given components. It will find all entities than contains all of the components of the given types, and pass a reference to all those components to func.
        template<typename ...TComponents>
        inline void Exec(std::function<void(TComponents&...)> func)
        {
            static_assert(((!std::is_reference<TComponents>::value) && ...), "TComponents must not be references.");

            for (size_t const &item: entities) {
                if (((_components_arrays.find(typeid(TComponents)) != _components_arrays.end()
                     && std::any_cast<SparseArray<TComponents>&>(_components_arrays[typeid(TComponents)]).HasEntity(item)) && ...)) {
                    func(GetComponentByEntity<TComponents>(item)...);
                }
            }
        }

    template<typename ...TComponents>
    inline auto Exec(std::function<bool(TComponents&...)> func) -> std::invoke_result_t<decltype(func), TComponents&...>
    {
        static_assert(((!std::is_reference<TComponents>::value) && ...), "TComponents must not be references.");

        for (size_t const &item: entities) {
            if (((_components_arrays.find(typeid(TComponents)) != _components_arrays.end()
                 && std::any_cast<SparseArray<TComponents>&>(_components_arrays[typeid(TComponents)]).HasEntity(item)) && ...)) {
                return func(GetComponentByEntity<TComponents>(item)...);
            }
        }
        // Valeur par défaut si aucune fonction n'est exécutée.
        return std::invoke_result_t<decltype(func), TComponents&...>();
    }

    size_t getNbEntities(void) {return entities.size();}
    std::vector<size_t> getEntities(void) {return entities;}

    private:
        std::unordered_map<std::type_index, std::any> _components_arrays;
        std::size_t _nextEntityId = 0;
        std::vector<std::function<void(Registry&)>> _systems;
        std::vector<size_t> entities;
        std::vector<size_t> _freeIndexes;
        inline static Registry *_registry;
};

template <class TComponent>
SparseArray<TComponent>& Registry::registerComponent()
{
    std::type_index const componentType = typeid(TComponent);

    if (_components_arrays.find(componentType) == _components_arrays.end()) {
        _components_arrays[componentType] = SparseArray<TComponent>();
    }
    return std::any_cast<SparseArray<TComponent>&>(_components_arrays[componentType]);
}

template <class TComponent>
SparseArray<TComponent>& Registry::getComponents()
{
    std::type_index componentType = typeid(TComponent);

    if (_components_arrays.find(componentType) != _components_arrays.end()) {
        return std::any_cast<SparseArray<TComponent>&>(_components_arrays[componentType]);
    }

    throw std::runtime_error("TComponent not registered in the Registry.");
}

template <class TComponent>
SparseArray<TComponent> const &Registry::getComponents() const
{
    return std::any_cast<SparseArray<TComponent>const &>(_components_arrays.at(typeid(TComponent)));
}

template <typename TComponent>
typename SparseArray<TComponent>::reference_type Registry::addComponent(size_t const& to, TComponent&& c)
{
    SparseArray<TComponent>& components = getComponents<TComponent>();

    if (to >= components.size()) {
        throw std::runtime_error("Entity does not exist or is out of range.");
    }

    return components.insertAt(to, std::forward<TComponent>(c));
}

template <typename TComponent, typename... TParams>
typename SparseArray<TComponent>::reference_type Registry::emplaceComponent(size_t const& to, TParams... p)
{
    SparseArray<TComponent>& components = getComponents<TComponent>();

    return components.emplace(to, p...);
}

template <typename TComponent>
void Registry::removeComponent(size_t const& from)
{
    SparseArray<TComponent>& components = getComponents<TComponent>();

    if (from >= components.size()) {
        throw std::runtime_error("Entity does not exist or is out of range.");
    }

    components.erase(from);
}

#endif /* !REGISTRY_HPP_ */

