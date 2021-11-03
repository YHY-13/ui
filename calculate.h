#ifndef CALCULATE_H
#define CALCULATE_H


class Calculate
{
public:
     float x1,x2,x3,x4,x5;//输入干燥参数
     //float y1,y2,y3,y4,y5;//输出干燥指标
public:
    Calculate(float x1,float x2,float x3,float x4,float x5){//构造函数
        this->x1=x1;
        this->x2=x2;
        this->x3=x3;
        this->x4=x4;
        this->x5=x5;
    }
    virtual float func_time()=0;//纯虚函数
    virtual float func_speed()=0;
    virtual float func_temp()=0;
    virtual float func_bud()=0;
    virtual float func_fatty()=0;
};
class corn:public Calculate
{
public:
    corn(float x1,float x2,float x3,float x4,float x5):Calculate(x1,x2,x3,x4,x5) {}
    virtual float func_time();
    virtual float func_speed();
    virtual float func_temp();
    virtual float func_bud();
    virtual float func_fatty();
};
class paddy:public Calculate
{
public:
    paddy(float x1,float x2,float x3,float x4,float x5):Calculate(x1,x2,x3,x4,x5) {}
    virtual float func_time();
    virtual float func_speed();
    virtual float func_temp();
    virtual float func_bud();
    virtual float func_fatty();
};
class wheat:public Calculate
{
public:
    wheat(float x1,float x2,float x3,float x4,float x5):Calculate(x1,x2,x3,x4,x5) {}
    virtual float func_time();
    virtual float func_speed();
    virtual float func_temp();
    virtual float func_bud();
    virtual float func_fatty();
};
class peanut:public Calculate
{
public:
    peanut(float x1,float x2,float x3,float x4,float x5):Calculate(x1,x2,x3,x4,x5) {}
    virtual float func_time();
    virtual float func_speed();
    virtual float func_temp();
    virtual float func_bud();
    virtual float func_fatty();
};
class potato:public Calculate
{
public:
    potato(float x1,float x2,float x3,float x4,float x5):Calculate(x1,x2,x3,x4,x5) {}
    virtual float func_time();
    virtual float func_speed();
    virtual float func_temp();
    virtual float func_bud();
    virtual float func_fatty();
    float func_energy();
};
#endif // CALCULATE_H
