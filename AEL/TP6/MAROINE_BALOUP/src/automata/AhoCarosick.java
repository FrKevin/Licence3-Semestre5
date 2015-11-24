package automata;

import java.util.Arrays;
import java.util.Collection;
import java.util.Iterator;
import java.util.Set;
import java.util.TreeSet;

public class AhoCarosick extends DAutomaton {
	
	private Set<String> motsATrouver = new TreeSet<String>();
	
	public AhoCarosick(String... mots) {
		this(Arrays.asList(mots));
	}
	
	public AhoCarosick(Collection<String> mots) {
		
		for (Iterator<String> it = mots.iterator(); it.hasNext();) {
			String curr = it.next();
			if (curr == null || curr.isEmpty()) continue;
			motsATrouver.add(curr);
		}
		
		
		generateAutomaton();
	}
	
	
	
	
	
	
	
	
	
	/**
	 * Méthode appelée pour générer l'automate selon les mots à chercher
	 */
	private void generateAutomaton() {
		
	}
	
	
	
	
	
	
	
	
	

}
