
#ifndef WORKFILE_HPP
#define WORKFILE_HPP

#include "Config.hpp"

void CheackCanOpenFile(bool te);

[[nodiscard]] std::wstring ReadFile(const std::string& name);

#endif //WORKFILE_HPP
