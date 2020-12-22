

inline void
push_quad(Mesh_Builder* mb, const Vertex& v0, Vertex v1, Vertex v2, Vertex v3) {
    assert(mb->vertices.size() < 65536 && "running out of indices");
    u16 base_index = (u16) mb->vertices.size();
    mb->vertices.push_back(v0);
    mb->vertices.push_back(v1);
    mb->vertices.push_back(v2);
    mb->vertices.push_back(v3);
    mb->indices.push_back(base_index);
    mb->indices.push_back(base_index + 1);
    mb->indices.push_back(base_index + 2);
    mb->indices.push_back(base_index);
    mb->indices.push_back(base_index + 2);
    mb->indices.push_back(base_index + 3);
}

inline void
push_quad(Mesh_Builder* mb,
           glm::vec3 p1, glm::vec2 t1, glm::vec3 n1,
           glm::vec3 p2, glm::vec2 t2, glm::vec3 n2,
           glm::vec3 p3, glm::vec2 t3, glm::vec3 n3,
           glm::vec3 p4, glm::vec2 t4, glm::vec3 n4) {
    push_quad(mb, {p1, t1, n1}, {p2, t2, n2}, {p3, t3, n3}, {p4, t4, n4});
}

void
push_cuboid_mesh(Mesh_Builder* mb, glm::vec3 c, glm::vec3 d) {
    d.x /= 2.0f; d.y /= 2.0f; d.z /= 2.0f;
    
    mb->vertices.reserve(4*6);
    mb->indices.reserve(6*6);
    
    // Front
    push_quad(mb,
              glm::vec3(c.x - d.x, c.y - d.y, c.z - d.z), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f),
              glm::vec3(c.x + d.x, c.y - d.y, c.z - d.z), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f),
              glm::vec3(c.x + d.x, c.y + d.y, c.z - d.z), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f),
              glm::vec3(c.x - d.x, c.y + d.y, c.z - d.z), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f));

    // Back
    push_quad(mb,
              glm::vec3(c.x - d.x, c.y - d.y, c.z + d.z), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f),
              glm::vec3(c.x - d.x, c.y + d.y, c.z + d.z), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f),
              glm::vec3(c.x + d.x, c.y + d.y, c.z + d.z), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f),
              glm::vec3(c.x + d.x, c.y - d.y, c.z + d.z), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    // Left
    push_quad(mb,
              glm::vec3(c.x - d.x, c.y - d.y, c.z - d.z), glm::vec2(0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f),
              glm::vec3(c.x - d.x, c.y + d.y, c.z - d.z), glm::vec2(1.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f),
              glm::vec3(c.x - d.x, c.y + d.y, c.z + d.z), glm::vec2(1.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f),
              glm::vec3(c.x - d.x, c.y - d.y, c.z + d.z), glm::vec2(0.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
    
    // Right
    push_quad(mb,
              glm::vec3(c.x + d.x, c.y - d.y, c.z - d.z), glm::vec2(0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f),
              glm::vec3(c.x + d.x, c.y - d.y, c.z + d.z), glm::vec2(1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f),
              glm::vec3(c.x + d.x, c.y + d.y, c.z + d.z), glm::vec2(1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f),
              glm::vec3(c.x + d.x, c.y + d.y, c.z - d.z), glm::vec2(0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                                
    // Top
    push_quad(mb,
              glm::vec3(c.x - d.x, c.y + d.y, c.z - d.z), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),
              glm::vec3(c.x + d.x, c.y + d.y, c.z - d.z), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),
              glm::vec3(c.x + d.x, c.y + d.y, c.z + d.z), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
              glm::vec3(c.x - d.x, c.y + d.y, c.z + d.z), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
               

    // Bottom
    push_quad(mb,
              glm::vec3(c.x - d.x, c.y - d.y, c.z - d.z), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f),
              glm::vec3(c.x - d.x, c.y - d.y, c.z + d.z), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f),
              glm::vec3(c.x + d.x, c.y - d.y, c.z + d.z), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f),
              glm::vec3(c.x + d.x, c.y - d.y, c.z - d.z), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f));
}

void
push_sphere(Mesh_Builder* mb, glm::vec3 c, f32 r, int detail_x=32, int detail_y=32) {
    printf("mb->vertices.size() = %zu\n", mb->vertices.size());
    // detail_x *= 2;
    for (int j = 0; j <= detail_y; j++) {
        for (int i = 0; i < detail_x; i++) {
            f32 phi   = glm::pi<f32>()*1.0f*((f32)j/(f32)detail_y) + glm::pi<f32>()/2.0f;
            f32 theta = glm::pi<f32>()*2.0f*((f32)i/(f32)detail_x);

            printf("phi = %f\n", phi);
            printf("theta = %f\n", theta);
            
            glm::vec3 normal = glm::normalize(glm::vec3(sin(theta)*cos(phi), cos(theta)*cos(phi), sin(phi)));
            glm::vec2 texcoord(0.0f); // TODO(alexander): wrap texcoords on sphere
            glm::vec3 pos = normal*r + c;

            Vertex v = { pos, texcoord, normal };

            mb->vertices.push_back(v);
            if (j != 0) {
                mb->indices.push_back(detail_x*(j - 0) + i);
                printf("index[%zu] = %u\n", mb->indices.size() - 1, mb->indices[mb->indices.size() - 1]);
                
                mb->indices.push_back(detail_x*(j - 1) + i);
                printf("index[%zu] = %u\n", mb->indices.size() - 1, mb->indices[mb->indices.size() - 1]);
             
            }
            
        }
        if (j != 0) {
            mb->indices.push_back(detail_x*(j - 0));
            mb->indices.push_back(detail_x*(j - 1));
        }
    }
}