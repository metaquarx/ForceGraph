// SPDX-FileCopyrightText: 2021 metaquarx <metaquarx@protonmail.com>
// SPDX-License-Identifier: Apache-2.0

#include "Arrow.hpp"

#include "Maths.hpp"

namespace fg {

Arrow::Arrow(sf::Vector2f pos1, sf::Vector2f pos2, float thickness_) : pos_1(pos1), pos_2(pos2), thickness(thickness_) {
	recalculate_points();
	set_colour(sf::Color::Magenta);
}

void Arrow::set_colour(sf::Color colour) {
	verts[0].color = colour;
	verts[1].color = colour;
	verts[2].color = colour;
	verts[3].color = colour;
}

void Arrow::recalculate_points() {
	auto direction = pos_1 - pos_2;
	direction = normalise(direction);
	direction = perpendicular(direction);

	auto offset = (thickness / 2.f) * direction;

	verts[0].position = pos_2 + offset;
	verts[1].position = pos_2 - offset;
	verts[2].position = pos_1 - offset;
	verts[3].position = pos_1 + offset;
}

void Arrow::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(verts, 4, sf::PrimitiveType::Quads, states);
}

}  // namespace fg
