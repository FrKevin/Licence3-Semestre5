package jadelex;

public class StepLength extends BaseToken {

	private int l;
	
	public StepLength(int length) {
		super(TokenType.STEP_LENGTH);
		l = length;
	}
	
	public int getLength() {
		return l;
	}
	
	

    public String toString(){
        return super.toString()+"["+l+"]";
    }
}
