    /*
    ** EPITECH PROJECT, 2023
    ** bootstrat
    ** File description:
    ** SparseArray
    */

    #ifndef SparseArray_HPP_
    #define SparseArray_HPP_

    #include <vector>
    #include <cstddef>
    #include <optional>
    #include <stdexcept>
    #include <unordered_map>

    template <typename TComponent> // You can also mirror the definition of std :: vector ,that takes an additional allocator .
    class SparseArray {
        public :
            using value_type = TComponent;  //   Choisir le type de la liste ex: SparseArray<int> mySparseArray
            using reference_type = value_type &;   // modifier depuis le déférence
            using const_reference_type = value_type const &;  //  accéder sans modifier
            using container_t = std::unordered_map<size_t, value_type>; //  créer un container avec un vector
            using size_type = typename container_t::size_type;  //  déffinir la taille du conteneur
            using iterator = typename container_t::iterator ; //  créer un iterateur pour parcourir le conteuneur
            using const_iterator = typename container_t::const_iterator ;

            SparseArray();
            SparseArray(SparseArray<TComponent> const &); // copy constructor
            SparseArray(SparseArray<TComponent> &&) noexcept; // move constructor
            ~SparseArray();
            SparseArray<TComponent> &operator=(SparseArray<TComponent> const &); // copy assignment operator
            SparseArray<TComponent> &operator=(SparseArray<TComponent> &&) noexcept; // move assignment operator
            TComponent &operator[](size_t idx);  // ex : component[0] = 10;
            const_reference_type operator[](size_t idx) const; // pareil mais peux pas modifier
            iterator begin();
            const_iterator begin () const;
            const_iterator cbegin () const;
            iterator end ();
            const_iterator end () const;
            const_iterator cend () const;
            size_type size () const;  // choper la size
            reference_type insertAt(size_type pos, TComponent const &);
            reference_type insertAt(size_type pos, TComponent &&);
            void insert(TComponent const &value);
            void insert(TComponent &value);
            void erase(size_type pos);
            size_type getIndex(value_type const &) const;   // choper l'index de la valeur

            template<typename ...TArgs>
            TComponent &emplace(size_t const &id, TArgs... args);

            [[nodiscard]] bool HasEntity(size_t const &entity) const;

    private :
            container_t _data;
    };

    template<typename TComponent>
    template<typename... TArgs>
    TComponent &SparseArray<TComponent>::emplace(size_t const &id, TArgs... args)
    {
        if (HasEntity(id)) {
            TComponent& existingComponent = _data.at(id);
            existingComponent = TComponent(args...);
            return existingComponent;
        }
    
        _data.insert(std::make_pair(id, TComponent(args...)));
        return _data.at(id);
    }
    

    template<typename TComponent>
    bool SparseArray<TComponent>::HasEntity(const size_t &entity) const
    {
        return _data.find(entity) != _data.end();
    }

    template <typename Component>
    SparseArray<Component>::SparseArray()
    {

    }

    template <typename Component>
    SparseArray<Component>::~SparseArray()
    {

    }

    template <typename Component>
    SparseArray<Component>::SparseArray(SparseArray const& other)
    {
        this->_data = other._data;
    }

    template <typename Component>
    SparseArray<Component>::SparseArray(SparseArray&& other) noexcept
    {
        this->_data = std::move(other._data);
    }

    template <typename Component>
    SparseArray<Component> &SparseArray<Component>::operator=(SparseArray const &other)
    {
        if (this != &other)
            this->_data = other._data;
        return *this;
    }

    template <typename Component>
    SparseArray<Component> &SparseArray<Component>::operator=(SparseArray && other) noexcept
    {
        if (this != &other)
            this->_data = std::move(other._data);
        return *this;
    }

    template <typename TComponent>
    TComponent &SparseArray<TComponent>::operator[](size_t idx)
    {
        if (_data.find(idx) == _data.end())
            throw std::out_of_range("The Entity #" + std::to_string(idx) + " has no component of the given type.");

        return _data.at(idx);
    }

    template <typename Component>
    typename SparseArray<Component>::const_reference_type SparseArray<Component>::operator[](size_t idx) const
    {
        return this->_data[idx];
    }

    template <typename Component>
    typename SparseArray<Component>::iterator SparseArray<Component>::begin()
    {
        return this->_data.begin();
    }

    template <typename Component>
    typename SparseArray<Component>::const_iterator SparseArray<Component>::begin() const
    {
        return this->_data.begin();
    }

    template <typename Component>
    typename SparseArray<Component>::const_iterator SparseArray<Component>::cbegin() const
    {
        return this->_data.cbegin();
    }

    template <typename Component>
    typename SparseArray<Component>::iterator SparseArray<Component>::end()
    {
        return this->_data.end();
    }

    template <typename Component>
    typename SparseArray<Component>::const_iterator SparseArray<Component>::end() const
    {
        return this->_data.end();
    }

    template <typename Component>
    typename SparseArray<Component>::const_iterator SparseArray<Component>::cend() const
    {
        return this->_data.cend();
    }

    template <typename Component>
    typename SparseArray<Component>::size_type SparseArray<Component>::size() const
    {
        return this->_data.size();
    }

    template <typename Component>
    typename SparseArray<Component>::reference_type SparseArray<Component>::insertAt(size_type pos, Component const &value)
    {
        this->_data.insert(this->_data.begin() + pos, value);
        return _data[pos];
    }

    template <typename Component>
    typename SparseArray<Component>::reference_type SparseArray<Component>::insertAt(size_type pos, Component &&value)
    {
        this->_data.insert(this->_data.at(pos), std::move(value));
        return _data[pos];
    }

    template <typename Component>
    void SparseArray<Component>::insert(Component const &value)
    {
        _data.push_back(value);
    }

    template <typename Component>
    void SparseArray<Component>::insert(Component &value)
    {
        _data.push_back(value);
    }

    template <typename Component>
    void SparseArray<Component>::erase(size_type pos)
    {
        _data.erase(pos);
    }

    template <typename Component>
    typename SparseArray<Component>::size_type SparseArray<Component>::getIndex ( value_type const &value) const
    {
        for (int i = 0; i < _data.size(); ++i) {
            if (_data[i] == value)
                return i;
        }
        return -1;
    }

    #endif
