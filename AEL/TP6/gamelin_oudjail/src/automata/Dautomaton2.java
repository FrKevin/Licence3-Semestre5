package automata;

/**
 * BUG
 */
import java.util.Collections;
import java.util.HashMap;
import java.util.Set;

public class Dautomaton2 extends AbstractAutomaton implements DeterministicAutomaton {

	protected State initialStates = null;
	protected HashMap<Key, State> delta;
	
	public Dautomaton2() {
		super();
		delta = new HashMap<Key, State>();
	}

	@Override
	public Set<State> getInitialStates() {
		Set<State> result = new PrintSet<>();
		if(initialStates != null) {
			result.add(initialStates);
		}
		return result;
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
	public boolean isInitial(State s) {
		if(initialStates == null) {
			return false;
		}
		return initialStates.equals(states);
	}
	
	@Override
	public void setInitial(State s) {
		initialStates = s;
	}

	@Override
	public Set<State> getTransitionSet(State from, char letter) throws StateException {
		State s = getTransition(from, letter);
		if (s==null) {
			return Collections.emptySet();
		}
		else {
			Set<State> ss = new PrintSet<>();
			ss.add(s);
			return Collections.unmodifiableSet(ss);
		}
	}

	@Override
	public Set<State> getTransitionSet(Integer from, char letter) throws StateException {
		return getTransitionSet(states.get(from), letter);
	}

	@Override
	public Set<State> getTransitionSet(String from, char letter) throws StateException {
		return getTransitionSet(states.get(from), letter);
	}
	
	@Override
	public State getTransition(State from, char letter) throws StateException {
		State result = delta.get(new Key(from, letter));
		return result;

	}

	@Override
	public State getTransition(String name, char letter) throws StateException {
		return getTransition(states.get(name), letter);
	}

	@Override
	public State getTransition(Integer id, char letter) throws StateException {
		return getTransition(states.get(id), letter);
	}
	
	@Override
	public State getInitialState() {
		return this.initialStates;
	}

	@Override
	public void addTransition(State from, Character letter, State to) {
		alphabet.add(letter);
		Key k = new Key(from, letter);
		//State arrival = delta.get(k);
		//if( arrival != null ){
			delta.put(k, to);
		//}
		System.out.println(delta);
	}

	@Override
	public boolean accept(String word) throws StateException {
		State state = this.getInitialState(); 
		for(int i=0; i < word.length(); ++i) {
			state = this.getTransition(state, word.charAt(i));
			if(state == null) {
				return false;
			}
		}
		return isAccepting(state);
	}
}
