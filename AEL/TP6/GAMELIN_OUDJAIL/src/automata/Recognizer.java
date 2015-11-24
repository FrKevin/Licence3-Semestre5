package automata;

/**
 * @author Bruno.Bogaert (at) univ-lille1.fr
 *
 */
public interface Recognizer {
	/**
	 * @param word : mot
	 * @return true si et seulement si word esta accepté.
	 * @throws StateException
	 */
	public boolean accept(String word) throws StateException;

}
