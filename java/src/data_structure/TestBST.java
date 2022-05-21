package data_structure;

public class TestBST {
    public static void main(String[] args) throws CloneNotSupportedException {
        // Create a BST
        BST<String> tree = new BST<>();
        tree.insert("George");
        tree.insert("Michael");
        tree.insert("Tom");
        tree.insert("Adam");
        tree.insert("Jones");
        tree.insert("Peter");
        tree.insert("Daniel");

        // Traverse tree
        System.out.print("Inorder (sorted): ");
        tree.inorder();
        System.out.print("\nPostorder: ");
        tree.postorder();
        System.out.print("\nPreorder: ");
        tree.preorder();
        System.out.print("\nThe number of nodes is " + tree.getSize());

        // Search for an element
        System.out.print("\nIs Peter in the tree? " +
                tree.search("Peter"));

        // Get a path from the root to Peter
        System.out.print("\nA path from the root to Peter is: ");
        java.util.ArrayList<BST.TreeNode<String>> path
                = tree.path("Peter");
        for (int i = 0; path != null && i < path.size(); i++)
            System.out.print(path.get(i).element + " ");

        Integer[] numbers = {4, 2, 5, 1, 3, 9, 7, 8};
        BST<Integer> intTree = new BST<>(numbers);
        System.out.print("\nInorder (sorted): ");
        intTree.inorder();
        System.out.println();
        intTree.preorder();
        System.out.println();
        intTree.postorder();
        System.out.println();
        intTree.seqPrint();
        System.out.println();
        System.out.println(intTree.isCompleteTree());
        BST<Integer> clone = (BST<Integer>) intTree.clone();
        clone.inorder();
    }
}
