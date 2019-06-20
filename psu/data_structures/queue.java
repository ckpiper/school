import java.util.ArrayList;
import java.util.*;

/**
 * This class is a class for Pure Queues. Like a line for something. You add stuff to the back and get rid of elements at the front.
 *
 * @author Colton Piper
 */

//package packageName

//import java.xxxxx.*;

public class PureQueue<E extends Object> {

    //
    private ArrayList<E> list;

    /**
     * Class constructor.
     *
     *
     */
    public PureQueue() {
        this.list = new ArrayList<E>();
    }

    /**
    * Returns a String version of the Queue you are calling on.
    *
    * @return  A String description of this.
    */
    public String toString(){
        return "Front --> " + this.list.toString() + " <-- Back";
    }

    /**
    * Adds an element to the back of your stack
    *
    * @param element this is the new elemenet you wish to add
    */
    public boolean add(E element){
        this.list.add(element);
        return true;
    }

    /**
    * Removes the top element of the stack and returns it
    *
    * @return The method returns the top element in the stack
    */
    public E remove(){
        if(this.list.size() == 0){
            throw new NoSuchElementException("The PureQueue is empty.");
        } else {
            E element = this.list.get(0);
            this.list.remove(0);
            return element;
        }
    }

    /**
    * This looks at the first element of the Queue, if empty it throws an exception in the remove method.
    *
    * @return looks at the first element in the Queue and returns it
    */
    public E element(){
        E element = this.remove();
        this.list.add(0, element);
        return element;
    }

    /**
    * This returns if Queue is empty or not
    *
    * @return this returns true if there are no elements in th Queue
    */
    public boolean isEmpty(){
        if(this.list.size() == 0){
            return true;
        } else {
          return false;
        }
    }

    /**
    * This returns if the two Queues are equal
    *
    * @return returns true if two PureQueues of the same type are equivalent
    */
    public boolean equals(PureQueue<E> queue){
        return this.list.equals(queue.list);
    }

    /**
    * This returns if the two Queues are equal
    *
    * @return Try catch statement to check if the ArrayList in the two Queues are the same type
    */
    public boolean equals(Object obj){
      try {
          PureQueue<E> other = (PureQueue<E>) obj;
          return this.equals(other);
      } catch (ClassCastException e) {
          return false;
      }
    }

    /**
    * This is the main method which does all the unit testing for the methods.
    *
    *
    */
    public static void main(String[] args){
        Integer element ;
        // These lines of code test out the toString and add methods
        System.out.println("  ");
        PureQueue<Integer> integers1 = new PureQueue<Integer>();
        PureQueue<String> strings1 = new PureQueue<String>();
        integers1.add(0);
        integers1.add(1);
        integers1.add(2);
        integers1.add(3);
        strings1.add("Hello");
        strings1.add("World");
        strings1.add("!!!");
        System.out.println("This should print PureQueue [0,1,2,3] : " + integers1);
        System.out.println("This should print PureQueue [Hello,World,!!!] : " + strings1);
        System.out.println("  ");

        // These lines of code test out the remove method.
        System.out.println("This takes out the first element and returns it : " + integers1.remove());
        System.out.println("Now integers1 should print [1,2,3] : " + integers1.toString());;
        System.out.println("This takes out the first element and returns it : " + strings1.remove());
        System.out.println("Now integers1 should print [World,!!!] : " + strings1.toString());
        PureQueue<Integer> emptyQueue = new PureQueue<Integer>();
        try {
            element = emptyQueue.remove();
        } catch (NoSuchElementException e) {
            System.out.println("NoSuchElementException : " + e.getMessage());
        }
        System.out.println("  ");

        // These lines of code test out the element method
        System.out.println("This looks at front of [1,2,3] : " + integers1.element());
        System.out.println("This looks at front of [World,!!!] : " + strings1.element());
        try {
            element = emptyQueue.element();
        } catch (NoSuchElementException e) {
            System.out.println("NoSuchElementException : " + e.getMessage());
        }
        System.out.println("  ");

        // These lines of code test out the isEmpty method.
        System.out.println("The Queue [1,2,3] is empty. : " + integers1.isEmpty());
        System.out.println("The Queue [World,!!!] is empty. : " + strings1.isEmpty());
        System.out.println("The Queue [] is empty. : " + emptyQueue.isEmpty());
        System.out.println("  ");

        // These lines of code test out the equals method.
        PureQueue<Integer> integersEqual = new PureQueue<Integer>();
        PureQueue<String> stringsEqual = new PureQueue<String>();
        integersEqual.add(1);
        integersEqual.add(2);
        integersEqual.add(3);
        stringsEqual.add("World");
        stringsEqual.add("!!!");
        PureQueue<Integer> integersNotEqual = new PureQueue<Integer>();
        PureQueue<String> stringsNotEqual = new PureQueue<String>();
        integersNotEqual.add(0);
        stringsNotEqual.add("Hello");
        System.out.println("This should be true : " + integers1.equals(integersEqual));
        System.out.println("This should be true : " + strings1.equals(stringsEqual));
        System.out.println("This should be false : " + integers1.equals(integersNotEqual));
        System.out.println("This should be false : " + strings1.equals(stringsNotEqual));
        System.out.println("This should be false : " + strings1.equals(integers1));
        System.out.println("  ");

    }

}
