package exemple1;
public class Yytoken {
  private String image ; // le texte correspondant au token trouvé
  
  public Yytoken(String source){
    this.image = source ;
  }
  
  public String image() {
    return image;
  }
}
