#pragma once
#include "Engine/Core/Core.h"

#include "Engine/math/vec4.h"
#include "Engine/math/vec3.h"

namespace BIGOS {

	__declspec(align(16))
		struct PhongLight
	{
		math::vec4 Ambient;
		math::vec4 Diffuse;
		math::vec4 Specular;

		math::vec3 Direction;

		PhongLight()
		{

		}

		PhongLight(const math::vec4& ambient, const math::vec4& diffuse, const math::vec4& specular, const math::vec3& direction)
			: Ambient(ambient), Diffuse(diffuse), Specular(specular), Direction(direction) {}
	};


	__declspec(align(16)) 
	struct Light
	{
		math::vec4 Color;
		math::vec3 Position;
		math::vec3 Direction;
		//float Intensity;

		Light()
		{

		}

		Light(const math::vec3& position, const math::vec4& color)
			: Position(position), Color(color) {}
	};

	class LightManager
	{
	public:
		~LightManager();

		static void AddLight(Light light);
		static void AddLight(const math::vec3& position, const math::vec4& color);

		uint32_t GetCount() const { return 4; }
		Light GetLightByIndex(size_t index) const { return s_Lights[index]; }
		static std::vector<Light> GetLights() { return s_Lights; }
		static Light* GetLightsPtr() { return s_Lights.data(); }

		static std::unique_ptr<LightManager> Create();
	private:
		static std::vector<Light> s_Lights;
	};
	
}