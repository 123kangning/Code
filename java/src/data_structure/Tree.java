package data_structure;

import java.util.Collection;

public interface Tree<E> extends Collection<E> {

    boolean search(E e);

    boolean insert(E e);

    boolean delete(E e);

    int getSize();

//    default E clone() {
//        return null;
//    }

    default E image() {
        return null;
    }

    default boolean isCompleteTree() {
        return false;
    }

    int getHigh();

    default void inorder() {
    }

    default void postorder() {
    }

    default void preorder() {
    }

    default void seqPrint() {
    }

    default boolean isEmpty() {
        return this.size() == 0;
    }

    default boolean contains(Object e) {
        return search((E) e);
    }

    default boolean add(E e) {
        return insert(e);
    }

    default boolean remove(Object e) {
        return delete((E) e);
    }

    default int size() {
        return getSize();
    }

    default boolean containsAll(Collection<?> c) {
        // Left as an exercise
        return false;
    }

    default boolean addAll(Collection<? extends E> c) {
        // Left as an exercise
        return false;
    }

    default boolean removeAll(Collection<?> c) {
        // Left as an exercise
        return false;
    }

    default boolean retainAll(Collection<?> c) {
        // Left as an exercise
        return false;
    }

    default Object[] toArray() {
        // Left as an exercise
        return null;
    }

    default <T> T[] toArray(T[] array) {
        // Left as an exercise
        return null;
    }
}