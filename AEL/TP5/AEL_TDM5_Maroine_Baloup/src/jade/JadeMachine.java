package jade;
public interface JadeMachine {
    
    /**
     * fixer la longueur du pas
     * n doit être strictement positif
     */
    public void setStepLength(int n);

    /**
     * fixer le mode crayon (true => actif)
     */
    public void setPenMode(boolean active);
    
    /**
     * réaliser un mouvement élémentaire de la longueur d'un pas dans la direction indiquée
     * si le mode crayon est activé, le segment de droite est tracé.
     *
     */
    public void move(Direction d);
 
    /**
     * aller jusqu'au point de coordonnées indiquées, sans dessiner.
     *
     */
    public void jump(int x, int y);

    /**
     * stopper la machine. Toute modification de son état est ensuite impossible
     *
     */
    public void bye(int x, int y);





}

