package jade;
import java.io.*;   
public class JadeRunner{
    public static void main (String[] arg) throws IOException{
    	/*
    	 * Note importante : la variable arg est modifiée manuellement au début du main()
    	 * car la ligne de commande est difficilement accessible dans Eclipse.
    	 * 
    	 * Le fichier à lire doit se trouver dans le dossier courant (cwd) et doit
    	 * s'appeler jade.txt
    	 */
    	System.out.println("Note importante : la variable arg est modifiée manuellement au début du main()"
		    	+" car la ligne de commande est difficilement accessible dans Eclipse.\n"
		    	+" Le fichier à lire doit se trouver dans le dossier courant (cwd) et doit"
		    	+" s'appeler jade.txt");
    	
    	
    	
    	
    	
        Reader input;
        if (/*arg.length>0*/true){
          input = new BufferedReader(new FileReader("jade.txt"));
          //input = new BufferedReader(new FileReader(arg[0]));
        }
        else {
          input = new InputStreamReader(System.in);
        }

        //JadeMachine machine = new LoggingMachine();
        JadeMachine machine = new DrawingMachine();
        jadelex.Tokenizer analyseur = new jadelex.TokenizerV1(input);
        
        JadeParser parser = new ParserLevel1(analyseur, machine);
        try {
            parser.run();
        }
        catch (JadeException e){
            System.out.println("*** Interpréteur arrêté suite à une erreur de syntaxe ***");
        }
        
    }
}