// SPDX-FileCopyrightText: 2021 metaquarx <metaquarx@protonmail.com>
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Components.hpp"

namespace fg::systems {

void drag_press(stch::Scene &registry, sf::Vector2i current_pos, const sf::RenderTarget &window);
void drag_release(stch::Scene &registry);
void drag_move(stch::Scene &registry, sf::Vector2i current_pos, sf::Vector2i &last_pos, float zoom);

}  // namespace fg::systems
