/*
 * Schluesselliste
 * Version 0.1
 */

#ifndef EINFL_H
#define EINFL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * Typen
 */
typedef enum einfl_rueckgabe {
	IO, LISTE_NULL, EINTRAG_NIO, ALLOK_FEHLG, NAME_FEHLT, KEIN_EINTRAG, KEINE_EINTRAEGE
} einfl_rueckgabe;

typedef struct einfl_eintrag {
	void* wert;
	struct einfl_eintrag* n_eintrag;
} einfl_eintrag;

typedef struct einfl_liste {
	struct einfl_eintrag* starteintrag;
	unsigned int eintraege_l;
} einfl_liste;

/*
 * Deklarationen
 */

/*
 * Konstruieren mit direkter Rückgabe, alloziert eine einfl_liste
 * Muss aufgelöst werden
 */
einfl_liste* einfl_ListeErstellenZeiger();

/*
 * Konstruieren mit Rückgabe über extern gegebenen Zeiger, alloziert eine einfl_liste
 * Muss aufgelöst werden
 * einfl_liste** liste: Zeiger auf einfl_liste-Zeiger
 */
einfl_rueckgabe einfl_ListeErstellen(einfl_liste** liste);

/*
 * Auflösen einer einfl_liste
 * einfl_liste* liste: Zeiger auf azuflösende einfl_liste
 * const int free_name: wenn 1, Schlüssel der Einträge deallozieren
 * const int free_wert: wenn 1, Werte der Einträge deallozieren
 */
einfl_rueckgabe einfl_ListeAufloesen(const einfl_liste* liste, const int free_wert);

/*
 * Eintrag zu einer einfl_liste hinzufügen
 * einfl_liste* liste: Zeiger auf einfl_liste, zu der der Eintrag hinzugefügt werden soll
 * const void* wert: Wert für den Eintrag
 * const int wert_kopieren: Wert kopieren?
 * const unsigned int wert_laenge: Falls der Wert kopiert werden soll, ist hier die Länge des zu allozierenden Speicherplatzes einzutragen
 */
einfl_rueckgabe einfl_ListeEintragHinzufuegen(einfl_liste* liste, const void* wert, const int wert_kopieren,
											  const unsigned int wert_laenge);
einfl_rueckgabe einfl_ListeAddBack(einfl_liste* liste, const void* wert, const int wert_kopieren,
											  const unsigned int wert_laenge);

/*
 * Eintrag aus einer einfl_liste entfernen
 * const einfl_liste* liste: Zeiger auf einfl_liste, aus der der Eintrag entfernt werden soll
 * const char* index: Index des Eintrags
 * const int free_wert: wenn 1, Wert des Eintrags deallozieren
 */
einfl_rueckgabe einfl_ListeEintragEntfernen(einfl_liste* liste, const unsigned int index, const int free_wert);
einfl_rueckgabe einfl_ListePopBack(einfl_liste* liste, const int free_wert);

/*
 * Zeiger auf Wert holen
 * const einfl_liste* liste: Zeiger auf einfl_liste, aus der der Wert geholt werden soll
 * void** v: Zeiger auf den Zeiger, der den Wert angeben soll
 * const char* index: Index des Eintrags
 */
einfl_rueckgabe einfl_ListeWertHolen(const einfl_liste* liste, void** v, const unsigned int index);
einfl_rueckgabe einfl_ListeWertFirst(const einfl_liste* liste, void** v);
einfl_rueckgabe einfl_ListeWertLast(const einfl_liste* liste, void** v);

/*
 * Zeiger auf Wert direkt ausgeben
 * const einfl_liste* liste: Zeiger auf einfl_liste, aus der der Wert geholt werden soll
 * const char* index: Index des Eintrags
 */
void* einfl_ListeWertHolenZeiger(const einfl_liste* liste, const unsigned int index);
void* einfl_ListeWertHolenZeigerFirst(const einfl_liste* liste);
void* einfl_ListeWertHolenZeigerLast(const einfl_liste* liste);

/*
 * Definitionen
 */

einfl_liste* einfl_ListeErstellenZeiger(){

	einfl_liste* ret = (einfl_liste*)calloc(1, sizeof(einfl_liste));
	return ret;

}

