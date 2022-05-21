package data_structure;

import java.util.*;

public class BST<E> implements Tree<E> {
    protected TreeNode<E> root;
    protected int size = 0;
    protected java.util.Comparator<E> c;

    public BST() {
        this.c = (e1, e2) -> ((Comparable<E>) e1).compareTo(e2);
    }

    public BST(java.util.Comparator<E> c) {
        this.c = c;
    }

    public BST(E[] objects) {
        this.c = (e1, e2) -> ((Comparable<E>) e1).compareTo(e2);
        for (int i = 0; i < objects.length; i++)
            add(objects[i]);
    }

    @Override
    public boolean search(E e) {
        TreeNode<E> current = root; // Start from the root

        while (current != null) {
            if (c.compare(e, current.element) < 0) {
                current = current.left;
            } else if (c.compare(e, current.element) > 0) {
                current = current.right;
            } else // element matches current.element
                return true; // Element is found
        }

        return false;
    }

    public boolean insert(E e) {
        if (root == null)
            root = createNewNode(e); // Create a new root
        else {
            // Locate the parent node
            TreeNode<E> parent = null;
            TreeNode<E> current = root;
            while (current != null) {
                if (c.compare(e, current.element) < 0) {
                    parent = current;
                    current = current.left;
                } else if (c.compare(e, current.element) > 0) {
                    parent = current;
                    current = current.right;
                } else
                    return false;
            }
            if (c.compare(e, parent.element) < 0) {
                parent.left = createNewNode(e);
            } else {
                parent.right = createNewNode(e);
            }
            size++;
        }

        size++;
        return true; // Element inserted successfully
    }

    protected TreeNode<E> createNewNode(E e) {
        return new TreeNode<>(e);
    }

    @Override
    public void inorder() {
        inorder(root);
    }

    protected void inorder(TreeNode<E> root) {
        if (root == null) return;
        inorder(root.left);
        System.out.print(root.element + " ");
        inorder(root.right);
    }

    @Override
    public void postorder() {
        postorder(root);
    }

    protected void postorder(TreeNode<E> root) {
        if (root == null) return;
        postorder(root.left);
        postorder(root.right);
        System.out.print(root.element + " ");
    }

    @Override
    public void preorder() {
        preorder(root);
    }

    public void seqPrint() {
        seqPrint(root);
    }

    public void seqPrint(TreeNode<E> root) {
        if (root == null) return;
        Deque<TreeNode<E>> queue = new ArrayDeque<>();
        queue.addLast(root);
        int head = 0;
        int tail = 1;
        while (head < tail) {
            if (Objects.requireNonNull(queue.peekFirst()).left != null) {
                queue.addLast(queue.peekFirst().left);
                tail++;
            }
            if (Objects.requireNonNull(queue.peekFirst()).right != null) {
                queue.addLast(queue.peekFirst().right);
                tail++;
            }
            System.out.print(queue.removeFirst().element + " ");
            head++;
        }
    }

    protected void preorder(TreeNode<E> root) {
        if (root == null) return;
        System.out.print(root.element + " ");
        preorder(root.left);
        preorder(root.right);
    }

    @Override
    /** Get the number of nodes in the tree */
    public int getSize() {
        return size;
    }

    public TreeNode<E> getRoot() {
        return root;
    }

    public java.util.ArrayList<TreeNode<E>> path(E e) {
        java.util.ArrayList<TreeNode<E>> list =
                new java.util.ArrayList<>();
        TreeNode<E> current = root; // Start from the root

        while (current != null) {
            list.add(current); // Add the node to the list
            if (c.compare(e, current.element) < 0) {
                current = current.left;
            } else if (c.compare(e, current.element) > 0) {
                current = current.right;
            } else
                break;
        }

        return list; // Return an array list of nodes
    }

