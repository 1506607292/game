#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "iostream"
using namespace std;

//void Drawsin()
//{
//    const float factor = 0.1;
//    glBegin(GL_LINES);
//    glVertex2f(-1,0);
//    glVertex2f(1,0);
//    glVertex2f(0, -1);
//    glVertex2f(0, 1);
//    glEnd();
//    glBegin(GL_LINE_STRIP);
//    for (float x = -1 / factor;x < 1 / factor;x += 0.001)
//    {
//        glVertex2f(x * factor, sin(x) * factor);
//    }
//    glEnd();
//    glBegin(GL_LINE_STRIP);
//    for (float y = -1 / factor; y < 1 / factor; y += 0.001)
//    {
//        glVertex2f(y*factor,cos(y)*factor);
//    }
//    glEnd();
//}
void DrawLines(float cursor_x,float cursor_y) {
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(0.0, 0.0, 0.f);
    //设置直线宽度
    glLineWidth(5.0f);
    glBegin(GL_LINES);
    {
        glColor3f(0.0f, 0.0f, 1.0f);
        // 设置直线坐标
        glVertex3f(-1.f, cursor_y, 0.0f);
        glVertex3f(1.f, cursor_y, 0.0f);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(cursor_x, -1.f, 0.0f);
        glVertex3f(cursor_x, 1.f, 0.0f);
    }
    glEnd();
    glPopMatrix();
}

void drawPoint(float x,float y,float size) {
    glPointSize(size);
    glBegin(GL_POINTS);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(x, y);
    glEnd();
}

void drawTriangle() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0);    // Red
    glVertex3f(0.0, 1.0, 0.0);
    glColor3f(0.0, 1.0, 0.0);    // Green
    glVertex3f(-1.0, -1.0, 0.0);
    glColor3f(0.0, 0.0, 1.0);    // Blue
    glVertex3f(1.0, -1.0, 0.0);
    glEnd();
}
void MidpointLine(int x0,int y0,int x1,int y1)
{
    int a,b,d1,d2,d,x,y;float m;if (x1<x0){d=x0,x0=x1,x1=d;d=y0,y0=y1,y1=d;}
    a=y0-y1,b=x1-x0;
    if (b==0)
        m=-1*a*100;
    else
        m=(float)a/(x0-x1);
    x=x0,y=y0;
    drawPoint(x,y,3);
    if (m>=0 && m<=1)
    {d=2*a+b;d1=2*a,d2=2*(a+b);
        while (x<x1)
        {	if (d<=0)	{	x++,y++,d+=d2;}
            else	{	x++,d+=d1;	}
            drawPoint(x,y,3);
        }}
    else if (m<=0 && m>=-1)
    {d=2*a-b;d1=2*a-2*b,d2=2*a;
        while (x<x1)
        {	if (d>0)	{	x++,y--,d+=d1;}
            else	{	x++,d+=d2;	}
            drawPoint(x,y,3);
        }	}
    else if (m>1)
    {d=a+2*b;d1=2*(a+b),d2=2*b;
        while (y<y1)
        {	if (d>0)	{	x++,y++,d+=d1;}
            else	{	y++,d+=d2;	}
            drawPoint(x,y,3);
        }	}
    else
    {d=a-2*b;d1=-2*b,d2=2*(a-b);
        while (y>y1)
        {	if (d<=0)	{	x++,y--,d+=d2;}
            else	{	y--,d+=d1;	}
            drawPoint(x,y,3);
        }}
}
void dda(double x1, double y1, double x2, double y2) {
    float x, y, xincre, yincre;
    int k = abs(x2 - x1);
    if (abs(y2 - y1) > k) { k = abs(y2 - y1); }
    xincre = (float) (x2 - x1) / k;
    yincre = (float) (y2 - y1) / k;
    x = x1;
    y = y1;
    for (int i = 1; i < k; i++) {
//        pDC->SetPixel(x, y, RGB(255, 0, 0));
        cout<<int(x)<<","<<int(y)<<endl;
        drawPoint(int(x),int(y),3);
        x = x + xincre;
        y = y + yincre;
    }
}
void drawLint(double x1, double y1, double x2, double y2) {

    glLineWidth(2);//设置线段宽度

    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(x1, y1); //定点坐标范围
    glVertex2f(x2, y2);
    glEnd();
}
void P2P(int x1,int y1,int x2,int y2) {
    int x, y, xi, yi;
    if (y1 > y2)  //将直线平移至原点
    {
        yi = y1 - y2;
        xi = x1 - x2;
    } else {
        yi = y2 - y1;
        xi = x2 - x1;
    }
    int FLAG = 0, f = x = y = 0;
    if ((y2 - y1) / (x2 - x1) > 0)
        FLAG = 1;  //判别平移后直线在第一还是第二象限
    int t = yi + xi;  //总步数

    glPointSize(1);


    glColor3f(1.0f, 1.0f, 0.0f);
    glPointSize(1);

    while (t)    //开始绘图
    {
        if (FLAG) {
            if (f <= 0) {
                y++;
                f += xi;
            } else {
                x++;
                f -= yi;
            }
        } else {
            if (f >= 0) {
                y++;
                f += xi;
            } else {
                x--;
                f += yi;
            }
        }
        glBegin(GL_POINTS);
        if (FLAG)
            glVertex2i(x, y);
        else
            glVertex2i(y, x);
        glEnd();
        t--;
    }
}


