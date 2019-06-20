import java.util.ArrayList;
import java.util.*;

/**
 * This class is a class made for Pure Stacks
 *
 * @author Colton Piper
 */

//package packageName

//import java.xxxxx.*;

public class PureStack<E extends Object>{

    private ArrayList<E> list;

    /**
     * Class constructor.
     *
     *
     */
    public PureStack() {
        this.list = new ArrayList<E>();
    }

    /**
    * Returns a String version of this.
    *
    * @return  A String description of this.
    */
    public String toString(){
        return "Top --> " + this.list.toString() + " <-- Bottom";
    }

    /**
    * Adds an element to the top of your stack
    *
    * @param element this is the new elemenet you wish to add
    */
    public void push(E element){
        this.list.add(0, element);
    }

    /**
    * Removes the top element of the stack and returns it
    *
    * @return The method returns the top element in the stack
    */
    public E pop(){
        if(this.list.size() == 0){
            throw new NoSuchElementException("The PureStack is empty.");
        } else {
            E element = this.list.get(0);
            this.list.remove(0);
            return element;
        }
    }

    /**
    * This looks at the first element of the stack, if empty it throws an exception in the pop method.
    *
    * @return Peeks at the first element in the Stack and returns it
    */
    public E peek(){
        E element = this.pop();
        this.push(element);
        return element;
    }

    /**
    * This returns if the top of the stack is empty or not
    *
    * @return this returns true if there are no elements in th stack
    */
    public boolean isEmpty(){
        if(this.list.size() == 0){
            return true;
        } else {
          return false;
        }
    }

    /**
    * This returns if the two stacks are equal
    *
    * @return returns if to PureStacks of the same type are equivalent
    */
    public boolean equals(PureStack<E> stack){
        return this.list.equals(stack.list);
    }

    /**
    * This returns if the two stacks are equal
    *
    * @return Try catch statement to check if the objects are the same type
    */
    public boolean equals(Object obj){
      try {
          PureStack<E> other = (PureStack<E>) obj;
          return this.equals(other);
      } catch (ClassCastException e) {
          return false;
      }
    }

    // /**
    // * Main method that tests all of the methods of this class
    // *
    // *
    // */
    // public static void main(String[] args){
    //     // This tests out the string method
    //     PureStack<String> stringStack = new PureStack<String>();
    //     System.out.println(stringStack.toString());
    //     System.out.println("");
    //
    //     // This tests out the push method and string method
    //     stringStack.push("!!!");
    //     stringStack.push("World");
    //     stringStack.push("Hello");
    //     System.out.println("Tests the add method adding Hello World!!! " + stringStack.toString());
    //     System.out.println("");
    //
    //     // This tests out the pop method
    //     System.out.println("Tests out the pop method for PureStack " + stringStack.toString() + " = " + stringStack.pop());
    //     System.out.println("Now stack looks like " + stringStack.toString());
    //     PureStack<String> emptyStack = new PureStack<String>();
    //     try{
    //         System.out.println("Tests pop method = " + emptyStack.pop());
    //     } catch(NoSuchElementException e){
    //         System.out.println("NoSuchElementException: " + e.getMessage());
    //     }
    //     stringStack.push("Hello");
    //     System.out.println("Added Hello again " + stringStack.toString());
    //     PureStack<Integer> integerStack = new PureStack<Integer>();
    //     integerStack.push(7);
    //     System.out.println("Takes only element 7 out of integer stack " + integerStack.pop());
    //     System.out.println("This is the integerStack now " + integerStack.toString());
    //     System.out.println("");
    //
    //     // This tests out the peek method
    //     System.out.println("This peeks at the stringStack " + stringStack.peek());
    //     try{
    //         System.out.println("This peeks at the integerStack " + integerStack.peek());
    //     } catch(NoSuchElementException e){
    //         System.out.println("NoSuchElementException: " + e.getMessage());
    //     }
    //     System.out.println("");
    //
    //     // This tests out the isEmpty method
    //     System.out.println("This tests out if " + integerStack.toString() + " is empty : " + integerStack.isEmpty());
    //     System.out.println("This tests out if " + stringStack.toString() + " is empty : " + stringStack.isEmpty());
    //     System.out.println("");
    //
    //     // This tests out the is equal method
    //     PureStack<String> stringStack2 = new PureStack<String>();
    //     integerStack.push(0);
    //     integerStack.push(1);
    //     integerStack.push(2);
    //     integerStack.push(3);
    //     stringStack2.push("!!!");
    //     stringStack2.push("World");
    //     stringStack2.push("Hello");
    //     System.out.println("Does " + stringStack.toString() + " = " + stringStack2.toString() + " : " + stringStack.equals(stringStack2));
    //     System.out.println("Does " + stringStack.toString() + " = " + integerStack.toString() + " : " + stringStack.equals(integerStack));
    //     PureStack<Integer> integerStack2 = new PureStack<Integer>();
    //     integerStack2.push(0);
    //     integerStack2.push(1);
    //     integerStack2.push(3);
    //     System.out.println("Does " + integerStack.toString() + " = " + integerStack2.toString() + " : " + integerStack.equals(integerStack2));
    //     System.out.println("");
    // }

}
