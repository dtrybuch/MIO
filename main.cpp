
#include "Population.h"
#include"Particle.h"
#include"funkcje.h"
#include<stdlib.h>
#include<iostream>
#include <fstream>

using namespace std;

int main()
{
	fstream plik;
	plik.open("wyniki najlepsza w kazdej iteracji.txt", ios::app);
	srand(time(NULL));
	double best[3] = { 10000.,10000.,10000. };
	Population pierwsza(20, 1.5, 1.5, best);
	Particle czastka;
	for (int i = 0; i < 4000; i++)
	{
		pierwsza.Next_Step(best);
		//cout  << best[0] << " " << best[1] << " " << best[2] << endl;
		//printf("%e ,%e, %e\n", best[0], best[1], best[2]);
		plik << i << " " << best[0]<<endl;
	}
	//plik << best[0] << " " << best[1] << " " << best[2] << endl;
	//plik << best[0] << endl;
	cout << best[0] << " " << best[1] << " " << best[2] << endl;
	plik.close();
	system("pause");
	return 0;
}