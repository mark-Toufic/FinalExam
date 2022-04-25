#pragma once
#include "Application/Layers/PostProcessingLayer.h"
#include "Graphics/ShaderProgram.h"
#include "Graphics/Textures/Texture1D.h"

class ToonShadingEffect : public PostProcessingLayer::Effect {
public:
	MAKE_PTRS(ToonShadingEffect);

	ToonShadingEffect();
	virtual ~ToonShadingEffect();

	virtual void Apply(const Framebuffer::Sptr& gBuffer) override;
	virtual void RenderImGui() override;

	ToonShadingEffect::Sptr FromJson(const nlohmann::json& data);
	virtual nlohmann::json ToJson() const override;

protected:
	ShaderProgram::Sptr _shader;
	Texture1D::Sptr		s_ToonTerm;


};


