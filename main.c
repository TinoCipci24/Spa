#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "stl.h"

int main(void) {
	Objekt3D objekt = citaj_binarni("primjerbin.stl");
	printf("Ucitano trokuta: %u\n", objekt.broj);

	zapisi_tekstualni("izlaz.stl", &objekt);

	Objekt3D objekt_tekst = citaj_tekstualni("izlaz.stl");
	printf("Ucitano iz tekstualne: %u trokuta\n", objekt_tekst.broj);

	zapisi_binarni("izlaz_kopija.stl", &objekt_tekst);

	obrisi_objekt(&objekt);
	obrisi_objekt(&objekt_tekst);

	return 0;
}