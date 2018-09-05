// Estefania Pitol Martinez 	A01551688
// Fernanda Montano Rios 		A01730440
// 5 Dicember 2017
// Final Proyect

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Node of the Tree of Books
struct treeNode {
	int id;
	int disabled;
	char title[100];
	char author[100];
	struct treeNode *left;
	struct treeNode *right;
};

typedef struct treeNode treeNode;

//Node for the list of pointers
struct listNode {
	treeNode *pointer;
	struct listNode *next;
};

typedef struct listNode listNode;

//Creates a tree node and returns a pointer to it
treeNode *createNode(int data, int d, char t[], char a[]) {
	treeNode *temp;
	temp = malloc(sizeof(treeNode));
	temp -> id = data;
	temp -> disabled = d;
	strcpy(temp -> title, t);
	strcpy(temp -> author, a);
	temp -> left = NULL;
	temp -> right = NULL;
	return temp;
}

//Creates a node for a linked list and returns a pointer to the new node
listNode *createListNode(treeNode *p) {
	listNode *temp;
	temp = malloc(sizeof(listNode));
	temp -> pointer = p;
	temp -> next = NULL;
}

//Inserts a node to the list of pointers
void insertListNode(listNode **head, treeNode *p) {
	if(!(*head))
		(*head) = createListNode(p);
	else {
		while((*head) -> next)
			head = &(*head) -> next;
		(*head) -> next = createListNode(p);
	}
}

//Inserts a book to the tree
//Parameter root - pointer to pointer to the root of the tree
//Parameter data - id of the book
//Parameter d - boolean disabled
//Parameter t - char array for the title
//Parameter a - char array for the author
//Parameter listNode - pointer to ponter to the head of the list of nodes
void insertNode(treeNode **root, int data, int d, char t[], char a[], listNode **head) {
	if(!*root) {
		*root = createNode(data, d, t, a);
		insertListNode(head, *root);
	}
	else
		if(data < (*root) -> id)
			insertNode(&(*root) -> left, data, d, t, a, head);
		else
			insertNode(&(*root) -> right, data, d, t, a, head);
}

//Deallocates the tree memory
void freeTree(treeNode **root) {
	if(*root) {
		freeTree(&(*root) -> left);
		freeTree(&(*root) -> right);
		free(*root);
	}
}

//Returns 1 if the certain id exists or 0 if not
//Parameter root - pointer to the root
//Parameter data - int for the id to search 
treeNode *exists(treeNode *root, int data) {
	if(root) {
		if(root -> id == data)
			return root;
		treeNode *temp;
		temp = exists(root -> left, data);
		if(temp)
			return temp;
		temp = exists(root -> right, data);
		if(temp)
			return temp;
		return NULL;
	}
	return NULL;
}

//Rreturns 1 if the string a is substring of the string b or 0 if not
//Parameter a - first string
//Parameter b - second string
int isSubstring(char a[], char b[]) {
	int i, j, found;
	found = 0;
	if(strlen(a) > strlen(b))
		return 0;
	for(i = 0; i <= strlen(b) - strlen(a); i++) {
		for(j = 0; j < strlen(a); j++)
			if(b[i + j] != a[j]) {
				found = 0;
				break;
			}
			else
				found = 1;
		if(found)
			return 1;
	}
	return 0;
}

//Calculates the height of the tree 
//Parameter node - pointer to a tree node
//Returns the height
int height(treeNode *root) {
    if(root) {
        int lheight, rheight;
        lheight = height(root -> left);
        rheight = height(root -> right);
        if(lheight > rheight)
            return lheight + 1;
        return rheight + 1;
    }
    return 0;
}

//Calculates the nodes of the tree
//Parameter root - pointer to the root
//Returns the number of nodes in the tree
int countNodes(treeNode *root) {
	if(root) {
		int leftNodes, rightNodes;
		leftNodes = countNodes(root -> left);
		rightNodes = countNodes(root -> right);
		return leftNodes + rightNodes + 1;
	}
	return 0;
}

//Prints a book
//Parameter node - pointer to a node 
void printBook(treeNode *node) {
	if(!(node -> disabled)) {
		printf("%5d. Título: %s\n", node -> id, node -> title);
		printf("       Autor:  %s\n", node -> author);
	}
}

//Prints the list
//Parameter head - pointer to the head of the list
void printList(listNode *head) {
	while(head) {
		printBook(head -> pointer);
		head = head -> next;
	}
	printf("\n");
}

//Prints all the books with a lesser id
//Parameter root - pointer to the root
//Parameter id - int for the id of the book
void printLesserID(treeNode *root, int id) {
	if(root) {
		printLesserID(root -> left, id);
		if(root -> id <= id)
			printBook(root);
		else
			return;
		printLesserID(root -> right, id);
	}
}

