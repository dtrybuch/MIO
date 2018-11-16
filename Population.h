#pragma once
#include<stdlib.h>
#include<iostream>
#include"funkcje.h"

class Population {
private:
	int _pop_size;
public:
	double gbest[2];
	Particle * ParticleTable;
	Population(int pop_size, double c1, double c2, double *best);
	void Next_Step(double *best);
};