#include "NegativeEffect.h"
#include "Utils/ResourceManager/ResourceManager.h"
#include "Utils/JsonGlmHelpers.h"
#include "Utils/ImGuiHelper.h"

NegativeEffect::NegativeEffect() :
	PostProcessingLayer::Effect(),
	_shader(nullptr)
	// _Lowhealth(Whatever variable is called)(nullptr)
	//_Strength(1.0)
{
	Name = "Negative Effect";

	_format = RenderTargetType::ColorRgb8;

	_shader = ResourceManager::CreateAsset<ShaderProgram>(std::unordered_map<ShaderPartType, std::string>{
		{ ShaderPartType::Vertex, "shaders/vertex_shaders/fullscreen_quad.glsl" },
		{ ShaderPartType::Fragment, "shaders/fragment_shaders/post_effects/NegativeEffect.glsl" }
	});
}

NegativeEffect::~NegativeEffect() = default;

void NegativeEffect::Apply(const Framebuffer::Sptr & gBuffer)
{
	_shader->Bind();
	//_shader->SetUniform("u_Strength", _Strength
	//_shader->SetUniform("u_LowHealth", _LowHealth(Whatever variable is called));
}

void NegativeEffect::RenderImGui()
{

}

NegativeEffect::Sptr NegativeEffect::FromJson(const nlohmann::json & data)
{
	NegativeEffect::Sptr result = std::make_shared<NegativeEffect>();
	result->Enabled = JsonGet(data, "enabled", true);
	return result;
}

nlohmann::json NegativeEffect::ToJson() const
{
	return {
		{ "enabled", Enabled },
	};
}