//Prints all the books with a greater id
//Parameter root - pointer to the root
//Parameter id - int for the id of the book
void printGreaterID(treeNode *root, int id) {
	if(root) {
		printGreaterID(root -> right, id);
		if(root -> id >= id)
			printBook(root);
		else
			return;
		printGreaterID(root -> left, id);
	}
}

//Prints the list in ascending order acording to id
//Parameter root - pointer to the root
void ascendingID(treeNode *root) {
	if(root) {
		ascendingID(root -> left);
		printBook(root);
		ascendingID(root -> right);
	}
}

//Prints the list in descending order acording to id
//Parameter root - pointer to the root
void descendingID(treeNode *root) {
	if(root) {
		descendingID(root -> right);
		printBook(root);
		descendingID(root -> left);
	}
}

//Swaps two list nodes
void swap(listNode *a, listNode *b) {
	treeNode *temp;
	temp = a -> pointer;
    a -> pointer = b -> pointer;
    b -> pointer = temp;
}

//Prints the list in ascending order acording to title
//Parameter head - pointer to the head
void ascendingTitle(listNode *head) {
	listNode *aux;
	int swapped;
	do {
		aux = head;
		swapped = 0;
		while(aux -> next) {
			if(strcmp(aux -> pointer -> title, aux -> next -> pointer -> title) > 0) {
				swap(aux, aux -> next);
				swapped = 1;
			}
			aux = aux -> next;
		}
	} while(swapped);
}

//Prints the list in descending order acording to title
//Parameter head - pointer to the head
void descendingTitle(listNode *head) {
	listNode *aux;
	int swapped;
	do {
		aux = head;
		swapped = 0;
		while(aux -> next) {
			if(strcmp(aux -> pointer -> title, aux -> next -> pointer -> title) < 0) {
				swap(aux, aux -> next);
				swapped = 1;
			}
			aux = aux -> next;
		}
	} while(swapped);
}

//Prints the list in ascending order acording to author
//Parameter head - pointer to the head
void ascendingAuthor(listNode *head) {
	listNode *aux;
	int swapped;
	do {
		aux = head;
		swapped = 0;
		while(aux -> next) {
			if(strcmp(aux -> pointer -> author, aux -> next -> pointer -> author) > 0) {
				swap(aux, aux -> next);
				swapped = 1;
			}
			aux = aux -> next;
		}
	} while(swapped);
}

//Prints the list in descending order acording to author
//Parameter head - pointer to the head
void descendingAuthor(listNode *head) {
	listNode *aux;
	int swapped;
	do {
		aux = head;
		swapped = 0;
		while(aux -> next) {
			if(strcmp(aux -> pointer -> author, aux -> next -> pointer -> author) < 0) {
				swap(aux, aux -> next);
				swapped = 1;
			}
			aux = aux -> next;
		}
	} while(swapped);
}

//Prints the book with the given title
//Parameter head - pointer to the head
//Parameter t - char array for the title
treeNode *printTitles(listNode *head, char t[]) {
	while(head) {
		if(strcmp(head -> pointer -> title, t) == 0)
			printBook(head -> pointer);
		head = head -> next;
	}
}
//Prints the book with the given author
//Parameter head - pointer to the head
//Parameter t - char array for the author
treeNode *printAuthors(listNode *head, char a[]) {
	while(head) {
		if(!strcmp(head -> pointer -> author, a))
			printBook(head -> pointer);
		head = head -> next;
	}
}

//Prints the book if the string is a substring of the given title
//Parameter head - pointer to the head
//Parameter t - char array for the title
treeNode *printSubstringTitles(listNode *head, char t[]) {
	while(head) {
		if(isSubstring(t, head -> pointer -> title))
			printBook(head -> pointer);
		head = head -> next;
	}
}

//Prints the book if the string is a substring of the given author
//Parameter head - pointer to the head
//Parameter t - char array for the author
treeNode *printSubstringAuthors(listNode *head, char t[]) {
	while(head) {
		if(isSubstring(t, head -> pointer -> author))
			printBook(head -> pointer);
		head = head -> next;
	}
}

//Checks out if the tree is balanced
//Returns a pointer to the root of the subtree with issues
//Parameter root - pointer to the root
treeNode *isBalanced(treeNode *root) {
	if(root) {
		treeNode *temp = isBalanced(root -> left);
		if(!temp)
			temp = isBalanced(root -> right);
		if(abs(height(root -> left) - height(root -> right)) > 1 && !temp)
			return temp = root;
		return temp;
	}
	return NULL;
}

