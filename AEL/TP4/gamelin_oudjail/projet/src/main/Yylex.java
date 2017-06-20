package main;

import exemple1.Yytoken;

public class Yylex {
	
	/**
	 * Constructeur
	 *	paramètre : le flux de lecture des données à analyser (texte)
	 */
	public Yylex(java.io.Reader in) { 
		
	}
	
	/**
	 * Principale méthode publique de la classe.
	 * Lit le prochain ’token’ dans le texte à analyser
	*/
	public Yytoken yylex() throws java.io.IOException {
		return null;
		
	}
	
	/**
	 * renvoie le texte correspondant au dernier token lu.
	 */
	public final String yytext() {
		return null;	
	}
}
