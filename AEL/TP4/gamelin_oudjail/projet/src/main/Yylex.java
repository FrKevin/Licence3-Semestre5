package main;

import exemple1.Yytoken;

public class Yylex {
	
	/**
	 * Constructeur
	 *	param�tre : le flux de lecture des donn�es � analyser (texte)
	 */
	public Yylex(java.io.Reader in) { 
		
	}
	
	/**
	 * Principale m�thode publique de la classe.
	 * Lit le prochain �token� dans le texte � analyser
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
