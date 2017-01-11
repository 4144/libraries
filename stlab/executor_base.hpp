/*
Copyright 2016 Adobe
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef SLABFUTURE_EXECUTOR_BASE_HPP
#define SLABFUTURE_EXECUTOR_BASE_HPP

#include <chrono>
#include <functional>
#include <stlab/system_timer.hpp>

namespace stlab
{

using executor_t = std::function<void(std::function<void()>)>;


/*
 * returns an executor that will schedule any passed task to it to execute
 * at the given time point on the executor provided
 * */

auto execute_at(std::chrono::system_clock::time_point when, executor_t executor)
{
    return [=](auto f) {
        system_timer(when, [=]{
            executor(f);
        });
    };
}

/*
 * returns an executor that will schedule the task to execute on the provided
 * executor duration after it is invoked
 * */
template <typename E>
auto execute_delayed(std::chrono::system_clock::duration duration, E executor) {
    return execute_at(std::chrono::system_clock::now() + duration, std::move(executor));
}

}

#endif // SLABFUTURE_EXECUTOR_BASE_HPP