void MidPoint_Circle(int x0,int y0,int r)
{
    int x = 0;
    int y = r;
    int d = 1 - r;//d是1.25-r取整的结果
    glVertex2i(x0, y0);
    while (x < y)
    {
        if (d < 0) {
            d += 2 * x + 3;
        }
        else {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
        glVertex2i(x + x0, y + y0);
        glVertex2i(y + x0, x + y0);
        glVertex2i(y + x0, -x + y0);
        glVertex2i(x + x0, -y + y0);
        glVertex2i(-x + x0, -y + y0);
        glVertex2i(-y + x0, -x + y0);
        glVertex2i(-x + x0, y + y0);
        glVertex2i(-y + x0, x + y0);
    }
}
void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.7, 0.0, 0.2);
    glPointSize(2);
    glBegin(GL_POINTS);
    MidPoint_Circle(200, 200, 150);
    glEnd();
    glFlush();
}
void Bresenham_Circle(int xc, int yc, int r)
{
    int x, y, d;
    x = 0;
    y = r;
    d = 3 - 2 * r;
    glVertex2i(x + xc, y + yc);
    while (x < y)
    {
        if (d < 0)
        {
            d = d + 4 * x + 6;
        }
        else
        {
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;
        glVertex2i(x + xc, y + yc);
        glVertex2i(y + xc, x + yc);
        glVertex2i(y + xc, -x + yc);
        glVertex2i(x + xc, -y + yc);
        glVertex2i(-x + xc, -y + yc);
        glVertex2i(-y + xc, -x + yc);
        glVertex2i(-x + xc, y + yc);
        glVertex2i(-y + xc, x + yc);
    }
}
void lineBres(float x1,float y1,float x2,float y2){
    float dx = abs(x2-x1);
    float dy = abs(y2-y1);
    float p = 2*dy-dx;
    float twody = 2*dy,twodxdy = 2*(dy-dx);
    float x,y;
    float xEnd;
    if(x1 > x2){
        x=x2;y=y2;xEnd=x1;
    }
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_LINES);
    glVertex2i(x,y);
    while(x<xEnd){
        x++;
        if(p<0){
            p+=twodxdy;
        } else{
            y++;
            p+=twodxdy;
        }
        cout<<x<<"  "<<y<<endl;
        glVertex2f(x,y);
    }
    glEnd();
    glFlush();
}

void display2(int x1=0,int y1=100,int x2=20,int y2 = 0)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int x,y;
    int temp1 = 2 * dy;
    int temp2 = 2 * (dy - dx);
    int p = temp1 - dx;
    if(x1 > x2)
    {
        x = x2;
        y = y2;
        x2 = x1;
    }
    else{
        x = x1;
        y = y1;
    }

    glVertex2i(x,y);
    while(x < x2)
    {
        x++;
        if(p < 0)
            p += temp1;
        else
        {
            y++;
            p += temp2;
        }
        glVertex2i(x,y);
    }

}
int main() {
    float width = 800;
    float height = 600;
    float length = 1000;
    if (!glfwInit()) {
        cout << "Init failed" << endl;
    }
    GLFWwindow *window = glfwCreateWindow(width, height, "OpenGL", nullptr, nullptr);
    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glOrtho(-(width / 2), (width / 2), -(height / 2), (height / 2), -(length / 2), (height / 2));
    bool flag = false;
    float R = 100;
    float a = R;
    double lastx = R, lasty = 0, newx = R, newy = 0;
    int n = 0;
    while (!glfwWindowShouldClose(window)) {
//        myDisplay();
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_POINTS);
        for (int i = a; i < 100 - a; i++) {
            display2(100 - i, i, i, i);
        }
        cout << a << endl;
        glEnd();
    }
}


