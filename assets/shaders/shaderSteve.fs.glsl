#version 330 core
out vec4 FragColor;
in vec3 Normal;
in vec2 TexCoords;
in vec3 crtPos;
uniform sampler2D texture_diffuse1;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;


vec4 pointLight()
{
   // used in two variables so I calculate it here to not have to do it twice
   vec3 lightVec = lightPos - crtPos;

   // intensity of light with respect to distance
   float dist = length(lightVec);
   float a = 3.0;
   float b = 0.7;
   float inten = 1.0f / (a * dist * dist + b * dist + 1.0f);

   // ambient lighting
   float ambient = 0.20f;

   // diffuse lighting
   vec3 normal = normalize(Normal);
   vec3 lightDirection = normalize(lightVec);
   float diffuse = max(dot(normal, lightDirection), 0.0f);

   // specular lighting
   float specularLight = 0.50f;
   vec3 viewDirection = normalize(camPos - crtPos);
   vec3 reflectionDirection = reflect(-lightDirection, normal);
   float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
   float specular = specAmount * specularLight;

   return texture(texture_diffuse1, TexCoords) * (diffuse * inten + ambient + specular) * lightColor;
}

vec4 direcLight()
{
   // ambient lighting
   float ambient = 0.20f;

   // diffuse lighting
   vec3 normal = normalize(Normal);
   vec3 lightDirection = normalize(vec3(-1.0f, -1.0f, 0.5f));
   float diffuse = max(dot(normal, lightDirection), 0.0f);

   // specular lighting
   float specularLight = 0.50f;
   vec3 viewDirection = normalize(camPos - crtPos);
   vec3 reflectionDirection = reflect(-lightDirection, normal);
   float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
   float specular = specAmount * specularLight;

   return texture(texture_diffuse1, TexCoords) * (diffuse + ambient + specular) * lightColor;
}

vec4 spotLight()
{
   // controls how big the area that is lit up is
   float outerCone = 0.90f;
   float innerCone = 0.95f;

   // ambient lighting
   float ambient = 0.20f;

   // diffuse lighting
   vec3 normal = normalize(Normal);
   vec3 lightDirection = normalize(lightPos - crtPos);
   float diffuse = max(dot(normal, lightDirection), 0.0f);

   // specular lighting
   float specularLight = 0.50f;
   vec3 viewDirection = normalize(camPos - crtPos);
   vec3 reflectionDirection = reflect(-lightDirection, normal);
   float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
   float specular = specAmount * specularLight;

   // calculates the intensity of the crntPos based on its angle to the center of the light cone
   float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
   float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

   return texture(texture_diffuse1, TexCoords) * (diffuse * inten + ambient + specular) * lightColor;
}



void main()
{
   FragColor = pointLight();
}