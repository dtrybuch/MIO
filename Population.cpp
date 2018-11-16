#include"Population.h"

Population::Population(int pop_size, double _c1, double _c2, double *best)
{
	_pop_size = pop_size;
	ParticleTable = new Particle[pop_size];
	for (int i = 0; i < pop_size; i++)
	{
		ParticleTable[i] = Particle();
		ParticleTable[i].c1 = _c1;
		ParticleTable[i].c2 = _c2;
		ParticleTable[i].pbest[0] = ParticleTable[i].polozenie[0];
		ParticleTable[i].pbest[1] = ParticleTable[i].polozenie[1];
		ParticleTable[i].best_wynik = function(ParticleTable[i].polozenie[0], ParticleTable[i].polozenie[1]);
		if (ParticleTable[i].best_wynik < *best)
		{
			best[0] = ParticleTable[i].best_wynik;
			best[1] = ParticleTable[i].pbest[0];
			best[2] = ParticleTable[i].pbest[1];
		}
	}
	for (int i = 0; i < _pop_size; i++)
	{
		ParticleTable[i].best_wynik = best[0];
		ParticleTable[i].gbest[0] = best[1];
		ParticleTable[i].gbest[1] = best[2];
	}
}
void Population::Next_Step(double *best)
{
	
	for (int i = 0; i < _pop_size; i++)
	{
		ParticleTable[i].change_position();
		ParticleTable[i].change_speed();
	}
	for (int i = 0; i < _pop_size; i++)
	{
		double tmp = function(ParticleTable[i].polozenie[0], ParticleTable[i].polozenie[1]);
		
		if (ParticleTable[i].best_wynik > tmp)
		{
			ParticleTable[i].pbest[0] = ParticleTable[i].polozenie[0];
			ParticleTable[i].pbest[1] = ParticleTable[i].polozenie[1];
			ParticleTable[i].best_wynik = tmp;
		}
		if (ParticleTable[i].best_wynik < best[0])
		{
			best[0] = ParticleTable[i].best_wynik;
			best[1] = ParticleTable[i].polozenie[0];
			best[2] = ParticleTable[i].polozenie[1];
		}
	}
	for (int i = 0; i < _pop_size; i++)
	{
		ParticleTable[i].best_wynik = best[0];
		ParticleTable[i].gbest[0] = best[1];
		ParticleTable[i].gbest[1] = best[2];
	}
}