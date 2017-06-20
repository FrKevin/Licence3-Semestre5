package automata;

import java.io.Writer;
import java.util.Set;

/**
 * Méthodes d'utlisation d'un automate
 * 
 * @author Bruno.Bogaert (at) univ-lille1.fr
 *
 */
public interface Automaton extends Recognizer {

	/**
	 * états de l'automate
	 * 
	 * @return états de l'automate
	 */
	Iterable<State> getStates();

	/**
	 * ensemble des états initiaux
	 * 
	 * @return états initiaux
	 */
	Set<State> getInitialStates();

	/**
	 * ensemble des lettres utilisées par l'automate
	 * 
	 * @return ensemble des lettres utilisées par l'automate
	 */
	Set<Character> usedAlphabet();

	/**
	 * indique si l'état est acceptant
	 * 
	 * @param s
	 *            état de l'automate
	 * @return vrai si l'état est acceptant
	 * @throws StateException
	 *             si l'état n'appartient pas à l'automate
	 */
	boolean isAccepting(State s) throws StateException;

	/**
	 * indique si l'état est acceptant
	 * 
	 * @param name
	 *            nom d'état
	 * @return vrai si l'état est acceptant
	 * @throws StateException
	 *             si ce nom d'état est invalide
	 */
	boolean isAccepting(String name) throws StateException;

	/**
	 * indique si l'état est acceptant
	 * 
	 * @param id
	 *            rang d'un état de l'automate
	 * @return vrai si l'état est acceptant
	 * @throws StateException
	 *             si le rang est invalide
	 */
	boolean isAccepting(Integer id) throws StateException;

	/**
	 * indique si l'état est initial
	 * 
	 * @param s
	 *            état de l'automate
	 * @return vrai si l'état est initial
	 * @throws StateException
	 *             si l'état n'appartient pas à l'automate
	 */
	boolean isInitial(State s) throws StateException;

	/**
	 * indique si l'état est initial
	 * 
	 * @param name
	 *            nom d'état
	 * @return vrai si l'état est initial
	 * @throws StateException
	 *             si ce nom d'état est invalide
	 */
	boolean isInitial(String name) throws StateException;

	/**
	 * indique si l'état est initial
	 * 
	 * @param id
	 *            rang d'état
	 * @return vrai si l'état est initial
	 * @throws StateException
	 *             si ce rang est invalide
	 */
	boolean isInitial(Integer id) throws StateException;

	/**
	 * Ensemble des transitions définies pour from, letter
	 * 
	 * @param from
	 *            état de départ
	 * @param letter
	 *            lettre
	 * @return transition delta(from,letter). null si la transition est
	 *         indéfinie
	 * @throws StateException
	 *             si l'état n'appartient pas à l'automate
	 */
	Set<State> getTransitionSet(State from, char letter) throws StateException;

	/**
	 * Ensemble des transitions définies pour from, letter
	 * 
	 * @param from
	 *            état de départ
	 * @param letter
	 *            lettre
	 * @return transition delta(from,letter). null si la transition est
	 *         indéfinie
	 * @throws StateException
	 *             si ce nom d'état est invalide
	 */
	Set<State> getTransitionSet(String from, char letter) throws StateException;

	/**
	 * Ensemble des transitions définies pour from, letter
	 * 
	 * @param from
	 *            état de départ
	 * @param letter
	 *            lettre
	 * @return transition delta(from,letter). null si la transition est
	 *         indéfinie
	 * @throws StateException
	 *             si ce rang est invalide
	 */
	Set<State> getTransitionSet(Integer from, char letter) throws StateException;

	/**
	 * représentation de l'automate en langage Graphviz
	 * 
	 * @return représentation de l'automate en langage Graphviz
	 */
	public String toGraphviz();

	/**
	 * Écrit l'image graphviz de l'automate dans le writer
	 * 
	 * @param buff
	 * @return writer fourni en argument
	 */
	public Writer writeGraphviz(Writer writer);

}
