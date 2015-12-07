package main;                                                                                                                             
                                                                                                                                                                                                                                                                                                                                                                                                  
import ard.ArdTokenizer;
import ard.ParserException;                                                                                                               
import ard.SyntaxException;                                                                                                               
import condenses_lex.TokenType;
import condenses_lex.Tokenizer;                                                                                                           
                                                                                                                                          
public class ArdExercice2 extends ArdTokenizer{                                                                                           
                                                                                                                                          
	protected ArdExercice2(Tokenizer in) {                                                                                                
		super(in);                                                                                                                        
	}                                                                                                                                     
	                                                                                                                                      
	private String S() throws SyntaxException, ParserException {                                                                          
		switch (current.getType()) {                                                                                                      
		case LETTRE :                                                                                                                     
		case OUVRANTE:                                                                                                                    
			// S -> ERS                                                                                                                   
			String expression = E();                                                                                                      
			int repeat = R();                                                                                                             
			StringBuilder developedExpression = new StringBuilder();                                                                      
			for(int i = 1; i <= repeat; ++i) {                                                                                            
				developedExpression.append(expression);                                                                                   
			}                                                                                                                             
			return developedExpression + S();                                                                                             
		case FERMANTE:                                                                                                                    
		case EOD:                                                                                                                         
			// S -> epsilon                                                                                                               
			return "";                                                                                                                    
		default:                                                                                                                          
			String myName = Thread.currentThread().getStackTrace()[1].getMethodName();                                                    
			throw new ParserException("No rule for variable "+ myName + " token " + current+ "	.");                                      
		}                                                                                                                                 
	}                                                                                                                                     
                                                                                                                                          
	private String E() throws SyntaxException, ParserException{                                                                           
		switch (current.getType()) {                                                                                                                
		case LETTRE:
			// E -> L                                                                                                                     
			return L();                                                                                                                   
		case OUVRANTE:                                                                                                                         
			// E -> (S)                                                                                                                   
			eat(TokenType.OUVRANTE);                                                                                                                     
			String result = S();                                                                                                          
			eat(TokenType.FERMANTE);                                                                                                                     
			return result;                                                                                                                
		default:                                                                                                                          
			String myName = Thread.currentThread().getStackTrace()[1].getMethodName();                                                    
			throw new ParserException("No rule for variable "+ myName + " token " + current + "	.");  		
		}                                                                                                                                 
	}                                                                                                                                     
                                                                                                                                                                                                                                                                      
	                                                                                                                                      
	private int R() throws SyntaxException, ParserException{                                                                              
		switch (current.getType()) {                                                                                                                
		case LETTRE:
		case OUVRANTE:                                                                                                                         
		case FERMANTE:                                                                                                                         
		case EOD:                                                                                                                  
			// R -> epsilon                                                                                                               
			return 1;  
		case ENTIER:
			// R -> Entier                                                                                                                 
			return C();               
		default:                                                                                                                                                                                                                                         
			String myName = Thread.currentThread().getStackTrace()[1].getMethodName();                                                    
			throw new ParserException("No rule for variable "+ myName + " token " + current+ "	.");                                                                           
		}                                                                                                                                 
	}                                                                                                                                     
	                                                                                                                                                                                                                                                                       
                                                                                                                                          
	@Override                                                                                                                             
	protected void axiom() throws SyntaxException, ParserException {                                                                      
		S();                                                                                                                              
	}                                                                                                                                     
                                                                                                                                          
}                                                                                                                                         
                                                                                                                                          