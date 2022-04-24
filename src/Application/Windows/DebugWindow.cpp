#include "DebugWindow.h"
#include "Application/Application.h"
#include "Application/ApplicationLayer.h"
#include "Application/Layers/RenderLayer.h"

DebugWindow::DebugWindow() :
	IEditorWindow()
{
	Name = "Debug";
	SplitDirection = ImGuiDir_::ImGuiDir_None;
	SplitDepth = 0.5f;
	Requirements = EditorWindowRequirements::Menubar;
}

DebugWindow::~DebugWindow() = default;

void DebugWindow::RenderMenuBar() 
{
	Application& app = Application::Get();
	RenderLayer::Sptr renderLayer = app.GetLayer<RenderLayer>(); 

	BulletDebugMode physicsDrawMode = app.CurrentScene()->GetPhysicsDebugDrawMode();
	if (BulletDebugDraw::DrawModeGui("Physics Debug Mode:", physicsDrawMode)) { 
		app.CurrentScene()->SetPhysicsDebugDrawMode(physicsDrawMode);
	}
	// for specular
	RenderFlags flags = renderLayer->GetRenderFlags();
	bool changed = false;
	bool temp = *(flags & RenderFlags::EnableSpecular);
	if (ImGui::Checkbox("Enable Specular Only", &temp)) {
		changed = true;
		flags = (flags & ~*RenderFlags::EnableSpecular) | (temp ? RenderFlags::EnableSpecular : RenderFlags::None);
	}
	
	if (changed) {
		renderLayer->SetRenderFlags(flags);
	}

	//ImGui::Separator();
	// for diffuse
	RenderFlags flags2 = renderLayer->GetRenderFlags();
	bool changed2 = false;
	bool temp2 = *(flags2 & RenderFlags::EnableDiffuse);
	if (ImGui::Checkbox("Enable Diffuse Only", &temp2)) {
		changed2 = true;
		flags2 = (flags2 & ~*RenderFlags::EnableDiffuse) | (temp2 ? RenderFlags::EnableDiffuse : RenderFlags::None);
	}

	if (changed2) {
		renderLayer->SetRenderFlags(flags2);
	}

	// for ambient
	RenderFlags flags3 = renderLayer->GetRenderFlags();
	bool changed3 = false;
	bool temp3 = *(flags3 & RenderFlags::EnableAmbient);
	if (ImGui::Checkbox("Enable Ambient Only", &temp3)) {
		changed3 = true;
		flags3 = (flags3 & ~*RenderFlags::EnableAmbient) | (temp3 ? RenderFlags::EnableAmbient : RenderFlags::None);
	}

	if (changed3) {
		renderLayer->SetRenderFlags(flags3);
	}
	/*
	// for no lighting
	RenderFlags flags4 = renderLayer->GetRenderFlags();
	bool changed4 = false;
	bool temp4 = *(flags4 & RenderFlags::EnableNoLight);
	if (ImGui::Checkbox("Disable Lighting", &temp4)) {
		changed4 = true;
		flags4 = (flags4 & ~*RenderFlags::EnableNoLight) | (temp4 ? RenderFlags::EnableNoLight : RenderFlags::None);
	}

	if (changed4) {
		renderLayer->SetRenderFlags(flags4);
	}
	*/
	/*ImGui::Separator();

	RenderFlags flags = renderLayer->GetRenderFlags();
	bool changed = false;
	bool temp = *(flags & RenderFlags::EnableColorCorrection);
	if (ImGui::Checkbox("Enable Color Correction", &temp)) {
		changed = true;
		flags = (flags & ~*RenderFlags::EnableColorCorrection) | (temp ? RenderFlags::EnableColorCorrection : RenderFlags::None);
	}

	if (changed) {
		renderLayer->SetRenderFlags(flags);
	}*/
}
