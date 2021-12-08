// SPDX-FileCopyrightText: 2021 metaquarx <metaquarx@protonmail.com>
// SPDX-License-Identifier: Apache-2.0

#include "ForceGraph/ForceSimulation.hpp"

#include "Components.hpp"
#include "PhysicsSystems.hpp"

#include <algorithm>

namespace fg {

ForceSimulation::ForceSimulation(const std::string &title)
: paused(true), reng(rdev()), rdist(-500, 500) {
	auto desktop = sf::VideoMode::getDesktopMode();
	sf::ContextSettings settings;
	settings.antialiasingLevel = 5;

	window.create(sf::VideoMode(desktop.width, desktop.height), title, sf::Style::Default, settings);

	auto width = static_cast<float>(desktop.width);
	auto height = static_cast<float>(desktop.height);
	center.reset({-width / 2, -height / 2, width, height});
	normal = window.getView();
	window.setView(center);

	set_tick_rate();
	set_framerate(-1);
}

void ForceSimulation::set_tick_rate(float interval) {
	tick_rate = interval;
}

void ForceSimulation::set_title(const std::string &title) {
	window.setTitle(title);
}

void ForceSimulation::set_framerate(int fps) {
	if (fps < 0) {
		window.setFramerateLimit(0);
		window.setVerticalSyncEnabled(true);
	} else if (fps == 0) {
		window.setVerticalSyncEnabled(false);
		window.setFramerateLimit(0);
	} else if (fps > 0) {
		window.setVerticalSyncEnabled(false);
		window.setFramerateLimit(static_cast<unsigned>(fps));
	}
}

void ForceSimulation::play() {
	paused = false;

	while (window.isOpen() && !paused) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			for (auto callback : on_event) {
				callback(event);
			}
		}

		update();
		display();
	}
}

void ForceSimulation::pause() {
	paused = true;
}

void ForceSimulation::append(const std::vector<Node> &nodes) {
	for (const auto &node : nodes) {
		auto node_entity = registry.emplace();

		registry.emplace<cp::Label>(node_entity, node.label);
		registry.emplace<cp::Mass>(node_entity, node.mass);
		registry.emplace<cp::Force>(node_entity);
		registry.emplace<cp::Position>(node_entity, sf::Vector2f{rdist(reng), rdist(reng)});
		registry.emplace<cp::LinksLabel>(node_entity, node.links);

		auto &shape = registry.emplace<sf::CircleShape>(node_entity);
		auto mass = static_cast<float>(node.mass);
		shape.setRadius(mass);
		shape.setOrigin(mass, mass);
		shape.setFillColor({54, 54, 54});
	}
}

void ForceSimulation::recalculate_connections() {
	registry.each<cp::LinksLabel>([this](auto entity, auto &labels) {
		cp::LinksEntity temp;

		registry.each<cp::Label>([&temp, &labels](auto id, auto &label) {
			if (std::find(labels.begin(), labels.end(), label) != labels.end()) {
				Arrow arrow;
				arrow.set_colour({60, 60, 60});
				arrow.thickness = 5.f;
				temp.push_back({id, arrow});
			}
		});

		if (!registry.all_of<cp::LinksEntity>(entity)) {
			registry.emplace<cp::LinksEntity>(entity, std::move(temp));
		} else {
			registry.get<cp::LinksEntity>(entity) = std::move(temp);
		}
	});
}

void ForceSimulation::update() {
	systems::calculate_forces(registry, 1.5f, 12000.f);
	systems::apply_forces(registry);
	systems::apply_positions(registry);
}

void ForceSimulation::display() {
	window.clear({247, 247, 247});

	// draw connectiosn
	registry.each<cp::LinksEntity, cp::Position>([this](auto, auto &connections, auto &) {
		for (auto &link : connections) {
			window.draw(link.connection);
		}
	});

	// draw nodes
	registry.each<sf::CircleShape, cp::Position>(
		[this](auto, auto &circle, auto &) { window.draw(circle); });

	window.display();
}

}  // namespace fg
