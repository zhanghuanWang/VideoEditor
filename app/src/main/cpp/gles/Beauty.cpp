//
// Created by zzh on 2018/7/31 0031.
//

#include <cstring>
#include <log.h>
#include "Beauty.h"
#include "glutil.h"
#include <GLES2/gl2ext.h>

const static char *VertexShader = ""
        "#version 300 es\n"
        "layout(location=0) in vec4 aPosition;\n"
        "layout(location=1) in vec4 aTexCoord;\n"
        "uniform mat4 mMatrix;\n"
        "out vec2 vTexCoord;\n"
        "void main() {\n"
        "    vTexCoord = (mMatrix * aTexCoord).xy;\n"
        "    gl_Position = aPosition;\n"
        "}";

const static char *FragmentShader = ""
        "#version 300 es\n"
        "#extension GL_OES_EGL_image_external_essl3 : require\n"
        "\n"
        "precision highp float;\n"
        "\n"
        "in highp vec2 vTexCoord;\n"
        "\n"
        "uniform samplerExternalOES sTexture;\n"
        "\n"
        "uniform highp vec2 singleStepOffset;\n"
        "uniform highp vec4 params;\n"
        "uniform highp float brightness;\n"
        "\n"
        "const highp vec3 W = vec3(0.299, 0.587, 0.114);\n"
        "const highp mat3 saturateMatrix = mat3(\n"
        "        1.1102, -0.0598, -0.061,\n"
        "        -0.0774, 1.0826, -0.1186,\n"
        "        -0.0228, -0.0228, 1.1772);\n"
        "\n"
        "highp vec2 blurCoordinates[24];\n"
        "\n"
        "highp float hardLight(highp float color) {\n"
        "    if (color <= 0.5)\n"
        "        color = color * color * 2.0;\n"
        "    else\n"
        "        color = 1.0 - ((1.0 - color)*(1.0 - color) * 2.0);\n"
        "    return color;\n"
        "}\n"
        "\n"
        "layout(location=0) out vec4 fragColor;\n"
        "\n"
        "void main() {\n"
        "    highp vec3 centralColor = texture(sTexture, vTexCoord).rgb;\n"
        "    blurCoordinates[0] = vTexCoord.xy + singleStepOffset * vec2(0.0, -10.0);\n"
        "    blurCoordinates[1] = vTexCoord.xy + singleStepOffset * vec2(0.0, 10.0);\n"
        "    blurCoordinates[2] = vTexCoord.xy + singleStepOffset * vec2(-10.0, 0.0);\n"
        "    blurCoordinates[3] = vTexCoord.xy + singleStepOffset * vec2(10.0, 0.0);\n"
        "    blurCoordinates[4] = vTexCoord.xy + singleStepOffset * vec2(5.0, -8.0);\n"
        "    blurCoordinates[5] = vTexCoord.xy + singleStepOffset * vec2(5.0, 8.0);\n"
        "    blurCoordinates[6] = vTexCoord.xy + singleStepOffset * vec2(-5.0, 8.0);\n"
        "    blurCoordinates[7] = vTexCoord.xy + singleStepOffset * vec2(-5.0, -8.0);\n"
        "    blurCoordinates[8] = vTexCoord.xy + singleStepOffset * vec2(8.0, -5.0);\n"
        "    blurCoordinates[9] = vTexCoord.xy + singleStepOffset * vec2(8.0, 5.0);\n"
        "    blurCoordinates[10] = vTexCoord.xy + singleStepOffset * vec2(-8.0, 5.0);\n"
        "    blurCoordinates[11] = vTexCoord.xy + singleStepOffset * vec2(-8.0, -5.0);\n"
        "    blurCoordinates[12] = vTexCoord.xy + singleStepOffset * vec2(0.0, -6.0);\n"
        "    blurCoordinates[13] = vTexCoord.xy + singleStepOffset * vec2(0.0, 6.0);\n"
        "    blurCoordinates[14] = vTexCoord.xy + singleStepOffset * vec2(6.0, 0.0);\n"
        "    blurCoordinates[15] = vTexCoord.xy + singleStepOffset * vec2(-6.0, 0.0);\n"
        "    blurCoordinates[16] = vTexCoord.xy + singleStepOffset * vec2(-4.0, -4.0);\n"
        "    blurCoordinates[17] = vTexCoord.xy + singleStepOffset * vec2(-4.0, 4.0);\n"
        "    blurCoordinates[18] = vTexCoord.xy + singleStepOffset * vec2(4.0, -4.0);\n"
        "    blurCoordinates[19] = vTexCoord.xy + singleStepOffset * vec2(4.0, 4.0);\n"
        "    blurCoordinates[20] = vTexCoord.xy + singleStepOffset * vec2(-2.0, -2.0);\n"
        "    blurCoordinates[21] = vTexCoord.xy + singleStepOffset * vec2(-2.0, 2.0);\n"
        "    blurCoordinates[22] = vTexCoord.xy + singleStepOffset * vec2(2.0, -2.0);\n"
        "    blurCoordinates[23] = vTexCoord.xy + singleStepOffset * vec2(2.0, 2.0);\n"
        "\n"
        "    highp float sampleColor = centralColor.g * 22.0;\n"
        "    sampleColor += texture(sTexture, blurCoordinates[0]).g;\n"
        "    sampleColor += texture(sTexture, blurCoordinates[1]).g;\n"
        "    sampleColor += texture(sTexture, blurCoordinates[2]).g;\n"
        "    sampleColor += texture(sTexture, blurCoordinates[3]).g;\n"
        "    sampleColor += texture(sTexture, blurCoordinates[4]).g;\n"
        "    sampleColor += texture(sTexture, blurCoordinates[5]).g;\n"
        "    sampleColor += texture(sTexture, blurCoordinates[6]).g;\n"
        "    sampleColor += texture(sTexture, blurCoordinates[7]).g;\n"
        "    sampleColor += texture(sTexture, blurCoordinates[8]).g;\n"
        "    sampleColor += texture(sTexture, blurCoordinates[9]).g;\n"
        "    sampleColor += texture(sTexture, blurCoordinates[10]).g;\n"
        "    sampleColor += texture(sTexture, blurCoordinates[11]).g;\n"
        "    sampleColor += texture(sTexture, blurCoordinates[12]).g * 2.0;\n"
        "    sampleColor += texture(sTexture, blurCoordinates[13]).g * 2.0;\n"
        "    sampleColor += texture(sTexture, blurCoordinates[14]).g * 2.0;\n"
        "    sampleColor += texture(sTexture, blurCoordinates[15]).g * 2.0;\n"
        "    sampleColor += texture(sTexture, blurCoordinates[16]).g * 2.0;\n"
        "    sampleColor += texture(sTexture, blurCoordinates[17]).g * 2.0;\n"
        "    sampleColor += texture(sTexture, blurCoordinates[18]).g * 2.0;\n"
        "    sampleColor += texture(sTexture, blurCoordinates[19]).g * 2.0;\n"
        "    sampleColor += texture(sTexture, blurCoordinates[20]).g * 3.0;\n"
        "    sampleColor += texture(sTexture, blurCoordinates[21]).g * 3.0;\n"
        "    sampleColor += texture(sTexture, blurCoordinates[22]).g * 3.0;\n"
        "    sampleColor += texture(sTexture, blurCoordinates[23]).g * 3.0;\n"
        "\n"
        "    sampleColor = sampleColor / 62.0;\n"
        "\n"
        "    highp float highPass = centralColor.g - sampleColor + 0.5;\n"
        "\n"
        "    for (int i = 0; i < 5; i++) {\n"
        "        highPass = hardLight(highPass);\n"
        "    }\n"
        "    highp float lumance = dot(centralColor, W);\n"
        "\n"
        "    highp float alpha = pow(lumance, params.r);\n"
        "\n"
        "    highp vec3 smoothColor = centralColor + (centralColor-vec3(highPass))*alpha*0.1;\n"
        "\n"
        "    smoothColor.r = clamp(pow(smoothColor.r, params.g), 0.0, 1.0);\n"
        "    smoothColor.g = clamp(pow(smoothColor.g, params.g), 0.0, 1.0);\n"
        "    smoothColor.b = clamp(pow(smoothColor.b, params.g), 0.0, 1.0);\n"
        "\n"
        "    highp vec3 lvse = vec3(1.0)-(vec3(1.0)-smoothColor)*(vec3(1.0)-centralColor);\n"
        "    highp vec3 bianliang = max(smoothColor, centralColor);\n"
        "    highp vec3 rouguang = 2.0*centralColor*smoothColor + centralColor*centralColor - 2.0*centralColor*centralColor*smoothColor;\n"
        "\n"
        "    fragColor = vec4(mix(centralColor, lvse, alpha), 1.0);\n"
        "    fragColor.rgb = mix(fragColor.rgb, bianliang, alpha);\n"
        "    fragColor.rgb = mix(fragColor.rgb, rouguang, params.b);\n"
        "\n"
        "    highp vec3 satcolor = fragColor.rgb * saturateMatrix;\n"
        "    fragColor.rgb = mix(fragColor.rgb, satcolor, params.a);\n"
        "    fragColor.rgb = vec3(fragColor.rgb + vec3(brightness));\n"
        "}";

