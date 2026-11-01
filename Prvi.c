#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int mystrlen(char *rijec) {
	int duzina = 0;
	while (rijec[duzina] != '\0') {
		duzina++;
	}
	return duzina;
}

void mystrcpy(char *prvi, char *drugi) {
	int i = 0;
	while (drugi[i] != '\0') {
		prvi[i] = drugi[i];
		i++;
	}
	prvi[i] = '\0';
}

int mystrcmp(char *prvi, char *drugi) {
	int i = 0;
	while (prvi[i] != '\0' && drugi[i] != '\0') {
		if (prvi[i] != drugi[i]) {
			return prvi[i] - drugi[i];
		}
		i++;
	}
	return prvi[i] - drugi[i];
}

void mystrcat(char *prvi, char *drugi) {
	int i = 0;
	int j = 0;
	while (prvi[i] != '\0') {
		i++;
	}
	while (drugi[j] != '\0') {
		prvi[i] = drugi[j];
		i++;
		j++;
	}
	prvi[i] = '\0';
}

char* mystrstr(char *prvi, char *drugi) {
	if (*drugi == '\0') {
		return prvi;
	}
	for (int i = 0; prvi[i] != '\0'; i++) {
		int j = 0;
		while (drugi[j] != '\0' &&
			prvi[i + j] == drugi[j]) {
			j++;
		}
		if (drugi[j] == '\0') {
			return &prvi[i];
		}
	}
	return NULL;
}

void reverse(char *prvi, char *drugi) {
	int duzina = mystrlen(prvi);
	int i = 0;

	for (i = 0; i < duzina; i++) {
		drugi[i] = prvi[duzina - 1 - i];
	}

	drugi[duzina] = '\0';
}

int main(void) {
	char prvi[100] = "Ovo je prvi string";
	char drugi[100] = "Ovo je drugi string";
	char kopija[100], dodani[200], obrnuti[100];

	printf("Duzina: %d / %zu\n", mystrlen(prvi), strlen(prvi));

	mystrcpy(kopija, prvi);
	char kopija2[100];
	strcpy(kopija2, prvi);
	printf("Kopiranje: %s / %s\n", kopija, kopija2);

	printf("Usporedba: %d / %d\n",mystrcmp(prvi, drugi), strcmp(prvi, drugi));

	mystrcpy(dodani, prvi);
	mystrcat(dodani, drugi);

	char dodani2[200];
	strcpy(dodani2, prvi);
	strcat(dodani2, drugi);
	printf("Spajanje: %s / %s\n", dodani, dodani2);

	char tekst1[] = "abcabbaan";
	char tekst2[] = "aaab";
	char *rezultat;

	rezultat = mystrstr(tekst1, "ba");
	printf("Trazenje 1: %s\n", rezultat != NULL ? rezultat : "NULL");

	rezultat = mystrstr(tekst2, "xxxabaaaaabaa");
	printf("Trazenje 2: %s\n", rezultat != NULL ? rezultat : "NULL");

	reverse(prvi, obrnuti);
	printf("Obrnuti string: %s\n", obrnuti);

	return 0;
}
