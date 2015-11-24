package automata;

/**
 * Méthodes spécifiques aux automates déterministes. Permet de récupérer l'état
 * initial ou une le résultat d'une transition sans qu'il soit empaqueté dans un
 * ensemble.
 * 
 * @author Bruno.Bogaert (at) univ-lille1.fr
 *
 */
public interface DeterministicAutomaton extends Automaton {

	/**
	 * état initial de l'automate
	 * 
	 * @return état initial de l'automate
	 */
	State getInitialState();

	/**
	 * transition pour s,letter. null si indéfinie
	 * 
	 * @param s
	 * @param letter
	 * @return transition delta(s,letter), null si indéfinie
	 * @throws StateException
	 *             si s est invalide
	 */
	State getTransition(State s, char letter) throws StateException;

	/**
	 * transition pour s,letter. null si indéfinie
	 * 
	 * @param name
	 *            nom d'un état s de l'automate
	 * @param letter
	 * @return transition delta(s,letter), null si indéfinie
	 * @throws StateException
	 */
	State getTransition(String name, char letter) throws StateException;

	/**
	 * transition pour s,letter. null si indéfinie
	 * 
	 * @param id
	 *            : rang d'un état s de l'automate
	 * @param letter
	 * @return transition delta(s,letter), null si indéfinie
	 * @throws StateException
	 */
	State getTransition(Integer id, char letter) throws StateException;

}
