package jadelex;

import jade.Direction;

public class Move extends BaseToken {

	protected Move(Direction dir) {
		super(TokenType.MOVE);
		d = dir;
	}
	
	
	private Direction d;
	
	public Direction getDirection() {
		return d;
	}
	

    public String toString(){
        return super.toString()+"["+d+"]";
    }
	
	

}
