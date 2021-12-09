// SPDX-FileCopyrightText: 2021 metaquarx <metaquarx@protonmail.com>
// SPDX-License-Identifier: Apache-2.0.

#include "GraphicsSystems.hpp"

namespace fg::systems {

void draw(stch::Scene &registry, sf::RenderWindow &window) {
	window.clear({247, 247, 247});

	registry.each<sf::View, cp::RenderType>([&](auto, auto &view, auto &camera_type) {
		window.setView(view);

		// draw connections
		registry.each<cp::LinksEntity, cp::RenderType>([&](auto, auto &connections, auto &type) {
			if (camera_type != type) {
				return;
			}

			for (auto &link : connections) {
				window.draw(link.connection);
			}
		});

		// draw nodes
		registry.each<sf::CircleShape, cp::RenderType>([&](auto, auto &circle, auto &type) {
			if (camera_type != type) {
				return;
			}

			window.draw(circle);
		});
	});

	// show
	window.display();
}

}  // namespace fg::systems
