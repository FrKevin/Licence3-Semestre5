package automata;

import java.io.PrintWriter;
import java.io.Writer;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;
import java.util.TreeSet;

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
		if (s==null)
			return Collections.emptySet();
		else
			return Collections.unmodifiableSet(s);
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
		Set<State> currentStates = new HashSet<State>(getInitialStates());
		
		for (char c : word.toCharArray()) {
			Set<State> nextStates = new HashSet<State>();
			
			for (State s : currentStates) {
				nextStates.addAll(getTransitionSet(s, c));
			}
			
			if (nextStates.isEmpty()) return false; // il n'y a pas de transition valide pour ce caractère
			
			currentStates = nextStates;
			
		}
		
		// on est arrivé à la fin du mot
		// on vérifie si un des états courants est un état final
		for (State s : currentStates) {
			if (isAccepting(s))
				return true;
		}
		
		return false;
	}
	
	
	
	
	public DAutomaton deterministic() {
		/*
		 * Cette méthode procèdera de la même manière que nous procédons à la main
		 */
		
		DeterministicTable table = new DeterministicTable(usedAlphabet());
		
		
		// états initiaux
		DeterministicTable.Entry firstEntry = table.createEntry();
		for (State s : getInitialStates()) {
			firstEntry.states.add(s);
			if (isAccepting(s))
				firstEntry.isFinal = true;
			for (char c : usedAlphabet()) {
				for (State nS : getTransitionSet(s, c))
					firstEntry.nextStates.get(c).add(nS);
			}
		}
		
		// création des lignes suivantes du tableau de déterminisation
		for (int currentAnalizingTableEntry = 0;
				currentAnalizingTableEntry<table.size();
				currentAnalizingTableEntry++) {
			DeterministicTable.Entry currentEntry = table.get(currentAnalizingTableEntry);
			
			// on ajoute des lignes au tableau, selon les états suivants, et on les complètes
			for (char nextC : currentEntry.nextStates.keySet()) {
				if (currentEntry.nextStates.get(nextC).isEmpty())
					continue;	// on ignore l'état puit
				if (table.containsEntry(currentEntry.nextStates.get(nextC)))
					continue;
				
				DeterministicTable.Entry newEntry = table.createEntry();
				for (State s : currentEntry.nextStates.get(nextC)) {
					newEntry.states.add(s);
					if (isAccepting(s))
						newEntry.isFinal = true;
					for (char c : usedAlphabet()) {
						for (State nS : getTransitionSet(s, c))
							newEntry.nextStates.get(c).add(nS);
					}
				}
				
			}
			
			
			
		}
		
		// on génère l'automate déterministe

		DAutomaton ret = new DAutomaton();

		for (DeterministicTable.Entry e : table) {
			ret.addNewState(e.states.toString());
			if (e.isFinal)
				ret.setAccepting(e.states.toString());
		}
		
		ret.setInitial(table.get(0).states.toString());
		
		for (DeterministicTable.Entry e : table) {
			for (char c : e.nextStates.keySet()) {
				if (!e.nextStates.get(c).isEmpty())
					ret.addTransition(e.states.toString(), c, e.nextStates.get(c).toString());
			}
		}
		
		
		return ret;
	}
	
	/**
	 * Représente un tableau de déterminisation
	 *
	 */
	@SuppressWarnings("serial")
	private class DeterministicTable extends ArrayList<DeterministicTable.Entry> {
		
		Set<Character> alphabet;
		
		public DeterministicTable(Set<Character> a) {
			alphabet = a;
		}
		
		/**
		 * Représente une ligne du tableau de déterminisation
		 *
		 */
		public class Entry {
			boolean isFinal = false;
			Set<State> states = new TreeSet<State>((e1, e2) -> e1.toString().compareTo(e2.toString()));
			Map<Character, Set<State>> nextStates = new HashMap<Character, Set<State>>();
		}
		
		public boolean containsEntry(Set<State> states) {
			for (Entry e : this) {
				if (e.states.equals(states))
					return true;
			}
			return false;
		}
		
		public Entry createEntry() {
			Entry e = new Entry();
			add(e);
			for (char c : alphabet)
				e.nextStates.put(c, new TreeSet<State>((e1, e2) -> e1.toString().compareTo(e2.toString())));
			return e;
		}
		
		@Override
		public String toString() {
			String ret = "final - state - nextStates: "+alphabet+"\n";
			for (Entry e : this) {
				ret += e.isFinal+" - "+e.states+" - "+e.nextStates+"\n";
			}
			
			return ret;
		}
		
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
