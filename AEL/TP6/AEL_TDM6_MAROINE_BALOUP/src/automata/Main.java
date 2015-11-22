package automata;

public class Main {

	public static void main(String[] args) {

		System.out.println("================================================");
		System.out.println("    TDM6 AEL : Maxime Maroine et Marc Baloup");
		System.out.println("================================================");
		System.out.println("------------------------------------------------");
		System.out.println("Test de la méthode accept() :");
		System.out.println("------------------------------------------------");
		System.out.println("L'automate testé a 2 état. État 1 initial, et état 2 acceptant.");
		System.out.println("transition 'a' de 1 à 1, et transition 'b' de 1 vers 2.");
		
		NDAutomaton automate = new NDAutomaton();
		automate.addNewState("1");
		automate.addNewState("2");
		automate.setAccepting("2");
		automate.setInitial("1");
		
		automate.addTransition("1", 'a', "1");
		automate.addTransition("1", 'b', "2");
		
		System.out.println("aaaaaaaabaaaa : "+automate.accept("aaaaaaaabaaaa"));
		System.out.println("aaaaaaaab : "+automate.accept("aaaaaaaab"));
		System.out.println("aaaaaa : "+automate.accept("aaaaaa"));
		System.out.println("b : "+automate.accept("b"));
		
		System.out.println();
		System.out.println("------------------------------------------------");
		System.out.println("Test de la méthode deterministic() :");
		System.out.println("------------------------------------------------");
		/*
		 * Utilisation de l'automate "Exemple de déterminisation" vue en TD
		 */
		automate = new NDAutomaton();
		automate.addNewState("q1");
		automate.addNewState("q2");
		automate.addNewState("q3");
		automate.addNewState("q4");
		automate.addNewState("q5");
		automate.setAccepting("q3");
		automate.setAccepting("q4");
		automate.setInitial("q1");
		
		automate.addTransition("q1", 'a', "q2");
		automate.addTransition("q2", 'b', "q3");
		automate.addTransition("q3", 'a', "q3");
		automate.addTransition("q2", 'b', "q4");
		automate.addTransition("q4", 'a', "q5");
		automate.addTransition("q5", 'b', "q4");
		
		DAutomaton determine = automate.deterministic();
		
		System.out.print(determine.toGraphviz());
		
		System.out.println();
		System.out.println("-----------------------------------------------");
		System.out.println("Test de la classe AhoCarosick :");
		System.out.println("-----------------------------------------------");
		System.out.println("Les mots à chercher sont 'at', 'cry' et 'create'");
		
		AhoCarosick automateRecherche = new AhoCarosick("at", "cry", "create");
		
		System.out.println(automateRecherche.toGraphviz());
		
		
		
		
	}

}
