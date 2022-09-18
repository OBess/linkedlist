#pragma once

#ifndef INCL_LINKEDLIST_HPP
#define INCL_LINKEDLIST_HPP

#include <stdexcept>

namespace container
{
    namespace detail
    {

        template <class Type>
        struct Node final
        {
            Type data;
            Node *prev = nullptr;
            Node *next = nullptr;

            Node(const Type &data, Node *prev = nullptr, Node *next = nullptr)
                : data{data}, prev{prev}, next{next} {}
            Node(Type &&data, Node *prev = nullptr, Node *next = nullptr) noexcept
                : data{std::move(data)}, prev{prev}, next{next} {}

            ~Node()
            {
                if (next)
                {
                    delete next;
                }
            }

            Node(const Node &) = delete;
            Node &operator=(const Node &) = delete;

            Node(Node &&) noexcept = default;
            Node &operator=(Node &&) noexcept = default;

            constexpr bool has_prev() const noexcept
            {
                return prev != nullptr;
            }

            constexpr bool has_next() const noexcept
            {
                return next != nullptr;
            }
        };

        template <class Type>
        class Iterator final
        {
        public:
            using pointer = Node<Type> *;

            constexpr Iterator(pointer node)
                : _node{node} {}

            Iterator operator++() const noexcept
            {
                if (_node == nullptr)
                {
                    return Iterator(nullptr);
                }

                _node = _node->next;
                return Iterator(_node);
            }

            Iterator operator--() const noexcept
            {
                if (_node == nullptr)
                {
                    return Iterator(nullptr);
                }

                _node = _node->prev;
                return Iterator(_node);
            }

            bool operator!=(const Iterator &other) const noexcept
            {
                return _node != nullptr && other != nullptr;
            }

            operator bool() const noexcept
            {
                return _node != nullptr;
            }

            Type &operator*() noexcept
            {
                return _node->data;
            }

            const Type &operator*() const noexcept
            {
                return _node->data;
            }

        private:
            mutable pointer _node = nullptr;
        };

    } // namespace detail

    template <class Type>
    class linkedlist
    {
    public:
        using value_type = Type;
        using size_type = std::size_t;
        using reference = value_type &;
        using const_reference = const value_type &;
        using node = detail::Node<value_type>;
        using pointer = node *;
        using const_pointer = const node *;
        using iterator = detail::Iterator<Type>;

        constexpr linkedlist() = default;

        ~linkedlist()
        {
            if (_parent)
            {
                delete _parent;
            }
        }

        iterator begin() noexcept
        {
            return iterator(_parent);
        }

        iterator end() noexcept
        {
            return iterator(_last);
        }

        const iterator begin() const noexcept
        {
            return iterator(_parent);
        }

        const iterator end() const noexcept
        {
            return iterator(_last);
        }

        void push_back(const Type &value)
        {
            if (_parent == nullptr)
            {
                _parent = new node(value);
                _last = _parent;
            }
            else
            {
                _last->next = new node(value, _last);
                _last = _last->next;
            }
            ++_size;
        }

        void push_front(const Type &value)
        {
            if (_parent == nullptr)
            {
                _parent = new node(value);
                _last = _parent;
            }
            else
            {
                node *tmp = new node(value, nullptr, _parent);
                _parent = tmp;
            }

            ++_size;
        }

        void pop_back() noexcept
        {
            if (_parent == nullptr)
            {
                return;
            }
            else if (_parent == _last)
            {
                delete _parent;
                _parent = _last = nullptr;
            }
            else
            {
                node *prev = _last->prev;
                delete _last;

                prev->next = nullptr;
                _last = prev;
            }

            --_size;
        }

        void pop_front() noexcept
        {
            if (_parent == nullptr)
            {
                return;
            }
            else if (_parent == _last)
            {
                delete _parent;
                _parent = _last = nullptr;
            }
            else
            {
                node *next = _parent->next;
                delete _parent;

                next->prev = nullptr;
                _parent = next;
            }

            --_size;
        }

        Type &operator[](const size_type index)
        {
            if (index >= _size)
            {
                throw std::range_error("Out of bounds!");
            }

            return get_by_index(index)->data;
        }

        const Type &operator[](const size_type index) const
        {
            if (index >= _size)
            {
                throw std::range_error("Out of bounds!");
            }

            return get_by_index(index)->data;
        }

        constexpr bool empty() const noexcept
        {
            return _parent == nullptr;
        }

        constexpr size_type size() const noexcept
        {
            return _size;
        }

    private:
        node *get_by_index(const size_type index) const noexcept
        {
            node *current = _parent;

            for (size_type i = 0; i < index; ++i)
            {
                current = current->next;
            }

            return current;
        }

        node *_parent = nullptr;
        node *_last = nullptr;
        size_type _size = 0;
    };

} // namespace container

#endif // INCL_LINKEDLIST_HPP