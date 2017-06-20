package automata;

import java.util.ArrayList;
import java.util.HashMap;

/**
 * 
 * @author Bruno.Bogaert (at) univ-lille1.fr
 * 
 *         Ensemble d'états. Au sein de l'ensemble, chaque état est identifiable
 *         par son rang de création (entier >=0) et un nom. Iterable par ordre
 *         de création des états.
 *
 */
class AutomatonStateSet extends ArrayList<State> {

	private HashMap<String, State> byName;
	private final Automaton automaton;
	
	public ArrayList<State> getList() {
		return this;
	}

	public HashMap<String, State> getByName() {
		return byName;
	}

	

	public Automaton getAutomaton() {
		return automaton;
	}

	public AutomatonStateSet(Automaton automaton) {
		this.automaton = automaton;
		byName = new HashMap<String,State>();
	}

	private class StateImpl implements State {
		final String name;
		final int rank;

		public String getName() {
			return name;
		}

		public int getId() {
			return rank;
		}

		public Automaton getAutomaton() {
			return AutomatonStateSet.this.automaton;
		}

		StateImpl(String name) throws StateException {
			this.rank = AutomatonStateSet.this.size();
			if (name == null)
				name = "q" + this.rank;
			this.name = name;
			if (byName.containsKey(this.name))
				throw new StateException();
			byName.put(this.name, this);
			AutomatonStateSet.this.add(this);
		}

		StateImpl() throws StateException {
			this(null);
		}
		public String toString(){
			return this.name;
		}
	}


	/**
	 * 
	 * @param name
	 *            nom de l'état
	 * @return état créé
	 * @throws StateException
	 *             si le nom est déjà utilisé
	 */
	public State addNewState(String name) throws StateException {
		return new StateImpl(name);
	}

	/**
	 * 
	 * @return état créé
	 */
	public State addNewState() throws StateException {
		
		return new StateImpl();
	}

	/**
	 * 
	 * @return état selon son rang
	 */
	public State get(int rank) {
		return this.get(rank);
	}

	/**
	 * 
	 * @return état selon son nom
	 */
	public State get(String name) {
		return byName.get(name);
	}
	
	
	public String toString(){
		if (this.isEmpty())
			return "{}";
		StringBuffer buff = new StringBuffer();
		buff.append("{");
		for (State elt : this){
			buff.append(elt.toString());
			buff.append(',');
		}
		buff.deleteCharAt(buff.length()-1);
		buff.append("}");
		return buff.toString();		
	}


}
