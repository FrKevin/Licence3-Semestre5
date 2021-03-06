package main;

import java.io.Reader;

import ard.ArdAbstract;
import ard.ErrorType;
import ard.ParserException;
import ard.SyntaxException;

/**
 * Implémentation d'un analyseur récursif descendant pour la grammaire
 * S -> ERS | epsilon 
 * E -> L   | (S) 
 * R -> C   | epsilon 
 * L -> a|b|c 
 * C -> 0|1|...|9
 * 
 * @author Gamelin Kevin, Oudjail Veis
 *
 */
public class ArdExercice1 extends ArdAbstract{


	
	protected ArdExercice1(Reader in) {
		super(in);
	}
	
	private String S() throws SyntaxException, ParserException {
		switch (current) {
		case 'a':
		case 'b':
		case 'c':
		case '(':
			// S -> ERS
			String expression = E();
			int repeat = R();
			StringBuilder developedExpression = new StringBuilder();
			for(int i = 1; i <= repeat; ++i) {
				developedExpression.append(expression);
			}
			return developedExpression + S();
		case ')':
		case END_MARKER:
			// S -> epsilon
			return "";
		default:
			// erreur
//			String myName = Thread.currentThread().getStackTrace()[1].getMethodName();
//			throw new ParserException("No rule for variable "+ myName + " token " + current+ "	."); 
			throw new SyntaxException(ErrorType.NO_RULE,current);
		}
	}

	private String E() throws SyntaxException, ParserException{
		switch (current) {
		case 'a':
		case 'b':
		case 'c':
			// E -> L
			return L();
		case '(':
			// E -> (S)
			eat('(');
			String result = S();
			eat(')');
			return result;
		default:
			throw new SyntaxException(ErrorType.NO_RULE,current);
		}
	}

	private String L() throws SyntaxException, ParserException{
		if(current >= 'a' && current <= 'c'){
			String result = "" + current;
			eat(current);
			return result;
		}
		else{
			throw new SyntaxException(ErrorType.NO_RULE,current);
		}
	}
	
	private int R() throws SyntaxException, ParserException{
		switch (current) {
		case 'a':
		case 'b':
		case 'c':
		case '(':
		case ')':
		case END_MARKER:
			// R -> epsilon
			return 1;
		default:
			if(current >= '0' && current <= '9'){
				// R -> C
				return C();
			}
			throw new SyntaxException(ErrorType.NO_RULE,current);
		}
	}
	
	private int C() throws SyntaxException, ParserException{
		if(current >= '0' && current <= '9'){
			// C -> 0 .. 9
			int result = Integer.parseInt("" +current);
			eat(current);
			return result;
			
		}
		else{
			throw new SyntaxException(ErrorType.NO_RULE,current);
		}
	}

	@Override
	protected void axiom() throws SyntaxException, ParserException {
		System.out.println(S());
	}
	
	@Override
	public String toString() {
		return "* Implémentation d'un analyseur récursif descendant pour la grammaire\n"
			 + "* S -> ERS | epsilon\n"
			 + "* E -> L   | (S)\n" 
			 + "* R -> C   | epsilon\n" 
			 + "* L -> a|b|c\n"
			 + "* C -> 0|1|...|9\n";
	}
}
