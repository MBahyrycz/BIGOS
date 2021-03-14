#include "TestLayer.h"
#include <memory>
#include "DemoMaterials.h"

#include <imgui/imgui.h>

__declspec(align(16))
struct PFConstantBufferData
{
	BIGOS::math::vec3 u_CameraPosition;
	BIGOS::Light u_Light;
};

__declspec(align(16))
struct POConstantBufferData
{
	BIGOS::math::mat4 u_Transform;
	BIGOS::math::mat4 u_ViewProj;
	BIGOS::Material u_Material;
};

TestLayer::TestLayer()
	: Layer("TestLayer")
{
}

void TestLayer::OnAttach()
{
	m_Shader = BIGOS::Shader::Create("assets/shaders/color.hlsl");
	m_Shader->Bind();

	m_Texture = BIGOS::Texture2D::Create("assets/textures/bricks.png");
	m_WhiteTexture = BIGOS::Texture2D::Create("assets/textures/white.png");

	m_GridMesh = BIGOS::MeshGenerator::CreateGrid(3.0f, 3.0f, 2, 2);
	m_CubeMesh = BIGOS::MeshGenerator::CreateBox({ 1.0f, 1.0f, 1.0f });
	//m_Cube = BIGOS::MeshGenerator::CreateSmoothCube(1.0f);
	//m_Cube = BIGOS::MeshGenerator::CreateSphere(1.0f, 32, 10);
	
	m_CBPerObject = BIGOS::ConstantBuffer::Create(sizeof(POConstantBufferData));
	m_CBPerFrame = BIGOS::ConstantBuffer::Create(sizeof(PFConstantBufferData));

	m_EditorCamera = BIGOS::EditorCamera(45.0f, 1.778f, 0.1f, 1000.0f);

	m_Light = new BIGOS::Light(BIGOS::math::vec4(0.2f), BIGOS::math::vec4(0.5f), BIGOS::math::vec4(1.0f), BIGOS::math::vec3(-0.2f, -0.3f, -1.0f));

	m_Materials = materialPallete;
}

void TestLayer::OnDetach()
{
	delete m_GridMesh;
	delete m_CubeMesh;
	delete m_Light;
}

void TestLayer::OnUpdate(BIGOS::Utils::Timestep ts)
{
	// Resize
	uint32_t width = BIGOS::Application::Get().GetWindow()->GetWidth();
	uint32_t height = BIGOS::Application::Get().GetWindow()->GetHeight();
	m_EditorCamera.SetViewportSize(width, height);

	//Clearing 
	BIGOS::RenderCommand::SetClearColor(m_ClearColor);
	BIGOS::RenderCommand::Clear();

	// Input
	// Editor cammera controlls movement
	m_EditorCamera.OnUpdate(ts);


	// Scene update
	PFConstantBufferData cbPerFrame;
	cbPerFrame.u_CameraPosition = m_EditorCamera.GetPosition();
	cbPerFrame.u_Light = *m_Light;
	m_CBPerFrame->SetData(&cbPerFrame, sizeof(cbPerFrame));
	m_CBPerFrame->Bind(0);

	POConstantBufferData cbPerObject;

	BIGOS::math::mat4 tempTrans = BIGOS::math::mat4::Translate(m_WallPosition);
	BIGOS::math::mat4 tempRot = BIGOS::math::mat4::Rotate(90.0f, { 1, 0, 0 });
	BIGOS::math::mat4 tempScale = BIGOS::math::mat4::Scale({ 5.0f, 5.0f, 5.0f });

	cbPerObject.u_Transform = tempTrans * tempRot * tempScale;
	cbPerObject.u_ViewProj = m_EditorCamera.GetViewProjection();
	cbPerObject.u_Material = m_Materials[4];
	m_CBPerObject->SetData(&cbPerObject, sizeof(cbPerObject));
	m_CBPerObject->Bind(1); // param is register
	m_Texture->Bind();
	m_GridMesh->Render();

	m_WhiteTexture->Bind();

	size_t matIndex = 0;
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			BIGOS::math::mat4 tempTrans = BIGOS::math::mat4::Translate({ -3.0f + 2 * j, 3.0f - 2 * i, 0.0f });
			BIGOS::math::mat4 tempRot = BIGOS::math::mat4::Rotate(m_Rotation, { 0, 1, 0 });
			BIGOS::math::mat4 tempScale = BIGOS::math::mat4::Scale({ 1.2f, 1.2f, 1.2f });

			cbPerObject.u_Transform = tempTrans * tempRot * tempScale;
			cbPerObject.u_ViewProj = m_EditorCamera.GetViewProjection();
			cbPerObject.u_Material = m_Materials[matIndex];
			m_CBPerObject->SetData(&cbPerObject, sizeof(cbPerObject));
			m_CBPerObject->Bind(1); // param is register

			m_CubeMesh->Render();
			matIndex++;
		}
	}



	m_Rotation += ts/50.0f;
}

void TestLayer::OnImGuiRender()
{
	static bool show_demo_window = true;
	ImGui::ShowDemoWindow(&show_demo_window);

	ImGui::Begin("Test");
	ImGui::Text("Hello World");
	ImGui::DragFloat3("Wall position", m_WallPosition.ptr());
	ImGui::End();
}

void TestLayer::OnEvent(BIGOS::Event& e)
{
	//BGS_TRACE(e.ToString());
	m_EditorCamera.OnEvent(e);

	BIGOS::EventManager manager(e);
	manager.Dispatch<BIGOS::KeyPressedEvent>(BGS_BIND_EVENT_FN(TestLayer::OnKeyPressed));
}

bool TestLayer::OnKeyPressed(BIGOS::KeyPressedEvent& e)
{
	if (BIGOS::Input::IsKeyPressed(BIGOS::Key::Escape))
		BIGOS::Application::Get().Close();
		
	return true;
}
