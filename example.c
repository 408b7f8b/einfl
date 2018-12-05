#include "einfl.h"

int main(){

	list_list* l = list_makeListPointer();

	char* eintrag1 = "hallo";
	char* eintrag2 = "ich bin eine";
	char* eintrag3 = "liste";

	list_add(l, eintrag1, 1, strlen(eintrag1)+1 );
	list_add(l, eintrag2, 1, strlen(eintrag2)+1 );
	list_add(l, eintrag3, 1, strlen(eintrag3)+1 );

	eintrag1 = NULL;
	eintrag2 = NULL;
	eintrag3 = NULL;

	printf("%s %s %s\n", (char*)list_getValueFirstPointer(l), (char*)list_getValuePointer(l, 1), (char*)list_getValueLastPointer(l));

	list_deleteList(l, 1);

	return 0;
}