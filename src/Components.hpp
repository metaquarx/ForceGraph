// SPDX-FileCopyrightText: 2021 metaquarx <metaquarx@protonmail.com>
// SPDX-License-Identifier: Apache-2.0

#include "Arrow.hpp"
#include "SFML/Graphics.hpp"
#include "Stitch/Scene.hpp"

#include <string>

#pragma once

namespace fg::cp {

using Label = std::string;
using LinksLabel = std::vector<Label>;

struct Link {
	stch::EntityID entity;
	Arrow connection;
};
using LinksEntity = std::vector<Link>;

struct Force {
	sf::Vector2f value;
};
using Mass = unsigned;
using Position = sf::Vector2f;

}  // namespace fg::cp