einfl_rueckgabe einfl_ListeAufloesen(const einfl_liste* liste, const int free_name, const int free_wert){

	if(liste == NULL)
		return LISTE_NULL;

	einfl_eintrag* p = liste->starteintrag;

	while(p != NULL) {
		einfl_eintrag* t= p->n_eintrag;

		if(free_wert){
			free(p->wert);
		}

		p = t;
	}

	return IO;

}

einfl_rueckgabe einfl_ListeEintragHinzufuegen(einfl_liste* liste, const void* wert, const int wert_kopieren, const unsigned int wert_laenge){

	if(liste == NULL)
		return LISTE_NULL;

	einfl_eintrag neuer_eintrag;
	neuer_eintrag.wert = (void*)wert;
	neuer_eintrag.n_eintrag = NULL;

	einfl_eintrag* p = liste->starteintrag;

	while(p != NULL) {
		p = p->n_eintrag;
	}

	p->n_eintrag = (einfl_eintrag*)calloc(1, sizeof(einfl_eintrag));

	if(p->n_eintrag == NULL){
		return ALLOK_FEHLG;
	}

	if(wert_kopieren){
		p->n_eintrag->wert = (char*)calloc(wert_laenge, 1);

		if(p->n_eintrag->wert == NULL){
			free(p->n_eintrag);
			return ALLOK_FEHLG;
		}

		memcpy(p->n_eintrag->wert, wert, wert_laenge);
	}else{
		p->n_eintrag->wert = neuer_eintrag.wert;
	}

	liste->eintraege_l++;

	return IO;
}

einfl_rueckgabe einfl_ListeAddBack(einfl_liste* liste, const void* wert, const int wert_kopieren,
								   const unsigned int wert_laenge){
	return einfl_ListeEintragHinzufuegen(liste, wert, wert_kopieren, wert_laenge);
}

einfl_rueckgabe einfl_ListeEintragEntfernen(einfl_liste* liste, const unsigned int index, const int free_wert){

	if(liste == NULL)
		return MAP_NULL;

	if(liste->starteintrag == NULL)
		return KEINE_EINTRAEGE;

	einfl_eintrag* vorg = NULL;
	einfl_eintrag* p = liste->starteintrag;

	unsigned int i;
	i = 0;

	while(i < index && p != NULL){
		++i;
		vorg = p;
		p = p->n_eintrag;
	}

	if(p == NULL){
		return KEIN_EINTRAG;
	}else{
		if(vorg != NULL){
			vorg->n_eintrag = p->n_eintrag;
		}
		if(free_wert == 1){
			free(p->wert);
		}
		free(p);
	}

	liste->eintraege_l--;

	return IO;
}

einfl_rueckgabe einfl_ListePopBack(einfl_liste* liste, const int free_wert){

	return einfl_ListeEintragEntfernen(liste, (liste->eintraege_l-1), free_wert);

}

einfl_rueckgabe einfl_ListeWertHolen(const einfl_liste* liste, void** v, const unsigned int index){

	einfl_eintrag* e;
	e = NULL;

	unsigned int i;
	i = 0;

	einfl_eintrag* p = liste->starteintrag;

	while(i < index && p != NULL){
		++i;
		vorg = p;
		p = p->n_eintrag;
	}

	if(p != NULL){
		*v = p->wert;
		return IO;
	}

	return KEIN_EINTRAG;
}

einfl_rueckgabe einfl_ListeWertFirst(const einfl_liste* liste, void** v){

	return einfl_ListeWertHolen(liste, v, 0);

}

einfl_rueckgabe einfl_ListeWertLast(const einfl_liste* liste, void** v){

	return einfl_ListeWertHolen(liste, v, (liste->eintraege_l-1));

}

void* einfl_ListeWertHolenZeiger(const einfl_liste* liste, const unsigned int index){

	void* v;
	v = NULL;

	if(einfl_ListeWertHolen(liste, &v, index) == IO){
		return v;
	}else{
		return NULL;
	}

}

void* einfl_ListeWertHolenZeigerFirst(const einfl_liste* liste){

	einfl_ListeWertHolenZeiger(liste, 0);

}

void* einfl_ListeWertHolenZeigerLast(const einfl_liste* liste){

	einfl_ListeWertHolenZeiger(liste, (liste->eintraege_l-1));

}

#ifdef __cplusplus
}
#endif

#endif