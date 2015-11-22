package automata;

import java.io.PrintWriter;
import java.io.StringWriter;
import java.io.Writer;
import java.util.Collections;
import java.util.Set;
import java.util.TreeSet;

/**
 * 
 * Base d'implémentation d'automate
 * 
 * Sont definies les méthodes concernant la définition d'états, d'état acceptant
 * ainsi que celle assurant le mapping entre nom ou rang d'état et état.
 * 
 * Méthodes non implémentées : celles concernant les état initiaux et les
 * transitions
 * 
 * @author Bruno.Bogaert (at) univ-lille1.fr
 *
 */
public abstract class AbstractAutomaton implements Recognizer, AutomatonBuilder {

	// Gestionnaire des états de l'automate
	protected AutomatonStateSet states;
	// Ensemble des lettres utilisées
	protected Set<Character> alphabet;
	// Ensemble des états acceptants
	protected Set<State> acceptingStates;

	// Représentation des couples (état,lettre)
	protected class Key {
		public final State from;
		public final Character letter;

		public Key(State from, Character letter) {
			super();
			this.from = from;
			this.letter = letter;
		}

		public String toString() {
			return "(" + from + "," + letter + ")";
		}

		@Override
		public int hashCode() {
			final int prime = 31;
			int result = 1;
			result = prime * result + getOuterType().hashCode();
			result = prime * result + ((from == null) ? 0 : from.hashCode());
			result = prime * result + ((letter == null) ? 0 : letter.hashCode());
			return result;
		}

		@Override
		public boolean equals(Object obj) {
			if (this == obj)
				return true;
			if (obj == null)
				return false;
			if (getClass() != obj.getClass())
				return false;
			Key other = (Key) obj;
			if (!getOuterType().equals(other.getOuterType()))
				return false;
			if (from == null) {
				if (other.from != null)
					return false;
			} else if (!from.equals(other.from))
				return false;
			if (letter == null) {
				if (other.letter != null)
					return false;
			} else if (!letter.equals(other.letter))
				return false;
			return true;
		}

		private AbstractAutomaton getOuterType() {
			return AbstractAutomaton.this;
		}

	}

	public AbstractAutomaton() {
		alphabet = new TreeSet<Character>();
		states = new AutomatonStateSet(this);
		acceptingStates = new PrintSet<State>();

	}

	@Override
	public Iterable<State> getStates() {
		return Collections.unmodifiableList(this.states);
	}

	@Override
	public Set<Character> usedAlphabet() {
		return Collections.unmodifiableSet(alphabet);
	}

	@Override
	public State addNewState(String name) throws StateException {
		return states.addNewState(name);
	}

	@Override
	public State addNewState() throws StateException {
		return states.addNewState();
	}

	@Override
	public void setAccepting(State s) throws StateException {
		if (s.getAutomaton() != this)
			throw new StateException();
		acceptingStates.add(s);
	}

	@Override
	public void setAccepting(String name) throws StateException {
		setAccepting(states.get(name));
	}

	@Override
	public void setAccepting(int id) throws StateException {
		setAccepting(states.get(id));
	}

	@Override
	public boolean isAccepting(State s) throws StateException {
		return acceptingStates.contains(s);
	}

	public boolean isAccepting(String name) throws StateException {
		return isAccepting(states.get(name));
	}

	public boolean isAccepting(Integer id) throws StateException {
		return isAccepting(states.get(id));
	}

	@Override
	abstract public void setInitial(State s);

	@Override
	public void setInitial(String name) {
		setInitial(states.get(name));
	}

	@Override
	public void setInitial(int id) {
		setInitial(states.get(id));
	}

	@Override
	public abstract boolean isInitial(State s);

	@Override
	public abstract void addTransition(State from, Character letter, State to);

	@Override
	public void addTransition(String from, Character letter, String to) {
		addTransition(states.get(from), letter, states.get(to));
	}

	@Override
	public void addTransition(int from, Character letter, int to) {
		addTransition(states.get(from), letter, states.get(to));
	}

	@Override
	public abstract boolean accept(String word) throws StateException;

	protected StringWriter imageWriter() {
		StringWriter buff = new StringWriter();
		PrintWriter out = new PrintWriter(buff);
		out.println("States :");
		out.println(states);
		out.println("Accepting States :");
		out.println(acceptingStates);
		return buff;
	}

	/**
	 * Image graphviz de l'état q
	 * 
	 * @param q
	 * @param withName
	 *            si vrai le nom de l'état apparaît, plutôt que son rang
	 * @return
	 */
	protected String stateToGV(State q, boolean withName) {
		String attributes = withName ? "label=\"" + q.getName() + "\"" : "";
		if (isAccepting(q)) {
			if (attributes.length() > 0)
				attributes += ",";
			attributes += "peripheries=2";
		}
		if (attributes.length() > 0)
			attributes = "[" + attributes + "]";
		return "  " + q.getId() + " " + attributes + ";";
	}

	protected Writer writeGraphvizStates(Writer buff, boolean withNames) {
		PrintWriter out = new PrintWriter(buff);
		out.println("  rankdir = LR");
		for (State s : states) {
			out.print(stateToGV(s, withNames));
		}
		return buff;
	}

	public Writer writeGraphvizInitials(Writer buff) {
		PrintWriter out = new PrintWriter(buff);
		for (State initial : getInitialStates()) {
			out.println("  start" + initial.getId() + " [style=invis]");
			out.println("  start" + initial.getId() + " -> " + initial.getId() + "[color=\"black:white:black\"]");
		}
		return buff;
	}

	public Writer writeGraphvizInner(Writer buff) {
		writeGraphvizStates(buff, true);
		return buff;
	}

	public Writer writeGraphviz(Writer buff) {
		PrintWriter out = new PrintWriter(buff);
		out.println("digraph Automaton { ");
		writeGraphvizInner(out);
		out.println("}");
		return buff;
	}

	public String toGraphviz() {
		StringWriter buff = new StringWriter();
		writeGraphviz(buff);
		return buff.toString();
	}

	public String toString() {
		return imageWriter().toString();
	}

}
