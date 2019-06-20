import java.util.ArrayList;
import java.util.*;

/**
 * This class is a class for Pure Priority Queues. Lists which are in the order you choose by a rule.s
 *
 * @author Colton Piper
 */

import java.util.Comparator;

//package packageName

//import java.xxxxx.*;

public class PurePriorityQueue<E extends Object> {

    // The list in this PurePriorityQueue
    private ArrayList<E> list;

    // This is the Comparator that is used with this PurePriorityQueue
    private Comparator<E> comp;

    /**
     * Class constructor.
     *
     * @param compare This is the comparator object that gets passed in and is used with the PurePriorityQueue.
     */
    public PurePriorityQueue(Comparator<E> compare) {
        this.list = new ArrayList<E>();
        this.comp = compare;
    }

    /**
    * Returns a String version of the Queue you are calling on.
    *
    * @return  A String description of this.
    */
    public String toString(){
        return "Highest Priority --> " + this.list.toString() + " <-- Lowest Priority";
    }

    /**
    * Adds an element to the back of your queue and sorts the list from Highest Priority to Lowest Priority
    *
    * @param element this is the new elemenet you wish to add
    */
    public void add(E element){
        this.list.add(element);
        this.list.sort(this.comp);
    }

    /**
    * This returns the element of highest order
    *
    * @throws NoSuchElementException if the PurePriorityQueue is empty
    * @return Returns the element of highest order in the Pure Priority Queue
    */
    public E element(){
        if(this.list.size() == 0){
            throw new NoSuchElementException("The PurePriorityQueue is empty.");
        } else {
            E element = this.list.get(0);
            for(E index : this.list){
                if(this.comp.compare(index, element) < 0){
                    element = index;
                }
            }
            return element;
        }
    }

    /**
    * Removes the top element of the stack and returns it
    *
    * @throws NoSuchElementException if the PurePriorityQueue is empty
    * @return The method returns the top element in the stack
    */
    public E remove(){
        if(this.list.size() == 0){
            throw new NoSuchElementException("The PurePriorityQueue is empty.");
        } else {
            E element = this.list.get(0);
            this.list.remove(0);
            return element;
        }
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
    * Checks to see if the two PurePriorityQueues have the same elements
    *
    * @return This returns true if they have all the same elements and false if they do not.
    */
    public boolean hasSameElementsAs(PurePriorityQueue<E> otherQueue){
        ArrayList<E> list1 = new ArrayList<E>();
        if(this.list.size() != otherQueue.list.size()){
            return false;
        } else {
            int index = 0;
            while(index < this.list.size()){
                list1.add(otherQueue.list.get(index));
                index++;
            }
            for(E element : this.list){
                if(list1.contains(element)){
                    list1.remove(element);
                } else {
                    return false;
                }
            }
            return true;
        }
    }

    /**
    * This is the main method which does the unit testing.
    *
    *
    */
    // public static void main(String[] args){
    //     //min gives higher priority to the lower number.
    //     Comparator<Integer> min = new Comparator<Integer>() {
    //         public int compare(Integer left, Integer right) {
    //             return left.intValue() - right.intValue();
    //         }
    //     };
    //
    //     //max gives higher priority to the lower number.
    //     Comparator<Integer> max = new Comparator<Integer>() {
    //         public int compare(Integer left, Integer right) {
    //             return right.intValue() - left.intValue();
    //         }
    //     };
    //
    //     //longest gives higher priority to the longer String
    //     Comparator<String> longest = new Comparator<String>() {
    //         public int compare(String a, String b) {
    //             return b.length() - a.length();
    //         }
    //     };
    //
    //     //lexicographical gives higher priority to strings that come first alphabetically
    //     Comparator<String> lexicographical = new Comparator<String>() {
    //         public int compare(String a, String b) {
    //             int minLength = Math.min(a.length(), b.length());
    //             for (int i = 0; i < minLength; i++) {
    //                 if (a.charAt(i) < b.charAt(i)) return -1;
    //                 if (a.charAt(i) > b.charAt(i)) return 1;
    //             }
    //             //one string is a prefix of the other
    //             return a.length() - b.length();
    //         }
    //     };
    //
    //     Integer element ;
    //     // These lines of code test out the toString and add methods
    //     System.out.println("  ");
    //     PurePriorityQueue<Integer> integers1 = new PurePriorityQueue<Integer>(min);
    //     PurePriorityQueue<Integer> integersMax = new PurePriorityQueue<Integer>(max);
    //     PurePriorityQueue<String> strings1 = new PurePriorityQueue<String>(longest);
    //     integers1.add(0);
    //     integers1.add(3);
    //     integers1.add(2);
    //     integers1.add(8);
    //     integersMax.add(0);
    //     integersMax.add(3);
    //     integersMax.add(2);
    //     integersMax.add(8);
    //     strings1.add("Hello");
    //     strings1.add("Worlds");
    //     strings1.add("!!!");
    //     System.out.println("This should print PureQueue [0,2,3,8] : " + integers1);
    //     System.out.println("This should print PureQueue [0,2,3,8] : " + integersMax);
    //     System.out.println("This should print PureQueue [Worlds, Hello, !!!] : " + strings1);
    //     System.out.println("  ");
    //
    //     // These lines of code test out the element method
    //     System.out.println("This should print 0 : " + integers1.element());
    //     System.out.println("This should print Worlds : " + strings1.element());
    //
    //     // These lines of code test out the remove method
    //     System.out.println("This should remove and return 0 : " + integers1.remove() + ". The new Queue looks like : " + integers1);
    //     System.out.println("This should remove and return Worlds : " + strings1.remove() + ". The new Queue looks like : " + strings1);
    //
    //     // These lines of the code test out the hasSameElementsAs method.
    //     PurePriorityQueue<Integer> integers2 = new PurePriorityQueue<Integer>(min);
    //     integers2.add(5);
    //     integers2.add(1);
    //     integers2.add(5);
    //     PurePriorityQueue<Integer> integers3 = new PurePriorityQueue<Integer>(min);
    //     integers3.add(5);
    //     integers3.add(5);
    //     integers3.add(1);
    //     PurePriorityQueue<Integer> integers4 = new PurePriorityQueue<Integer>(min);
    //     integers4.add(5);
    //     integers4.add(1);
    //     PurePriorityQueue<Integer> integers5 = new PurePriorityQueue<Integer>(min);
    //     integers5.add(1);
    //     integers5.add(1);
    //     integers5.add(5);
    //     System.out.println("This should print true : " + integers2.hasSameElementsAs(integers3));
    //     System.out.println("This should print false : " + integers2.hasSameElementsAs(integers5));
    //     System.out.println("This should print false : " + integers2.hasSameElementsAs(integers4));
    //     System.out.println("This should print false : " + integers3.hasSameElementsAs(integers5));
    //     System.out.println("This should print false : " + integers4.hasSameElementsAs(integers5));
    // }
}
