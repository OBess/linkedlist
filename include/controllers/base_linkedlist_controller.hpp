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
        base_linkedlist_controller(base_linkedlist_view *view, container::linkedlist &list)
            : _view{view}, _list{&list}
        {
            view.reset_controller(this);
        }

        virtual ~base_linkedlist_controller() = default;

        inline void reset_view(std::shared_ptr<base_linkedlist_view> view)
        {
            _view = std::move(view);
        }

        inline void reset_(container::linkedlist &list)
        {
            _list = &list;
        }

    protected:
        std::shared_ptr<base_linkedlist_view> _view;

        container::linkedlist *_list = nullptr;
    };

} // namespace mvc

#endif // INCL_CONTROLLERS_BASE_LINKEDLIST_CONTROOLER_HPP