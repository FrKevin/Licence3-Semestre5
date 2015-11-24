package automata;

/**
 * 
 * Méthodes de construction incrémentales d'un automate
 * 
 * @author Bruno.Bogaert (at) univ-lille1.fr
 *
 */
public interface AutomatonBuilder extends Automaton {
	/**
	 * Crée un nouvel état
	 * 
	 * @param name
	 *            nom attribué à l'état
	 * @return état créé
	 * @throws StateException
	 *             si le nom est incorrect (déjà attribué, par exemple)
	 */
	State addNewState(String name) throws StateException;

	/**
	 * Crée un nouvel état. Son nom sera attribué automatiquement.
	 * 
	 * @return état créé
	 * @throws StateException
	 */
	State addNewState() throws StateException;

	/**
	 * Rend l'état s acceptant
	 * 
	 * @param s
	 * @throws StateException
	 *             si s est invalide
	 */
	void setAccepting(State s) throws StateException;;

	/**
	 * Rend l'état acceptant
	 * 
	 * @param name
	 *            nom de l'état
	 * @throws StateException
	 *             si s est invalide
	 */
	void setAccepting(String name) throws StateException;;

	/**
	 * Rend l'état acceptant
	 * 
	 * @param id
	 *            : identifiant de l'état
	 * @throws StateException
	 *             si s est invalide
	 */
	void setAccepting(int id) throws StateException;

	/**
	 * Rend l'état initial
	 * 
	 * @param s
	 * @throws StateException
	 *             si s est invalide
	 */
	void setInitial(State s) throws StateException;

	/**
	 * Rend l'état initial
	 * 
	 * @param name
	 * @throws StateException
	 *             si s est invalide
	 */
	void setInitial(String name) throws StateException;

	/**
	 * Rend l'état initial
	 * 
	 * @param id
	 * @throws StateException
	 *             si s est invalide
	 */
	void setInitial(int id) throws StateException;

	/**
	 * Ajoute une transition
	 * 
	 * @param from
	 * @param letter
	 * @param to
	 * @throws StateException
	 *             Si l'un des état est invalide
	 */
	void addTransition(State from, Character letter, State to) throws StateException;

	/**
	 * Ajoute une transition
	 * 
	 * @param from
	 * @param letter
	 * @param to
	 * @throws StateException
	 *             Si l'un des état est invalide
	 */
	void addTransition(String from, Character letter, String to) throws StateException;

	/**
	 * Ajoute une transition
	 * 
	 * @param from
	 * @param letter
	 * @param to
	 * @throws StateException
	 *             Si l'un des état est invalide
	 */
	void addTransition(int from, Character letter, int to) throws StateException;
}
