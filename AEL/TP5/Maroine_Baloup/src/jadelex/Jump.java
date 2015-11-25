package jadelex;

public class Jump extends BaseToken {

	private int X, Y;
	
	public Jump(int x, int y) {
		super(TokenType.JUMP);
		X = x;
		Y = y;
	}
	
	public int getX() { return X; }
	public int getY() { return Y; }

    public String toString(){
        return super.toString()+"["+X+";"+Y+"]";
    }
}
