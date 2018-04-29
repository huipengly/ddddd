#ifndef _PSO_H_
#define _PSO_H_

#include "search.h"

using std::vector;

class Particle
{
protected:
    int dimension;
    int position[1000];           //粒子位置
    double velocity[1000];        //粒子速度
    double result;                  //粒子当前位置结果
    Route_info route_info;
    int best_position[1000];      //记录粒子历史最优位置
    double best_result;             //记录粒子历时最优值
    Route_info best_route_info;
    double position_min_value;
    double position_max_value;
    double velocity_min_value;
    double velocity_max_value;
    double c1;
    double c2;
    double omega;
public:
    Particle();
    ~Particle();
//    void print();
//    void init(int dsize, double min, double max);//初始化粒子，dsize是维数
    void move();            //粒子移动
    double UpdateValue();   //更新粒子值
	void UpdateSpeed(Particle best_particle);
    Particle& operator= (const Particle& obj);//重载等号，数组复制值，而不是地址
	double get_best_result();
	void set_c1_c2(double c1, double c2);
//    double *getx();
};

//template<typename T>//粒子的取值，整数规划/实数规划
class PSO
{
protected:
    vector<Particle> particle_swarm;     //粒子群
	int generation;                     //进化代数
    int max_generation;                 //最大进化代数

    int particle_number;                 //粒子数
//    int particle_dimension;             //粒子维数
//
//    int particle_min_value;             //粒子最小取值范围
//    int particle_max_value;             //粒子最大取值范围

    Particle best_particle;            //历史最优粒子

public:
    PSO(int max_generation, int particle_number);
    ~PSO();
//	void init(int nsize, int dsize, int min, int max, int maxgen);
    void print(int i);
    void find_best_result();
    void swarm_move();
    void swarm_update_speed();
    void run();
	double get_best_result();

};

#endif
