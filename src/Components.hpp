// SPDX-FileCopyrightText: 2021 metaquarx <metaquarx@protonmail.com>
// SPDX-License-Identifier: Apache-2.0

#include "Arrow.hpp"
#include "SFML/Graphics.hpp"
#include "Stitch/Scene.hpp"

#include <string>

#pragma once

namespace fg::cp {

// Node
using Label = std::string;
using LinksLabel = std::vector<Label>;

struct Link {
	stch::EntityID entity;
	Arrow connection;
};

using LinksEntity = std::vector<Link>;

// Physics
struct Force {
	sf::Vector2f value;
};

using Mass = unsigned;
using Position = sf::Vector2f;

// Graphics
enum class RenderType { None, Normal, Centered };

}  // namespace fg::cp
