#pragma once

#ifndef INCL_VIEWS_BASE_LINKEDLIST_VIEW_HPP
#define INCL_VIEWS_BASE_LINKEDLIST_VIEW_HPP

#include <memory>

#include <controllers/base_linkedlist_controller.hpp>

namespace mvc
{

    class base_linkedlist_view
    {
    public:
        base_linkedlist_view() = default;

        virtual ~base_linkedlist_view() = default;

        virtual void show() = 0;

    protected:
        inline class base_linkedlist_controller *controller() noexcept
        {
            return _controller;
        }

        inline const class base_linkedlist_controller *controller() const noexcept
        {
            return _controller;
        }

        virtual void update(const container::linkedlist<int> &list) = 0;

    private:
        void reset_controller(base_linkedlist_controller *controller)
        {
            _controller = controller;
        }

        base_linkedlist_controller *_controller;

        friend base_linkedlist_controller;
    };

} // namespace mvc

#endif // INCL_VIEWS_BASE_LINKEDLIST_VIEW_HPP