import java.util.ArrayList;
import java.util.*;
import java.util.Comparator;

/**
 * This class is a class for Pure Binary Tree.
 *
 * @author Colton Piper
 */

//package packageName

//import java.xxxxx.*;

public class PureBinaryTree<E extends Object>{

    // This is the head of a Tree
    private E value;

    // This is the right branch
    private PureBinaryTree<E> rightChild;

    // This is the left branch
    private PureBinaryTree<E> leftChild;

    /**
     * Class constructor.
     *
     * @param value  The value of the head of this tree.
     */
    public PureBinaryTree(E value) {
        this.value = value;
        rightChild = null;
        leftChild = null;
    }

    /*
    * This toString method takes a parameter, which is how much you want to indent
    *
    * @param indent this is how much you want to indent each tree
    * @return returns a string of the tree
    */
    public String toString(String indent) {
        StringBuilder builder = new StringBuilder();
        if (this.leftChild != null) {
            builder.append(this.leftChild.toString(indent + "  "));
        }
        builder.append(indent + this.value + "\n");

        if (this.rightChild != null) {
            builder.append(this.rightChild.toString(indent + "  "));
        }

        return builder.toString();
    }

    /*
    * This toString method which
    *
    * @return returns a string of the tree
    */
    public String toString() {
        return this.toString("");
    }

    /*
    * This method gets the value of the node
    *
    * @return This returns the value you want from the specified node
    */
    public E getValue(){
        return this.value;
    }

    /*
    * This method sets the value of the node
    *
    * @param newValue The value you want to set the node to
    */
    public void setValue(E newValue){
        this.value = newValue;
    }

    /*
    * This method sets the leftChild tree with a new PureBinaryTree
    *
    * @param newBranch what you want to set the left branch to
    */
    public void setLeftChild(PureBinaryTree<E> newBranch){
        this.leftChild = newBranch;
    }

    /*
    * This method sets the rightChild tree with a new PureBinaryTree
    *
    * @param newBranch what you want to set the right branch to
    */
    public void setRightChild(PureBinaryTree<E> newBranch){
        this.rightChild = newBranch;
    }

    /*
    * This method gets the leftChild tree with a new PureBinaryTree
    *
    * @return This returns the left child
    */
    public PureBinaryTree<E> getLeftChild(){
        return this.leftChild;
    }

    /*
    * This method gets the RightChild tree with a new PureBinaryTree
    *
    * @return This returns the right child
    */
    public PureBinaryTree<E> getRightChild(){
        return this.rightChild;
    }

    /*
    * This method tells you the height of the tree
    *
    * @return This returns the height of the tree
    */
    public Integer getHeight(){
        Integer leftHeight = new Integer(1);
        if(this.leftChild != null){
            leftHeight = leftHeight + this.leftChild.getHeight();
        }

        Integer rightHeight = new Integer(1);
        if(this.rightChild != null){
            rightHeight = rightHeight + this.rightChild.getHeight();
        }

        if(leftHeight > rightHeight){
            return leftHeight;
        } else {
            return rightHeight;
        }
    }

    /*
    * This method checks to see if two Binary Trees are equal or not.
    *
    * @param otherTree This is the other tree you would like to compare
    * @return Returns true if trees are equal and false if they are not
    */
    public boolean equals(PureBinaryTree<E> otherTree){
        if(!this.value.equals(otherTree.value)){
            return false;
        }
        boolean leftTreeEqual = false;
        if(this.leftChild != null && otherTree.leftChild != null){
            leftTreeEqual = this.leftChild.equals(otherTree.leftChild);
        } else if(this.leftChild == null && otherTree.leftChild == null){
            leftTreeEqual = true;
        } else {
            leftTreeEqual = false;
        }
        boolean rightTreeEqual = false;
        if(this.rightChild != null && otherTree.rightChild != null){
            rightTreeEqual = this.rightChild.equals(otherTree.rightChild);
        } else if(this.rightChild == null && otherTree.rightChild == null){
            rightTreeEqual = true;
        } else {
            leftTreeEqual = false;
        }
        if(leftTreeEqual && rightTreeEqual){
            return true;
        } else {
            return false;
        }
    }

