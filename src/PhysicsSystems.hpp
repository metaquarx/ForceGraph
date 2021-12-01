// SPDX-FileCopyrightText: 2021 metaquarx <metaquarx@protonmail.com>
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Components.hpp"

namespace fg::systems {

void calculate_forces(stch::Scene &registry, float gravity, float force);
void apply_forces(stch::Scene &registry);
void apply_positions(stch::Scene &registry);

}  // namespace fg::systems
