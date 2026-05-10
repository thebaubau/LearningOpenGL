#version 460 core
out vec4 FragColor;
  
in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform vec2      offsets[9];
uniform int       edge_kernel[9];
uniform float     blur_kernel[9];

uniform bool chaos;
uniform bool confuse;
uniform bool shake;

// const float offset = 1.0 / 300.0;

void main()
{
    // Inverse
    // FragFragColor = vec4(vec3(1.0 - texture(screenTexture, TexCoords)), 1.0);

    // Greyscale
    //FragFragColor = texture(screenTexture, TexCoords);
    //float average = (FragFragColor.r + FragFragColor.g + FragFragColor.b) / 3.0;
    //FragFragColor = vec4(average, average, average, 1.0);

    // Greyscale Weighted
    // FragFragColor = texture(screenTexture, TexCoords);
    // float average = 0.2126 * FragFragColor.r + 0.7152 * FragFragColor.g + 0.0722 * FragFragColor.b;
    // FragFragColor = vec4(average, average, average, 1.0);
    
    // vec2 offsets[9] = vec2[](
        // vec2(-offset,  offset), // top-left
        // vec2( 0.0f,    offset), // top-center
        // vec2( offset,  offset), // top-right
        // vec2(-offset,  0.0f),   // center-left
        // vec2( 0.0f,    0.0f),   // center-center
        // vec2( offset,  0.0f),   // center-right
        // vec2(-offset, -offset), // bottom-left
        // vec2( 0.0f,   -offset), // bottom-center
        // vec2( offset, -offset)  // bottom-right    
    // );

    // float kernel[9] = float[](
    //     -1, -1, -1,
    //     -1,  9, -1,
    //     -1, -1, -1
    // );
    // 
    // vec3 sampleTex[9];
    // for(int i = 0; i < 9; i++)
    // {
    //     sampleTex[i] = vec3(texture(screenTexture, TexCoords.st + offsets[i]));
    // }
    // vec3 col = vec3(0.0);
    // for(int i = 0; i < 9; i++)
    //     col += sampleTex[i] * kernel[i];
    // 
    // FragFragColor = vec4(col, 1.0);

    // Final effects
    FragColor = vec4(0.0f);
    vec3 samples[9];

    // sample from texture offsets if using convolution matrix
    if(chaos || shake)
        for(int i = 0; i < 9; i++)
            samples[i] = vec3(texture(screenTexture, TexCoords.st + offsets[i]));

    // process effects
    if (chaos)
    {           
        for(int i = 0; i < 9; i++)
            FragColor += vec4(samples[i] * edge_kernel[i], 0.0f);
        FragColor.a = 1.0f;
    }
    else if (confuse)
    {
        FragColor = vec4(1.0 - texture(screenTexture, TexCoords).rgb, 1.0);
    }
    else if (shake)
    {
        for(int i = 0; i < 9; i++)
            FragColor += vec4(samples[i] * blur_kernel[i], 0.0f);
        FragColor.a = 1.0f;
    }
    else
    {
        FragColor =  texture(screenTexture, TexCoords);
    }

    // Normal
    // FragFragColor = texture(screenTexture, TexCoords);
}