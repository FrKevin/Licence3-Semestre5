package postfixees;
public class Plus  extends Operateur implements Yytoken{
 
  protected int calcul(int... values){
    return values[0]+values[1];
  }
  
  public Plus(String image){
    super(image,2);
  }
}
