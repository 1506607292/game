#include <thread>
#include "iostream"
#include "unistd.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include<queue>
#include <ctime>
#include "../include/circle.h"
#include "../include/board.h"

#define  Cwidth 1000
#define  Cheight 1000
#define  Clength 1000
GLFWwindow *window;
GLint width{}, height{};
static char msg[128] = {0};
GLfloat xpos, ypos;
GLfloat oldxpos, oldypos;

static void error_callback(int error, const char *description) {
    return;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (action != GLFW_PRESS)
        return;
    switch (key) {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, GL_TRUE);
            break;
        default:
            break;
    }
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    if (action == GLFW_PRESS)
        switch (button) {
            case GLFW_MOUSE_BUTTON_LEFT:
                strcpy(msg, "Mosue left button clicked!");
                break;
            case GLFW_MOUSE_BUTTON_MIDDLE:
                strcpy(msg, "Mosue middle button clicked!");
                break;
            case GLFW_MOUSE_BUTTON_RIGHT:
                strcpy(msg, "Mosue right button clicked!");
                break;
            default:
                return;
        }
    return;
}

void cursor_position_callback(GLFWwindow *window, double x, double y) {
    sprintf(msg, "Mouse position move to [%d:%d]", int(x), int(y));
    oldxpos = xpos;
    oldypos = ypos;
    std::cout << x << " " << y << std::endl;
    xpos = float((x - width / 2) / width) * 2;
    ypos = float(0 - (y - height / 2) / height) * 2;
    return;
}

void init_opengl(void) {
    glShadeModel(GL_SMOOTH);                            // Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);                // Black Background
    glClearDepth(1.0f);                                    // Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);                            // Enables Depth Testing
    glDepthFunc(GL_LEQUAL);                                // The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);    // Really Nice Perspective Calculations
}

void draw_green_board(float x = 1 + xpos * 2, float width = 0.1f, float y = -0.99, float thickness = 0.01) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, 0.0f);  //投影的距离 越大越远越小
    glBegin(GL_POLYGON);/* f6: right */
    glColor3f(0.5f, 1.0f, 0.0f);
    glVertex2f(x + width / 2, y + thickness / 2);//减去他的宽度  1/5 最后也就是0.5/2.5
    glVertex2f(x - width / 2, y + thickness / 2);
    glVertex2f(x - width / 2, y - thickness / 2);
    glVertex2f(x + width / 2, y - thickness / 2);
    glEnd();
}

void draw_red_circle(float xx = 0, float yy = 0, bool CC = false) {
    glBegin(GL_POLYGON);
    if (CC) {
        glColor3f((random() % 1000) / 1000.0, (random() % 1000) / 1000.0, (random() % 1000) / 1000.0);
    } else {
        glColor3f(1.0f, 0.0f, 0.0f);
    }
    glVertex2f(0.05f + xx, 0.05f + yy);//减去他的宽度  1/5 最后也就是0.5/2.5
    glVertex2f(0.0f + xx, 0.0625f + yy);//减去他的宽度  1/5 最后也就是0.5/2.5
    glVertex2f(-0.05f + xx, 0.05f + yy);
    glVertex2f(-0.0625f + xx, 0.0f + yy);
    glVertex2f(-0.05f + xx, -0.05f + yy);
    glVertex2f(0.0f + xx, -0.0625f + yy);
    glVertex2f(0.05f + xx, -0.05f + yy);
    glVertex2f(0.0625f + xx, 0.0f + yy);
    glEnd();
}

void show() {
    while (1) {
        std::cout << "x:" << xpos << std::endl;
        std::cout << "y:" << ypos << std::endl;
        std::cout << "speed:" << oldxpos - xpos << std::endl;

        std::cout << std::endl;
        sleep(1);
        time_t rawtime;
        struct tm *timeinfo;
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        printf("当前系统时间: %s", asctime(timeinfo));
        break;
    }
}

int flag = 0;
int model = 0;
float speedModel() {
    switch (flag) {
        case 4:
            flag = -1;
            model = 0;
            break;
        case 3:
            return 0.5;
            break;
        case 2:
            return 0.1;
            break;
        case 1:
            return -0.2;
            break;
        case 0:
            return (2000.0 - random() % 1000) / 2000.0;
            break;
    }
}

