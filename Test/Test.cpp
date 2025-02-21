#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

int main() {
    // Инициализация GLFW
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(800, 600, "Textured Sphere", NULL, NULL);
    glfwMakeContextCurrent(window);

    // Инициализация GLEW
    glewExperimental = GL_TRUE;
    glewInit();

    GLuint texture;

    // Загрузка изображения
    int width, height, nrChannels;
    unsigned char* data = stbi_load("EarthMap.png", &width, &height, &nrChannels, 0);
    if (data) {
        //GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }

    // Установка параметров текстуры
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Включение текстурирования
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Создание объекта квадрики
    GLUquadric* quad = gluNewQuadric();
    gluQuadricTexture(quad, GL_TRUE);

    // Цикл рендеринга
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Отображение текстурированной сферы
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        //glColor3f(1, 0, 0);
        gluSphere(quad, 1.0, 32, 32);

        gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

 

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    gluDeleteQuadric(quad);
    glfwTerminate();
    return 0;
}
