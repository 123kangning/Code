package data_structure;

public class TestAVLTree {
    public static void main(String[] args) {
        // Create an AVL tree
        AVLTree<Integer> tree = new AVLTree<>(new Integer[]{4, 2, 6, 1, 3, 5, 8});
        printTree(tree);
        System.out.println(tree.isCompleteTree());
        AVLTree<Integer> tree1 = tree.clone();
        printTree(tree1);

    }

    public static void printTree(BST tree) {
        // Traverse tree
        System.out.print("\nInorder (sorted): ");
        tree.inorder();
        System.out.print("\nPostorder: ");
        tree.postorder();
        System.out.print("\nPreorder: ");
        tree.preorder();
        System.out.print("\nSeq order: ");
        tree.seqPrint();
        System.out.print("\nThe number of nodes is " + tree.getSize());
        System.out.println();
    }
}
