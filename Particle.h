#pragma once
#include<stdlib.h>
#include<iostream>
#include<time.h>

class Particle {
private:
	double _speed[2];
	
public:
	double c1;
	double c2;
	double pbest[2];
	double gbest[2];
	double polozenie[2];
	double best_wynik; // najlepsze dopasowanie funkcji- wartosc 
	Particle()
	{
		polozenie[0] = losuj(-10, 10);
		polozenie[1] = losuj(-10, 10);
		_speed[0] = losuj(0, 0.1);
		_speed[1] = losuj(0, 0.1);
	}
	void change_position();
	void change_speed();
	double losuj(double zakres1, double zakres2);
};


