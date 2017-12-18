#pragma once

#include <memory>

#include "d3dutil.h"
#include "Model.h"

class Engine {
public:
	Engine();

	/**
	 * Update data corresponding to the current scene,
	 * stepping the game simulation forward one step
	 * using the time delta since the last call.
	 */
	void UpdateScene();

	/**
	 * Renders all data associated with the current display
	 * to the active DX11 context.
	 */
	void DrawScene();

	/**
	 * Releases all data and buffers loaded by this class.
	 */
	void Release();

private:
	/**
	 * Updates the camera's world/view/projection matrices 
	 * and sets corresponding to data to be loaded into
	 * the vertex shaders.
	 */
	void UpdateCamera();

	std::unique_ptr<Model> test;
};