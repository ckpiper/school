/**
 * A brief description of this class...
 *
 * @author Colton Piper
 */

//package packageName

//import java.xxxxx.*;

public class PureLinkedList<Type> {

    //the value at the head of this list
    private Type value;

    //the tail of this list
    private PureLinkedList<Type> tail;

    /**
     * Class constructor.
     *
     * @param value  The value of the head of this list
     */
    public PureLinkedList(Type value) {
        this.value = value;
        tail = null;
    }

    /**
     * Returns a String version of this.
     *
     * @return  A String description of this.
     */
    public String toString() {
       if (this.tail == null) {
           return "[" + this.value + "]";
       } else {
           String tailString = this.tail.toString();
           String tailMinusLeftBracket = tailString.substring(1);
           return "[" + this.value + ", " + tailMinusLeftBracket;
       }
    }

    /**
    * Creates the new linked list as the tail value
    *
    * @param newValue This is the value you wish to add
    */
    public void add(Type newValue){
        if(tail == null){
            this.tail = new PureLinkedList<Type>(newValue);
        } else {
            tail.add(newValue);
        }
    }

    /**
    * Tells us if this is the last item in the list
    *
    * @return Tells us if this is the last item in the list
    */
    public boolean isLast(){
        return this.tail == null;
    }

    /**
    * Will return the length of the linked list
    *
    * @return returns length of the linked list
    */
    public int length(){
        int count = 1;
        if(tail == null){
            return count;
        } else {
            count = count + tail.length();
            return count;
        }
    }

    /**
    * Will return the first element of the list
    *
    * @return returns the first element of the linked list
    */
    public Type getFirst(){
        return this.value;
    }

    /**
    * Will set the first element of the list
    *
    * @param newValue This is the value you want to set the head to
    * precondition set element needs to be same type as linked lists elements
    */
    public void setFirst(Type newValue){
        this.value = newValue;
    }

    /**
    * Will get the tail and everything after the first tail
    *
    * @return returns the first tail of the linked list
    */
    public PureLinkedList<Type> getTail(){
        return this.tail;
    }

    /**
    * Will set the first tail as a newValue
    *
    * @param newValue This is the value you want to set the tail to
    * precondition newValue element needs to be same type as linked lists elements
    */
    public void setTail(PureLinkedList<Type> newValue){
        this.tail = newValue;
    }

    /**
    * This method gets the element at the index requested
    *
    * @param index The index you want (Cannot be larger then the list and cannot be negative)
    * @return returns the element at index in Linked List
    */
    public Type get(int index){
        if(index > this.length()-1 || index < 0){
            throw new IndexOutOfBoundsException("Your index is to high or to low!!");
        } else {
            if (index == 0){
                return this.value;
            } else {
                Type element = this.tail.get(index-1);
                return element;
            }
        }
    }

    /**
    * This method sets the element at the index requested
    *
    * @param index The index you want to set (Cannot be larger then the list and cannot be negative)
    * @param element This is the element you want to put in to index
    */
    public void set(int index, Type element){
        if(index > this.length()-1 || index < 0){
            throw new IndexOutOfBoundsException("Your index is to high or to low!!");
        } else {
            if (index == 0){
                this.setFirst(element);
            } else {
                this.tail.set(index-1, element);
            }
        }
    }

    /**
    * This method tells us if two linked lists are equivalent
    *
    * @param linkedList the linked list that you are comparing
    * @return returns a boolean statement if the linked lists are equivalent (precondition have lists be the same Type)
    */
    public boolean equals(PureLinkedList<Type> linkedList){
        if (this.length() != linkedList.length()){
            return false;
        } else if (this.value.equals(linkedList.value) && this.tail != null && linkedList.tail != null){
            return this.tail.equals(linkedList.tail);
        } else if (this.value.equals(linkedList.value)){
            return true;
        } else {
            return false;
        }
    }

    /**
     * Returns whether this equals another object.
     *
     * @param obj  The object to determine equivalence with this.
     * @return  True if obj is a linkedList with elements equivalent to this, false otherwise.
     */
    public boolean equals(Object obj) {
        try {
            PureLinkedList<Type> other = (PureLinkedList<Type>) obj;
            return this.equals(other);
        } catch (ClassCastException e) {
            return false;
        }
    }

