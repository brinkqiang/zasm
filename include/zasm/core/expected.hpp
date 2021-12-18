#pragma once

#include <variant>

namespace zasm
{
    namespace detail
    {
        template<typename T> struct Unexpected
        {
            const T failure;

            constexpr Unexpected(const T& val)
                : failure{ val }
            {
            }
        };
    } // namespace detail

    template<typename TSuccess, typename TFailure> class Expected
    {
        std::variant<TSuccess, detail::Unexpected<TFailure>> data;

    public:
        constexpr Expected(const TSuccess& val)
            : data{ val }
        {
        }
        constexpr Expected(TSuccess&& val)
            : data{ std::move(val) }
        {
        }
        constexpr Expected(const detail::Unexpected<TFailure>& val)
            : data{ val }
        {
        }
        constexpr Expected(detail::Unexpected<TFailure>&& val)
            : data{ std::move(val) }
        {
        }
        constexpr operator bool() const
        {
            return data.index() == 0;
        }
        constexpr const TFailure& error() const
        {
            return std::get<detail::Unexpected<TFailure>>(data).failure;
        }
        constexpr TSuccess& value()
        {
            return std::get<TSuccess>(data);
        }
        constexpr const TSuccess& value() const
        {
            return std::get<TSuccess>(data);
        }
        constexpr TSuccess& operator*()
        {
            return std::get<TSuccess>(data);
        }
        constexpr const TSuccess& operator*() const
        {
            return std::get<TSuccess>(data);
        }
    };

    template<typename T> constexpr detail::Unexpected<T> makeUnexpected(const T& val)
    {
        return detail::Unexpected<T>(val);
    }

} // namespace xstd