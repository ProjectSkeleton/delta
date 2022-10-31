#include <chrono>

#include <delta/delta.hh>
#include <glm/gtc/matrix_transform.hpp>

int main() {
  auto instance = Delta::CreateInstance();
  auto window = instance->CreateWindow();

  Delta::FrameBufferInfo frame_buffer_info;
  frame_buffer_info.width = 512;
  frame_buffer_info.height = 512;
  auto frame_buffer = instance->CreateFrameBuffer(frame_buffer_info);

  Delta::ShaderInfo shader_info;
  shader_info.spv_paths.vert_path = "spv/flat.vert.spv";
  shader_info.spv_paths.frag_path = "spv/flat.frag.spv";
  shader_info.render_target = window;
  auto shader = instance->CreateShader(shader_info);
  auto u_projection = shader->GetUniformBuffer("u_projection");
  auto u_model = shader->GetUniformBuffer("u_model");

  window->SetResizeCallback([&](unsigned int width, unsigned int height){
    u_projection->Upload(glm::perspectiveFov(1.57f, (float)width, (float)height, 0.1f, 1000.0f));
  });

  Delta::MeshInfo mesh_info;
  mesh_info.vertex_layout = shader->GetVertexInputLayout();
  mesh_info.vertices = {
  // x      y     z     u     v
    0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
   -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
   -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
  };
  mesh_info.indices = {
    0, 1, 3,
    1, 2, 3,
  };
  auto mesh = instance->CreateMesh(mesh_info);

  auto texture = instance->CreateTexture("res/pepper.png");
  auto u_diffuse_texture = shader->GetSampler2d("u_diffuse_texture");

  Delta::RenderPassInfo fb_render_pass_info;
  fb_render_pass_info.render_target = frame_buffer;
  fb_render_pass_info.on_begin = Delta::RenderPassBeginOp::kClear;
  fb_render_pass_info.clear_color = { 0.2f, 0.4f, 0.6f, 1.0f };
  fb_render_pass_info.on_complete = Delta::RenderPassCompleteOp::kPreserveExistingContents;
  auto fb_render_pass = instance->CreateRenderPass(fb_render_pass_info);
  fb_render_pass->RecordBindShaderCommand(shader);
  fb_render_pass->RecordRenderMeshCommand(mesh);

  Delta::RenderPassInfo window_render_pass_info;
  window_render_pass_info.render_target = window;
  window_render_pass_info.on_begin = Delta::RenderPassBeginOp::kClear;
  window_render_pass_info.clear_color = { 0.6f, 0.4f, 0.2f, 1.0f };
  window_render_pass_info.on_complete = Delta::RenderPassCompleteOp::kSwapchainPresent;
  auto window_render_pass = instance->CreateRenderPass(window_render_pass_info);
  window_render_pass->RecordBindShaderCommand(shader);
  window_render_pass->RecordRenderMeshCommand(mesh);

  glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);
  auto start_time = std::chrono::high_resolution_clock::now();

  while (window->IsOpen()) {
    window->PollEvents();
    auto current_time = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration<float, std::chrono::seconds::period>(current_time - start_time).count();
    pos.z = sin(time) - 1.5f;
    u_model->Upload(glm::translate(glm::mat4(1.0f), pos));
    u_diffuse_texture->SetTexture(texture);
    fb_render_pass->Execute();

    u_diffuse_texture->SetTexture(frame_buffer);
    window_render_pass->Execute();
  }
}
