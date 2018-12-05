/*
 * Einfacher Listendatentyp mit Funktionen
 * Version 0.1
 *
 * Copyright (c) 2018 D. Breunig, FhG IPA
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * ---------------------------------------------------------------------------------------------------------------------
 *
 * Hiermit wird unentgeltlich jeder Person, die eine Kopie der Software und der zugehörigen Dokumentationen (die
 * "Software") erhält, die Erlaubnis erteilt, sie uneingeschränkt zu nutzen, inklusive und ohne Ausnahme mit dem Recht,
 * sie zu verwenden, zu kopieren, zu verändern, zusammenzufügen, zu veröffentlichen, zu verbreiten, zu unterlizenzieren
 * und/oder zu verkaufen, und Personen, denen diese Software überlassen wird, diese Rechte zu verschaffen, unter den
 * folgenden Bedingungen:
 * Der obige Urheberrechtsvermerk und dieser Erlaubnisvermerk sind in allen Kopien oder Teilkopien der Software
 * beizulegen.
 *
 * DIE SOFTWARE WIRD OHNE JEDE AUSDRÜCKLICHE ODER IMPLIZIERTE GARANTIE BEREITGESTELLT, EINSCHLIEẞLICH DER GARANTIE ZUR
 * BENUTZUNG FÜR DEN VORGESEHENEN ODER EINEM BESTIMMTEN ZWECK SOWIE JEGLICHER RECHTSVERLETZUNG, JEDOCH NICHT DARAUF
 * BESCHRÄNKT. IN KEINEM FALL SIND DIE AUTOREN ODER COPYRIGHTINHABER FÜR JEGLICHEN SCHADEN ODER SONSTIGE ANSPRÜCHE
 * HAFTBAR ZU MACHEN, OB INFOLGE DER ERFÜLLUNG EINES VERTRAGES, EINES DELIKTES ODER ANDERS IM ZUSAMMENHANG MIT DER
 * SOFTWARE ODER SONSTIGER VERWENDUNG DER SOFTWARE ENTSTANDEN.
 */

#ifndef EINFL_H
#define EINFL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <memory.h>

/*
 * Typen
 */
typedef enum list_return_value {
	OK, LIST_NULL, ALLOC_FAILED, NO_ENTRY, NO_ENTRIES
} list_return_value;

typedef struct list_entry {
	void* value;
	struct list_entry* next_entry;
} list_entry;

typedef struct list_list {
	struct list_entry* first_entry;
	unsigned int number_entries;
} list_list;

/*
 * Deklarationen
 */

/*
 * Konstruieren mit direkter Rückgabe, alloziert eine einfl_liste
 * Muss aufgelöst werden
 */
list_list* list_makeListPointer();

/*
 * Konstruieren mit Rückgabe über extern gegebenen Zeiger, alloziert eine einfl_liste
 * Muss aufgelöst werden
 * einfl_liste** liste: Zeiger auf einfl_liste-Zeiger
 */
list_return_value list_makeList(list_list** liste);

/*
 * Auflösen einer einfl_liste
 * einfl_liste* liste: Zeiger auf azuflösende einfl_liste
 * const int free_name: wenn 1, Schlüssel der Einträge deallozieren
 * const int free_wert: wenn 1, Werte der Einträge deallozieren
 */
list_return_value list_deleteList(list_list* liste, const int free_wert);

/*
 * Eintrag zu einer einfl_liste hinzufügen
 * einfl_liste* liste: Zeiger auf einfl_liste, zu der der Eintrag hinzugefügt werden soll
 * const void* wert: Wert für den Eintrag
 * const int wert_kopieren: Wert kopieren?
 * const unsigned int wert_laenge: Falls der Wert kopiert werden soll, ist hier die Länge des zu allozierenden
 * Speicherplatzes einzutragen
 */
list_return_value list_add(list_list* liste, const void* value, const int copy_value, const unsigned int value_size);

/*
 * Eintrag aus einer einfl_liste entfernen
 * const einfl_liste* liste: Zeiger auf einfl_liste, aus der der Eintrag entfernt werden soll
 * const char* index: Index des Eintrags
 * const int free_wert: wenn 1, Wert des Eintrags deallozieren
 */
list_return_value liste_pop(list_list* liste, const unsigned int index, const int free_wert);

/*
 * Zeiger auf Wert holen
 * const einfl_liste* liste: Zeiger auf einfl_liste, aus der der Wert geholt werden soll
 * void** v: Zeiger auf den Zeiger, der den Wert angeben soll
 * const char* index: Index des Eintrags
 */
