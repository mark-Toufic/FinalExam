#pragma once
#include "Application/Layers/PostProcessingLayer.h"
#include "Graphics/ShaderProgram.h"
#include "Graphics/Textures/Texture3D.h"
//#include "Components/(where ever our character health is at).h

class NegativeEffect : public PostProcessingLayer::Effect {
public:
	MAKE_PTRS(NegativeEffect);
	//Texture3D::Sptr Lut;

	NegativeEffect();
	virtual ~NegativeEffect();

	virtual void Apply(const Framebuffer::Sptr& gBuffer) override;
	virtual void RenderImGui() override;

	NegativeEffect::Sptr FromJson(const nlohmann::json& data);
	virtual nlohmann::json ToJson() const override;

protected:
	ShaderProgram::Sptr _shader;
	//float _Strength;
	//(Where ever our character health is at)::Sptr _CharacterOBJ;


};
