package postfixees;
public abstract class Operateur extends AbstractToken implements Yytoken {
  public final int arite;
  public int arite(){
    return arite;
  }
  protected abstract int calcul(int... values);
  
  public int evaluate(int [] values) throws AriteException{
    if (values.length != arite)
      throw new AriteException();
    return calcul(values);
  }
  
  public Operateur(String image, int arite){
    super(image);
    this.arite = arite;
  }
}
