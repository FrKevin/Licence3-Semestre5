package jadelex;
/**
 *   Minimal  YYtoken implementation
 **/

class BaseToken implements Yytoken{
    private final TokenType type;
    
    /**
     * Token type
     */
    public TokenType getType(){
        return type;
    }
    protected BaseToken(TokenType type){
        this.type = type;
    }
    public String toString(){
        return "<"+type+">";
    }
}