// AVL tree implementation in C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Node
{
	char song_name[100];
	char singer[100];
	char lyricist[100];
	char album[100];
	char composer[100];
	char genre[100];
	int duration;
	int flag;
	int index;
	int height;
	struct Node *left;
	struct Node *right;
};

// Create Node
// struct Node {
//  int key;
//  struct Node *left;
//  struct Node *right;
//  int height;
//};

// Calculate height
int height(struct Node *N)
{
	if (N == NULL)
		return 0;
	return N->height;
}

int max(int a, int b)
{
	return (a > b) ? a : b;
}

// Create a node
struct Node *newNode(char *song_name, char *singer, char *lyricist, char *album, char *composer, char *genre, int duration)
{
	struct Node *node = (struct Node *)
		malloc(sizeof(struct Node));
	strcpy(node->song_name, song_name);
	strcpy(node->singer, singer);
	strcpy(node->lyricist, lyricist);
	strcpy(node->album, album);
	strcpy(node->composer, composer);
	strcpy(node->genre, genre);
	node->duration = duration;
	node->left = NULL;
	node->right = NULL;
	node->height = 1;
	return (node);
}

// Right rotate
struct Node *rightRotate(struct Node *y)
{
	struct Node *x = y->left;
	struct Node *T2 = x->right;

	x->right = y;
	y->left = T2;

