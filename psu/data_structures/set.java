import java.util.ArrayList;
import java.util.*;
import java.util.Comparator;

/**
 * This class is a class for Pure Sets.
 *
 * @author Colton Piper
 */

//package packageName

//import java.xxxxx.*;

public class PureSet<E extends Object>{

    // The list in this PureSet
    private final ArrayList<E> elements;

    /**
     * Class constructor.
     *
     * @param elements This is the underlying ArrayList for the PureSet
     */
    public PureSet(Iterable<E> elements) {
        this.elements = new ArrayList<E>();
        for(E element : elements){
            if (!this.contains(element)) {
                this.elements.add(element);
            }
        }
    }

    /**
    * Returns a String version of the Set you are calling on.
    *
    * @return  A String description of this.
    */
    public final String toString(){
        return "{" + this.elements.toString().substring(1, this.elements.toString().length()-1) + "}" ;
    }

    /*
    * This method tells you if a PureSet contains the element you put in as an arguement
    *
    * @param obj this is the element you want to know if it is in the set
    * @return This returns true if the PureSet contains the obj and false if it does not contain the obj
    */
    public final boolean contains(E obj){
        for(E element : this.elements){
            if(obj.equals(element)){
                return true;
            }
        }
        return false;
    }


    /**
    * This gives us the intersection of two Sets
    *
    * @param otherSet this is the other set you are comparing this set to
    * @return Returns the new PureSet of elements common in both sets
    */
    public final PureSet<E> intersectionWith(PureSet<E> otherSet){
        List<E> newSet = new ArrayList<E>();
        for (E element : this.elements) {
            if (otherSet.contains(element)) {
                newSet.add(element);
            }
        }
        return new PureSet<E>(newSet);
    }

    /**
    * This gives us the union of two Sets
    *
    * @param otherSet this is the other set you are comparing this set to
    * @return Returns the new PureSet of all elements in both sets
    */
    public final PureSet<E> unionWith(PureSet<E> otherSet){
        List<E> newSet = new ArrayList<E>();
        for(E element : this.elements){
            newSet.add(element);
        }
        for(E element : otherSet.elements){
            newSet.add(element);
        }
        return new PureSet<E>(newSet);
    }

    /**
    * This gives us this - otherSet
    *
    * @param otherSet this is the other set you are comparing this set to
    * @return Returns the new PureSet of all elements in this and not in otherSet
    */
    public final PureSet<E> differenceWith(PureSet<E> otherSet){
        List<E> newSet = new ArrayList<E>();
        for (E element : this.elements) {
            if (!otherSet.contains(element)) {
                newSet.add(element);
            }
        }
        return new PureSet<E>(newSet);
    }

    /**
    * This gives us is this subset of otherSet
    *
    * @param otherSet this is the other set you are comparing this set to
    * @return Returns true if otherSet contatins every element in this and false otherwise
    */
    public final boolean isSubsetOf(PureSet<E> otherSet){
        return this.elements.equals(this.intersectionWith(otherSet).elements);
    }

    /**
    * This gives us if the two sets are equal
    *
    * @param otherSet this is the other set you are comparing this set to
    * @return Returns true if the two sets contain the same elements
    */
    public final boolean equals(PureSet<E> otherSet){
        return this.isSubsetOf(otherSet) && otherSet.isSubsetOf(this);
    }

    /**
    * This returns a generic list of the elements of this
    *
    * @return Returns a list of all the elements of this
    */
    public List toList(){
        ArrayList<E> list = new ArrayList<E>();
        for(E element : this.elements){
            list.add(element);
        }
        return (List)list;
    }

    // /**
    // * The Unit testing takes place here
    // *
    // *
    // */
    // public static void main(String[] args) {
    //     // This code tests out the constructor and toString method
    //     ArrayList<Integer> numbers = new ArrayList<Integer>();
    //     numbers.add(1);
    //     numbers.add(2);
    //     numbers.add(3);
    //     PureSet<Integer> numerals = new PureSet<Integer>(numbers);
    //     System.out.println("numeralsSet: " + numerals);
    //     Vector<String> strings = new Vector<String>();
    //     strings.add("Narwhal");
    //     strings.add("Beluga");
    //     strings.add("Narwhal");
    //     PureSet<String> stringSet = new PureSet<String>(strings);
    //     System.out.println("stringSet: " + stringSet);
    //     TreeSet<String> moreStrings = new TreeSet<String>();
    //     moreStrings.add("llama");
    //     moreStrings.add("alpaca");
    //     moreStrings.add("vicuna");
    //     stringSet = new PureSet<String>(moreStrings);
    //     System.out.println("After resetting, stringSet: " + stringSet);
    //
    //     // This code tests out the contains method
    //     System.out.println("\n" + "numerals does contain 2: " + numerals.contains(2));
    //     System.out.println("numerals does not contain 4: " + numerals.contains(4));
    //     System.out.println("stringSet does contain llama: " + stringSet.contains("llama"));
    //     System.out.println("stringSet does not contain llamas: " + stringSet.contains("llamas"));
    //
    //     // This code tests out the intersectionWith method
    //     ArrayList<Integer> numbers2 = new ArrayList<Integer>();
    //     numbers2.add(1);
    //     numbers2.add(2);
    //     numbers2.add(4);
    //     PureSet<Integer> numerals2 = new PureSet<Integer>(numbers2);
    //     System.out.println("\n" + numerals + " intersected with " + numerals2 + " = " + numerals.intersectionWith(numerals2));
    //     TreeSet<String> moreStrings2 = new TreeSet<String>();
    //     moreStrings2.add("lamb");
    //     moreStrings2.add("alpaca");
    //     moreStrings2.add("llama");
    //     PureSet<String> stringSet2 = new PureSet<String>(moreStrings2);
    //     System.out.println(stringSet + " intersected with " + stringSet2 + " = " + stringSet.intersectionWith(stringSet2));
    //
    //     // This code tests out the unionWith method
    //     System.out.println("\n" + numerals + " U " + numerals2 + " = " + numerals.unionWith(numerals2));
    //     System.out.println(stringSet + " U " + stringSet2 + " = " + stringSet.unionWith(stringSet2));
    //
    //     // This code tests out the differenceWith method
    //     System.out.println("\n" + numerals + " - " + numerals2 + " = " + numerals.differenceWith(numerals2));
    //     System.out.println(stringSet + " - " + stringSet2 + " = " + stringSet.differenceWith(stringSet2));
    //
    //     // This code tests out the isSubsetOf method
    //     numbers2.add(3);
    //     PureSet<Integer> numerals3 = new PureSet<Integer>(numbers2);
    //     System.out.println("\n" + numerals + " is a subset of " + numerals2 + ": " + numerals.isSubsetOf(numerals2));
    //     System.out.println(numerals + " is a subset of " + numerals3 + ": " + numerals.isSubsetOf(numerals3));
    //     System.out.println(stringSet.intersectionWith(stringSet2) + " is a subset of " + stringSet2 + ": " + stringSet.intersectionWith(stringSet2).isSubsetOf(stringSet2));
    //
    //     // This code tests out the equals method
    //     numbers.add(4);
    //     PureSet<Integer> numerals4 = new PureSet<Integer>(numbers);
    //     System.out.println("\n" + numerals + " = " + numerals2 + ": " + numerals.equals(numerals2));
    //     System.out.println(numerals3 + " = " + numerals4 + ": " + numerals3.equals(numerals4));
    //
    //     // This code tests out the toList method
    //     System.out.println("\n" + numerals + " to generic List: " + numerals.toList());
    //
    // }

}
