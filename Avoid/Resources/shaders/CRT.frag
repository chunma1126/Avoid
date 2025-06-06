#ifdef GL_ES
precision mediump float;
#endif

uniform sampler2D CC_Texture0;
uniform vec2 resolution;
varying vec2 v_texCoord;

#define FILTER_SIZE 2
#define COLOR_LEVELS 7.0
#define EDGE_FILTER_SIZE 2
#define EDGE_THRESHOLD 0.05

vec4 edgeFilter(in int px, in int py)
{
    vec4 color = vec4(0.0);
    for (int y = -EDGE_FILTER_SIZE; y <= EDGE_FILTER_SIZE; ++y)
    {
        for (int x = -EDGE_FILTER_SIZE; x <= EDGE_FILTER_SIZE; ++x)
        {
            color += texture2D(CC_Texture0, v_texCoord + vec2(px + x, py + y) / resolution);
        }
    }
    color /= float((2 * EDGE_FILTER_SIZE + 1) * (2 * EDGE_FILTER_SIZE + 1));
    return color;
}

void main(void)
{
    vec4 color = vec4(0.0);
    for (int y = -FILTER_SIZE; y <= FILTER_SIZE; ++y)
    {
        for (int x = -FILTER_SIZE; x <= FILTER_SIZE; ++x)
        {
            color += texture2D(CC_Texture0, v_texCoord + vec2(x, y) / resolution);
        }
    }
    color /= float((2 * FILTER_SIZE + 1) * (2 * FILTER_SIZE + 1));
    for (int c = 0; c < 3; ++c)
    {
        color[c] = floor(COLOR_LEVELS * color[c]) / COLOR_LEVELS;
    }

    vec4 sum = abs(edgeFilter(0,1) - edgeFilter(0,-1));
    sum += abs(edgeFilter(1,0) - edgeFilter(-1,0));
    sum /= 2.0;

    if (length(sum) > EDGE_THRESHOLD)
    {
        color.rgb = vec3(0.0);
    }

    gl_FragColor = color;
}