int main() {
    float width = 800;
    float height = 600;
    float length = 1000;
    if (!glfwInit()) {
        cout << "Init failed" << endl;
    }
    GLFWwindow *window = glfwCreateWindow(width, height, "OpenGL", nullptr, nullptr);
    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glOrtho(-(width/2),(width/2),-(height/2),(height/2),-(length/2),(height/2));
    bool flag = false;
    float R = 100;
    float a=R;
    double lastx=R,lasty=0,newx=R,newy=0;
    int n=0;
    while (!glfwWindowShouldClose(window)) {
//        myDisplay();
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1.0,0.0,0.0);
        glBegin(GL_POINTS);
        for(int i=a;i<100-a;i++){
            display2(100-i,i,i,i);
        }
        cout<<a<<endl;
        glEnd();
        glFlush();
//        dda(0,50,90,0);
//        MidpointLine(0,50,90,0);
//        drawLint(0,5,9,0);
//         P2P(-200,-200,12,12);
//        drawLint(lastx,lasty,newx,newy);
//        lineBres(0,90,50,0);
        lastx=newx;
        lasty=newy;
        if(!flag){
//            drawPoint(a,pow((R*R-a*a),1.0/2.0),5);
            a += 1;
            newx = a;
            newy = pow((R*R-a*a),1.0/2.0);
        }
        else{
//            drawPoint(a,pow((R*R-a*a),1.0/2.0),5);
            a -= 1;
            newx = a;
            newy = -pow((R*R-a*a),1.0/2.0);
        }
        if(a>100){
            flag = true;
        }
        else if(a<-100){
            flag = false;
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

//        #include "glad/glad.h"
//#include "GLFW/glfw3.h"
//#include "iostream"
//using namespace std;
//
//void Drawsin()
//{
//    const float factor = 0.1;
//    glBegin(GL_LINES);
//    glVertex2f(-1,0);
//    glVertex2f(1,0);
//    glVertex2f(0, -1);
//    glVertex2f(0, 1);
//    glEnd();
//    glBegin(GL_LINE_STRIP);
//    for (float x = -1 / factor;x < 1 / factor;x += 0.001)
//    {
//        glVertex2f(x * factor, sin(x) * factor);
//    }
//    glEnd();
//    glBegin(GL_LINE_STRIP);
//    for (float y = -1 / factor; y < 1 / factor; y += 0.001)
//    {
//        glVertex2f(y*factor,cos(y)*factor);
//    }
//    glEnd();
//}
//void DrawLines(float cursor_x,float cursor_y) {
//    glPushMatrix();
//    glLoadIdentity();
//    glTranslatef(0.0, 0.0, 0.f);
//    //设置直线宽度
//    glLineWidth(5.0f);
//    glBegin(GL_LINES);
//    {
//        glColor3f(0.0f, 0.0f, 1.0f);
//        // 设置直线坐标
//        glVertex3f(-1.f, cursor_y, 0.0f);
//        glVertex3f(1.f, cursor_y, 0.0f);
//        glColor3f(1.0f, 0.0f, 0.0f);
//        glVertex3f(cursor_x, -1.f, 0.0f);
//        glVertex3f(cursor_x, 1.f, 0.0f);
//    }
//    glEnd();
//    glPopMatrix();
//}
//
//void drawPoint(float x,float y,float size) {
//    glPointSize(size);
//    glBegin(GL_POINTS);
//    glColor3f(1.0, 0.0, 0.0);
//    glVertex2f(x, y);
//    glEnd();
//}
//
//void drawTriangle() {
//    glClearColor(0.0, 0.0, 0.0, 0.0);
//    glClear(GL_COLOR_BUFFER_BIT);
//    glBegin(GL_TRIANGLES);
//    glColor3f(1.0, 0.0, 0.0);    // Red
//    glVertex3f(0.0, 1.0, 0.0);
//    glColor3f(0.0, 1.0, 0.0);    // Green
//    glVertex3f(-1.0, -1.0, 0.0);
//    glColor3f(0.0, 0.0, 1.0);    // Blue
//    glVertex3f(1.0, -1.0, 0.0);
//    glEnd();
//}
//void MidpointLine(int x0,int y0,int x1,int y1)
//{
//    int a,b,d1,d2,d,x,y;float m;if (x1<x0){d=x0,x0=x1,x1=d;d=y0,y0=y1,y1=d;}
//    a=y0-y1,b=x1-x0;
//    if (b==0)
//        m=-1*a*100;
//    else
//        m=(float)a/(x0-x1);
//    x=x0,y=y0;
//    drawPoint(x,y,3);
//    if (m>=0 && m<=1)
//    {d=2*a+b;d1=2*a,d2=2*(a+b);
//        while (x<x1)
//        {	if (d<=0)	{	x++,y++,d+=d2;}
//            else	{	x++,d+=d1;	}
//            drawPoint(x,y,3);
//        }}
//    else if (m<=0 && m>=-1)
//    {d=2*a-b;d1=2*a-2*b,d2=2*a;
//        while (x<x1)
//        {	if (d>0)	{	x++,y--,d+=d1;}
//            else	{	x++,d+=d2;	}
//            drawPoint(x,y,3);
//        }	}
//    else if (m>1)
//    {d=a+2*b;d1=2*(a+b),d2=2*b;
//        while (y<y1)
//        {	if (d>0)	{	x++,y++,d+=d1;}
//            else	{	y++,d+=d2;	}
//            drawPoint(x,y,3);
//        }	}
//    else
//    {d=a-2*b;d1=-2*b,d2=2*(a-b);
//        while (y>y1)
//        {	if (d<=0)	{	x++,y--,d+=d2;}
//            else	{	y--,d+=d1;	}
//            drawPoint(x,y,3);
//        }}
//}
//void dda(double x1, double y1, double x2, double y2) {
//    float x, y, xincre, yincre;
//    int k = abs(x2 - x1);
//    if (abs(y2 - y1) > k) { k = abs(y2 - y1); }
//    xincre = (float) (x2 - x1) / k;
//    yincre = (float) (y2 - y1) / k;
//    x = x1;
//    y = y1;
//    for (int i = 1; i < k; i++) {
////        pDC->SetPixel(x, y, RGB(255, 0, 0));
//        cout<<int(x)<<","<<int(y)<<endl;
//        drawPoint(int(x),int(y),3);
//        x = x + xincre;
//        y = y + yincre;
//    }
//}
//void drawLint(double x1, double y1, double x2, double y2) {
//
//    glLineWidth(2);//设置线段宽度
//
//    glBegin(GL_LINES);
//    glColor3f(1.0, 0.0, 0.0);
//    glVertex2f(x1, y1); //定点坐标范围
//    glVertex2f(x2, y2);
//    glEnd();
//}
//void P2P(int x1,int y1,int x2,int y2) {
//    int x, y, xi, yi;
//    if (y1 > y2)  //将直线平移至原点
//    {
//        yi = y1 - y2;
//        xi = x1 - x2;
//    } else {
//        yi = y2 - y1;
//        xi = x2 - x1;
//    }
//    int FLAG = 0, f = x = y = 0;
//    if ((y2 - y1) / (x2 - x1) > 0)
//        FLAG = 1;  //判别平移后直线在第一还是第二象限
//    int t = yi + xi;  //总步数
//
//    glPointSize(1);
//
//
//    glColor3f(1.0f, 1.0f, 0.0f);
//    glPointSize(1);
//
//    while (t)    //开始绘图
//    {
//        if (FLAG) {
//            if (f <= 0) {
//                y++;
//                f += xi;
//            } else {
//                x++;
//                f -= yi;
//            }
//        } else {
//            if (f >= 0) {
//                y++;
//                f += xi;
//            } else {
//                x--;
//                f += yi;
//            }
//        }
//        glBegin(GL_POINTS);
//        if (FLAG)
//            glVertex2i(x, y);
//        else
//            glVertex2i(y, x);
//        glEnd();
//        t--;
//    }
//}
//
//
//void MidPoint_Circle(int x0,int y0,int r)
//{
//    int x = 0;
//    int y = r;
//    int d = 1 - r;//d是1.25-r取整的结果
//    glVertex2i(x0, y0);
//    while (x < y)
//    {
//        if (d < 0) {
//            d += 2 * x + 3;
//        }
//        else {
//            d += 2 * (x - y) + 5;
//            y--;
//        }
//        x++;
//        glVertex2i(x + x0, y + y0);
//        glVertex2i(y + x0, x + y0);
//        glVertex2i(y + x0, -x + y0);
//        glVertex2i(x + x0, -y + y0);
//        glVertex2i(-x + x0, -y + y0);
//        glVertex2i(-y + x0, -x + y0);
//        glVertex2i(-x + x0, y + y0);
//        glVertex2i(-y + x0, x + y0);
//    }
//}
//void myDisplay(void)
//{
//    glClear(GL_COLOR_BUFFER_BIT);
//    glColor3f(0.7, 0.0, 0.2);
//    glPointSize(2);
//    glBegin(GL_POINTS);
//    MidPoint_Circle(200, 200, 150);
//    glEnd();
//    glFlush();
//}
//void Bresenham_Circle(int xc, int yc, int r)
//{
//    int x, y, d;
//    x = 0;
//    y = r;
//    d = 3 - 2 * r;
//    glVertex2i(x + xc, y + yc);
//    while (x < y)
//    {
//        if (d < 0)
//        {
//            d = d + 4 * x + 6;
//        }
//        else
//        {
//            d = d + 4 * (x - y) + 10;
//            y--;
//        }
//        x++;
//        glVertex2i(x + xc, y + yc);
//        glVertex2i(y + xc, x + yc);
//        glVertex2i(y + xc, -x + yc);
//        glVertex2i(x + xc, -y + yc);
//        glVertex2i(-x + xc, -y + yc);
//        glVertex2i(-y + xc, -x + yc);
//        glVertex2i(-x + xc, y + yc);
//        glVertex2i(-y + xc, x + yc);
//    }
//}
//void lineBres(float x1,float y1,float x2,float y2){
//    float dx = abs(x2-x1);
//    float dy = abs(y2-y1);
//    float p = 2*dy-dx;
//    float twody = 2*dy,twodxdy = 2*(dy-dx);
//    float x,y;
//    float xEnd;
//    if(x1 > x2){
//        x=x2;y=y2;xEnd=x1;
//    }
//    glClear(GL_COLOR_BUFFER_BIT);
//    glColor3f(1.0,0.0,0.0);
//    glBegin(GL_LINES);
//    glVertex2i(x,y);
//    while(x<xEnd){
//        x++;
//        if(p<0){
//            p+=twodxdy;
//        } else{
//            y++;
//            p+=twodxdy;
//        }
//       cout<<x<<"  "<<y<<endl;
//        glVertex2f(x,y);
//    }
//    glEnd();
//    glFlush();
//}
//
//void display2(int x1=0,int y1=100,int x2=20,int y2 = 0)
//{
//    int dx = abs(x2 - x1);
//    int dy = abs(y2 - y1);
//    int x,y;
//    int temp1 = 2 * dy;
//    int temp2 = 2 * (dy - dx);
//    int p = temp1 - dx;
//    if(x1 > x2)
//    {
//        x = x2;
//        y = y2;
//        x2 = x1;
//    }
//    else{
//        x = x1;
//        y = y1;
//    }
//
//    glVertex2i(x,y);
//    while(x < x2)
//    {
//        x++;
//        if(p < 0)
//            p += temp1;
//        else
//        {
//            y++;
//            p += temp2;
//        }
//        glVertex2i(x,y);
//    }
//
//}






//
//for(int i=0;i<cq.size();i++){
//std::cout<<"==="<<std::endl;
//std::cout<<cq.front().getX()<<"==="<<cq.front().getY()<<std::endl;
//float yy = cq.front().getY();
//float xx = cq.front().getX();
//draw_red_circle(xx,yy);
//if(yy<=-0.85f+0.01f && yy>=-0.85f-0.01f){
//if( (xx<1.1+xpos * 2 && xx>0.9+xpos * 2)){
//cq.front().changeYdrec();
//}
//}
//cq.front().move();
//if(strcmp(msg,"Mosue left button clicked!") == 0){
//std::cout<<"using left mouse"<<std::endl;
//
//cq.front().setXspeed((random()%1000 - 500.0)/500.0);
//cq.front().setYspeed((random()%1000 - 500.0)/500.0);
//
//strcpy(msg,"");
//}
//cq.push(cq.front());
//cq.pop();
//}