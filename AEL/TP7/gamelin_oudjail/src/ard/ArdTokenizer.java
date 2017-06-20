package ard;

import java.io.IOException;

import condenses_lex.Eod;
import condenses_lex.TokenType;
import condenses_lex.Tokenizer;
import condenses_lex.Yytoken;


/**
 * Classe de Base pour Analyseur Récursif Descendant
 * Les symboles à analyser sont des Token fourni à l'instanciation.
 * Cette classe doit être étendue pour implémenter des méthodes d'analyse adaptées à la grammaire
 * 
 * @author Gamelin Kevin, Oudjail Veis
 *
 */
public abstract class ArdTokenizer implements Ard{
	public static final TokenType END_MARKER = TokenType.EOD;
	Tokenizer input;

	private boolean invalid = false;
	
	protected Yytoken current;
	
	protected ArdTokenizer(Tokenizer in) {
		input = in;
		shift();
	}

	/**
	 * Avance d'une position dans la lecture du texte
	 * @throws ParserException si on est en fin de texte.
	 */
	protected void next() throws ParserException {
		if (current.getType().equals(END_MARKER)){
			throw new ParserException();
		}
		shift();
	}
	
	private void shift(){
		try {
			current = input.yylex();
			if (current == null) {
				current = new Eod("\n");
			}
		} catch (IOException e) {
			throw new RuntimeException("Erreur de lecture de l'entrée", e);
		}
	}

	/**
	 * Vérifie que le caractère courant correspond au caractère attendu
	 * puis progresse d'une position dans la lecture du texte.
	 * @throws SyntaxException si la vérification de correspondance échoue
	 */
	protected void eat(Yytoken expected) throws SyntaxException, ParserException {
		if (!current.equals(expected))
		   throw new SyntaxException("Error type : " + ErrorType.UNMATCHING_CHAR +  ", current : " + current.getType() + "excepted " + expected);
		next();
	}

	/**
	 * Vérifie que le caractère courant correspond au caractère attendu
	 * puis progresse d'une position dans la lecture du texte.
	 * @throws SyntaxException si la vérification de correspondance échoue
	 */
	protected void eat(TokenType expected) throws SyntaxException, ParserException {
		if (!current.getType().equals(expected))
			throw new SyntaxException("Error type : " + ErrorType.UNMATCHING_CHAR +  ", current : " + current.getType());
		next();
	}
	
	/**
	 * Doit simplement invoquer la méthode implémentant l'axiome de la grammaire.
	 */
	protected abstract void axiom() throws SyntaxException, ParserException;

	/**
	 * Analyse le texte. Déclenche une exception en cas d'erreur.
	 * 
	 * Ne peut être invoquée qu'une seule fois.
	 * 
	 * @throws SyntaxException En cas d'erreur de syntaxe
	 * @throws ParserException  En cas d'erruer de utilisation du parser.
	 */
	public void parse() throws SyntaxException, ParserException{
		if (invalid) 
			throw new ParserException();
		// Axiom :
		axiom();
		// check end of data :
		if (!(current.getType().equals(END_MARKER)))
			throw new SyntaxException("Error type : " + ErrorType.UNMATCHING_CHAR +  ", current : " + current.getType());
		this.invalid = true;
	}
	

}
