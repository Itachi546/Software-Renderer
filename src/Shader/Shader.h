#include "../Math/Math.h"

struct Light{
  vec3 position;
};
class Shader{

 private:
  Light light;
  vec3 cameraPos;
 public:
  void set_uniforms(vec3 lightpos, vec3 cameraPos){
    this->light.position = lightpos;
    this->cameraPos = cameraPos;
  }
  
  vec3 vertex_lighting(Vertex3d v0, vec3 normal){
    /*

	vec3 lightDir = normalize(light.position - vertex_position);	
	
	float diffuseFactor = dot(normal, lightDir);
	diffuseFactor = max(diffuseFactor, 0.0f);

	float dist = length(light.position - vertex_position);
	float attenuation = 1/(light.attenuation.x + dist * light.attenuation.y  + dist * dist * light.attenuation.z) * light.intensity;

	vec3 viewDir = normalize(camera_position - vertex_position);
	vec3 halfwayVector = normalize(lightDir + viewDir);

	float specularFactor = max(dot(normal, halfwayVector), 0.0f);
	specularFactor = pow(specularFactor, light.shininess);

	vec3 ambientColor = 0.1 * light.color * attenuation;
	vec3 diffuseColor = diffuseFactor *  attenuation * light.color;
	vec3 specularColor = specularFactor * light.color *   attenuation;


	return (ambientColor + diffuseColor + specularColor);

     */
    normal = vec3::normalize(normal);
    vec3 lightDir = vec3::normalize(light.position - v0.position);
    float diffuse = vec3::dot(normal, lightDir);
    diffuse = std::max(diffuse, 0.1f);
    
    vec3 viewDir = vec3::normalize(cameraPos - v0.position);
    vec3 halfwayVector = vec3::normalize(viewDir + lightDir);
    float specular = std::max(vec3::dot(normal, halfwayVector), 0.0f);
    specular = std::pow(specular, 32.0f);

    float totalColor = std::min(diffuse + specular, 1.0f);

    vec3 result =  vec3(0, 255, 255) * totalColor;
    
    result.x = std::min(result.x, 255.0f);
    result.y = std::min(result.y, 255.0f);
    result.z = std::min(result.z, 255.0f);
      
    return result;

  }
  
};
