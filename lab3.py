import numpy as np
import math
import random
import matplotlib.pyplot as plt
import pylab

liczba_pop = 20  #liczba chromosomow
dlugosc_pop = 22  #N genow
population = np.random.randint(2, size=(liczba_pop, dlugosc_pop))


class wynik:
    najlepszy_wynik = 0
    index = -3
    argument = 0
    y = []
    x = []
    srednia = []
    iteracja = []
    liczba_iteracji = 0
    odch_standardowe = []
# print(new_population)


def funkcja(x):
    return x * math.sin(10 * math.pi * x) + 1


def logical_xor(x,y):
    if x==y:
        return 0
    else:
        return 1


def przeliczanie_na_dz(ktora):
    i = dlugosc_pop - 1
    suma1 = 0
    for z in population[ktora, ]:
        suma1 = suma1 + math.pow(z * 2, i)
        i = i - 1
    wynik = suma1 / 1398101 - 1
    return wynik


def przeliczanie_na_graya(ktora):
    zamienione = np.zeros((liczba_pop, dlugosc_pop), dtype=int)  # tablica do zapisania zamienionych z kodu graya na binarne

    zamienione[ktora, 0] = population[ktora, 0]
    for g in range(1, dlugosc_pop-1):
        zamienione[ktora, g] = logical_xor(zamienione[ktora, g-1], population[ktora, g])
    i = dlugosc_pop - 1
    suma1 = 0
    for z in zamienione[ktora, ]:
        suma1 = suma1 + math.pow(z * 2, i)
        i = i - 1
    wynik = suma1 / 1398101 - 1
    return wynik


def naj_przystosowanie():
    #print(przeliczanie_na_dz(2))
    najlepszy = przeliczanie_na_dz(0)
    #najlepszy = przeliczanie_na_graya(0)

    index = 0
    przystosowanie = []
    suma = 0
    argument = 0
    for x in range(liczba_pop - 1):
        przystosowanie.append(funkcja(przeliczanie_na_dz(x)))
        #przystosowanie.append(funkcja(przeliczanie_na_graya(x)))
        suma = suma + funkcja(przeliczanie_na_dz(x))
        #suma = suma + funkcja(przeliczanie_na_graya(x))
        if przystosowanie[x] > najlepszy:
            najlepszy = przystosowanie[x]
            index = x
            argument = przeliczanie_na_dz(x)
            #argument = przeliczanie_na_graya(x)
    if najlepszy > wynik.najlepszy_wynik:
        wynik.najlepszy_wynik = najlepszy
        wynik.index = index
        wynik.argument = argument

    wynik.y.append(najlepszy)
    wynik.x.append(argument)
    wynik.srednia.append(suma/liczba_pop)
    wynik.liczba_iteracji += 1
    suma_odchylenie = 0
    for i in range(liczba_pop - 1):
        suma_odchylenie += ((suma/liczba_pop)- przystosowanie[i]) * ((suma/liczba_pop)-przystosowanie[i])
    wynik.odch_standardowe.append(math.sqrt(suma_odchylenie/liczba_pop))
    #print(przystosowanie)
    #print("Najlepszy:\n", najlepszy)
    #print("Index:\n", index)
    #print("Argument", argument)
    #print("Suma", suma)
    #print(population)
    return przystosowanie


def selekcja():
    przystosowanie = naj_przystosowanie()
    szerokosc = []
    # suma przystosowan
    suma1 = 0
    # tablica z ruletka
    ruletka = np.zeros(liczba_pop)
    # tablica przezywajacych
    survivors = []
    for i in range(liczba_pop):
        przystosowanie.append(funkcja(przeliczanie_na_dz(i)))
        #przystosowanie.append(funkcja(przeliczanie_na_graya(i)))
        suma1 = suma1 + funkcja(przeliczanie_na_dz(i))
        #suma1 = suma1 + funkcja(przeliczanie_na_graya(i))
    for l in range(liczba_pop):
        szerokosc.append(funkcja(przeliczanie_na_dz(l)) / suma1)
        #szerokosc.append(funkcja(przeliczanie_na_graya(l)) / suma1)
        if l == 0:
            ruletka[l] = szerokosc[l]
        else:
            ruletka[l] = ruletka[l - 1] + szerokosc[l]
    #print(ruletka)
    for q in range(liczba_pop):
        losowa = random.uniform(0, 1)
        for i in range(liczba_pop):
            if losowa <= ruletka[i]:
                survivors.append(i)
                break
   # print(survivors)
    return survivors


def zamiana_pop(populacja):
    survivors = selekcja()
    new_population = np.zeros((liczba_pop, dlugosc_pop), dtype=int)
    for o in range(liczba_pop-1):
        new_population[o] = (populacja[survivors[o]])
    return new_population


def krzyzowanie():
    # liczba osobnikow do krzyzowania
    pcross = 0.2
    ilosc = math.floor(pcross * liczba_pop)
    rantab = []  # tablica wylosowanych elementow
    for x in range(ilosc):
        obecny = random.randint(1, liczba_pop)
        for i in range(x):
            if rantab[i] == obecny:
                obecny = random.randint(1, liczba_pop)
        rantab.append(obecny)
    if ilosc % 2 != 0:
        rantab.append((random.randint(1, liczba_pop)))
        ilosc += 1
   # print(rantab)
    dlugosc = math.floor(ilosc / 2)
    locus = random.randint(1, dlugosc_pop)
    #print(locus)
    # krzyzowanie wlasciwe
    licznik = 0
    while licznik < dlugosc:
        for i in range(locus, dlugosc_pop):
            if population[rantab[licznik] - 1, i] != population[rantab[licznik + 1] - 1, i]:
                tmp = population[rantab[licznik] - 1, i]
                population[rantab[licznik] - 1, i] = population[rantab[licznik + 1] - 1, i]
                population[rantab[licznik + 1] - 1, i] = tmp
        licznik += 2


def mutacja():
    pmut = 0.01
    ilosc = math.floor(pmut*liczba_pop*dlugosc_pop)
    rantab = np.zeros((ilosc, 2), dtype=int)  # tablica wylosowanych elementow
    for liczba in range(ilosc):
        rantab[liczba, 0] = random.randint(1, liczba_pop)
        rantab[liczba, 1] = random.randint(1, dlugosc_pop)

    for i in range(ilosc-1):
        if population[rantab[i, 0]-1, rantab[i, 1]-1] == 0:
            population[rantab[i, 0]-1, rantab[i, 1]-1] = 1
        else:
            population[rantab[i, 0]-1, rantab[i, 1]-1] = 0


i = 0

while i < 100:
    wynik.iteracja.append(wynik.liczba_iteracji)
    population = zamiana_pop(population)  #selekcja
    krzyzowanie()
    mutacja()
    naj_przystosowanie()
    wynik.iteracja.append(wynik.liczba_iteracji)
    i += 1

print("Index: ", wynik.index,  "\n Argument: ", wynik.argument, "\n Najlepszy: ", wynik.najlepszy_wynik)
#plt.plot(wynik.x, wynik.y)
#plt.plot(wynik.x, wynik.srednia)
#plt.plot(wynik.iteracja, wynik.srednia)
#plt.plot(wynik.iteracja, wynik.odch_standardowe)
plt.plot(wynik.iteracja, wynik.y)
plt.title("Kodowanie binarne, srednie przystosowanie")
plt.xlabel("Liczba sprawdzania przystosowan")
plt.show()