int main(int argc, char *argv[]) {

    std::cout
            << "Enter the maximum number of balls\n the smaller the number \n the more difficult the game\n default = 7 (0<maxNum<25)"
            << std::endl;
    int maxCircle;
    std::cin >> maxCircle;
    if (maxCircle > 25 || maxCircle < 1) {
        maxCircle = 7;
    }
    int spilit;
    std::cout << "Do you like more difficult games?If so, enter yes" << std::endl;
    std::string infoinput;
    std::cin >> infoinput;
    if (infoinput == "yes") {
        spilit = 0;
    } else {
        spilit = 1;
    }
    int count = 0;
    std::thread showing(show);
    showing.detach();
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window = glfwCreateWindow(Cwidth, Cheight, "opengl", nullptr, nullptr);
    if (window == nullptr) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwMakeContextCurrent(window);
    glfwGetFramebufferSize(window, &width, &height);
    if (glewInit() != GLEW_OK) {
        exit(EXIT_FAILURE);
    }
    init_opengl();
    std::queue<Circle> c;
    std::queue<Circle> cc;
    for (float i = 1 - 0.1; i > -1; i -= 0.15) {
        for (float j = 1; j > -0.5; j -= 0.15) {
            Circle item;
            item.setX(i);
            item.setY(j);
            item.setXspeed(0);
            item.setYspeed(0);
            cc.push(item);
        }
    }
    Board b;
    while (!glfwWindowShouldClose(window)) {

        for (int i = 0; i < cc.size(); i++) {
            cc.front().move();
            cc.push(cc.front());
            cc.pop();
        }

        draw_green_board(1 + xpos * 2, b.getWidth(), b.getY(), 0.02);
        b.setX(1 + xpos * 2);
        if (strcmp(msg, "Mosue left button clicked!") == 0) {
            if (c.size() < maxCircle) {
                Circle itemm;
                itemm.setX(1 + xpos * 2);
                c.push(itemm);
                strcpy(msg, "");
            }
        }
        if (strcmp(msg, "Mosue right button clicked!") == 0) {
            for (int i = 0; i < c.size(); i++) {
                c.pop();
            }
            strcpy(msg, "");
        }
        for (int j = 0; j < cc.size(); j++) {
            draw_red_circle(cc.front().getX(), cc.front().getY());

            for (int jj = 0; jj < c.size(); jj++) {
                if (cc.front().isBump(c.front().getX(), c.front().getY())) {
//                    c.front().setXspeed(15*(c.front().getX()-cc.front().getX()));
//                    c.front().setXspeed(-15*(c.front().getY()-cc.front().getY()));
//                    c.front().changeYdrec();
//                    c.front().changeXdrec();
                    count++;
                    cc.pop();
                }
                c.push(c.front());
                c.pop();
            }
            cc.push(cc.front());
            cc.pop();
        }
        if (cc.empty()) {
            for (float i = 1 - 0.1; i > -1; i -= 0.15) {
                for (float j = 1; j > -0.5; j -= 0.15) {
                    Circle item;
                    item.setX(i);
                    item.setY(j);
                    if (model == 0) {
                        item.setXspeed(i);
                        item.setYspeed(j);
                    } else {
                        item.setXspeed(speedModel());
                        item.setYspeed(speedModel());
                    }
                    cc.push(item);
                }
            }
            model++;
            flag++;
        }
        for (int i = 0; i < c.size(); i++) {
            if (b.isBump(c.front().getX(), c.front().getY()) && c.front().getYspeed() < 0) {
                c.front().changeYdrec();
                c.front().setXspeed(c.front().getXspeed() - (oldxpos - xpos) * 10);
                if (c.size() < maxCircle) {
                    Circle split = c.front();
                    split.randSpeed();
                    if (spilit)
                        c.push(split);//分裂成几个 =========================
                }
                continue;
            }
            c.front().move();
            if (strcmp(msg, "Mosue left button clicked!") == 0) {
                if (c.size() < maxCircle) {
                    Circle itemm;
                    itemm.setX(1 + xpos * 2);
                    c.push(itemm);
                    strcpy(msg, "");
                }
            }
            draw_red_circle(c.front().getX(), c.front().getY(), true);
            if (c.front().getY() <= -1) {
                c.pop();
            }
            c.push(c.front());
            c.pop();
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    exit(EXIT_SUCCESS);
}