// SPDX-FileCopyrightText: 2021 metaquarx <metaquarx@protonmail.com>
// SPDX-License-Identifier: Apache-2.0

#include "GraphicsSystems.hpp"

#include <iostream>
#include <optional>

namespace fg::systems {

void draw(stch::Scene &registry, sf::RenderWindow &window, float zoom, sf::Vector2f &zoom_offset, sf::Font &font) {
	window.clear({247, 247, 247});

	std::optional<stch::EntityID> hovering = std::nullopt;

	registry.each<sf::View, cp::RenderType, cp::Position>([&](auto, auto &view, auto &camera_type, auto &move) {
		// apply move to view
		view.move(-move);
		view.move(-zoom_offset);
		move = {};

		// work on copy to not zoom on stored view
		sf::View copy(view);
		copy.zoom(zoom);
		window.setView(copy);

		registry.each<sf::CircleShape, cp::LinksEntity, cp::RenderType>(
			[&](auto id, auto &circle, auto &connections, auto &type) {
				if (camera_type != type) {
					return;
				}

				// draw connections
				for (auto &link : connections) {
					window.draw(link.connection);
				}

				// draw circles
				window.draw(circle);

				if (registry.all_of<cp::Hovering, cp::Label>(id)) {
					hovering = id;
				}
			});
	});
	zoom_offset = {};

	// leave center applied by default
	registry.each<sf::View, cp::RenderType>([&](auto, auto &view, auto &type) {
		if (type == cp::RenderType::Centered) {
			sf::View copy(view);
			copy.zoom(zoom);
			window.setView(copy);
		}
	});

	if (hovering) {
		// phase out overlay
		sf::RectangleShape overlay(zoom * 10 * sf::Vector2f(window.getSize()));
		overlay.setPosition(overlay.getSize() / -2.f);
		overlay.setFillColor({255, 255, 255, 50});
		window.draw(overlay);

		// circle
		auto circle = registry.get<sf::CircleShape>(*hovering);
		circle.setOutlineColor(circle.getFillColor());
		circle.setOutlineThickness(3);
		circle.setRadius(circle.getRadius() - 1.f);
		circle.setFillColor({158, 0, 58});
		window.draw(circle);

		// links
		for (auto link : registry.get<cp::LinksEntity>(*hovering)) {
			link.connection.set_colour({158, 0, 58});
			link.connection.recalculate_points();
			window.draw(link.connection);
		}

		// label
		sf::Text label(registry.get<cp::Label>(*hovering), font);
		label.setCharacterSize(30);
		label.setStyle(sf::Text::Regular);
		sf::Vector2f pos = circle.getPosition();
		pos += {-label.getLocalBounds().width / 2, circle.getRadius() + 10};
		label.setPosition(sf::Vector2f(sf::Vector2i(pos)));
		label.setFillColor({34, 34, 34});

		window.draw(label);
	}

	// show
	window.display();
}

}  // namespace fg::systems
