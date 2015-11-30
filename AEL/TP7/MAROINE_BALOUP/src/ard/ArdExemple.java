package ard;

import java.io.Reader;

/**
 * Exemple d'implémentation d'un analyseur récursif descendant pour la grammaire
 * S -> AB  | Da
 * A -> aAb | epsilon
 * B -> bB  | epsilon
 * D -> dD  | e
 * 
 * @author Bruno.Bogaert (at) univ-lille1.fr
 *
 */
public class ArdExemple extends Ard {

	public ArdExemple(Reader in) {
		super(in);
	}

	private void S() throws SyntaxException, ParserException {
		switch (current) {
		case 'a':
		case 'b':
		case END_MARKER:
			// S -> AB
			A();
			B();
			break;
		case 'd':
		case 'e':
			// S -> Da
			D();
			eat('a');
			break;
		default:
			// erreur
//			String myName = Thread.currentThread().getStackTrace()[1].getMethodName();
//			throw new ParserException("No rule for variable "+ myName + " token " + current+ "	."); 
			throw new SyntaxException(ErrorType.NO_RULE,current);
		}
	}

	private void A() throws SyntaxException, ParserException {
		switch (current) {
		case 'a':
			// A -> aAb
			eat('a');
			A();
			eat('b');
			break;
		case 'b':
		case END_MARKER:
			// A -> epsilon
			break;
		default:
			throw new SyntaxException(ErrorType.NO_RULE,current);
		}
	}

	private void B() throws SyntaxException, ParserException {
		switch (current) {
		case 'b':
			// B -> bB
			eat('b');
			B();
		case END_MARKER:
			// B -> epsilon
			break;
		default:
			throw new SyntaxException(ErrorType.NO_RULE,current);
		}
	}

	private void D() throws SyntaxException, ParserException {
		switch (current) {
		case 'd':
			// D -> dD
			eat('d');
			D();
			break;
		case 'e':
			// D -> e
			eat('e');
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
