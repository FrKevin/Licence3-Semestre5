package automata;

import java.util.HashMap;
import java.util.Map;
import java.util.Set;

public class AhoCarosick extends DAutomaton {

	protected String[] words;
	
	protected State [] endNode;

	protected State root;
	
	protected Map<State, State> fallbacks;
	
	public AhoCarosick(String... words) {
		if(!checkWords(words)) {
			throw new IllegalArgumentException();
		}
		this.words = words;
		endNode = new State[words.length];
		fallbacks = new HashMap<>();
		constructStates();
		completeAutomaton();
	}

	protected boolean checkWords(String[] words) {
		return !(words == null) && !(words.length == 0);
	}
	
	
	protected State createNewState(State parent, char letter) {
		
		String newStateName = ((parent.getName().equals("'root'"))?"":parent.getName())+letter;
		State newState;
		try {
			newState = addNewState(newStateName);
		} catch (StateException e) {
			return getTransition(parent, letter);
		}
		addTransition(parent, letter, newState);
		if (parent.equals(root)) {
			fallbacks.put(newState, root);
		}
		else {
			State state = parent, stateForLetter = null;
			do {
				state = fallbacks.get(state);
				stateForLetter = getTransition(state, letter);
			} while (stateForLetter == null && !root.equals(state));
			if (stateForLetter != null) {
				fallbacks.put(newState, stateForLetter);
				if (isAccepting(stateForLetter)) {
					setAccepting(newState);
				}
			}
			else {
				fallbacks.put(newState, root);
			}
		}
		return newState;
	}
	
	protected void completeAutomaton() {
		for (State state : getStates()) {
			for(Character letter : usedAlphabet()) {
				if (getTransition(state, letter) == null) {
					if (state.equals(root)) {
						addTransition(state, letter, root);
					}
					else {
						addTransition(state, letter, getTransition(fallbacks.get(state), letter));
					}
				}
				
			}
		}
	}
	
	protected void constructStates() {
		root = addNewState("'root'");
		for (int i = 0; i < words.length; i++) {
			endNode[i] = root;
		}
		String maxWord = words[getGreatString(words)];
		for (int l = 0; l < maxWord.length(); ++l) {
			for (int i = 0; i < words.length; ++i) {
				if (l < words[i].length()) {
					State state = createNewState(endNode[i], words[i].charAt(l));
					endNode[i] = state;
					if (l + 1 == words[i].length()) {
						setAccepting(endNode[i]);
					}
				}
			}
		}
	}
	
	protected static int getGreatString(String[] words) {
		int idMax = 0;
		for (int i = 1; i < words.length; i++) {
			if(words[idMax].length() < words[i].length()) {
				idMax = i;
			}
		}
		return idMax;
	}
	
	
	
}
