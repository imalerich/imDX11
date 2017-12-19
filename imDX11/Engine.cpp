#include "Engine.h"

Engine::Engine() {
	test = std::make_unique<Model>("Models/monkey.obj");
}

void Engine::Release() {
	test->Release();
}

void Engine::UpdateScene() {
	UpdateCamera();
}

void Engine::DrawScene() {
	ClearContext();
	test->Draw();
	SwapChain->Present(0, 0);
}

void Engine::UpdateCamera() {
	glm::vec3 campos(0.0f, 0.0f, -0.5f);
	glm::vec3 camtarget(0.0f, 0.0f, 0.0f);
	glm::vec3 camup(0.0f, 1.0f, 0.0f);

	static float theta = 0.0f;
	theta += 0.00005f;

	glm::mat4 proj = glm::perspective(glm::radians(75.0f),
		(float)SCREEN_W / (float)SCREEN_H, 0.1f, 100.0f);
	glm::mat4 view = glm::lookAt(campos, camtarget, camup);
	glm::mat4 world = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 3.0f))
		* glm::rotate(glm::mat4(), theta, glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 WVP = proj * view * world;

	cbPerObj.WVP = glm::transpose(WVP);
	cbPerObj.IW = glm::inverse(world);
	context->UpdateSubresource(cbPerObjectBuffer, 0, NULL, &cbPerObj, 0, 0);
	context->VSSetConstantBuffers(0, 1, &cbPerObjectBuffer);
}