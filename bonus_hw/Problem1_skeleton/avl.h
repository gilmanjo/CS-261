#ifndef __AVL_H
#define __AVL_H

# ifndef TYPE
# define TYPE   int
# endif

#ifndef EQ
#define EQ(a, b) (a == b)
#endif

#ifndef LT
#define LT(a, b) (a < b)
#endif

struct AVLnode {
	TYPE         val;
	struct AVLnode *left;
	struct AVLnode *right;
	int height;
};

struct AVLTree {
	struct AVLnode *root;
	int          cnt;
};

/* the public interface */

/* Alocate and initialize AVL tree structure. */
struct AVLTree * newAVLTree();

/* Initialize AVL tree structure. */
void initAVLTree(struct AVLTree *tree);

/* Deallocate nodes in AVL tree and deallocate the AVL tree structure. */
void deleteAVLTree(struct AVLTree *tree);

/* Deallocate nodes in AVL tree. */
void clearAVLTree(struct AVLTree *tree);

void addAVLTree(struct AVLTree *tree, TYPE val);
void removeAVLTree(struct AVLTree * tree, TYPE val);
int containsAVLTree(struct AVLTree *tree, TYPE val);

/* the internal interface */
struct AVLnode * rotateLeft(struct AVLnode * current);
struct AVLnode * rotateRight(struct AVLnode * current);
struct AVLnode * AVLnodeAdd(struct	AVLnode * current, TYPE newValue);


#endif