list_return_value list_getValue(const list_list* liste, void** v, const unsigned int index);

list_return_value list_getValueFirst(const list_list* liste, void** v);

list_return_value list_getValueLast(const list_list* liste, void** v);

/*
 * Zeiger auf Wert direkt ausgeben
 * const einfl_liste* liste: Zeiger auf einfl_liste, aus der der Wert geholt werden soll
 * const char* index: Index des Eintrags
 */
void* list_getValuePointer(const list_list* liste, const unsigned int index);

void* list_getValueFirstPointer(const list_list* liste);

void* list_getValueLastPointer(const list_list* liste);

/*
 * Definitionen
 */

list_list* list_makeListPointer() {

	list_list* ret;
	ret = (list_list*) calloc(1, sizeof(list_list));
	return ret;

}

list_return_value list_deleteList(list_list* liste, const int free_wert) {

	if (liste == NULL)
		return LIST_NULL;

	list_entry* p;
	p = liste->first_entry;

	if (p == NULL)
		return NO_ENTRIES;

	while (p != NULL) {
		list_entry* t;
		t = p->next_entry;

		if (free_wert) {
			free(p->value);
		}

		free(p);
		p = t;
	}

	free(liste);

	return OK;

}

list_return_value list_add(list_list* liste, const void* value, const int copy_value, const unsigned int value_size) {

	if (liste == NULL)
		return LIST_NULL;

	list_entry neuer_eintrag;
	neuer_eintrag.value = (void*) value;
	neuer_eintrag.next_entry = NULL;

	list_entry** p;
	p = &liste->first_entry;

	while (*p != NULL) {
		p = &(*p)->next_entry;
	}

	*p = (list_entry*) calloc(1, sizeof(list_entry));

	if (*p == NULL) {
		return ALLOC_FAILED;
	}

	if (copy_value) {
		neuer_eintrag.value = (char*) calloc(value_size, 1);

		if (neuer_eintrag.value == NULL) {
			return ALLOC_FAILED;
		}

		memcpy(neuer_eintrag.value, value, value_size);
	}

	memcpy(*p, &neuer_eintrag, sizeof(list_entry));

	liste->number_entries++;

	return OK;

}

list_return_value liste_pop(list_list* liste, const unsigned int index, const int free_wert) {

	if (liste == NULL)
		return LIST_NULL;

	if (liste->first_entry == NULL)
		return NO_ENTRIES;

	list_entry** vorg;
	vorg = NULL;
	list_entry** p;
	p = &liste->first_entry;

	unsigned int i;
	i = 0;

	while (i < index && *p != NULL) {
		++i;
		vorg = p;
		p = &(*p)->next_entry;
	}

	if (*p == NULL) {
		return NO_ENTRY;
	} else {
		if (*vorg != NULL) {
			(*vorg)->next_entry = (*p)->next_entry;
		}
		if (free_wert == 1) {
			free((*p)->value);
		}
		free(*p);
	}

	liste->number_entries--;

	return OK;

}

list_return_value list_popBack(list_list* liste, const int free_wert) {

	return liste_pop(liste, (liste->number_entries - 1), free_wert);

}

list_return_value list_getValue(const list_list* liste, void** v, const unsigned int index) {

	if (liste == NULL)
		return LIST_NULL;

	if (liste->number_entries <= index)
		return NO_ENTRY;

	list_entry* e;
	e = NULL;

	unsigned int i;
	i = 0;

	list_entry* p;
	p = liste->first_entry;

	while (i < index && p != NULL) {
		++i;
		p = p->next_entry;
	}

	if (p != NULL) {
		*v = p->value;
		return OK;
	}

	return NO_ENTRY;

}

list_return_value list_getValueFirst(const list_list* liste, void** v) {

	return list_getValue(liste, v, 0);

}

list_return_value list_getValueLast(const list_list* liste, void** v) {

	return list_getValue(liste, v, (liste->number_entries - 1));

}

void* list_getValuePointer(const list_list* liste, const unsigned int index) {

	void* v;
	v = NULL;

	list_getValue(liste, &v, index);

}

void* list_getValueFirstPointer(const list_list* liste) {

	list_getValuePointer(liste, 0);

}

void* list_getValueLastPointer(const list_list* liste) {

	list_getValuePointer(liste, (liste->number_entries - 1));

}

#ifdef __cplusplus
}
#endif
#endif