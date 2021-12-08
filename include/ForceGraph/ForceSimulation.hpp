// SPDX-FileCopyrightText: 2021 metaquarx <metaquarx@protonmail.com>
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "ForceGraph/Node.hpp"

#include "SFML/Graphics.hpp"
#include "Stitch/Scene.hpp"

#include <functional>
#include <random>

namespace fg {

/**
 * @brief      Class that represents a force directed graph simulation.
 */
class ForceSimulation {
public:
	//////////////////// Meta ////////////////////

	/**
	 * @brief      Create a new simulation window
	 *
	 * @param[in]  title  The title of the created window.
	 *
	 * The size of the generated window defaults to half the size of user's monitor.
	 */
	ForceSimulation(const std::string &title = "Force Graph");

	/**
	 * @brief      Change the title of the window.
	 *
	 * @param[in]  title  The new title
	 */
	void set_title(const std::string &title);

	/**
	 * @brief      Set the graphics framerate of the window
	 *
	 * @param[in]  fps   The FPS value. If this is 0, the framerate is uncapped. If it is a negative
	 * value, vsync is enabled (default).
	 */
	void set_framerate(int fps);

	//////////////////// SIMULATION ////////////////////

	/**
	 * @brief      Set the tick rate of the internal physics engine.
	 *
	 * @param[in]  interval  The interval between ticks. Defaults to 20 times a second.
	 */
	void set_tick_rate(float interval = 1.f / 20.f);

	/**
	 * @brief      Start the simulation.
	 *
	 * This can be interrupted either by the user closing the window, or by calling `pause()` from
	 * inside the event callback (`on_event()`).
	 */
	void play();

	/**
	 * @brief      Pause the simulation.
	 *
	 * This stops `play()` from blocking, and returns control back to the user.
	 */
	void pause();

	//////////////////// Listeners ////////////////////

	/**
	 * @brief      Called when a window event is received.
	 */
	std::vector<std::function<void(sf::Event)>> on_event;

	//////////////////// Data ////////////////////

	/**
	 * @brief      Append nodes to the simulation.
	 *
	 * @param[in]  nodes  The nodes to append.
	 */
	void append(const std::vector<Node> &nodes = {});

	/**
	 * @brief      Recalculate the connections between different nodes.
	 *
	 * This should be called after `append()`ing nodes, though it is not called automatically incase
	 * you choose to append nodes through multiple append calls.
	 */
	void recalculate_connections();

private:
	void update();
	void display();

	stch::Scene registry;

	sf::RenderWindow window;
	sf::View center;
	sf::View normal;

	float tick_rate;
	bool paused;

	std::random_device rdev;
	std::default_random_engine reng;
	std::uniform_real_distribution<float> rdist;
};

/**
 * @example Collatz.cpp
 */

};	// namespace fg
