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
	 * @param[in]  interval  The interval between ticks. Defaults to 30 times a second.
	 */
	void set_tick_rate(float interval = 1.f / 30.f);

	/**
	 * @brief      Start the simulation.
	 *
	 * This can be interrupted either by the user closing the window, or by calling @ref pause from
	 * inside the event callback (@ref on_event).
	 */
	void play();

	/**
	 * @brief      Pause the simulation.
	 *
	 * This stops @ref play from blocking, and returns control back to the user. This can then be
	 * resumed again using the same @ref play method.
	 */
	void pause();

	//////////////////// Listeners ////////////////////

	/**
	 * @brief      Called when a window event is received.
	 *
	 * You can use this to listen for events and act accordingly. For example,
	 * @code
	 * fs.on_event.push_back([&](sf::Event event) {
	 *     fs.append(node);
	 *     fs.recalculate_connections();
	 * });
	 * @endcode
	 */
	std::vector<std::function<void(sf::Event)>> on_event;

	//////////////////// Data ////////////////////

	/**
	 * @brief      Append nodes to the simulation.
	 *
	 * These nodes are appended alongside the ones that already exist in the simulation. After
	 * calling this method, you should call @ref recalculate_connections.
	 *
	 * @param[in]  nodes  The nodes to append.
	 */
	void append(const std::vector<Node> &nodes = {});

	/**
	 * @brief      Recalculate the connections between different nodes.
	 *
	 * This makes sure the links between nodes are up to date.
	 *
	 * This should be called after you @ref append nodes. This is not called automatically, to allow
	 * you to append multiple nodes sequentially, without increasing overhead.
	 */
	void recalculate_connections();

private:
	void update();

	stch::Scene registry;

	sf::RenderWindow window;
	sf::Clock clock;
	float zoom;

	sf::Vector2i last_mouse_position;

	float tick_rate;
	float accumulator;

	bool paused;

	std::random_device rdev;
	std::default_random_engine reng;
	std::uniform_real_distribution<float> rdist;
};

/**
 * @class fg::ForceSimulation
 * @ingroup ForceSimulation
 *
 * This will be the main class you will be interacting with while using this library.
 *
 * It is responsible for storing all of your nodes, and simulating their movement and interactions
 * with the user.
 *
 * @example Collatz.cpp
 */

};	// namespace fg
