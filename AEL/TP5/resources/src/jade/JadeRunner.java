package jade;
import java.io.*;   
public class JadeRunner{
    public static void main (String[] arg) throws IOException{
        Reader input;
        if (arg.length>0){
          input = new BufferedReader(new FileReader(arg[0]));
        }
        else {
          input = new InputStreamReader(System.in);
        }

        JadeMachine machine = new LoggingMachine();
        //JadeMachine machine = new DrawingMachine();
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