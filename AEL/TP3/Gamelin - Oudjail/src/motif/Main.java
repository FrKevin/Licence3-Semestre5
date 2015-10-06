package motif;

public class Main {
	/**
	 * le programme principal permet de tester Knuth-Morris-Pratt On passe sur
	 * la ligne de commande comme premier argument, le mot, et comme second
	 * argument, le motif.
	 */
	public static void main(String args[]) {
		Mot mot = new Mot("bacbababaabcbab");
		//System.out.println("indice : " + mot.indiceMotifNaif(new Mot("our")));
		
		System.out.println(mot.indiceMotifKMP(new Mot("cbab")));
	}
}
