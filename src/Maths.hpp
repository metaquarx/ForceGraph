// SPDX-FileCopyrightText: 2021 metaquarx <metaquarx@protonmail.com>
// SPDX-License-Identifier: Apache-2.0

#include "SFML/Graphics.hpp"
#include <cmath>

#pragma once

namespace fg {

float magnitude(sf::Vector2f);
float distance(sf::Vector2f, sf::Vector2f);
sf::Vector2f normalise(sf::Vector2f);
sf::Vector2f perpendicular(sf::Vector2f);

}  // namespace fg
