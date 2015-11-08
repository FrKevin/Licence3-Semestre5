package jadelex;

public class Repeat extends BaseToken {
	
	private int n;
	
	public Repeat(int nb) {
		super(TokenType.REPEAT);
		n = nb;
	}
	
	public int getOccurences() {
		return n;
	}
	
}
