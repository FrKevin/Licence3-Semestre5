package exercices;

import java.io.InputStreamReader;

import ard.ParserException;

public class TestTokenArd {

	public static void main(String[] args) {
		
		System.out.println("Interprétation de l'entrée standard :");
		
		TokenizerEx2 t = new TokenizerEx2(new InputStreamReader(System.in));
		
		ArdExercice2 ard = new ArdExercice2(t);
		
		try {
			ard.parse();
			System.out.println(ard.getExpandedExpression());
		} catch (SyntaxException | ParserException e) {
			e.printStackTrace();
		}
		System.out.println("Fin.");
	}
	
}