    /**
     * Unit test for PureLinkedList

     * @param args  Arguments used to test this class.
     */
    public static void main(String[] args) {
        //This tests out the printing method
        PureLinkedList<Integer> integers = new PureLinkedList<Integer>(5);
        System.out.println("Printing Test for integers = " + integers.toString());
        PureLinkedList<String> strings = new PureLinkedList<String>("Hello");
        System.out.println("Printing Test for strings = " + strings );
        System.out.println("  ");

        //This tests out the add method and prints it
        integers.add(6);
        integers.add(7);
        System.out.println("Adding Test 6,7 = " + integers);
        strings.add("World");
        System.out.println("Adding 'World' = " + strings);
        System.out.println("  ");

        //This tests out isLast
        PureLinkedList<Integer> number = new PureLinkedList<Integer>(0);
        System.out.println("Tests isLast method = " + number.isLast());
        System.out.println("Tests isLast method = " + integers.isLast());
        System.out.println("  ");

        //This tests the length method
        System.out.println("Tests length method = " + integers.length());
        System.out.println("  ");

        //This tests out the getFirst method
        System.out.println("Tests getFirst method = " + integers.getFirst());
        System.out.println("Tests getFirst method = " + strings.getFirst());
        System.out.println("  ");

        //This tests out the setFirst method
        integers.setFirst(8);
        strings.setFirst("Hi");
        System.out.println("Tests setFirst method = " + integers);
        System.out.println("Tests setFirst method = " + strings);
        System.out.println("  ");

        //This tests out the getTail method
        System.out.println("Tests getTail method = " + integers.getTail());
        System.out.println("Tests getTail method = " + strings.getTail());
        System.out.println("  ");

        //This tests out the setTail method
        PureLinkedList<Integer> integers2 = new PureLinkedList<Integer>(7);
        integers2.add(6);
        integers2.add(5);
        integers.setTail(integers2);
        PureLinkedList<String> strings2 = new PureLinkedList<String>(".");
        strings2.add("What's");
        strings2.add("up?");
        strings.setTail(strings2);
        System.out.println("Tests setTail method = " + integers);
        System.out.println("Tests setTail method = " + strings);
        System.out.println("  ");

        //This tests out the get method
        System.out.println("Tests get method = " + integers.get(0));
        try{
            System.out.println("Tests get method = " + integers.get(10));
        } catch(IndexOutOfBoundsException e){
            System.out.println("IndexOutOfBoundsException:" + e.getMessage());
        }
        System.out.println("Tests get method = " + strings.get(2));
        System.out.println("  ");

        //This tests out the set method
        integers.set(2, 1);
        System.out.println("Tests set method (1) = " + integers);
        strings.set(3, "going on?");
        System.out.println("Tests set method (going on?) = " + strings);
        try{
            integers.set(10, 3);
            System.out.println("Tests get method = " + integers);
        } catch(IndexOutOfBoundsException e){
            System.out.println("IndexOutOfBoundsException:" + e.getMessage());
        }
        System.out.println("  ");

        //This tests out the equals method
        PureLinkedList<Integer> integersEqual = new PureLinkedList<Integer>(8);
        integersEqual.add(7);
        integersEqual.add(6);
        integersEqual.add(1);
        PureLinkedList<String> stringsEqual = new PureLinkedList<String>("Hi");
        stringsEqual.add(".");
        stringsEqual.add("What's");
        stringsEqual.add("going on?");
        System.out.println("Tests equals method = " + integers.equals(integersEqual));
        System.out.println("Tests equals method = " + strings.equals(stringsEqual));
        System.out.println("Tests equals method = " + integers.equals(integers2));
        PureLinkedList<Integer> integersNotEqual = new PureLinkedList<Integer>(8);
        integersNotEqual.add(7);
        integersNotEqual.add(6);
        integersNotEqual.add(5);
        System.out.println("Tests equals method = " + integers.equals(integersNotEqual));
    }

}