    /*
    * Main method has the unit testing
    *
    *
    */
    public static void main(String[] args){
        // This tests out our toString methods
        PureBinaryTree<Integer> nullTree = new PureBinaryTree<Integer>(5);
        if(nullTree.getLeftChild() == null){
            System.out.println("Left Child = null");
        }
        PureBinaryTree<Integer> intTree = new PureBinaryTree<Integer>(5);
        PureBinaryTree<String> strTree = new PureBinaryTree<String>("Hello");
        System.out.println("Prints just 5: " + intTree.toString(" "));
        System.out.println("No indentation: " + intTree.toString());
        System.out.println("Prints just Hello: " + strTree.toString(" "));
        System.out.println("No indentation: " + strTree.toString());

        // Tests the getValue and setValue methods
        System.out.println("Gets 5: " + intTree.getValue());
        System.out.println("Gets Hello: " + strTree.getValue());
        intTree.setValue(0);
        System.out.println("Sets 0: " + intTree);
        strTree.setValue("Hola");
        System.out.println("Sets Hola: "  + strTree);

        // Tests the setLeft/RightChild methods
        PureBinaryTree<Integer> firstRowLeft = new PureBinaryTree<Integer>(1);
        PureBinaryTree<Integer> firstRowRight = new PureBinaryTree<Integer>(1);
        intTree.setLeftChild(firstRowLeft);
        intTree.setRightChild(firstRowRight);
        PureBinaryTree<Integer> secondRowMiddle = new PureBinaryTree<Integer>(2);
        firstRowRight.setLeftChild(secondRowMiddle);
        firstRowLeft.setRightChild(secondRowMiddle);
        System.out.println("Sets childs:\n" + intTree + "\n");

        PureBinaryTree<String> pokemon = new PureBinaryTree<String>("Bulbasaur");
        PureBinaryTree<String> psychics = new PureBinaryTree<String>("Ghastly");
        PureBinaryTree<String> ivysaur = new PureBinaryTree<String>("Ivysaur");
        pokemon.setRightChild(ivysaur);
        pokemon.setLeftChild(psychics);
        psychics.setLeftChild(new PureBinaryTree<String>("Kadabra"));
        psychics.setRightChild(new PureBinaryTree<String>("Gengar"));
        PureBinaryTree gengar = psychics.getRightChild();
        gengar.setRightChild(new PureBinaryTree<String>("Haunter"));
        System.out.println("Sets pokemon:\n" + pokemon);
        System.out.println("Gets node of gengar: " + gengar.getValue());

        // This tests out the height method
        System.out.println("\nHeight of pokemon: " + pokemon.getHeight());
        System.out.println("\nHeight of : " + intTree.getHeight() + "\n");

        // This tests the equals method
        PureBinaryTree<String> pokemon2 = new PureBinaryTree<String>("Bulbasaur");
        PureBinaryTree<String> psychics2 = new PureBinaryTree<String>("Ghastly");
        PureBinaryTree<String> ivysaur2 = new PureBinaryTree<String>("Ivysaur");
        pokemon2.setRightChild(ivysaur2);
        pokemon2.setLeftChild(psychics2);
        psychics2.setLeftChild(new PureBinaryTree<String>("Kadabra"));
        psychics2.setRightChild(new PureBinaryTree<String>("Gengar"));
        PureBinaryTree gengar2 = psychics2.getRightChild();
        gengar2.setRightChild(new PureBinaryTree<String>("Haunter"));
        System.out.println("Sets pokemon:\n" + pokemon2 + "\n");
        System.out.println("Gets node of gengar: " + gengar2.getValue());
        PureBinaryTree<String> pokemon3 = new PureBinaryTree<String>("Bulbasaur");
        PureBinaryTree<String> psychics3 = new PureBinaryTree<String>("Ghastly");
        pokemon3.setLeftChild(psychics3);
        psychics3.setLeftChild(new PureBinaryTree<String>("Kadabra"));
        psychics3.setRightChild(new PureBinaryTree<String>("Gengar"));
        PureBinaryTree gengar3 = psychics3.getRightChild();
        gengar3.setRightChild(new PureBinaryTree<String>("Haunter"));
        System.out.println("Sets pokemon:\n" + pokemon3 + "\n");
        System.out.println("This should be equal(true): " + pokemon.equals(pokemon2));
        System.out.println("This should be not equal(false): " + pokemon.equals(intTree));
        System.out.println("This should be not equal(false): " + pokemon.equals(pokemon3));
    }


}
