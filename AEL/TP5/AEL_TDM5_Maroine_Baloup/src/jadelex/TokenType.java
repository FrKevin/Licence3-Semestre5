package jadelex;
/**
 * Token Types for Jade Tokenizer
 */

public enum TokenType {
    /* Jade niveau 1 */
   MOVE, PEN_MODE, JUMP, STEP_LENGTH, REPEAT, UNKNOWN,
    /* Jade Niveau 2 */
   BEGIN, END, IDENT,  DEFINE;   
}