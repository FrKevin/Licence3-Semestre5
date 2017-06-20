package ard;

import java.io.Reader;
import java.util.NoSuchElementException;
import java.util.Scanner;
/**
 * Classe de Base pour Analyseur Récursif Descendant
 * Les symboles à analyser sont des caractères lus dans le Reader fourni à l'instanciation.
 * Cette classe doit être étendue pour implémenter des méthodes d'analyse adaptées à la grammaire
 * 
 * @author Bruno.Bogaert (at) univ-lille1.fr
 *
 */
public abstract class Ard {
	public static final char END_MARKER = '#';
	Scanner input;

	private boolean invalid = false;
	
	protected char current;
	private String currentLine;
	private int currentIndex;

	/**
	 * Avance d'une position dans la lecture du texte
	 * @throws ParserException si on est en fin de texte.
	 */
	protected void next() throws ParserException {
		if (current == END_MARKER){
			throw new ParserException();
		}
		shift();
	}
	
	private void shift(){
		try {
			currentIndex++;
			if (currentLine == null || currentIndex >= currentLine.length()) {
				currentLine = input.nextLine();
				currentIndex = 0;
			}
			current = currentLine.charAt(currentIndex);
		} catch (NoSuchElementException e) {
			current = END_MARKER;
		}
	}

	/**
	 * Vérifie que le caractère courant correspond au caractère attendu
	 * puis progresse d'une position dans la lecture du texte.
	 * @throws SyntaxException si la vérification de correspondance échoue
	 */
	protected void eat(char expected) throws SyntaxException, ParserException {
		if (current != expected)
			//throw new ParserException("expected : " + c + ", found : " + current);
		   throw new SyntaxException(ErrorType.UNMATCHING_CHAR, current, expected);
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
		if (current != END_MARKER)
			throw new SyntaxException(ErrorType.UNMATCHING_CHAR,current);
		this.invalid = true;
	}
	

	protected Ard(Reader in) {
		input = new Scanner(in);
		shift();
	}

}
