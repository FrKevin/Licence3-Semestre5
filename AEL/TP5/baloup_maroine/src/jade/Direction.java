package jade;
/**
 * Cardinal directions for Jade
 */
public enum Direction{
    EAST(1,0), NORTH(0,1), WEST(-1,0), SOUTH (0,-1);
    
    final int x, y;
    public int getX(){
        return x;
    }
    public int getY(){
        return y;
    }
    private Direction(int x, int y){
        this.x = x;
        this.y = y;
    }
}