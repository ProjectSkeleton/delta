#include <chrono>

#include <delta/delta.hh>
#include <glm/gtc/matrix_transform.hpp>

int main() {
  auto instance = Delta::CreateInstance();

  Delta::WindowCreateInfo window_info;
  window_info.clear_color = { 0.2f, 0.4f, 0.6f, 1.0f };
  auto window = instance->CreateWindow(window_info);

  Delta::ShaderCreateInfo shader_info;
  shader_info.spv_paths.vert_path = "spv/flat.vert.spv";
  shader_info.spv_paths.frag_path = "spv/flat.frag.spv";
  shader_info.render_target = window;
  auto shader = instance->CreateShader(shader_info);
  auto u_projection = shader->GetUniformBuffer("u_projection");
  auto u_model = shader->GetUniformBuffer("u_model");

  window->SetResizeCallback([&](unsigned int width, unsigned int height){
    u_projection->Upload(glm::perspectiveFov(1.57f, (float)width, (float)height, 0.1f, 1000.0f));
  });

  Delta::MeshCreateInfo mesh_info;
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

  auto test_texture = instance->CreateTexture("res/test.png");
  shader->GetSampler2d("u_test_texture")->SetTexture(test_texture);
  auto pepper_texture = instance->CreateTexture("res/pepper.png");
  shader->GetSampler2d("u_pepper_texture")->SetTexture(pepper_texture);

  auto render_pass = instance->CreateRenderPass(window);
  render_pass->RecordBindShaderCommand(shader);
  render_pass->RecordRenderMeshCommand(mesh);

  glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);
  auto start_time = std::chrono::high_resolution_clock::now();

  while (window->IsOpen()) {
    window->PollEvents();
    auto current_time = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration<float, std::chrono::seconds::period>(current_time - start_time).count();
    pos.z = sin(time) - 1.5f;
    u_model->Upload(glm::translate(glm::mat4(1.0f), pos));
    render_pass->Execute();
  }
}
