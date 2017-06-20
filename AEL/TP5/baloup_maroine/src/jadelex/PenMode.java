package jadelex;

/**
 *  YYtoken implementation for PEN_MODE token type
 */

public class PenMode extends BaseToken{
    private boolean  on;
    /**
     * Choosen mode.
     * true <==> writing mode
     */
    public boolean getMode(){
        return on;
    }
    public PenMode(boolean on){
        super(TokenType.PEN_MODE);
        this.on = on;
    }
    public String toString(){
        return super.toString()+"["+on+"]";
    }
}