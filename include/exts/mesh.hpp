#ifndef MESH_HPP
#define MESH_HPP

#include "../vk_api/wrapper.hpp"
#include "../third_party/ass.hpp"
#include "../third_party/glms.hpp"
#include "../as/utils.hpp"
#include "module/module.hpp"

namespace as
{
    struct Vertex
    {
        glm::vec3 positon_{};
        glm::vec3 normal_{};
        glm::vec3 uv_{};
        glm::vec3 color_{1.0f, 1.0f, 1.0f};
    };

    class VertexBuffer
    {
      private:
        VirtualObj<Buffer> buffer_;
        std::vector<Vertex> vertices_{};

      public:
        size_t offset_ = 0;

        VertexBuffer(VirtualObj<Buffer> buffer, aiMesh* mesh);
        ~VertexBuffer();
    };

    class IndexBuffer
    {
      private:
        VirtualObj<Buffer> buffer_;
        std::vector<uint32_t> indices_{};

      public:
        size_t offset_ = 0;

        IndexBuffer(VirtualObj<Buffer> buffer, aiMesh* mesh);
        ~IndexBuffer();
    };

    class InstanceMatrics
    {
      private:
        UniqueObj<Buffer> buffer_{nullptr};

      public:
        std::vector<glm::mat4> matrics_{};

        InstanceMatrics(RenderModule& render);
        ~InstanceMatrics();
    };
}; // namespace as

#endif // MESH_HPP
