package main;

import automata.AhoCarosick;
import automata.NDAutomaton;

public class Main {

	public static void main(String[] args) {
		
		NDAutomaton automate = new NDAutomaton();
		NDAutomaton deterministAutomate;
		automate.addNewState("Q1");
		automate.addNewState("Q2");
		
		automate.setInitial("Q1");
		automate.setAccepting("Q2");
		
		automate.addTransition("Q1", 'a', "Q2");
		deterministAutomate = automate.deterministic();
		System.out.println(deterministAutomate);
		
		String[] words = {"create", "at", "cry"};
		AhoCarosick ahoCarosick = new AhoCarosick(words);
		System.out.println(ahoCarosick.toGraphviz());
	}	

}
