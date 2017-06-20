package condenses_lex;
/**
 * YYtoken implentation for End of Data
 */

public class Eod extends BaseToken{
  
  public Eod(String source){
     super(TokenType.EOD);
  }
      
  public String toString(){
        return super.toString();
  }

}