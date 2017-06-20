package automata;

import java.util.Set;

public class DAutomaton extends NDAutomaton implements DeterministicAutomaton {

	@Override
	public State getInitialState() {
		Set<State> states = getInitialStates();
		if (states.isEmpty())
			return null;
		return states.iterator().next();
	}
	
	@Override
	public void setInitial(State s) throws StateException {
		
		if (getInitialState() != null)
			return; //throw new StateException("There is already an initialState");
		
		super.setInitial(s);
	}

	@Override
	public State getTransition(State s, char letter) throws StateException {
		Set<State> states = getTransitionSet(s, letter);
		if (states.isEmpty())
			return null;
		return states.iterator().next();
	}

	@Override
	public State getTransition(String name, char letter) throws StateException {
		Set<State> states = getTransitionSet(name, letter);
		if (states.isEmpty())
			return null;
		return states.iterator().next();
	}

	@Override
	public State getTransition(Integer id, char letter) throws StateException {
		Set<State> states = getTransitionSet(id, letter);
		if (states.isEmpty())
			return null;
		return states.iterator().next();
	}
	
	@Override
	public void addTransition(State from, Character letter, State to) {

		if (getTransition(from, letter) != null)
			return; //throw new StateException("There is already a transition from state '"+from+"' for letter "+letter+".");
		
		super.addTransition(from, letter, to);
	}


}
