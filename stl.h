#define _CRT_SECURE_NO_WARNINGS
#ifndef STL_H
#define STL_H

#pragma pack(push, 1)

typedef struct {
	float x;
	float y;
	float z;
}Vrh;

typedef struct {
	Vrh normala;
	Vrh vrhovi[3];
	unsigned short boja;
}Trokut;

#pragma pack(pop)

typedef struct {
	Trokut *trokuti;
	unsigned int broj;
}Objekt3D;

Objekt3D citaj_binarni(const char *naziv_datoteke);
int zapisi_binarni(const char *naziv_datoteke, const Objekt3D *objekt);
int zapisi_tekstualni(const char *naziv_datoteke, const Objekt3D *objekt);
Objekt3D citaj_tekstualni(const char *naziv_datoteke);
void obrisi_objekt(Objekt3D *objekt);

#endif
