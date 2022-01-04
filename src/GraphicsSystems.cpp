// SPDX-FileCopyrightText: 2021 metaquarx <metaquarx@protonmail.com>
// SPDX-License-Identifier: Apache-2.0

#include "GraphicsSystems.hpp"

#include <iostream>

namespace fg::systems {

void draw(stch::Scene &registry, sf::RenderWindow &window, float zoom, sf::Font &font) {
	window.clear({247, 247, 247});

	registry.each<sf::View, cp::RenderType, cp::Position>([&](auto, auto &view, auto &camera_type, auto &move) {
		view.move(-move);
		move = {};

		sf::View copy(view);
		copy.zoom(zoom);

		window.setView(copy);

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
		registry.each<sf::CircleShape, cp::RenderType>([&](auto id, auto &circle, auto &type) {
			if (camera_type != type) {
				return;
			}

			window.draw(circle);

			if (registry.all_of<cp::Hovering, cp::Label>(id)) {
				sf::Text label(registry.get<cp::Label>(id), font);
				label.setCharacterSize(30);
				label.setStyle(sf::Text::Regular);
				sf::Vector2 pos = circle.getPosition();
				pos += {-label.getLocalBounds().width / 2, circle.getRadius() + 10};
				label.setPosition(pos);
				label.setFillColor({34, 34, 34});

				window.draw(label);
			}
		});
	});

	// leave center applied by default
	registry.each<sf::View, cp::RenderType>([&](auto, auto &view, auto &type) {
		if (type == cp::RenderType::Centered) {
			sf::View copy(view);
			copy.zoom(zoom);
			window.setView(copy);
		}
	});

	// show
	window.display();
}

}  // namespace fg::systems
