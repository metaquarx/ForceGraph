// SPDX-FileCopyrightText: 2021 metaquarx <metaquarx@protonmail.com>
// SPDX-License-Identifier: Apache-2.0

#include <SFML/Graphics.hpp>

#pragma once

namespace fg {

class Arrow : public sf::Drawable {
public:
	Arrow(sf::Vector2f pos1 = {}, sf::Vector2f pos2 = {}, float thickness = 1.f);

	void set_colour(sf::Color);
	void recalculate_points();

	sf::Vector2f pos_1;
	sf::Vector2f pos_2;
	float thickness;

private:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	sf::Vertex verts[4];
};

}  // namespace fg