//Rotates the tree to get it balanced
//Parameter root - pointer to the root
treeNode *zyxRotation(treeNode *root) {
	treeNode *c, *y;
	c = root -> left -> right;
	y = root -> left;
	y -> right = root;
	y -> right -> left = c;
	return y;
}

//Rotates the tree to get it balanced
//Parameter root - pointer to the root
treeNode *zxyRotation(treeNode *root) {
	treeNode *b, *c, *y;
	b = root -> left -> right -> left;
	c = root -> left -> right -> right;
	y = root -> left -> right;
	y -> left = root -> left;
	y -> right = root;
	y -> left -> right = b;
	y -> right -> left = c;
	return y;
}

//Rotates the tree to get it balanced
//Parameter root - pointer to the root
treeNode *xzyRotation(treeNode *root) {
	treeNode *b, *c, *y;
	b = root -> right -> left -> left;
	c = root -> right -> left -> right;
	y = root -> right -> left;
	y -> left = root;
	y -> right = root -> right;
	y -> left -> right = b;
	y -> right -> left = c;
	return y;
}

//Rotates the tree to get it balanced
//Parameter root - pointer to the root
treeNode *xyzRotation(treeNode *root) {
	treeNode *b, *y;
	b = root -> right -> left;
	y = root -> right;
	y -> left = root;
	y -> left -> right = b;
	return y;
}

//Returns a pointer to the parent node of the given child
//Parameter root - pointer to the root
//Parameter n - int for the id
treeNode *parentNode(treeNode *root, int n) {
	if(root) {
		if(root -> id == n)
			return NULL;
		if((root -> left && root -> left -> id == n) || (root -> right && root -> right -> id == n)) {
			return root;
		}
		if(n < root -> id)
			return parentNode(root -> left, n);
		else 
			return parentNode(root -> right, n);
		return NULL;
	}
	return NULL;
}

//Checks which method must be used to balance the tree if is not balanced 
//Parameter root - pointer to the pointer to the root of the tree
void balanceTree(treeNode **root) {
	treeNode *problem, *parent, *balanced;
	problem = isBalanced(*root);
	if(problem) {
		parent = parentNode(*root, problem -> id);
		if(countNodes(problem -> left) > countNodes(problem -> right))
			if(countNodes(problem -> left -> left) > countNodes(problem -> left -> right))
				balanced = zyxRotation(problem);
			else
				balanced = zxyRotation(problem);
		else
			if(countNodes(problem -> right -> left) > countNodes(problem -> right -> right))
				balanced = xzyRotation(problem);
			else
				balanced = xyzRotation(problem);
		if(parent)
			if(parent -> left -> id == problem -> id)
				parent -> left = balanced;
			else
				parent -> right = balanced;
		else
			*root = balanced;
	}
}

//Prints a certain level of the tree
//Parameter root - pointer to the pointer to the root
//Parameter f - pointer to a file
//Parameter root - pointer to the root
//Parameter level - level to be printed
void printGivenLevel(treeNode *root, int level, FILE *f) {
    if(root) {
	    if(level == 1) {
	    	fprintf(f, "%d\n", root -> id);
	    	fprintf(f, "%d\n", root -> disabled);
	    	fprintf(f, "%s\n", root -> title);
	    	fprintf(f, "%s\n", root -> author);
	    }
	    else 
	    	if(level > 1) {
		        printGivenLevel(root -> left, level - 1, f);
		        printGivenLevel(root -> right, level - 1, f);
	    	}
    }
}

//Write the level traversal of the tree in a txt file
void writeBreadthFirst(treeNode *root, FILE *f) {
    int h, i, n;
    h = height(root);
    n = countNodes(root);
    fprintf(f, "%d\n", n);
    for(i = 1; i <= h; i++)
        printGivenLevel(root, i, f);
}

//Reads the level traversal of a tree in a txt file and creates a tree out of it
void readBreadthFirst(treeNode **root, FILE *f, char t[], char a[], listNode **head) {
	int i, n, id, disabled;
    fscanf(f, "%d", &n);
	for(i = 0; i < n; i++){
    	fscanf(f, "%d", &id);
    	fscanf(f, "%d", &disabled);
    	fscanf(f, "\n");
    	fgets(t, 100, (FILE*)f);
    	t[strlen(t) - 1]= '\0';
    	fscanf(f, "\n");
    	fgets(a, 100, (FILE*)f);
    	a[strlen(a) - 1]= '\0';
    	insertNode(root, id, disabled, t, a, head);
	}
}

