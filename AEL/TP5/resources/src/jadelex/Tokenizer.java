package jadelex;
/**
 *  Jade Lexical Parser 
 */
public interface Tokenizer{
    /**
     * @return next Token from source
     */
    jadelex.Yytoken yylex() throws java.io.IOException;
    
    /**
     * raw text of the token
     */
    String yytext();
}