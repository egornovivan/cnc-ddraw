#ifndef OPENGLSHADER_H
#define OPENGLSHADER_H

/* OpenGL 2.0 */

const char PASSTHROUGH_VERT_SHADER_110[] =
    "#version 110\n"
    "varying vec2 TEX0; \n"
    "\n"
    "void main()\n"
    "{\n"
    "    gl_Position = ftransform(); \n"
    "    TEX0 = gl_MultiTexCoord0.xy; \n"
    "}\n";

const char PALETTE_FRAG_SHADER_110[] =
    "#version 110\n"
    "uniform sampler2D Texture; \n"
    "uniform sampler2D PaletteTexture; \n"
    "varying vec2 TEX0; \n"
    "\n"
    "void main()\n"
    "{\n"
    "   vec4 pIndex = texture2D(Texture, TEX0); \n"
    "   gl_FragColor = texture2D(PaletteTexture, vec2(pIndex.r * (255.0/256.0) + (0.5/256.0), 0)); \n"
    "}\n";


const char PASSTHROUGH_FRAG_SHADER_110[] =
    "#version 110\n"
    "uniform sampler2D Texture; \n"
    "varying vec2 TEX0; \n"
    "\n"
    "void main()\n"
    "{\n"
    "   vec4 texel = texture2D(Texture, TEX0); \n"
    "   gl_FragColor = texel; \n"
    "}\n";

/* OpenGL 3.0 */

const char PASSTHROUGH_VERT_SHADER[] =
    "#version 130\n"
    "in vec4 VertexCoord;\n"
    "in vec4 COLOR;\n"
    "in vec4 TexCoord;\n"
    "out vec4 COL0;\n"
    "out vec4 TEX0;\n"
    "uniform mat4 MVPMatrix;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    gl_Position = MVPMatrix * VertexCoord;\n"
    "    COL0 = COLOR;\n"
    "    TEX0.xy = TexCoord.xy;\n"
    "}\n";


const char PALETTE_FRAG_SHADER[] =
    "#version 130\n"
    "out vec4 FragColor;\n"
    "uniform sampler2D Texture;\n"
    "uniform sampler2D PaletteTexture;\n"
    "in vec4 TEX0;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    vec4 pIndex = texture(Texture, TEX0.xy);\n"
    "    FragColor = texture(PaletteTexture, vec2(pIndex.r * (255.0/256.0) + (0.5/256.0), 0));\n"
    "}\n";


const char PASSTHROUGH_FRAG_SHADER[] =
    "#version 130\n"
    "out vec4 FragColor;\n"
    "uniform sampler2D Texture;\n"
    "in vec4 TEX0;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    vec4 texel = texture(Texture, TEX0.xy);\n"
    "    FragColor = texel;\n"
    "}\n";

/* OpenGL 3.2 (Core Profile) */

const char PASSTHROUGH_VERT_SHADER_CORE[] =
    "#version 150\n"
    "in vec4 VertexCoord;\n"
    "in vec4 COLOR;\n"
    "in vec4 TexCoord;\n"
    "out vec4 COL0;\n"
    "out vec4 TEX0;\n"
    "uniform mat4 MVPMatrix;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    gl_Position = MVPMatrix * VertexCoord;\n"
    "    COL0 = COLOR;\n"
    "    TEX0.xy = TexCoord.xy;\n"
    "}\n";


const char PALETTE_FRAG_SHADER_CORE[] =
    "#version 150\n"
    "out vec4 FragColor;\n"
    "uniform sampler2D Texture;\n"
    "uniform sampler2D PaletteTexture;\n"
    "in vec4 TEX0;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    vec4 pIndex = texture(Texture, TEX0.xy);\n"
    "    FragColor = texture(PaletteTexture, vec2(pIndex.r * (255.0/256.0) + (0.5/256.0), 0));\n"
    "}\n";


const char PASSTHROUGH_FRAG_SHADER_CORE[] =
    "#version 150\n"
    "out vec4 FragColor;\n"
    "uniform sampler2D Texture;\n"
    "in vec4 TEX0;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    vec4 texel = texture(Texture, TEX0.xy);\n"
    "    FragColor = texel;\n"
    "}\n";

/*   
//    The following code is licensed under the MIT license: https://gist.github.com/TheRealMJP/bc503b0b87b643d3505d41eab8b332ae
//    Ported from code: https://gist.github.com/TheRealMJP/c83b8c0f46b63f3a88a5986f4fa982b1
//    Samples a texture with Catmull-Rom filtering, using 9 texture fetches instead of 16.
//    See http://vec3.ca/bicubic-filtering-in-fewer-taps/ for more details
//    Modified to use 5 texture fetches
*/

