
#ifndef CONFIGLEXER_HPP
#define CONFIGLEXER_HPP

template<typename T>
concept IsChar = requires(T ch)
{
    std::is_same_v<T, char>             ||
    std::is_same_v<T, wchar_t>          ||
    std::is_same_v<T, const char&>      ||
    std::is_same_v<T, const wchar_t&>;
};


template<IsChar T>
[[nodiscard]] static constexpr bool IsDoubleQuote(T&& ch)
{
    return ch == '\"';
}

template<IsChar T>
[[nodiscard]] static constexpr bool IsOneQuote(T&& ch)
{
    return ch == '\'';
}



#endif //CONFIGLEXER_HPP
