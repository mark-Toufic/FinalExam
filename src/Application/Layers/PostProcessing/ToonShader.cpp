#include "ToonShader.h"
#include "Utils/ResourceManager/ResourceManager.h"
#include "Utils/JsonGlmHelpers.h"
#include "Utils/ImGuiHelper.h"

ToonShadingEffect::ToonShadingEffect() :
	PostProcessingLayer::Effect(),
	_shader(nullptr),
	s_ToonTerm(nullptr)
{
	Name = "ToonShader";

	_format = RenderTargetType::ColorRgb8;

	_shader = ResourceManager::CreateAsset<ShaderProgram>(std::unordered_map<ShaderPartType, std::string>{
		{ ShaderPartType::Vertex, "shaders/vertex_shaders/fullscreen_quad.glsl" },
		{ ShaderPartType::Fragment, "shaders/fragment_shaders/post_effects/ToonShader.glsl" }
	});
	s_ToonTerm = ResourceManager::CreateAsset<Texture1D>("luts/toon-1D.png");
	s_ToonTerm->SetWrap(WrapMode::ClampToEdge);
}

ToonShadingEffect::~ToonShadingEffect() = default;

void ToonShadingEffect::Apply(const Framebuffer::Sptr & gBuffer)
{
	_shader->Bind();
	s_ToonTerm->Bind(1);
}

void ToonShadingEffect::RenderImGui()
{

}

ToonShadingEffect::Sptr ToonShadingEffect::FromJson(const nlohmann::json & data)
{
	ToonShadingEffect::Sptr result = std::make_shared<ToonShadingEffect>();
	result->Enabled = JsonGet(data, "enabled", true);
	return result;
}

nlohmann::json ToonShadingEffect::ToJson() const
{
	return {
		{ "enabled", Enabled },
	};
}
