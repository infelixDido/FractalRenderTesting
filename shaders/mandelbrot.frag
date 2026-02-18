#version 330 core

out vec4 FragColor; 

uniform vec2 u_resolution;
uniform int u_max_iterations;

void main() {
  vec2 uv = gl_FragCoord.xy / u_resolution;
  vec2 c = (uv - 0.5) * 4.0;

  vec2 z = vec2(0.0);
  int iterations = 0;

  for (int i = 0; i < u_max_iterations; i++) {
    if (dot(z, z) > 4.0) break;

    float x_temp = z.x * z.x - z.y * z.y + c.x;
    z.y = 2.0 * z.x * z.y + c.y;
    z.x = x_temp;

    iterations++;
  }

  float color = float(iterations) / float(u_max_iterations);
  FragColor = vec4(vec3(color), 1.0); 
}
