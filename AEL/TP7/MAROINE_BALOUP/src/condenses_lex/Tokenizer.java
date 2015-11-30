package condenses_lex;
/**
 *  Lexical Parser 
 */
public interface Tokenizer{
    /**
     * @return next Token from source
     */
    Yytoken yylex() throws java.io.IOException;
    
    /**
     * raw text of the token
     */
    String yytext();
}