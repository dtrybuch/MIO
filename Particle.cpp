#include"Particle.h"

void Particle::change_position()
{
	if ((polozenie[0] + _speed[0] > -10 && polozenie[0] + _speed[0] <10) && (polozenie[1] + _speed[1] > -10 && polozenie[1] + _speed[1]<10))
	{
		polozenie[0] = polozenie[0] + _speed[0];
		polozenie[1] = polozenie[1] + _speed[1];
	}
	else if (polozenie[0] + _speed[0] < -10 && (polozenie[1] + _speed[1] > -10 && polozenie[1] + _speed[1] < 10))
	{
		double tmp = polozenie[0] + _speed[0] + 10;
		polozenie[0] = polozenie[0] + _speed[0] - tmp;
		polozenie[1]= polozenie[1]+_speed[1];
	}
	else if (polozenie[0] + _speed[0] > 10 && (polozenie[1] + _speed[1] > -10 && polozenie[1] + _speed[1] < 10))
	{
		double tmp = polozenie[0] + _speed[0] - 10;
		polozenie[0] = polozenie[0] + _speed[0] + tmp;
		polozenie[1] = polozenie[1] + _speed[1];
	}
	else if ((polozenie[0] + _speed[0] > -10 && polozenie[0] + _speed[0] < 10) && polozenie[1] + _speed[1] < -10)
	{
		double tmp = polozenie[1] + _speed[1] + 10;
		polozenie[0] = polozenie[0] + _speed[0];
		polozenie[1] = polozenie[1] + _speed[1] - tmp;
	}
	else if ((polozenie[0] + _speed[0] > -10 && polozenie[0] + _speed[0] < 10) && polozenie[1] + _speed[1] > 10)
	{
		double tmp = polozenie[1] + _speed[1] - 10;
		polozenie[0] = polozenie[0] + _speed[0] ;
		polozenie[1] = polozenie[1] + _speed[1] + tmp;
	}
	else if (polozenie[0] + _speed[0] < -10 && polozenie[1] + _speed[1] < -10)
	{
		double tmp1 = polozenie[0] + _speed[0] + 10;
		double tmp2 = polozenie[1] + _speed[1] + 10;
		polozenie[0] = polozenie[0] + _speed[0] - tmp1;
		polozenie[1] = polozenie[1] + _speed[1] - tmp2;
	}
	else if ((polozenie[0] + _speed[0] > 10 && polozenie[1] + _speed[1] < -10))
	{
		double tmp1 = polozenie[0] + _speed[0] - 10;
		double tmp2 = polozenie[1] + _speed[1] + 10;
		polozenie[0] = polozenie[0] + _speed[0] + tmp1;
		polozenie[1] = polozenie[1] + _speed[1] - tmp2;
	}
	else if ((polozenie[0] + _speed[0] > 10 && polozenie[1] + _speed[1] > 10))
	{
		double tmp1 = polozenie[0] + _speed[0] - 10;
		double tmp2 = polozenie[1] + _speed[1] - 10;
		polozenie[0] = polozenie[0] + _speed[0] + tmp1;
		polozenie[1] = polozenie[1] + _speed[1] + tmp2;
	}
	else
	{
		double tmp1 = polozenie[0] + _speed[0] + 10;
		double tmp2 = polozenie[1] + _speed[1] - 10;
		polozenie[0] = polozenie[0] + _speed[0] - tmp1;
		polozenie[1] = polozenie[1] + _speed[1] + tmp2;
	}
	
}
double Particle::losuj(double zakres1, double zakres2)
{
	double dlugosc = zakres2 - zakres1;
	double wynik = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	wynik = wynik * dlugosc - dlugosc / 2;
	return wynik;
}
void Particle::change_speed()
{
	if ((_speed[0] <= 0.01 &&_speed[0]>=-0.01) &&(_speed[1] <= 0.01 &&_speed[1] >= -0.01))
	{
		_speed[0] = _speed[0] + losuj(0, c1)*(pbest[0] - polozenie[0]) + losuj(0, c2)*(gbest[0] - polozenie[0]);
		_speed[1] = _speed[1] + losuj(0, c1)*(pbest[1] - polozenie[1]) + losuj(0, c2)*(gbest[1] - polozenie[1]);
	}
	else
	{
		_speed[0] = 0.01;
		_speed[1] = 0.01;
	}
	//std::cout <<"speed :"<< _speed[0] <<" "<<_speed[1] <<std::endl;
}