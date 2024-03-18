//
// Created by nikita on 10.03.24.
//

#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>

[[nodiscard]] std::wstring ConvertString(const std::string& string);
[[nodiscard]] std::string ConvertWstring(const std::wstring& string);

#endif //CONFIG_HPP
