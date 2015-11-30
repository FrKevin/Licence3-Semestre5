package exercices;

import java.io.Reader;

import ard.Ard;
import ard.ErrorType;
import ard.ParserException;
import ard.SyntaxException;

public class ArdExercice1 extends Ard {

	public ArdExercice1(Reader in) {
		super(in);
	}
	
	
	
	private String expandedExpression = null;
	
	
	
	
	private String S() throws SyntaxException, ParserException {
		switch(current) {
		case 'a':
		case 'b':
		case 'c':
		case '(':
			String ret = "";
			String repeted = E();
			int count = R();
			for (int i=0;i<count; i++)
				ret+=repeted;
			ret+=S();
			return ret;
		case ')':
		case END_MARKER:
			return "";
		default:
			throw new SyntaxException(ErrorType.NO_RULE,current);
		}
	}
	
	
	
	private String E() throws SyntaxException, ParserException {
		switch(current) {
		case 'a':
		case 'b':
		case 'c':
			return L();
		case '(':
			eat('(');
			String s = S();
			eat(')');
			return s;
		default:
			throw new SyntaxException(ErrorType.NO_RULE,current);
		}
	}
	
	
	
	private int R() throws SyntaxException, ParserException {
		switch(current) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			return C();
			
		case 'a':
		case 'b':
		case 'c':
		case '(':
		case ')':
		case END_MARKER:
			return 1;
		default:
			throw new SyntaxException(ErrorType.NO_RULE,current);
		}
	}
	
	
	
	private String L() throws SyntaxException, ParserException {
		switch(current) {
		case 'a':
		case 'b':
		case 'c':
			char c = current;
			eat(current);
			return c+"";
		default:
			throw new SyntaxException(ErrorType.NO_RULE,current);
		}
	}
	
	
	
	
	
	
	
	
	
	private int C() throws SyntaxException, ParserException {
		switch(current) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			char c = current;
			eat(current);
			return Integer.parseInt(c+"");
		default:
			throw new SyntaxException(ErrorType.NO_RULE,current);
		}
	}
	
	
	

	@Override
	protected void axiom() throws SyntaxException, ParserException {
		expandedExpression = S();
	}



	public String getExpandedExpression() {
		return expandedExpression;
	}


	

}
