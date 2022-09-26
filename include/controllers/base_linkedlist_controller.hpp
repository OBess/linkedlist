#pragma once

#ifndef INCL_CONTROLLERS_BASE_LINKEDLIST_CONTROOLER_HPP
#define INCL_CONTROLLERS_BASE_LINKEDLIST_CONTROOLER_HPP

#include <memory>

#include <models/linkedlist.hpp>
#include <views/base_linkedlist_view.hpp>

namespace mvc
{
    enum class Event : uint8_t
    {
        Add = 0,
        Remove = 1,
        Find = 2,
        Update = 3
    };

    class base_linkedlist_controller
    {
    public:
        base_linkedlist_controller(base_linkedlist_view &view, container::linkedlist<int> &list)
            : _view{&view}, _list{&list}
        {
            view.reset_controller(this);
        }

        virtual ~base_linkedlist_controller() = default;

        virtual void notify(Event event) = 0;

        inline void reset_view(base_linkedlist_view *view)
        {
            _view = view;
            notify(Event::Update);
        }

        inline void reset_list(container::linkedlist<int> &list)
        {
            _list = &list;
            notify(Event::Update);
        }

    protected:
        inline base_linkedlist_view *view() noexcept
        {
            return _view;
        }

        inline const base_linkedlist_view *view() const noexcept
        {
            return _view;
        }

        inline container::linkedlist<int> *list() noexcept
        {
            return _list;
        }

        inline const container::linkedlist<int> *list() const noexcept
        {
            return _list;
        }

        inline void send(const container::linkedlist<int> &list)
        {
            if (_view)
            {
                _view->update(list);
            }
        }

    private:
        base_linkedlist_view *_view = nullptr;

        container::linkedlist<int> *_list = nullptr;
    };

} // namespace mvc

#endif // INCL_CONTROLLERS_BASE_LINKEDLIST_CONTROOLER_HPP