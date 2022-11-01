#include <delta/delta.hh>
#include <glm/gtc/matrix_transform.hpp>

int main() {
  auto instance = Delta::CreateInstance();
  auto window = instance->CreateWindow();

  Delta::TextureInfo pepper_texture_info;
  pepper_texture_info.filter = Delta::TextureFilter::kNearest;
  pepper_texture_info.path = "res/pepper.png";
  auto pepper_texture = instance->CreateTexture(pepper_texture_info);

  auto frame_buffer = instance->CreateFrameBuffer();

  Delta::ShaderInfo entity_shader_info;
  entity_shader_info.render_target = frame_buffer;
  entity_shader_info.spv_paths.vert_path = "spv/entity.vert.spv";
  entity_shader_info.spv_paths.frag_path = "spv/entity.frag.spv";
  auto entity_shader = instance->CreateShader(entity_shader_info);
  auto u_projection = entity_shader->GetUniformBuffer("u_projection");
  auto u_model = entity_shader->GetUniformBuffer("u_model");
  entity_shader->GetSampler2d("u_diffuse_texture")->SetTexture(pepper_texture);

  Delta::ShaderInfo final_shader_info;
  final_shader_info.render_target = window;
  final_shader_info.spv_paths.vert_path = "spv/final.vert.spv";
  final_shader_info.spv_paths.frag_path = "spv/final.frag.spv";
  auto final_shader = instance->CreateShader(final_shader_info);
  final_shader->GetSampler2d("u_frame_buffer_texture")->SetTexture(frame_buffer);
 
  Delta::MeshInfo viewport_mesh_info;
  viewport_mesh_info.vertex_layout = final_shader->GetVertexInputLayout();
  viewport_mesh_info.vertices = {
  // x      y     z     u     v
    1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
    1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
   -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
   -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
  };
  viewport_mesh_info.indices = {
    0, 1, 3,
    1, 2, 3,
  };
  auto viewport_mesh = instance->CreateMesh(viewport_mesh_info);

  Delta::RenderPassInfo scene_render_pass_info;
  scene_render_pass_info.render_target = frame_buffer;
  scene_render_pass_info.clear_color = { 0.6f, 0.4f, 0.2f, 1.0f };
  scene_render_pass_info.on_begin = Delta::RenderPassBeginOp::kClear;
  scene_render_pass_info.on_complete = Delta::RenderPassCompleteOp::kPreserveExistingContents;
  auto scene_render_pass = instance->CreateRenderPass(scene_render_pass_info);
  scene_render_pass->RecordBindShaderCommand(entity_shader);
  scene_render_pass->RecordRenderMeshCommand(viewport_mesh);

  Delta::RenderPassInfo final_render_pass_info;
  final_render_pass_info.render_target = window;
  final_render_pass_info.enable_depth_test = false;
  final_render_pass_info.on_begin = Delta::RenderPassBeginOp::kDontCare;
  final_render_pass_info.on_complete = Delta::RenderPassCompleteOp::kSwapchainPresent;
  auto final_render_pass = instance->CreateRenderPass(final_render_pass_info);
  final_render_pass->RecordBindShaderCommand(final_shader);
  final_render_pass->RecordRenderMeshCommand(viewport_mesh);

  u_model->Upload(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -1.5f)));
  window->SetResizeCallback([&](unsigned int width, unsigned int height) {
    u_projection->Upload(glm::perspectiveFov(1.57f, (float)width, (float)height, 0.1f, 1000.0f));
    frame_buffer->Resize(width, height);
  });

  while (window->IsOpen()) {
    window->PollEvents();
    scene_render_pass->Execute();
    final_render_pass->Execute();
  }
}
