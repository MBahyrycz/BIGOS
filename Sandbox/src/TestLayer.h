#pragma once

#include <BIGOS.h>

class TestLayer : public BIGOS::Layer
{
public:
	TestLayer();
	virtual ~TestLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(BIGOS::Utils::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(BIGOS::Event& e) override;

	bool OnKeyPressed(BIGOS::KeyPressedEvent& e);
private:
	BIGOS::math::vec4 m_ClearColor = { 0.1f, 0.1f, 0.1f, 1.0f };

	std::shared_ptr<BIGOS::Shader> m_Shader;
	std::shared_ptr<BIGOS::VertexBuffer> m_VertexBuffer;
};