package jade;
import java.io.IOException;

import jadelex.*;

public class ParserLevel1 implements JadeParser {
    private final jadelex.Tokenizer tokenizer;
    private final jade.JadeMachine machine;
    
    public ParserLevel1(jadelex.Tokenizer tokenizer, jade.JadeMachine machine){
        this.tokenizer = tokenizer;
        this.machine = machine;
    }
    
    
    /*----------------------------------------------
     * Les méthodes ...Action reçoivent en paramètre un token
     * correspondant à une instruction simple et
     * envoient à la JadeMachine
     * la commande correspondante 
     *------------------------------------------------
     */
    
    /*
     * Déclenche l'action correspondant à un instruction simple
     */
    private void simpleAction(Yytoken t) {
    	switch(t.getType()) {
    	case MOVE:
    		moveAction((Move)t);
    		break;
    	case PEN_MODE:
    		penModeAction((PenMode)t);
    		break;
    	case STEP_LENGTH:
    		stepLengthAction((StepLength)t);
    		break;
    	case JUMP:
    		jumpAction((Jump)t);
    		break;
    	}
    }
    
    /*
     * déclenche le déplacement indiqué par le token
     */
    private void moveAction(Move token){
    	machine.move(token.getDirection());
    }
    
    /*
     * déclenche le changement de mode indiqué par le token
     */
    private void penModeAction(PenMode token){
    	machine.setPenMode(token.getMode());
    }
    
    /*
     * déclenche le saut indiqué par le token
     */
    private void jumpAction(Jump token){
    	machine.jump(token.getX(), token.getY());
    }
    
    /*
     * déclenche le changement de longueur de pas indiqué par le token
     */
    private void stepLengthAction(StepLength token){
    	machine.setStepLength(token.getLength());
    }
    
    /*
     * Indique si le token correspond à une instruction simple
    */
    private boolean isSimple(Yytoken t){
    	return (
    			t.getType() == TokenType.JUMP
    			|| t.getType() == TokenType.MOVE
    			|| t.getType() == TokenType.PEN_MODE
    			|| t.getType() == TokenType.STEP_LENGTH
    			); // TODO
    }
  
    /*--------------------------------------
     * Analyseur syntaxique proprement dit
     *--------------------------------------
     */
    /*
     * dernier token lu
     */
    private jadelex.Yytoken currentToken;
    
    /*
     * progession de lecture. Modifie currentToken
     */
    private void nextToken() throws IOException{
        currentToken = tokenizer.yylex();
    }
    
    /*
     * Appelée en cas d'erreur de syntaxe
     */
    private void error(String message) throws JadeException {
    	throw new JadeException();
    }

    
    
    /*
     * Cette méthode lit une séquence d'instructions terminée par la fin de fichier
     *
     * Initialement, currentToken est le premier token de la séquence à analyser
     * En fin de méthode, currentToken est le premier token QUI SUIT la séquence à analyser (donc ici null)
     *
     * 
     */
    private void parseSequence() throws IOException, JadeException {
    	nextToken();
    	
    	while(currentToken != null) {
    		if (isSimple(currentToken)) {
    			simpleAction(currentToken);
    			nextToken();
    		}
    		else {
    			parseRepeat();
    			// pas de nextToken() puisqu'à la sortie de parseRepeat, on est déjà sur le token suivant
    		}
    	}
    	
    	
    }

    /*
     * Cette méthode lit une répétition complète, c'est à dire un opérateur de répétition
     * suivi d'une instruction simple à répéter
     * 
     * Initialement, currentToken est le premier token à analyser (donc de type REPEAT)
     * En fin de méthode, currentToken est le premier token QUI SUIT l'instruction à répéter
     *
     */
    private void parseRepeat() throws IOException, JadeException {
    	if (currentToken.getType() != TokenType.REPEAT)
    		throw new JadeException("REPEAT token expected but the current token is "+currentToken);
    	int nbRepeat = ((Repeat)currentToken).getOccurences();
    	nextToken();
    	if (currentToken == null)
    		error("Unexpected end of sequence after REPEAT token.");
    	
    	if (isSimple(currentToken)) {
    		for (int i=0; i<nbRepeat; i++) {
    			simpleAction(currentToken);
    		}
    		nextToken();
    	}
    	else {
    		error("Unexpected "+currentToken.getType()+" token after REPEAT token. Simple action token expected.");
    	}
    	
    }
    
    /**
     * Déclenche l'analyse syntaxique et l'interprétation
     *
     */
    public void run() throws JadeException{
    	try {
			parseSequence();
		} catch (IOException e) {
			e.printStackTrace();
		}
    }
 
}