const static GLfloat Vertices[] = {
        -1.0f, 1.0f,
        1.0f, 1.0f,
        -1.0f, -1.0f,
        1.0f, -1.0f
};

const static GLfloat TexCoords[] = {
        0.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f
};

const static GLushort Indices[] = {
        0, 1, 2,
        1, 2, 3
};

const static GLuint AttribPosition = 0;
const static GLuint AttribTexCoord = 1;
const static GLuint VertexPosSize = 2;
const static GLuint IndexNumber = 6;
const static GLuint TexCoordPosSize = 2;

Beauty::Beauty() : mEGLCore(new EGLCore), mWindow(nullptr), mTexOes(0), mMatrixLoc(0), mTexLoc(0),
                   mParamsLoc(0), mBrightnessLoc(0), mSingleStepOffsetLoc(0), mVao(0),
                   mPboReadIndex(0), mPboMapIndex(-1) {
    memset(mVboIds, 0, sizeof(mVboIds));
    memset(mPboIds, 0, sizeof(mPboIds));
}

Beauty::~Beauty() {
    if (mWindow) {
        ANativeWindow_release(mWindow);
        mWindow = nullptr;
    }

    if (mEGLCore) {
        delete mEGLCore;
        mEGLCore = nullptr;
    }
}

int Beauty::init(AAssetManager *manager, ANativeWindow *window, int width, int height) {
    mWindow = window;
    resize(width, height);

    if (!mEGLCore->buildContext(window)) {
        LOGE("buildContext failed");
        return -1;
    }

    mProgram = loadProgram(VertexShader, FragmentShader);
    if (!mProgram) {
        LOGE("loadProgram failed!");
        return -1;
    }

    // 设置默认帧缓冲区纹理
    glGenTextures(1, &mTexOes);
    glBindTexture(GL_TEXTURE_EXTERNAL_OES, mTexOes);
    glTexParameterf(GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_EXTERNAL_OES, 0);

    initVbo();
    initVao();
    initPbo();

    mMatrixLoc = glGetUniformLocation(mProgram, "mMatrix");
    mTexLoc = glGetUniformLocation(mProgram, "sTexture");
    mParamsLoc = glGetUniformLocation(mProgram, "params");
    mBrightnessLoc = glGetUniformLocation(mProgram, "brightness");
    mSingleStepOffsetLoc = glGetUniformLocation(mProgram, "singleStepOffset");

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    return mTexOes;
}