const char CATMULL_ROM_FRAG_SHADER[] =
    "#version 130\n"
    "out mediump vec4 FragColor;\n"
    "uniform int FrameDirection;\n"
    "uniform int FrameCount;\n"
    "uniform vec2 OutputSize;\n"
    "uniform vec2 TextureSize;\n"
    "uniform vec2 InputSize;\n"
    "uniform sampler2D Texture;\n"
    "in vec4 TEX0;\n"
    "\n"
    "#define Source Texture\n"
    "#define vTexCoord TEX0.xy\n"
    "\n"
    "#define SourceSize vec4(TextureSize, 1.0 / TextureSize)\n"
    "#define outsize vec4(OutputSize, 1.0 / OutputSize)\n"
    "\n"
    "void main()\n"
    "{\n"
    "    vec2 samplePos = vTexCoord * SourceSize.xy;\n"
    "    vec2 texPos1 = floor(samplePos - 0.5) + 0.5;\n"
    "\n"
    "    vec2 f = samplePos - texPos1;\n"
    "\n"
    "    vec2 w0 = f * (-0.5 + f * (1.0 - 0.5 * f));\n"
    "    vec2 w1 = 1.0 + f * f * (-2.5 + 1.5 * f);\n"
    "    vec2 w2 = f * (0.5 + f * (2.0 - 1.5 * f));\n"
    "    vec2 w3 = f * f * (-0.5 + 0.5 * f);\n"
    "\n"
    "    vec2 w12 = w1 + w2;\n"
    "    vec2 offset12 = w2 / (w1 + w2);\n"
    "\n"
    "    vec2 texPos0  = texPos1 - 1.;\n"
    "    vec2 texPos3  = texPos1 + 2.;\n"
    "    vec2 texPos12 = texPos1 + offset12;\n"
    "\n"
    "    texPos0  *= SourceSize.zw;\n"
    "    texPos3  *= SourceSize.zw;\n"
    "    texPos12 *= SourceSize.zw;\n"
    "\n"
    "    float wtm = w12.x * w0.y;\n"
    "    float wml = w0.x * w12.y;\n"
    "    float wmm = w12.x * w12.y;\n"
    "    float wmr = w3.x * w12.y;\n"
    "    float wbm = w12.x * w3.y;\n"
    "\n"
    "    vec3 result = vec3(0.0f);\n"
    "\n"
    "    result += texture(Source, vec2(texPos12.x, texPos0.y)).rgb * wtm;\n"
    "    result += texture(Source, vec2(texPos0.x, texPos12.y)).rgb * wml;\n"
    "    result += texture(Source, vec2(texPos12.x, texPos12.y)).rgb * wmm;\n"
    "    result += texture(Source, vec2(texPos3.x, texPos12.y)).rgb * wmr;\n"
    "    result += texture(Source, vec2(texPos12.x, texPos3.y)).rgb * wbm;\n"
    "\n"
    "    FragColor = vec4(result * (1. / (wtm + wml + wmm + wmr + wbm)), 1.0);\n"
    "}\n";


const char CATMULL_ROM_FRAG_SHADER_CORE[] =
    "#version 150\n"
    "out mediump vec4 FragColor;\n"
    "uniform int FrameDirection;\n"
    "uniform int FrameCount;\n"
    "uniform vec2 OutputSize;\n"
    "uniform vec2 TextureSize;\n"
    "uniform vec2 InputSize;\n"
    "uniform sampler2D Texture;\n"
    "in vec4 TEX0;\n"
    "\n"
    "#define Source Texture\n"
    "#define vTexCoord TEX0.xy\n"
    "\n"
    "#define SourceSize vec4(TextureSize, 1.0 / TextureSize)\n"
    "#define outsize vec4(OutputSize, 1.0 / OutputSize)\n"
    "\n"
    "void main()\n"
    "{\n"
    "    vec2 samplePos = vTexCoord * SourceSize.xy;\n"
    "    vec2 texPos1 = floor(samplePos - 0.5) + 0.5;\n"
    "\n"
    "    vec2 f = samplePos - texPos1;\n"
    "\n"
    "    vec2 w0 = f * (-0.5 + f * (1.0 - 0.5 * f));\n"
    "    vec2 w1 = 1.0 + f * f * (-2.5 + 1.5 * f);\n"
    "    vec2 w2 = f * (0.5 + f * (2.0 - 1.5 * f));\n"
    "    vec2 w3 = f * f * (-0.5 + 0.5 * f);\n"
    "\n"
    "    vec2 w12 = w1 + w2;\n"
    "    vec2 offset12 = w2 / (w1 + w2);\n"
    "\n"
    "    vec2 texPos0  = texPos1 - 1.;\n"
    "    vec2 texPos3  = texPos1 + 2.;\n"
    "    vec2 texPos12 = texPos1 + offset12;\n"
    "\n"
    "    texPos0  *= SourceSize.zw;\n"
    "    texPos3  *= SourceSize.zw;\n"
    "    texPos12 *= SourceSize.zw;\n"
    "\n"
    "    float wtm = w12.x * w0.y;\n"
    "    float wml = w0.x * w12.y;\n"
    "    float wmm = w12.x * w12.y;\n"
    "    float wmr = w3.x * w12.y;\n"
    "    float wbm = w12.x * w3.y;\n"
    "\n"
    "    vec3 result = vec3(0.0f);\n"
    "\n"
    "    result += texture(Source, vec2(texPos12.x, texPos0.y)).rgb * wtm;\n"
    "    result += texture(Source, vec2(texPos0.x, texPos12.y)).rgb * wml;\n"
    "    result += texture(Source, vec2(texPos12.x, texPos12.y)).rgb * wmm;\n"
    "    result += texture(Source, vec2(texPos3.x, texPos12.y)).rgb * wmr;\n"
    "    result += texture(Source, vec2(texPos12.x, texPos3.y)).rgb * wbm;\n"
    "\n"
    "    FragColor = vec4(result * (1. / (wtm + wml + wmm + wmr + wbm)), 1.0);\n"
    "}\n";



#endif