	y->height = max(height(y->left), height(y->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;

	return x;
}

// Left rotate
struct Node *leftRotate(struct Node *x)
{
	struct Node *y = x->right;
	struct Node *T2 = y->left;

	y->left = x;
	x->right = T2;

	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;

	return y;
}

// Get the balance factor
int getBalance(struct Node *N)
{
	if (N == NULL)
		return 0;
	return height(N->left) - height(N->right);
}

// Insert node
struct Node *insertNode(struct Node *root, char *song_name, char *singer, char *lyricist, char *album, char *composer, char *genre, int duration)
{
	// Find the correct position to insertNode the node and insertNode it
	if (root == NULL)
		return (newNode(song_name, singer, lyricist, album, composer, genre, duration));

	if (strcmp(song_name, root->song_name) < 0)
		root->left = insertNode(root->left, song_name, singer, lyricist, album, composer, genre, duration);
	else if (strcmp(song_name, root->song_name) > 0)
		root->right = insertNode(root->right, song_name, singer, lyricist, album, composer, genre, duration);
	else
		return root;

	// Update the balance factor of each node and
	// Balance the tree
	root->height = 1 + max(height(root->left), height(root->right));

	int balance = getBalance(root);
	if (balance > 1 && strcmp(song_name, root->left->song_name) < 0)
		return rightRotate(root);

	if (balance < -1 && strcmp(song_name, root->right->song_name) > 0)
		return leftRotate(root);

	if (balance > 1 && strcmp(song_name, root->left->song_name) > 0)
	{
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}

	if (balance < -1 && strcmp(song_name, root->right->song_name) < 0)
	{
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	return root;
}

struct Node *minValueNode(struct Node *node)
{
	struct Node *current = node;

	while (current->left != NULL)
		current = current->left;

	return current;
}

// Delete a nodes
struct Node *deleteNode(struct Node *root, char *song_name)
{
	// Find the node and delete it
	if (root == NULL)
		return root;

	if (strcmp(song_name, root->song_name) < 0)
		root->left = deleteNode(root->left, song_name);

	else if (strcmp(song_name, root->song_name) > 0)
		root->right = deleteNode(root->right, song_name);

	else
	{
		if ((root->left == NULL) || (root->right == NULL))
		{
			struct Node *temp = root->left ? root->left : root->right;

			if (temp == NULL)
			{
				temp = root;
				root = NULL;
			}
			else
				*root = *temp;
			free(temp);
		}
		else
		{
			struct Node *temp = minValueNode(root->right);

			strcpy(root->song_name, temp->song_name);
			strcpy(root->singer, temp->singer);
			strcpy(root->lyricist, temp->lyricist);
			strcpy(root->album, temp->album);
			strcpy(root->composer, temp->composer);
			strcpy(root->genre, temp->genre);
			///------------------------------------
			/*
			char song_name[100];
		  char singer[100];
		  char lyricist[100];
		  char album[100];
		  char composer[100];
		  char genre[100];
		  int duration;
		  int flag;
		  int index;
		  int height;
			*/

			root->right = deleteNode(root->right, temp->song_name);
		}
	}

	if (root == NULL)
		return root;

	// Update the balance factor of each node and
	// balance the tree
	root->height = 1 + max(height(root->left),
						   height(root->right));

	int balance = getBalance(root);
	if (balance > 1 && getBalance(root->left) >= 0)
		return rightRotate(root);

	if (balance > 1 && getBalance(root->left) < 0)
	{
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}

	if (balance < -1 && getBalance(root->right) <= 0)
		return leftRotate(root);

	if (balance < -1 && getBalance(root->right) > 0)
	{
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	return root;
}

// Print the tree
void printInOrder(struct Node *root)
{
	if (root != NULL)
	{
		printInOrder(root->left);
		printf("Song: %s\n", root->song_name);
		printf("Singer: %s\n", root->singer);
		printf("Lyricist: %s\n", root->lyricist);
		printf("Album/Film: %s\n", root->album);
		printf("Composer: %s\n", root->composer);
		printf("Genre: %s\n", root->genre);
		printf("Duration: %d seconds\n", root->duration);
		printInOrder(root->right);
	}
}
void printInOrderDash(struct Node *root)
{
	if (root != NULL)
	{
		printInOrderDash(root->right);
		printf("Song: %s\n", root->song_name);
		printf("Singer: %s\n", root->singer);
		printf("Lyricist: %s\n", root->lyricist);
		printf("Album/Film: %s\n", root->album);
		printf("Composer: %s\n", root->composer);
		printf("Genre: %s\n", root->genre);
		printf("Duration: %d seconds\n", root->duration);
		printInOrderDash(root->left);
	}
}
//----------------------------------------------------------------------------------------------------------------------

struct Node *deleteSong(struct Node *root, char *song_name)
{
	// Find the node and delete it
	if (root == NULL)
		return root;

	if (strcmp(song_name, root->song_name) < 0)
		root->left = deleteSong(root->left, song_name);

	else if (strcmp(song_name, root->song_name) > 0)
		root->right = deleteSong(root->right, song_name);

	else
	{
		if ((root->left == NULL) || (root->right == NULL))
		{
			struct Node *temp = root->left ? root->left : root->right;

			if (temp == NULL)
			{
				temp = root;
				root = NULL;
			}
			else
				*root = *temp;
			free(temp);
		}
		else
		{
			struct Node *temp = minValueNode(root->right);

			strcpy(root->song_name, temp->song_name);
			strcpy(root->singer, temp->singer);
			strcpy(root->lyricist, temp->lyricist);
			strcpy(root->album, temp->album);
			strcpy(root->composer, temp->composer);
			strcpy(root->genre, temp->genre);
			///------------------------------------
			/*
			char song_name[100];
		  char singer[100];
		  char lyricist[100];
		  char album[100];
		  char composer[100];
		  char genre[100];
		  int duration;
		  int flag;
		  int index;
		  int height;
			*/

			root->right = deleteSong(root->right, temp->song_name);
		}
	}

	if (root == NULL)
		return root;

	// Update the balance factor of each node and
	// balance the tree
	root->height = 1 + max(height(root->left),
						   height(root->right));

	int balance = getBalance(root);
	if (balance > 1 && getBalance(root->left) >= 0)
		return rightRotate(root);

	if (balance > 1 && getBalance(root->left) < 0)
	{
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}

	if (balance < -1 && getBalance(root->right) <= 0)
		return leftRotate(root);

	if (balance < -1 && getBalance(root->right) > 0)
	{
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	return root;
}

struct Node *deleteArtist(struct Node *root, char *song_name)
{
	// Find the node and delete it
	if (root == NULL)
		return root;

	root->left = deleteArtist(root->left, song_name);

	root->right = deleteArtist(root->right, song_name);

	if (strcmp(root->singer, song_name) == 0)
	{

		if ((root->left == NULL) || (root->right == NULL))
		{

			struct Node *temp = root->left ? root->left : root->right;

			if (temp == NULL)
			{
				temp = root;
				root = NULL;
			}
			else
			{
				*root = *temp;
			}
			free(temp);
		}

		else
		{

			struct Node *temp = minValueNode(root->right);

			strcpy(root->song_name, temp->song_name);
			strcpy(root->singer, temp->singer);
			strcpy(root->lyricist, temp->lyricist);
			strcpy(root->album, temp->album);
			strcpy(root->composer, temp->composer);
			strcpy(root->genre, temp->genre);
			///------------------------------------
			/*
			char song_name[100];
			char singer[100];
			char lyricist[100];
			char album[100];
			char composer[100];
			char genre[100];
			int duration;
			int flag;
			int index;
			int height;
			*/

			root->right = deleteArtist(root->right, temp->song_name);
		}

		if (root == NULL)
			return root;

		// Update the balance factor of each node and
		// balance the tree
		root->height = 1 + max(height(root->left),
							   height(root->right));

		int balance = getBalance(root);
		if (balance > 1 && getBalance(root->left) >= 0)
			return rightRotate(root);

		if (balance > 1 && getBalance(root->left) < 0)
		{
			root->left = leftRotate(root->left);
			return rightRotate(root);
		}

		if (balance < -1 && getBalance(root->right) <= 0)
			return leftRotate(root);

		if (balance < -1 && getBalance(root->right) > 0)
		{
			root->right = rightRotate(root->right);
			return leftRotate(root);
		}
	}

	return root;
}

// void DeleteSong(struct Song **head_ref, char song_name[], char artist_name[])
// {
//     // Initialize two pointers to traverse the doubly linked list
//     struct Song *current = *head_ref;
//     struct Song *temp = NULL;

//     // Traverse through the list to find the song_name and artist_name provided by the user
//     while (current != NULL) {
//         // If the current node contains the song_name and artist_name, delete that node
//         if (strcmp(current->song_name, song_name) == 0 && strcmp(current->singer, artist_name) == 0) {
//             // Update the head of the linked list if the node to be deleted is the head node
//             if (*head_ref == current) {
//                 *head_ref = current->next;
//             }
//             // If the node to be deleted is not the first node, update the pointers of the previous and next nodes
//             if (current->prev != NULL) {
//                 current->prev->next = current->next;
//             }
//             if (current->next != NULL) {
//                 current->next->prev = current->prev;
//             }
//             // Free the memory of the node to be deleted
//             temp = current;
//             current = current->next;
//             free(temp);
//         } else {
//             current = current->next;
//         }
//     }
// }

struct Node *lptr = NULL;

void createPlaylist(struct Node *root)
{

	struct Node input_att;
	strcpy(input_att.album, "#");
	strcpy(input_att.composer, "#");
	strcpy(input_att.genre, "#");
	strcpy(input_att.lyricist, "#");
	strcpy(input_att.singer, "#");
	strcpy(input_att.song_name, "#");
	int choice;
	do
	{
		printf("\nCreate a play-list based on the attribute\n"); // update
		printf("1. song_name\n");
		printf("2. singer\n");
		printf("3. lyricist\n");
		printf("4. album\n");
		printf("5. composer\n");
		printf("6. genre\n");
		printf("0. Exit\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			printf("Enter song name: ");
			scanf("%s", input_att.song_name);
			break;
		case 2:
			printf("Enter singer name: ");
			scanf("%s", input_att.singer);
			break;
		case 3:
			printf("Enter lyricist name: ");
			scanf("%s", input_att.lyricist);
			break;
		case 4:
			printf("Enter album/film name: ");
			scanf("%s", input_att.album);
			break;
		case 5:
			printf("Enter composer name: ");
			scanf("%s", input_att.composer);
			break;
		case 6:
			printf("Enter genre: ");
			scanf("%s", input_att.genre);
			break;
		case 0:
			printf("Exiting program...\n");
			break;
		default:
			printf("Invalid choice, please try again.\n");
		}
	} while (choice != 0);

	playlist(root, input_att);
}

int i;

void indexing(struct Node *root)
{
	i = 0;
	iindexing(root);
}

void iindexing(struct Node *root)
{
	if (root != NULL)
	{
		iindexing(root->left);
		root->index = i++;
		iindexing(root->right);
	}
}

void q6(struct Node *root, int n)
{

	printInOrdern(root, n);

	int c;
	printf("Enter prev(-1) or next(1)\n");
	scanf("%d", &c);

	printInOrdern(root, n + c);
}

void q7(struct Node *root, int n, int k)
{
	printInOrdern(root, n);
	if (n - k >= 0)
		printInOrdern(root, n - k);
	printInOrdern(root, n + k);
}

void printInOrdern(struct Node *root, int n)
{
	if (root != NULL)
	{
		printInOrdern(root->left, n);
		// printf("Song: %s\n", root->song_name);
		// printf("Singer: %s\n", root->singer);
		// printf("Lyricist: %s\n", root->lyricist);
		// printf("Album/Film: %s\n", root->album);
		// printf("Composer: %s\n", root->composer);
		// printf("Genre: %s\n", root->genre);
		// printf("Duration: %d seconds\n", root->duration);

		if (n == root->index)
		{
			printf("index: %s\n", root->index);
			printf("Song: %s\n", root->song_name);
			printf("Singer: %s\n", root->singer);
			printf("Lyricist: %s\n", root->lyricist);
			printf("Album/Film: %s\n", root->album);
			printf("Composer: %s\n", root->composer);
			printf("Genre: %s\n", root->genre);
			printf("Duration: %d seconds\n", root->duration);
		}

		printInOrdern(root->right, n);
	}
}

void playlist(struct Node *root, struct Node *cur)
{

	if (root == NULL)
	{
		return;
	}

	if (root->left)
	{
		playlist(root->left, cur);
	}
	if ((strcmp(input_att.song_name, "#") == 0 || strcmp(input_att.song_name, cur->song_name) == 0) &&
		(strcmp(input_att.singer, "#") == 0 || strcmp(input_att.singer, cur->singer) == 0) &&
		(strcmp(input_att.lyricist, "#") == 0 || strcmp(input_att.lyricist, cur->lyricist) == 0) &&
		(strcmp(input_att.album, "#") == 0 || strcmp(input_att.album, cur->album) == 0) &&
		(strcmp(input_att.composer, "#") == 0 || strcmp(input_att.composer, cur->composer) == 0) &&
		(strcmp(input_att.genre, "#") == 0 || strcmp(input_att.genre, cur->genre) == 0))
	{
		lptr = insertNode(lptr, cur->song_name, cur->singer, cur->lyricist, cur->album, cur->composer, cur->genre, cur->duration);
	}
	if (root->right)
	{
		playlist(root->right, cur);
	}
}

//-----------------------------------------------------------------------------------------------------------------------------------

struct Node *InsertData()
{

	struct Node *head;

	struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
	FILE *fp;
	char line[200];
	fp = fopen("dspd6670inputs.txt", "r");
	if (fp == NULL)
	{
		printf("Error opening file.");
		exit(1);
	}

	while (fgets(line, sizeof(line), fp) != NULL)
	{
		struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
		sscanf(line, "%[^;]; %[^;]; %[^;]; %[^;]; %[^;]; %[^;]; %d", new_node->song_name, new_node->singer, new_node->lyricist, new_node->album, new_node->composer, new_node->genre, &(new_node->duration));

		new_node->right = NULL;
		new_node->left = NULL;
		if (head == NULL)
		{
			head = new_node;
		}
		else
		{
			new_node->right = head;
			head->left = new_node;
			head = new_node;
		}
	}

	fclose(fp);

	return head;
}

int main()
{
	struct Node *root = NULL;

	root = insertNode(root, "hello", "mello", "jello", "bello", "gello", "tello", 87);
	root = insertNode(root, "dello", "bello", "jello", "bello", "gello", "tello", 89);
	root = insertNode(root, "zello", "fello", "jello", "bello", "gello", "tello", 90);
	root = insertNode(root, "gello", "zello", "jello", "bello", "gello", "tello", 87);
	root = insertNode(root, "eello", "rello", "jello", "bello", "gello", "tello", 86);
	root = insertNode(root, "aello", "aello", "jello", "bello", "gello", "tello", 78);
	root = insertNode(root, "hello", "cello", "jello", "bello", "gello", "tello", 77);

	printInOrder(root);

	root = deleteNode(root, "dello");

	printf("\nAfter deletion: \n");
	printInOrder(root);
	printInOrderDash(root);

	return 0;
}
