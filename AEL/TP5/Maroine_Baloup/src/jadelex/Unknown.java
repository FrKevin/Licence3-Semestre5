package jadelex;
/**
 * YYtoken implentation for all unknown patterns 
 */

public class Unknown extends BaseToken{
  private String source;
  /**
   * Token original text
   */
  public String getSource(){
    return source;
  }
  public Unknown(String source){
     super(TokenType.UNKNOWN);
     this.source = source;
  }
      
  public String toString(){
        return super.toString()+"["+source+"]";
  }

}