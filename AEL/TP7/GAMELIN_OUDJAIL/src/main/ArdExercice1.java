package main;

import java.io.Reader;

import ard.Ard;
import ard.ErrorType;
import ard.ParserException;
import ard.SyntaxException;

public class ArdExercice1 extends Ard{

	protected ArdExercice1(Reader in) {
		super(in);
	}
	
	private void S() throws SyntaxException, ParserException {
		switch (current) {
		case 'a':
		case 'b':
		case 'c':
		case '(':
			// S -> ERS
			E();
			R();
			S();
			break;
		case ')':
		case END_MARKER:
			// S -> epsilon
			break;
		default:
			// erreur
//			String myName = Thread.currentThread().getStackTrace()[1].getMethodName();
//			throw new ParserException("No rule for variable "+ myName + " token " + current+ "	."); 
			throw new SyntaxException(ErrorType.NO_RULE,current);
		}
	}

	private void E() throws SyntaxException, ParserException{
		switch (current) {
		case 'a':
		case 'b':
		case 'c':
			// E -> L
			L();
			break;
		case '(':
			// E -> (S)
			eat('(');
			S();
			eat(')');
			break;
		default:
			throw new SyntaxException(ErrorType.NO_RULE,current);
		}
	}

	private void L() throws SyntaxException, ParserException{
		if(current >= 'a' && current <= 'c'){
			eat(current);
		}
		else{
			throw new SyntaxException(ErrorType.NO_RULE,current);
		}
	}
	
	private void R() throws SyntaxException, ParserException{
		switch (current) {
		case 'a':
		case 'b':
		case 'c':
		case '(':
		case ')':
		case END_MARKER:
			// R -> epsilon
			break;
		default:
			if(current >= '0' && current <= '9'){
				// R->C
				C();
			}
			throw new SyntaxException(ErrorType.NO_RULE,current);
		}
	}
	
	private void C() throws SyntaxException, ParserException{
		if(current >= '0' && current <= '9'){
			eat(current);
		}
		else{
			throw new SyntaxException(ErrorType.NO_RULE,current);
		}
	}

	@Override
	protected void axiom() throws SyntaxException, ParserException {
		S();
	}

}
