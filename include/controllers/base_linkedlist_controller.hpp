#pragma once

#ifndef INCL_CONTROLLERS_BASE_LINKEDLIST_CONTROOLER_HPP
#define INCL_CONTROLLERS_BASE_LINKEDLIST_CONTROOLER_HPP

#include <memory>

#include <models/linkedlist.hpp>
#include <views/base_linkedlist_view.hpp>

namespace mvc
{

    class base_linkedlist_controller
    {
    public:
        base_linkedlist_controller(base_linkedlist_view *view, container::linkedlist<int> &list)
            : _view{view}, _list{&list}
        {
            view->reset_controller(this);
        }

        virtual ~base_linkedlist_controller() = default;

        inline void reset_view(std::shared_ptr<base_linkedlist_view> view)
        {
            _view = std::move(view);
        }

        inline void reset_list(container::linkedlist<int> &list)
        {
            _list = &list;
        }

    protected:
        inline std::shared_ptr<base_linkedlist_view> &view() noexcept
        {
            return _view;
        }

        inline const std::shared_ptr<base_linkedlist_view> &view() const noexcept
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

    private:
        std::shared_ptr<base_linkedlist_view> _view;

        container::linkedlist<int> *_list = nullptr;
    };

} // namespace mvc

#endif // INCL_CONTROLLERS_BASE_LINKEDLIST_CONTROOLER_HPP