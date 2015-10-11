package postfixees;
import java.util.*;
import java.io.*;
public class Evaluateur {
   public static void main(String arg[]) throws IOException, AriteException {
    Yylex yy = new Yylex(new BufferedReader(new FileReader(arg[0]))) ;
    Yytoken token ;
    
    Stack<Integer> pile = new Stack<Integer>();

    while ((token = yy.yylex()) != null){
        if (token instanceof Valeur) {
            Valeur v = (Valeur) token;
            pile.push(v.value());
        } else if (token instanceof Operateur){
            Operateur op = (Operateur) token;
            int[] args = new int[op.arite()];
            for (int i=0; i<args.length; i++)
                args[i] = pile.pop();
            pile.push(op.evaluate(args));
        }
    }
    System.out.println(pile.pop());
  }

}