void Beauty::initVbo() {
    // 缓存顶点坐标、纹理坐标、索引数据到缓冲区中
    glGenBuffers(3, mVboIds);
    glBindBuffer(GL_ARRAY_BUFFER, mVboIds[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, mVboIds[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(TexCoords), TexCoords, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVboIds[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
}

void Beauty::initVao() {
    glGenVertexArrays(1, &mVao);
    // 使用缓冲区的数据设置顶点属性，并绑定至 vao
    glBindVertexArray(mVao);
    glBindBuffer(GL_ARRAY_BUFFER, mVboIds[0]);
    glEnableVertexAttribArray(AttribPosition);
    glVertexAttribPointer(AttribPosition, VertexPosSize, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, mVboIds[1]);
    glEnableVertexAttribArray(AttribTexCoord);
    glVertexAttribPointer(AttribTexCoord, TexCoordPosSize, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVboIds[2]);

    glBindVertexArray(0);
}

void Beauty::initPbo() {
    // 生成 pbo
    glGenBuffers(2, mPboIds);
    glBindBuffer(GL_PIXEL_PACK_BUFFER, mPboIds[0]);
    glBufferData(GL_PIXEL_PACK_BUFFER, mWidth * mHeight * 4, nullptr, GL_DYNAMIC_COPY);
    glBindBuffer(GL_PIXEL_PACK_BUFFER, mPboIds[1]);
    glBufferData(GL_PIXEL_PACK_BUFFER, mWidth * mHeight * 4, nullptr, GL_DYNAMIC_COPY);
}

void
Beauty::draw(GLfloat *matrix, GLfloat beauty, GLfloat saturate, GLfloat bright, bool recording) {
    glViewport(0, 0, mWidth, mHeight);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(mProgram);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_EXTERNAL_OES, mTexOes);
    glUniform1i(mTexLoc, 0);

    glUniformMatrix4fv(mMatrixLoc, 1, GL_FALSE, matrix);
    glUniform4fv(mParamsLoc, 1, getParams(beauty, saturate));
    glUniform1f(mBrightnessLoc, getBright(bright));
    glUniform2fv(mSingleStepOffsetLoc, 1, getSingleStepOffset(mWidth, mHeight));

    // 从 vao 中读取数据并渲染
    glBindVertexArray(mVao);
    glDrawElements(GL_TRIANGLES, IndexNumber, GL_UNSIGNED_SHORT, 0);
    glBindVertexArray(0);

//    if (recording) {
//        int rgbSize = mWidth * mHeight * 4;
//        glReadBuffer(GL_COLOR_ATTACHMENT0);
//        glBindBuffer(GL_PIXEL_PACK_BUFFER, mPboIds[mPboReadIndex]);
//        // 从默认帧缓冲区读取数据到 PBO 中
//        glReadPixels(0, 0, mWidth, mHeight, GL_RGBA, GL_UNSIGNED_BYTE, 0);
//        if (mPboMapIndex >= 0) {
//            glBindBuffer(GL_PIXEL_PACK_BUFFER, mPboIds[mPboMapIndex]);
//            uint8_t *mapData = (uint8_t *) glMapBufferRange(GL_PIXEL_PACK_BUFFER, 0, rgbSize,
//                                                            GL_MAP_READ_BIT);
//            uint8_t *rgb = new uint8_t[rgbSize];
//            memcpy(rgb, mapData, (size_t) rgbSize);
//            recordImage(rgb, rgbSize, mWidth, mHeight, PIXEL_FORMAT_ABGR);
//            glUnmapBuffer(GL_PIXEL_PACK_BUFFER);
//        }
//        mPboMapIndex = mPboReadIndex;
//        mPboReadIndex = 1 - mPboReadIndex;
//        glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
//    }

    glFlush();
    mEGLCore->swapBuffer();
}

GLfloat *Beauty::getParams(const GLfloat beauty, const GLfloat saturate) {
    GLfloat *value = new GLfloat[4];
    value[0] = 1.6f - 1.2f * beauty;
    value[1] = 1.3f - 0.6f * beauty;
    value[2] = -0.2f + 0.6f * saturate;
    value[3] = -0.2f + 0.6f * saturate;
    return value;
}

GLfloat Beauty::getBright(const GLfloat bright) {
    return 0.6f * (-0.5f + bright);
}

GLfloat *Beauty::getSingleStepOffset(const GLfloat width, const GLfloat height) {
    GLfloat *value = new GLfloat[2];
    value[0] = 2.0f / width;
    value[1] = 2.0f / height;
    return value;
}

void Beauty::stop() {
    glDeleteProgram(mProgram);
    glDeleteTextures(1, &mTexOes);
    glDeleteBuffers(2, mPboIds);
    glDeleteBuffers(1, &mVao);
    glDeleteBuffers(3, mVboIds);
}