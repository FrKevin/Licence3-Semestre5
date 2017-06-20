package postfixees;
import java.io.*;
class TestPF {
  public static void main(String arg[]) throws IOException {
      // créer un Yylex qui va prendre ses entrées dans le fichier
      // de nom arg[0]
    Yylex yy = new Yylex(new BufferedReader(new FileReader(arg[0]))) ;
    Yytoken token ;
      // la fin de fichier est codée par un token null
    while ((token = yy.yylex()) != null){
      System.out.print("["+token.image()+"]<"+token.nom()+">");
    }
    System.out.println();
  }
}
