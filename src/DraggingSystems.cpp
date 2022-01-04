// SPDX-FileCopyrightText: 2021 metaquarx <metaquarx@protonmail.com>
// SPDX-License-Identifier: Apache-2.0

#include "DraggingSystems.hpp"

#include "Maths.hpp"

namespace fg::systems {

void hover(stch::Scene &registry, sf::RenderTarget &window, sf::Vector2i pos) {
	registry.each<cp::Hovering>([&](auto id, auto) { registry.erase<cp::Hovering>(id); });

	registry.each<sf::CircleShape>([&](auto id, auto &c) {
		if (distance(c.getPosition(), window.mapPixelToCoords(pos)) <= c.getRadius()) {
			registry.emplace<cp::Hovering>(id);
		}
	});
}

void drag_press(stch::Scene &registry, sf::Vector2i current_pos, const sf::RenderTarget &window) {
	bool found = false;
	std::vector<stch::EntityID> other;

	registry.each<cp::Draggable>([&](auto id, auto &drag) {
		// handle nodes first, everything else afterwards
		if (!registry.all_of<sf::CircleShape>(id)) {
			other.push_back(id);
			return;
		}
		auto &circle = registry.get<sf::CircleShape>(id);

		// only 1 node should be draggable
		if (found) {
			return;
		}

		if (distance(circle.getPosition(), window.mapPixelToCoords(current_pos)) > circle.getRadius()) {
			return;
		}

		drag.in_progress = true;
		registry.emplace<cp::ForceDisable>(id);	 // stop physics system from taking over
		found = true;
	});

	if (!found) {
		for (auto background : other) {
			auto &drag = registry.get<cp::Draggable>(background);
			drag.in_progress = true;
		}
	}
}

void drag_release(stch::Scene &registry) {
	registry.each<cp::Draggable>([&](auto id, auto &drag) {
		drag.in_progress = false;
		if (registry.all_of<cp::ForceDisable>(id)) {
			registry.erase<cp::ForceDisable>(id);
		}
	});
}

void drag_move(stch::Scene &registry, sf::Vector2i current_pos, sf::Vector2i &last_pos, float zoom) {
	auto delta = last_pos - current_pos;
	registry.each<cp::Draggable, cp::Position>([&](auto, auto &drag, auto &pos) {
		if (drag.in_progress) {
			pos -= sf::Vector2f(delta) * zoom;
		}
	});
	last_pos = current_pos;
}

}  // namespace fg::systems
