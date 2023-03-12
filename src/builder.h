// Copyright 2022 nullptr

#pragma once

#include "builder/base.h"

namespace pgeon {

std::shared_ptr<ArrayBuilder> MakeBuilder(const SqlTypeInfo&, const UserOptions&);

}  // namespace pgeon
