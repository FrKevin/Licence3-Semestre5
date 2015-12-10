package main;                                                                                                                             
                                                                                                                                                                                                                                                                                                                                                                                                  
import ard.ArdTokenizer;
import ard.ParserException;                                                                                                               
import ard.SyntaxException;
import condenses_lex.Entier;
import condenses_lex.Lettre;
import condenses_lex.TokenType;
import condenses_lex.Tokenizer;                                                                                                           

/**
 * Implémentation d'un analyseur récursif descendant pour la grammaire (VERSION TOKENIZER)
 * S -> ERS    | epsilon 
 * E -> Lettre | OuvranteSFermante 
 * R -> Nombre | epsilon
 * 
 * @author Gamelin Kevin, Oudjail Veis
 *
 */
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
		String result;
		switch (current.getType()) {                                                                                                                
		case LETTRE:
			// E -> Lettre
			//System.out.println("E() : switch(LETTRE)");
			result = ((Lettre) current).getValue();
			eat(TokenType.LETTRE);
			return result;                                                                                                                   
		case OUVRANTE:                                                                                                                         
			// E -> OuvranteSFermante
			//System.out.println("E() : switch(OUVRANTE)");
			eat(TokenType.OUVRANTE);                                                                                                                     
			result = S();                                                                                                          
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
			//System.out.println("R() : switch(ALL)");
			return 1;  
		case ENTIER:
			// R -> Entier 
			//System.out.println("R() : switch(ENTIER)");
			int result = ((Entier) current).getValue();
			eat(TokenType.ENTIER);
			return result;               
		default:                                                                                                                                                                                                                                         
			String myName = Thread.currentThread().getStackTrace()[1].getMethodName();                                                    
			throw new ParserException("No rule for variable "+ myName + " token " + current+ "	.");                                                                           
		}                                                                                                                                 
	}                                                                                                                                     
	                                                                                                                                                                                                                                                                       
                                                                                                                                          
	@Override                                                                                                                             
	protected void axiom() throws SyntaxException, ParserException {                                                                      
		System.out.println(S());                                                                                                                           
	}                                                                                                                                     
    
	@Override
	public String toString() {
		return "* Implémentation d'un analyseur récursif descendant pour la grammaire\n"
			 + "* S -> ERS    | epsilon\n"
			 + "* E -> Lettre | OuvranteSFermante\n" 
			 + "* R -> Nombre | epsilon";
	}
}                                                                                                                                         
                                                                                                                                          