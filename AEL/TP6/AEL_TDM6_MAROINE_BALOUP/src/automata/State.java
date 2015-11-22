package automata;

/**
 * État d'un automate
 * @author Bruno.Bogaert (at) univ-lille1.fr
 *
 */
public interface State {
	/**
	 * @return nom de l'état
	 */
	String getName();
	
	/**
	 * @return rang de l'état
	 */
	int getId();
	
	/**
	 * @return automate auquel appartient l'état
	 */
	public Automaton getAutomaton() ;

}
