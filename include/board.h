//
// Created by 孙文礼 on 2021/5/8.
//

#ifndef UNTITLED2_BOARD_H
#define UNTITLED2_BOARD_H

class Board {
    float x, y;
    float width;
    float thickness;
public:
    Board(){
        this->x = 0.0f;
        this->y = -0.8f;
        this->width = 0.5f;
        this->thickness = 0.01f;
    }

    float getX() const { return this->x; }

    void setX(float data) { this->x = data; }

    float getY() const { return this->y; }

    void setY(float data) { this->y = data; }

    float getWidth() const{return this->width;}

    void setWidth(float data){this->width = data;}

    bool isBump(float xx,float yy){
        if(xx<this->x+this->width/2 && xx>this->x-this->width/2){
            if(yy<this->y+0.05f && yy>this->y-0.05f){
                return true;
            }
        }
        return false;
    }

};

#endif //UNTITLED2_BOARD_H
