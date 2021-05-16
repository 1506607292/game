//
// Created by 孙文礼 on 2021/5/8.
//

#ifndef UNTITLED2_CIRCLE_H
#define UNTITLED2_CIRCLE_H
class Circle{
    float x,y;
    float xspeed,yspeed;
    float speed;
public:
    Circle(){
        this->x=0;
        this->y=-0.8;
        this->xspeed = (random()%1000 - 500.0)/500.0;
        this->yspeed = (random()%1000 - 500.0)/500.0;
        this->speed = 50;
    }
    void randSpeed(){
        this->xspeed = (random()%1000 - 500.0)/500.0;
        this->yspeed = (random()%1000 - 500.0)/500.0;
    }
    void move(){
        this->x+=this->xspeed/this->speed;
        this->y+=this->yspeed/this->speed;
        if(this->y>=1||this->y<=-1){
            this->yspeed=-this->yspeed;
        }
        if(this->x>=1||this->x<=-1){
            this->xspeed=-this->xspeed;
        }
    }
    float getX(){
        return this->x;
    }
    float getY(){
        return this->y;
    }
    void setX(float data){
        this->x = data;
    }
    void setY(float data){
        this->y = data;
    }
    void changeXdrec(){
        this->xspeed = -this->xspeed;
    }
    void changeYdrec(){
        this->yspeed = -this->yspeed;
    }
    void setXspeed(float data){
        this->xspeed = data;
    }
    void setYspeed(float data){
        this->yspeed = data;
    }
    float getXspeed(){
        return this->xspeed;
    }
    float getYspeed(){
        return this->yspeed;
    }
    void setSpeed(float data){
        this->speed = data;
    }

    bool isBump(float xx,float yy){
        if((this->x-xx)*(this->x-xx)+(this->y-yy)*(this->y-yy) < 0.01){
            return true;
        }
        return false;
    }

};
#endif //UNTITLED2_CIRCLE_H
