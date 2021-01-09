
struct Mesh {
    GLuint  vbo;
    GLuint  ibo;
    GLuint  vao;
    GLsizei count;
    GLenum  mode; // e.g. GL_TRIANGLES
    bool is_two_sided; // aka. disable culling?
};

struct Height_Map {
    f32* data;
    f32 scale_x;
    f32 scale_y;
    int width;
    int height;
};

struct Texture {
    GLenum target; // e.g. GL_TEXTURE_2D
    GLuint handle;
};

struct Basic_2D_Shader {
    GLuint program;
    GLint u_color;
    GLint u_mvp_transform;
};

struct Basic_Shader {
    GLuint program;
    GLint u_color;
    GLint u_light_attenuation;
    GLint u_light_intensity;
    GLint u_mvp_transform;
};

struct Phong_Shader {
    GLuint program;
    GLint u_color;
    GLint u_diffuse;
    GLint u_specular;
    GLint u_shininess;

    GLint u_model_transform;
    GLint u_mvp_transform;

    GLint u_fog_color; // usually same as clear color
    GLint u_fog_density; // increase density -> more fog (shorter view distance)
    GLint u_fog_gradient; // increase gradient -> sharper transition

    struct {
        GLint u_pos;
        GLint u_view_pos;
        GLint u_ambient;
        GLint u_diffuse;
        GLint u_specular;
    } light_setup;
};

struct Sky_Shader {
    GLuint program;
    GLint u_map;
    GLint u_fog_color;
    GLint u_vp_transform;
};

struct Light_Setup {
    glm::vec3 pos;
    glm::vec3 view_pos;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

enum Material_Type {
    Material_Type_None,
    Material_Type_Basic,
    Material_Type_Phong,
    Material_Type_Sky,
};

struct Basic_Material {
    Basic_Shader* shader;
    glm::vec4 color;
};

struct Phong_Material {
    Phong_Shader* shader;
    glm::vec3 color;
    Texture* diffuse;
    Texture* specular;
    f32 shininess;
};

struct Sky_Material {
    Sky_Shader* shader;
    Texture* map;
};

struct Material {
    Material_Type type;
    union {
        Basic_Material Basic;
        Phong_Material Phong;
        Sky_Material Sky;
    };
};

struct Transform {
    glm::vec3 local_position;
    glm::quat local_rotation;
    glm::vec3 local_scale;
    glm::mat4 matrix; // cached transform calculation
    bool is_dirty; // does matrix need to be updated?
};

struct Camera_3D {
    f32 fov;
    f32 near;
    f32 far;
    f32 aspect_ratio;
    Transform transform;
    glm::mat4 perspective_matrix; // perspective * view (aka. camera transform)
    glm::mat4 combined_matrix; // perspective * view (or camera transform matrix)
    bool is_dirty; // does projection and combined matrix need to be updated?
};

struct Camera_2D {
    f32 offset_x;
    f32 offset_y;
    f32 x;
    f32 y;
    f32 zoom;
};

void begin_frame(const glm::vec4& clear_color, const glm::vec4& viewport, bool depth_testing=false);

void apply_basic_shader(Basic_Shader* shader, f32 light_intensity, f32 light_attenuation);

void apply_material(Material* material,
                           Light_Setup* light_setup=NULL,
                           glm::vec3 sky_color=glm::vec3(0.0f),
                           f32 fog_desnity=0.0f,
                           f32 fog_gradient=0.0f);

void draw_mesh(const Mesh& mesh,
               const Material& material,
               const glm::mat4& model_matrix,
               const glm::mat4& view_matrix,
               const glm::mat4& projection_matrix,
               const glm::mat4& view_proj_matrix);

void end_frame();

void initialize_camera_3d(Camera_3D* camera,
                          f32 fov=glm::radians(90.0f),
                          f32 near=0.1f,
                          f32 far=100000.0f,
                          f32 aspect_ratio=1.0f);


void initialize_transform(Transform* transform,
                          glm::vec3 pos=glm::vec3(0.0f),
                          glm::quat rot=glm::quat(glm::vec3(0.0f, 0.0f, 0.0f)),
                          glm::vec3 scale=glm::vec3(1.0f));
void update_transform(Transform* transform);

void update_camera_2d(Camera_2D* camera, Input* input);

Texture generate_white_2d_texture();
Texture load_texture_2d_from_file(const char* filepath,
                                  bool gen_mipmaps=true,
                                  f32 mipmap_bias=-0.8f,
                                  bool use_anisotropic_filtering=true, // requires gen_mipmaps=true
                                  f32 max_anisotropy=4.0f);
Texture create_texture_2d_from_data(void* data,
                                    int width,
                                    int height,
                                    bool hdr_texture=false,
                                    bool gen_mipmaps=true,
                                    f32 mipmap_bias=-0.8f,
                                    bool use_anisotropic_filtering=true, // requires gen_mipmaps=true
                                    f32 max_anisotropy=4.0f);
    
Basic_2D_Shader compile_basic_2d_shader();
Basic_Shader compile_basic_shader();
Phong_Shader compile_phong_shader();
