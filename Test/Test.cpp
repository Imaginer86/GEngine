#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

// Ідентифікатор текстури
GLuint texture;

// Кути обертання
float angleX = 0.0f;
float angleY = 0.0f;

// Функція для завантаження текстури
static void loadTexture() {
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Завантаження зображення текстури
    int width, height, nrChannels;
    //unsigned char* data = stbi_load("EarthMap.png", &width, &height, &nrChannels, 0);
    unsigned char* data = stbi_load("ball8.png", &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        printf("Failed to load texture\n");
    }
    stbi_image_free(data);

    // Налаштування параметрів текстури
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

// Функція для налаштування GLUquadric і відображення сфери з текстурою
static void display() {
    GLUquadric* quad = gluNewQuadric();
    gluQuadricTexture(quad, GL_TRUE);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    glPushMatrix();
    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);
    gluSphere(quad, 1.0, 36, 18);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    gluDeleteQuadric(quad);

    glfwSwapBuffers(glfwGetCurrentContext());
}

// Функція для оновлення кута обертання
void update() {
    angleX += 1.0f;
    angleY += 1.0f;
    if (angleX > 360) angleX -= 360;
    if (angleY > 360) angleY -= 360;
}

// Основна функція
int main() {
    if (!glfwInit()) {
        printf("Failed to initialize GLFW\n");
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "Textured and Rotating Sphere", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glewInit();

    glEnable(GL_DEPTH_TEST);
    loadTexture();

    while (!glfwWindowShouldClose(window)) {
        display();
        update();
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}