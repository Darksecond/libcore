#pragma once

namespace core
{

    template <typename TO, typename FROM>
    inline TO union_cast(FROM from)
    {
        static_assert(sizeof(TO) == sizeof(FROM), "Can only cast from types of the same size.");

        union
        {
            FROM cast_from;
            TO cast_to;
        };

        cast_from = from;
        return cast_to;
    }
};
