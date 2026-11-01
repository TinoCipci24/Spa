#define _CRT_SECURE_NO_WARNINGS
#include "stl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Objekt3D citaj_binarni(const char *ime) {
	Objekt3D objekt = { NULL,0 };
	FILE *dat = fopen(ime, "rb");
	if (dat==NULL) {
		perror("Pogreška u otvaranju datoteke");
		return objekt;
	}
	fseek(dat, 80, SEEK_SET);
	if (fread(&objekt.broj, sizeof(unsigned int), 1, dat) != 1) {
		perror("Pogreska pri citanju broja trokuta");
		fclose(dat);
		return objekt;
	}
	objekt.trokuti = malloc(objekt.broj*sizeof(Trokut));
	int procitano = fread(objekt.trokuti, sizeof(Trokut), objekt.broj, dat);
	if (procitano != objekt.broj) {
		perror("Nisu procitani svi trokuti");
	}
	fclose(dat);
	return objekt;
}

int zapisi_binarni(const char *ime, const Objekt3D *objekt) {
	FILE *dat = fopen(ime, "wb");
	if (dat == NULL) {
		perror("Pogreška u otvaranju datoteke ");
		return 0;
	}
	char zaglavlje[80] = { 0 };
	fwrite(zaglavlje, 80, 1, dat);
	fwrite(&objekt->broj,sizeof(unsigned int),1,dat);
	fwrite(objekt->trokuti,sizeof(Trokut),1,dat);
	fclose(dat);
	return 1;
}

int zapisi_tekstualni(const char *ime, const Objekt3D *objekt) {
	FILE *dat = fopen(ime, "wt");
	if (dat == NULL) {
		perror("Pogreska u otvaranju datoteke");
		return 0;
	}
	
	for (unsigned int i = 0; i < objekt->broj; i++) {
		Trokut t = objekt->trokuti[i];
		fprintf(dat, "  facet normal %f %f %f\n", t.normala.x, t.normala.y, t.normala.z);
		fprintf(dat, "    outer loop\n");
		fprintf(dat, "      vertex %f %f %f\n", t.vrhovi[0].x, t.vrhovi[0].y, t.vrhovi[0].z);
		fprintf(dat, "      vertex %f %f %f\n", t.vrhovi[1].x, t.vrhovi[1].y, t.vrhovi[1].z);
		fprintf(dat, "      vertex %f %f %f\n", t.vrhovi[2].x, t.vrhovi[2].y, t.vrhovi[2].z);
		fprintf(dat, "    endloop\n");
		fprintf(dat, "  endfacet\n");
	}

	fclose(dat);
	return 1;
}

Objekt3D citaj_tekstualni(const char *ime) {
	Objekt3D objekt = { NULL, 0 };
	FILE *dat = fopen(ime, "r");
	if (dat == NULL) {
		perror("Greska pri otvaranju datoteke");
		return objekt;
	}
	int kapacitet = 10;
	char buffer[256];
	objekt.trokuti = malloc(kapacitet * sizeof(Trokut));
	while (fscanf(dat, "%255s", buffer) == 1) {
		if (strcmp(buffer, "facet") == 0) {
			Trokut t;
			fscanf(dat, "%255s", buffer);
			fscanf(dat, "%f %f %f",&t.normala.x, &t.normala.y, &t.normala.z);
			fscanf(dat, "%255s", buffer);
			fscanf(dat, "%255s", buffer);
			for (int i = 0; i < 3; i++) {
				fscanf(dat, "%255s", buffer);
				fscanf(dat, "%f %f %f",&t.vrhovi[i].x,&t.vrhovi[i].y,&t.vrhovi[i].z);
			}
			fscanf(dat, "%255s", buffer);
			fscanf(dat, "%255s", buffer);
			t.boja = 0;
			if (objekt.broj == kapacitet) {
				kapacitet *= 2;
				Trokut *temp = realloc(objekt.trokuti,kapacitet * sizeof(Trokut));
				if (temp == NULL) {
					break;
				}
				objekt.trokuti = temp;
			}
			objekt.trokuti[objekt.broj++] = t;
		}
	}
	fclose(dat);
	return objekt;
}

void obrisi_objekt(Objekt3D *objekt) {
	free(objekt->trokuti);
	objekt->trokuti = NULL;
	objekt->broj = 0;
}