// Principal method for the program execution
// Returns - 0
int main() {
	int op, id;
	char title[100], author[100], confirm[10], fileName[10];
	treeNode *root, *temp;
	listNode *head;
	FILE *f;
	root = NULL;
	head = NULL;
	op = -1;
	root = NULL;
	f = fopen("data.txt", "r");
	if(f){
		readBreadthFirst(&root, f, title, author, &head);
		fclose(f);
	}
	else {
		printf("No se encontró información guardada\n");
		printf("Se ha creado un nuevo archivo\n");
	}
	while(op != 0) {
		printf("\n==========================================\n");
		printf("  ADMINISTRADOR DE LIBROS\n");
		printf("==========================================\n");
		printf("  Menú\n");
		printf("------------------------------------------\n");
		printf("  1. Insertar nuevo libro\n");
		printf("  2. Borrar libro\n");
		printf("  3. Editar libro\n");
		printf("  4. Recuperar libro borrado\n");
		printf("  5. Reporte total\n");
		printf("  6. Buscar\n");
		printf("  7. Herramientas administrativas\n");
		printf("  0. Salir\n");
		printf("------------------------------------------\n\n");
		scanf("%d", &op);
		switch(op) {
			case 1:
				printf("Escriba el ID del libro:\n");
				scanf("%d", &id);
				if(exists(root, id))
					printf("Ya existe un libro con el mismo ID\n");
				else {
					printf("Escriba el título del libro:\n");
					scanf("\n");
					fgets(title, 100, stdin);
					title[strlen(title) - 1]= '\0';
					printf("Escriba el nombre del autor del libro:\n");
					scanf("\n");
					fgets(author, 100, stdin);
					author[strlen(author) - 1]= '\0';
					insertNode(&root, id, 0, title, author, &head);
					balanceTree(&root);
				}				
			break;
			case 2:
				printf("Escriba el ID del libro que desea borrar:\n");
				scanf("%d", &id);
				temp = exists(root, id);
				if(temp) {
					printf("Libro seleccionado: \n");
					printBook(temp);
					printf("¿Seguro que quieres borrar el libro?\n");
					scanf("\n");
					fgets(confirm, 10, stdin);
					if(confirm[0] == 's' || confirm[0] == 'S')
						temp -> disabled = 1;
				}
			break;
			case 3:
				printf("Escriba el ID del libro que desea editar:\n");
				scanf("%d", &id);
				temp = exists(root, id);
				if(temp) {
					printf("Libro seleccionado: \n");
					printBook(temp);
					printf("Escriba el nuevo título del libro:\n");
					scanf("\n");
					fgets(title, 100, stdin);
					title[strlen(title) - 1]= '\0';
					printf("Escriba el nombre del nuevo autor del libro:\n");
					scanf("\n");
					fgets(author, 100, stdin);
					author[strlen(author) - 1]= '\0';
					strcpy(temp -> title, title);
					strcpy(temp -> author, author);
				}
			break;
			case 4:
				printf("Escriba el ID del libro que desea recuperar:\n");
				scanf("%d", &id);
				temp = exists(root, id);
				if(temp)
					temp -> disabled = 0;
			break;
			case 5:
				printf("\n------------------------------------------\n");
				printf("       5. Reporte total\n");
				printf("------------------------------------------\n");
				printf("       1. Orden ascendente por ID\n");
				printf("       2. Orden descendente por ID\n");
				printf("       3. Orden ascendente por título\n");
				printf("       4. Orden descendente por título\n");
				printf("       5. Orden ascendente por autor\n");
				printf("       6. Orden descendente por autor\n");
				printf("------------------------------------------\n\n");
				scanf("%d", &op);
				switch(op) {
					case 1:
						printf("\n------------------------------------------\n");
						ascendingID(root);
						printf("------------------------------------------\n");
					break;
					case 2:
						printf("\n------------------------------------------\n");
						descendingID(root);
						printf("------------------------------------------\n");
					break;
					case 3:
						ascendingTitle(head);
						printf("\n------------------------------------------\n");
						printList(head);
						printf("------------------------------------------\n");
					break;
					case 4:
						descendingTitle(head);
						printf("\n------------------------------------------\n");
						printList(head);
						printf("------------------------------------------\n");
					break;
					case 5:
						ascendingAuthor(head);
						printf("\n------------------------------------------\n");
						printList(head);
						printf("------------------------------------------\n");
					break;
					case 6:
						descendingAuthor(head);
						printf("\n------------------------------------------\n");
						printList(head);
						printf("------------------------------------------\n");
					break;
				}
			break;
			case 6:
				printf("\n------------------------------------------\n");
				printf("     6. Buscar\n");
				printf("------------------------------------------\n");
				printf("     1. Por ID\n");
				printf("     2. Por título\n");
				printf("     3. Por autor\n");
				printf("------------------------------------------\n\n");
				scanf("%d", &op);
				switch(op) {
					case 1:
						printf("\n------------------------------------------\n");
						printf("        6.1. Por ID\n");
						printf("------------------------------------------\n");
						printf("        1. ID exacto\n");
						printf("        2. Libros con ID menor o igual\n");
						printf("        3. Libros con ID mayor o igual\n");
						printf("------------------------------------------\n\n");
						scanf("%d", &op);
						switch(op) {
							case 1:
								printf("Escriba el ID del libro:\n");
								scanf("%d", &id);
								temp = exists(root, id);
								if(temp) {
									printf("\n------------------------------------------\n");
									printBook(temp);
									printf("------------------------------------------\n");
								}
								else
									printf("No existe libro con ese ID\n");
							break;
							case 2:
								printf("Escriba el ID del libro:\n");
								scanf("%d", &id);
								printf("\n------------------------------------------\n");
								printLesserID(root, id);
								printf("------------------------------------------\n");
							break;
							case 3:
								printf("Escriba el ID del libro:\n");
								scanf("%d", &id);
								printf("\n------------------------------------------\n");
								printGreaterID(root, id);
								printf("------------------------------------------\n");
							break;
						}
					break;
					case 2:
						printf("\n------------------------------------------\n");
						printf("        6.2. Por título\n");
						printf("------------------------------------------\n");
						printf("        1. Título exacto\n");
						printf("        2. Subcadena en el título\n");
						printf("------------------------------------------\n\n");
						scanf("%d", &op);
						switch(op) {
							case 1:
								printf("Escriba el título del libro:\n");
								scanf("\n");
								fgets(title, 100, stdin);
								title[strlen(title) - 1]= '\0';
								printf("\n------------------------------------------\n");
								printTitles(head, title);
								printf("------------------------------------------\n");
							break;
							case 2:
								printf("Escriba el título del libro:\n");
								scanf("\n");
								fgets(title, 100, stdin);
								title[strlen(title) - 1]= '\0';
								printf("\n------------------------------------------\n");
								printSubstringTitles(head, title);
								printf("------------------------------------------\n");
							break;
						}
					break;
					case 3:
						printf("\n------------------------------------------\n");
						printf("        6.3. Por autor\n");
						printf("------------------------------------------\n");
						printf("        1. Autor exacto\n");
						printf("        2. Subcadena en el autor\n");
						printf("------------------------------------------\n\n");
						scanf("%d", &op);
						switch(op) {
							case 1:
								printf("Escriba el autor del libro:\n");
								scanf("\n");
								fgets(author, 100, stdin);
								author[strlen(author) - 1]= '\0';
								printf("\n------------------------------------------\n");
								printAuthors(head, author);
								printf("------------------------------------------\n");
							break;
							case 2:
								printf("Escriba el autor del libro:\n");
								scanf("\n");
								fgets(author, 100, stdin);
								author[strlen(author) - 1]= '\0';
								printf("\n------------------------------------------\n");
								printSubstringAuthors(head, author);
								printf("------------------------------------------\n");
							break;
						}
					break;
				}
			break;
			case 7:
				printf("\n------------------------------------------\n");
				printf("     7. Herramientas administrativas\n");
				printf("------------------------------------------\n");
				printf("     1. Guardar información\n");
				printf("     2. Cargar información\n");
				printf("------------------------------------------\n\n");
				scanf("%d", &op);
				switch(op) {
					case 1:
						printf("Escriba el nombre del archivo en donde desea guardar la información:\n");
						scanf("\n");
						fgets(fileName, 100, stdin);
						fileName[strlen(fileName) - 1]= '\0';
						f = fopen(fileName, "w");
						writeBreadthFirst(root, f);
						fclose(f);
					break;
					case 2:
						printf("Escriba el nombre del archivo del que desea cargar la información:\n");
						scanf("\n");
						fgets(fileName, 100, stdin);
						fileName[strlen(fileName) - 1]= '\0';
						printf("¿Seguro que quieres borrar toda la información actual?\n");
						scanf("\n");
						fgets(confirm, 10, stdin);
						if(confirm[0] == 's' || confirm[0] == 'S') {
							freeTree(&root);
							root = NULL;
							f = fopen(fileName, "r");
							readBreadthFirst(&root, f, title, author, &head);
							fclose(f);
						}
					break;
				}
			break;
			case 0:
				f = fopen("data.txt", "w");
				writeBreadthFirst(root, f);
				fclose(f);
			break;
		}
	}
	return 0;
}