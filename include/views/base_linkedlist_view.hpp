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

    protected:
        inline std::shared_ptr<base_linkedlist_controller> &get() noexcept
        {
            return _controller;
        }

        inline const std::shared_ptr<base_linkedlist_controller> &get() const noexcept
        {
            return _controller;
        }

    private:
        inline void reset_controller(std::shared_ptr<base_linkedlist_controller> controller)
        {
            _controller = std::move(controller);
        }

        std::shared_ptr<base_linkedlist_controller> _controller;

        friend base_linkedlist_controller;
    };

} // namespace mvc

#endif // INCL_VIEWS_BASE_LINKEDLIST_VIEW_HPP