    @Override
    public boolean delete(E e) {
        // Locate the node to be deleted and also locate its parent node
        TreeNode<E> parent = null;
        TreeNode<E> current = root;
        while (current != null) {
            if (c.compare(e, current.element) < 0) {
                parent = current;
                current = current.left;
            } else if (c.compare(e, current.element) > 0) {
                parent = current;
                current = current.right;
            } else
                break; // Element is in the tree pointed at by current
        }

        if (current == null)
            return false; // Element is not in the tree

        // Case 1: current has no left child
        if (current.left == null) {
            // Connect the parent with the right child of the current node
            if (parent == null) {
                root = current.right;
            } else {
                if (c.compare(e, parent.element) < 0)
                    parent.left = current.right;
                else
                    parent.right = current.right;
            }
        } else {
            // Case 2: The current node has a left child
            // Locate the rightmost node in the left subtree of
            // the current node and also its parent
            TreeNode<E> parentOfRightMost = current;
            TreeNode<E> rightMost = current.left;

            while (rightMost.right != null) {
                parentOfRightMost = rightMost;
                rightMost = rightMost.right; // Keep going to the right
            }

            // Replace the element in current by the element in rightMost
            current.element = rightMost.element;

            // Eliminate rightmost node
            if (parentOfRightMost.right == rightMost)
                parentOfRightMost.right = rightMost.left;
            else
                // Special case: parentOfRightMost == current
                parentOfRightMost.left = rightMost.left;
        }

        size--; // Reduce the size of the tree
        return true; // Element deleted successfully
    }

    @Override
    /** Obtain an iterator. Use inorder. */
    public java.util.Iterator<E> iterator() {
        return new InorderIterator();
    }

    @Override
    /** Remove all elements from the tree */
    public void clear() {
        root = null;
        size = 0;
    }

    public BST<E> clone() {
        ArrayList<TreeNode<E>> list = toList();
        BST<E> ans = new BST<>();
        for (TreeNode<E> e : list) {
            ans.insert(e.element);
        }
        return ans;
    }

    public ArrayList<TreeNode<E>> toList() {
        ArrayList<TreeNode<E>> list = new ArrayList<>();
        if (root == null) return null;
        Stack<TreeNode<E>> stack = new Stack<>();
        stack.add(root);
        TreeNode<E> current = root;
        while (!stack.isEmpty()) {
            if (current != null) {
                stack.add(current);
                current = current.left;
            } else {
                list.add(stack.peek());
                current = stack.pop().right;
            }
        }
        return list;
    }

    public int getHigh() {
        return getHigh(root);
    }

    public int getHigh(TreeNode<E> root) {
        if (root == null) return 0;
        int m1 = getHigh(root.left);
        int m2 = getHigh(root.right);
        return 1 + (m1 > m2 ? m1 : m2);
    }

    public boolean isCompleteTree() {
        return isCompleteTree(root);
    }

    public boolean isCompleteTree(TreeNode<E> root) {
        if (root == null) return true;
        if (getHigh(root.left) < getHigh(root.right)) return false;
        return isCompleteTree(root.left) && isCompleteTree(root.right);
    }

    public static class TreeNode<E> {
        protected E element;
        protected TreeNode<E> left;
        protected TreeNode<E> right;

        public TreeNode(E e) {
            element = e;
        }
    }

    // Inner class InorderIterator
    private class InorderIterator implements java.util.Iterator<E> {
        // Store the elements in a list
        private java.util.ArrayList<E> list =
                new java.util.ArrayList<>();
        private int current = 0; // Point to the current element in list

        public InorderIterator() {

            inorder(); // Traverse binary tree and store elements in list
        }

        /**
         * Inorder traversal from the root
         */
        private void inorder() {
            inorder(root);
        }

        /**
         * Inorder traversal from a subtree
         */
        private void inorder(TreeNode<E> root) {
            if (root == null) return;
            inorder(root.left);
            list.add(root.element);
            inorder(root.right);
        }

        @Override
        /** More elements for traversing? */
        public boolean hasNext() {
            if (current < list.size())
                return true;

            return false;
        }

        @Override
        /** Get the current element and move to the next */
        public E next() {
            return list.get(current++);
        }

        @Override // Remove the element returned by the last next()
        public void remove() {
            if (current == 0) // next() has not been called yet
                throw new IllegalStateException();

            delete(list.get(--current));
            list.clear(); // Clear the list
            inorder(); // Rebuild the list
        }
    }
}
