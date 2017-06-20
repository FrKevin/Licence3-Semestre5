package automata;

import java.io.PrintWriter;
import java.io.Writer;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.Map;
import java.util.Set;


/**
 * 
 * Implémentation d'un automate non déterministe.
 * Version à compléter ou à étendre.
 * 
 * @author Bruno.Bogaert (at) univ-lille1.fr
 *
 */
public class NDAutomaton extends AbstractAutomaton implements Recognizer, AutomatonBuilder {

	protected Set<State> initialStates;
	protected HashMap<Key, Set<State>> delta;

	public NDAutomaton() {
		super();
		initialStates = new PrintSet<State>();
		delta = new HashMap<Key, Set<State>>();
	}
	@Override
	public boolean isInitial(String name) throws StateException {
		return isInitial(states.get(name));
	}

	@Override
	public boolean isInitial(Integer id) throws StateException {
		return isInitial(states.get(id));
	}

	@Override
	public Set<State> getTransitionSet(State from, char letter) {
		Set<State> s = delta.get(new Key(from, letter));
		if (s==null) {
			return Collections.emptySet();
		}
		else {
			return Collections.unmodifiableSet(s);
		}
	}

	@Override
	public Set<State> getTransitionSet(String from, char letter) {
		return getTransitionSet(states.get(from), letter);
	}

	@Override
	public Set<State> getTransitionSet(Integer from, char letter) {
		return getTransitionSet(states.get(from), letter);
	}

	@Override
	public Set<State> getInitialStates() {
		return Collections.unmodifiableSet(this.initialStates);
	}

	@Override
	public void setInitial(State s) {
		initialStates.add(s);
	}

	@Override
	public boolean isInitial(State s) {
		return initialStates.contains(s);
	}

	@Override
	public void addTransition(State from, Character letter, State to) {
		alphabet.add(letter);
		Key k = new Key(from, letter);
		Set<State> arrival = delta.get(k);
		if (arrival == null) {
			arrival = new PrintSet<State>();
		}
		if (!arrival.contains(to)) {
			arrival.add(to);
			delta.put(k, arrival);
		}
	}

	@Override
	public boolean accept(String word) {
		Set<State> states = this.getInitialStates();
		for(int i=0; i < word.length(); ++i) {	
			Set<State> stateTmp = new HashSet<>();
			for(State st : states) {
				stateTmp.addAll(this.getTransitionSet(st, word.charAt(i))); /* Cela marche si la methode ne renvoie pas null, mais une collection vide */
			}
			states = stateTmp;
			if(states.isEmpty()) return false;
		}
		for(State st : states) {
			if(this.isAccepting(st)) {
				return true;
			}
		}
		return false;
	}
	
	public NDAutomaton deterministic() {
		NDAutomaton deterministic = new NDAutomaton();
		boolean isInitial = true;
		Map<Set<State>, State> createStates = new HashMap<>();
		LinkedList<Set<State>> proccessStates = toQueueSetState(this.getInitialStates()); 
		Set<Character> lalphabets = usedAlphabet();
		while(!proccessStates.isEmpty()) {
			Set<State> current = proccessStates.getFirst();
			if(!createStates.containsKey(current)) {
				createStates.put(current, deterministic.addNewState());
			}
			for(Character lt : lalphabets) {
				Set<State> stateForlt = getAllStateForLetter(current, lt);
				if(!createStates.containsKey(stateForlt)) {
					createStates.put(stateForlt, deterministic.addNewState(toStringForSetState(stateForlt)));
					proccessStates.add(stateForlt);
				}
				deterministic.addTransition(createStates.get(current), lt, createStates.get(stateForlt));
			}
			if(isAcceptingForSetState(current)) {
				deterministic.setAccepting(createStates.get(current));
			}
			if(isInitial) {
				deterministic.setInitial(createStates.get(current));
				isInitial = false;
			}
			proccessStates.removeFirst();
		}
		return deterministic;
	}
	
	private boolean isAcceptingForSetState(Set<State> states) {
		for(State st : states) {
			if(isAccepting(st)) {
				return true;
			}
		}
		return false;
	}
		
	private String toStringForSetState(Set<State> states) {
		String result = states.isEmpty() ? "puit" : null;
		return result;
	}

	private Set<State> getAllStateForLetter(Set<State> states, Character letter) {
		Set<State> result = new HashSet<>();
		Set<State> transision;
		for(State st : states) {
			transision = getTransitionSet(st, letter);
			for(State st2 : transision) {
				result.add(st2);
			}
		}
		return result;
	}
	
	private static LinkedList<Set<State>> toQueueSetState(Iterable<State> iterable) {
		LinkedList<Set<State>> result = new LinkedList<>();
		Set<State> element = new PrintSet<>();
		for(State st : iterable) {
			element.add(st);
		}
		result.add(element);
		return result;
	}
	
	public Writer writeGraphvizTransitions(Writer buff) {
		PrintWriter out = new PrintWriter(buff);
		for (Map.Entry<Key, Set<State>> entry : delta.entrySet()) {
			for (State dest : entry.getValue()) {
				out.print("  " + entry.getKey().from.getId() + " -> " + dest.getId());
				out.println(" [label = \"" + entry.getKey().letter + "\" ]");
			}
		}
		return buff;
	}

	public Writer writeGraphvizInner(Writer buff) {
		writeGraphvizStates(buff, true);
		writeGraphvizInitials(buff);
		writeGraphvizTransitions(buff);
		return buff;
	}


}
