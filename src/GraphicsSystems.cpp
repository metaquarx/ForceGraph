// SPDX-FileCopyrightText: 2021 metaquarx <metaquarx@protonmail.com>
// SPDX-License-Identifier: Apache-2.0.

#include "GraphicsSystems.hpp"

namespace fg::systems {

void draw(stch::Scene &registry, sf::RenderWindow &window) {
	window.clear({247, 247, 247});

	// draw connections
	registry.each<cp::LinksEntity, cp::Position>([&](auto, auto &connections, auto &) {
		for (auto &link : connections) {
			window.draw(link.connection);
		}
	});

	// draw nodes
	registry.each<sf::CircleShape, cp::Position>(
		[&](auto, auto &circle, auto &) { window.draw(circle); });

	// show
	window.display();
}

}  // namespace fg::systems
