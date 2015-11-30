package ard;

import java.io.Reader;

public class ArdExercice1 extends Ard {

	protected ArdExercice1(Reader in) {
		super(in);
	}
	
	
	
	
	private void S() throws SyntaxException, ParserException {
		switch(current) {
		case 'a':
		case 'b':
		case 'c':
		case '(':
			E();
			R();
			S();
			break;
		case ')':
		case END_MARKER:
			break;
		default:
			throw new SyntaxException(ErrorType.NO_RULE,current);
		}
	}
	
	
	
	private void E() throws SyntaxException, ParserException {
		switch(current) {
		case 'a':
		case 'b':
		case 'c':
			L();
			break;
		case '(':
			eat('(');
			S();
			eat(')');
			break;
		default:
			throw new SyntaxException(ErrorType.NO_RULE,current);
		}
	}
	
	
	
	private void R() throws SyntaxException, ParserException {
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
			C();
			break;
		case 'a':
		case 'b':
		case 'c':
		case '(':
		case ')':
		case END_MARKER:
			break;
		default:
			throw new SyntaxException(ErrorType.NO_RULE,current);
		}
	}
	
	
	
	private void L() throws SyntaxException, ParserException {
		switch(current) {
		case 'a':
		case 'b':
		case 'c':
			eat(current);
			break;
		default:
			throw new SyntaxException(ErrorType.NO_RULE,current);
		}
	}
	
	
	
	
	
	
	
	
	
	private void C() throws SyntaxException, ParserException {
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
			eat(current);
			break;
		default:
			throw new SyntaxException(ErrorType.NO_RULE,current);
		}
	}
	
	
	

	@Override
	protected void axiom() throws SyntaxException, ParserException {
		S();
	}

}
