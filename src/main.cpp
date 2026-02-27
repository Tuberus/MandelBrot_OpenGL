#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

constexpr int WINDOW_WIDTH = 1920;
constexpr int WINDOW_HEIGHT = 1080;
constexpr int MAX_ITERATIONS = 100;

int calculateMandelbrot(double x0, double y0) {
    double x = 0.0;
    double y = 0.0;
    int iteration = 0;

    while (x * x + y * y <= 4.0 && iteration < MAX_ITERATIONS) {
        double xtemp = x * x - y * y + x0;
        y = 2 * x * y + y0; 
        x = xtemp;
        iteration++;
    }
    return iteration;
}

int main() {
    if (!glfwInit()) return -1;
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hundsdorf Mondaufgang", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glewInit();

    std::vector<unsigned char> pixelBuffer(WINDOW_WIDTH * WINDOW_HEIGHT * 3);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        for (int py = 0; py < WINDOW_HEIGHT; py++) {
            for (int px = 0; px < WINDOW_WIDTH; px++) {
                double x0 = (px - WINDOW_WIDTH * 0.7) * (3.5 / WINDOW_WIDTH);
                double y0 = (py - WINDOW_HEIGHT * 0.5) * (2.0 / WINDOW_HEIGHT);

                int iter = calculateMandelbrot(x0, y0);

                int idx = (py * WINDOW_WIDTH + px) * 3;
                if (iter == MAX_ITERATIONS) {
                    pixelBuffer[idx] = 0;
                    pixelBuffer[idx + 1] = 0;
                    pixelBuffer[idx + 2] = 0;
                } else {
                    unsigned char color = (unsigned char)(255 * iter / MAX_ITERATIONS);
                    pixelBuffer[idx] = color;
                    pixelBuffer[idx + 1] = color / 4;
                    pixelBuffer[idx + 2] = color / 2;
                }
            }
        }

        glDrawPixels(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, pixelBuffer.data());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}