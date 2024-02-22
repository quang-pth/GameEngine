#pragma once

#include<memory>
#include<stdint.h>

template<typename T> using Shared = std::shared_ptr<T>;
template<typename T> using Unique = std::unique_ptr<T>;
