#pragma once
#include "juce_core/juce_core.h"

namespace units
{
auto percentage = [] (auto value, auto)
{
    constexpr auto unit = " %";
    auto v { value * 100.f };
    if (v < 10.0f)
        return juce::String { v, 2 } + unit;
    if (v < 100.0f)
        return juce::String { v, 1 } + unit;
    return juce::String { v } + unit;
};

auto Hz = [] (auto value, auto)
{
    constexpr auto unit = " Hz";

    if (auto v { std::round (value * 10.0f) / 10.0f }; v < 100.0f)
        return juce::String { v, 1 } + unit;

    return juce::String { std::round (value) } + unit;
};

auto ms = [] (auto value, auto)
{
    constexpr auto unit = " ms";

    if (auto v { std::round (value * 10.0f) / 10.0f }; v < 100.0f)
        return juce::String { v, 1 } + unit;

    return juce::String { std::round (value) } + unit;
};
} // namespace units
