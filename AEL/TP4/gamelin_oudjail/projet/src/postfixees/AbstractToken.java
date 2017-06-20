package postfixees;
public abstract class AbstractToken implements Yytoken {
    public final String image;
    public String image(){
        return image;
    }
    
    public String nom(){
        return this.getClass().getSimpleName();
    }
    protected AbstractToken(String image){
        this.image = image;
    }
}
