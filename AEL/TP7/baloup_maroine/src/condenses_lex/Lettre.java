package condenses_lex;
/**
 *  YYtoken implementation for LETTRE
 */
public class Lettre extends BaseToken{
    private final String value;
    public String getValue(){
        return value;
    }
    public Lettre(String value){
        super(TokenType.LETTRE);
        this.value = value;
    }
    public String toString(){
        return super.toString()+"["+value+"]";
    }

}