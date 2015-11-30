package exercices;

import ard.ErrorType;
import ard.ParserException;
import condenses_lex.Entier;
import condenses_lex.Lettre;
import condenses_lex.TokenType;
import condenses_lex.Tokenizer;

public class ArdExercice2 extends Ex2AbstractArd {

	public ArdExercice2(Tokenizer in) {
		super(in);
	}
	
	
	
	private String expandedExpression = null;
	
	
	
	
	private String S() throws SyntaxException, ParserException {
		switch(current.getType()) {
		case LETTRE:
		case OUVRANTE:
			String ret = "";
			String repeted = E();
			int count = R();
			for (int i=0;i<count; i++)
				ret+=repeted;
			ret+=S();
			return ret;
		case FERMANTE:
		case EOD:
			return "";
		default:
			throw new SyntaxException(ErrorType.NO_RULE,current);
		}
	}
	
	
	
	private String E() throws SyntaxException, ParserException {
		switch(current.getType()) {
		case LETTRE:
			return L();
		case OUVRANTE:
			eat(TokenType.OUVRANTE);
			String s = S();
			eat(TokenType.FERMANTE);
			return s;
		default:
			throw new SyntaxException(ErrorType.NO_RULE,current);
		}
	}
	
	
	
	private int R() throws SyntaxException, ParserException {
		switch(current.getType()) {
		case ENTIER:
			return C();
			
		case LETTRE:
		case OUVRANTE:
		case FERMANTE:
		case EOD:
			return 1;
		default:
			throw new SyntaxException(ErrorType.NO_RULE,current);
		}
	}
	
	
	
	private String L() throws SyntaxException, ParserException {
		switch(current.getType()) {
		case LETTRE:
			String c = ((Lettre)current).getValue();
			eat(current);
			return c;
		default:
			throw new SyntaxException(ErrorType.NO_RULE,current);
		}
	}
	
	
	
	
	
	
	
	
	
	private int C() throws SyntaxException, ParserException {
		switch(current.getType()) {
		case ENTIER:
			int c = ((Entier)current).getValue();
			eat(current);
			return c;
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
