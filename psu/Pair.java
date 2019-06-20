/**
 * Represents a Pair of values.
 *
 * @author  Colton Piper
 */

 public class Pair<FirstType, SecondType> {

    //the first element in the pair
    private FirstType first ;

    //the second element in the pair
    private SecondType second ;

  /**
   * Class constructor.
   *
   * @param first  The first element in this Pair.
   * @param second  The second element in this Pair.
   */
    public Pair(FirstType first, SecondType second){
        this.first = first ;
        this.second = second ;
    }

  /**
   * Returns a String representation of this Pair.
   *
   * @return  A String, "(X, Y)", where X is the first element and Y is the second element.
   */
    public String toString() {
      return "(" + this.first + ", " + this.second + ")";
    }

  /**
   * Sets the first element.
   *
   * @param newFirst  The value to set the first element to.
   */
   public void setFirst(FirstType newFirst){
     this.first = newFirst ;
   }

   /**
    * Sets the second element.
    *
    * @param newSecond  The value to set the second element to.
    */
    public void setSecond(SecondType newSecond){
      this.second = newSecond ;
    }

  /**
   * Returns the first element.
   *
   * @return the first element in this.
   */
   public FirstType getFirst(){
     return this.first ;
   }

  /**
   * Returns the second element.
   *
   * @return the second element in this.
   */
   public SecondType getSecond(){
     return this.second ;
   }

   /**
    * Tests whether two Pairs are equal.
    *
    * @param other  Another pair that might be equivalent to this.
    * @return  True if both the first element of this equals the first element of other
      and the second element of this equals the second element of other, false otherwise.
    */
    public boolean equals(Pair<FirstType, SecondType> other) {
      boolean firstsEqual = this.getFirst().equals(other.getFirst());
      boolean secondsEqual = this.getSecond().equals(other.getSecond());
      return firstsEqual && secondsEqual;
    }

    /**
     * Returns whether this equals another object.
     *
     * @param obj  The object to determine equivalence with this.
     * @return  True if obj is a Pair with elements equivalent to this, false otherwise.
     */
    public boolean equals(Object obj) {
        try {
            Pair<FirstType, SecondType> other = (Pair<FirstType, SecondType>) obj;
            return this.equals(other);
        } catch (ClassCastException e) {
            return false;
        }
    }

    /**
     * Returns a pair with the elements swapped.
     *
     * @return  A new Pair with the elements in reverse order.
     */
    public Pair<SecondType, FirstType> getReverse() {
        return new Pair<SecondType, FirstType>(this.getSecond(), this.getFirst());
    }

    /**
     * Unit test.
     *
     * @param args  Command-line parameters for this test.  Currently unused.
     */
    public static void main(String[] args) {
        boolean allCorrect = true ;
        boolean isCorrect ;
        String success = "Test completed successfully" ;
        String failure = "Something went wrong!!!!!!!!!!!" ;
        Pair<String, Integer> twoThings = new Pair<String, Integer>("Hi", new Integer(5)) ;
        Integer integer = twoThings.getSecond() ;
        Pair<Integer, String> pair = new Pair<Integer, String>(6, "Hi") ;
        Pair<String, Integer> things = new Pair<String, Integer>("Beluga", 56) ;
        String output = twoThings.toString() ;

        System.out.println("twoThings: " + output) ;
        isCorrect = output.equals("(Hi, 5)") ;
        System.out.println((isCorrect ? success : failure)) ;
        allCorrect = allCorrect && isCorrect ;

        output = twoThings.getFirst() ;
        isCorrect = output.equals("Hi") ;
        System.out.println((isCorrect ? success : failure)) ;
        allCorrect = allCorrect && isCorrect ;

        integer = pair.getFirst() ;
        isCorrect = integer.equals(6) ;
        System.out.println((isCorrect ? success : failure)) ;
        allCorrect = allCorrect && isCorrect ;

        pair.setFirst(-124) ;
        integer = pair.getFirst() ;
        isCorrect = integer.equals(-124) ;
        System.out.println((isCorrect ? success : failure)) ;
        allCorrect = allCorrect && isCorrect ;

        things.setFirst("Puma") ;
        String string = things.getFirst() ;
        isCorrect = string.equals("Puma") ;
        System.out.println((isCorrect ? success : failure)) ;
        allCorrect = allCorrect && isCorrect ;

        pair.setSecond("Puma") ;
        string = pair.getSecond() ;
        isCorrect = string.equals("Puma") ;
        System.out.println((isCorrect ? success : failure)) ;
        allCorrect = allCorrect && isCorrect ;

        //Two integer-string pairs with same values
        pair = new Pair<Integer, String>(16, "beluga");
        Pair<Integer,String> otherPair = new Pair<Integer, String>(16, "beluga");
        System.out.println("Now testing whether " + pair + " equals " + otherPair + ":");
        isCorrect = pair.equals(otherPair);
        System.out.println(isCorrect);
        System.out.println((isCorrect ? success : failure));
        allCorrect = allCorrect && isCorrect;

        //Two integer-string pairs with different values
        pair = new Pair<Integer, String>(15, "beluga");
        otherPair = new Pair<Integer, String>(16, "beluga");
        System.out.println("Now testing whether " + pair + " equals " + otherPair + ":");
        isCorrect = pair.equals(otherPair);
        System.out.println(isCorrect);
        System.out.println((isCorrect ? success : failure));
        allCorrect = allCorrect && isCorrect;

        //Two string-string pairs with same values
        Pair<String, String> newthings = new Pair<String, String>("Puma", "beluga");
        Pair<String, String> stringsPair = new Pair<String, String>("Puma", "beluga");
        System.out.println("Now testing whether " + newthings + " equals " + stringsPair + ":");
        isCorrect = newthings.equals(stringsPair);
        System.out.println(isCorrect);
        System.out.println((isCorrect ? success : failure));
        allCorrect = allCorrect && isCorrect;

        //Two string-string pairs with different values
        newthings = new Pair<String, String>("Puma", "beluga");
        stringsPair = new Pair<String, String>("Panther", "beluga");
        System.out.println("Now testing whether " + newthings + " equals " + stringsPair + ":");
        isCorrect = things.equals(stringsPair);
        System.out.println(isCorrect);
        System.out.println((isCorrect ? success : failure));
        allCorrect = allCorrect && isCorrect;

        //One integer-integer pair and one integer-string pair
        Pair<Integer, Integer> numbers = new Pair<Integer, Integer>(1, 2);
        otherPair = new Pair<Integer, String>(1, "beluga");
        System.out.println("Now testing whether " + numbers + " equals " + otherPair + ":");
        isCorrect = numbers.equals(otherPair);
        System.out.println(isCorrect);
        System.out.println((isCorrect ? success : failure));
        allCorrect = allCorrect && isCorrect;

        pair = new Pair<Integer, String>(16, "bebop") ;
        otherPair = new Pair<Integer, String>(16, "bebop") ;
        System.out.println("Now testing whether " + pair + " equals " + otherPair + ":");
        isCorrect = pair.equals((Object) otherPair) ;
        System.out.println(isCorrect);
        System.out.println((isCorrect ? success : failure));
        allCorrect = allCorrect && isCorrect;

        System.out.println("Now testing whether " + pair + " equals " + otherPair + ":");
        isCorrect = ((Object) pair).equals(otherPair);
        System.out.println(isCorrect);
        System.out.println((isCorrect ? success : failure));
        allCorrect = allCorrect && isCorrect;

        Pair<String, Integer> opposePair = pair.getReverse() ;
        Pair<String, String> opposeStringsPair = stringsPair.getReverse();
        System.out.println(pair + " reversed is " + opposePair);
        System.out.println(stringsPair + " reversed is " + opposeStringsPair);

        System.out.println((allCorrect ? "All tests were successful!" : "At least one test failed!")) ;

    }

}
