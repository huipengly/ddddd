#include <iostream>
#include <algorithm>
#include <ctime>
#include "pso.h"
#include "search.h"

using namespace std;

Particle::Particle()
{
    dimension = 1000;
    this->position_min_value = 0;
    this->position_max_value = 2;
    this->velocity_min_value = -2;
    this->velocity_max_value = 2;

    for(auto &pos : position)       //随机位置
    {
        pos = rand_for_alternative_route();
    }

    for (auto &vel : velocity)      //每个维度速度随机一个
    {
        vel = velocity_min_value + (velocity_max_value - velocity_min_value) * rand() / RAND_MAX;
    }

    best_result = 1;

    c1 = 2.05;
    c2 = 1.85;
    omega = 0.5;
}

Particle::~Particle()
{

}

//void Particle::print()
//{
//    for(int i = 0; i < d; i++)
//    {
//        cout << "x" << i+1 << " = " << x[i] << endl;
//    }
//    for(int i = 0; i < d; i++)
//    {
//        cout << "v" << i+1 << " = " << v[i] << endl;
//    }
//    cout << "value is " << value << endl;
//}

void Particle::move()
{
    for(int i = 0; i < dimension; ++i)
    {
        position[i] += velocity[i];
        if(position[i] > position_max_value)
        {
            position[i] = static_cast<int>(position_max_value);
        }
        if(position[i] < position_min_value)
        {
            position[i] = static_cast<int>(position_min_value);
        }
    }
}

double Particle::UpdateValue()
{
    result = calculate_max_percentage(position, route_info);
    if(result < best_result)
    {
        best_result = result;      //保存最优值
        for(int i = 0; i < dimension; i++)
        {
            best_position[i] = position[i];
        }
        best_route_info = route_info;
    }
    return result;
}

void Particle::UpdateSpeed(Particle best_particle)
{
    for(int i = 0; i < dimension; i++)
    {
        double kxi = (rand() / static_cast<double>(RAND_MAX));
        double eta = (rand() / static_cast<double>(RAND_MAX));
        velocity[i] = omega*velocity[i] + c1 * kxi * (best_position[i] - position[i]) + c2 * eta * (best_particle.best_position[i] - position[i]);
    }
}

double Particle::get_best_result()
{
    return best_result;
}

//double* Particle::getx()
//{
//    return x;
//}

PSO::PSO(int max_generation, int particle_number)
{
    this->max_generation = max_generation;
    this->particle_number = particle_number;
    generation = 0;
    particle_swarm.resize(particle_number);
}

PSO::~PSO()
= default;

void PSO::print(int i)
{
    cout << "This is " << i + 1 << "'s generation" << endl;
    cout << "best result = " << best_particle.get_best_result() << endl;
}

void PSO::find_best_result()
{
    double result[1000];
    for(int i = 0; i < 1000; ++i)
    {
        result[i] = particle_swarm[i].UpdateValue();//计算每个粒子值
    }

    double *temp_min_result = min_element(&result[0], &result[999]);

    if(best_particle.get_best_result() < *temp_min_result)//当前粒子群里最低，比历史最优还低。替换历史最优
    {
        best_particle = particle_swarm[temp_min_result - &result[0]];//FIXME:复制的时候有数组，只复制了指针
    }
}

void PSO::swarm_move()
{
    for(auto particle : particle_swarm)
    {
        particle.move();//每个粒子移动
    }
}

void PSO::swarm_update_speed()
{
    for(auto particle : particle_swarm)
    {
        particle.UpdateSpeed(best_particle);//TODO:添加变omega
    }
}

void PSO::run()
{

	////测试已知三维最优解
	//double *a = p[0].getx();
	//a[0] = 1;
	//a[1] = 1;
	//a[2] = 1;

	//double *a = p[0].getx();
	//for (int i = 0; i < 50; i++)
	//{
	//	a[i] = 1;
	//}

    find_best_result();
    swarm_move();
    find_best_result();
    while (generation < max_generation)
    {
        swarm_update_speed();
        swarm_move();
        find_best_result();
        ++generation;
        //print(gen);
    }

//    cout << "final result is:" << endl;
    cout << "best value = " << best_particle.get_best_result() << endl;
//    for(int i = 0; i < dsize; i++)
//    {
//        cout << "x" << i+1 << " = " << bestpx[i] << endl;
//    }
}

double PSO::get_best_result()
{
	return best_particle.get_best_result();
}