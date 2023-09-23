$input v_texcoord0, v_normal, v_fragPosition

#include <bgfx_shader.sh>

SAMPLER2D(s_Diffuse, 0);
SAMPLER2D(s_Specular, 1);
//SAMPLER2D(s_Normal, 2);
//SAMPLER2D(s_Emission, 3);

uniform vec4 u_Material;
uniform vec4 u_ViewPosition;
uniform vec4 u_DirLight[4];

// We can make this smaller by putting specular into the w component of the 012 vectro4
#define DirLight_Direction u_DirLight[0].xyz
#define DirLight_Ambient u_DirLight[1].xyz
#define DirLight_Diffuse u_DirLight[2].xyz
#define DirLight_Specular u_DirLight[3].xyz

struct DirLight
{
    vec3 Direction;
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
};

struct Material
{
    vec3 Diffuse;
    vec3 Specular;
    //vec3 Normal;
    //vec3 Emission;
    float Shininess;
};

vec3 CalcDirectionalLighting(Material material, vec3 norm, vec3 viewDir);

void main()
{
    // Material
    Material material;
    material.Diffuse = texture2D(s_Diffuse, v_texcoord0).xyz;
    material.Specular = texture2D(s_Specular, v_texcoord0).xyz;
    //material.Normal = texture2D(s_Normal, v_texcoord0).xyz;
    //material.Emission = texture2D(s_Emission, v_texcoord0).xyz;
    material.Shininess = u_Material.x;

    // Pre-calc some properties
    vec3 norm = normalize(v_normal);
    vec3 viewDir = normalize(u_ViewPosition.xyz - v_fragPosition);
    // Add directional light
    vec3 result = CalcDirectionalLighting(material, norm, viewDir);

    gl_FragColor = vec4(result, 1.0);
}

vec3 CalcDirectionalLighting(Material material, vec3 norm, vec3 viewDir)
{
    // Ambient lighting
    vec3 ambient = DirLight_Ambient * material.Diffuse;

	// Diffuse lighting
    vec3 lightDir = normalize(-DirLight_Direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = DirLight_Diffuse * diff * material.Diffuse;


	// Specular lighting
    vec3 reflectDir = reflect(-lightDir, norm);  

    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(norm, halfwayDir), 0.0), material.Shininess);

    //float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.Shininess);
    vec3 specular = DirLight_Specular * spec * material.Specular;

    return ambient + diffuse + specular;
}