package exercices;

import ard.ErrorType;
import condenses_lex.Yytoken;

@SuppressWarnings("serial")
public class SyntaxException extends Exception {

	public SyntaxException() {
	}
	
	static protected String prepareMessage(ErrorType error, Yytoken current, Yytoken expected){
		switch (error){
		case NO_RULE :
			return "variable "+ Thread.currentThread().getStackTrace()[4].getMethodName() + ", token " + current+ ": no rule";
		case UNMATCHING_CHAR :
			return "found : " + current + ", expected : " + expected;
		default :
			return null;
		}
	}
	static protected String prepareMessage(ErrorType error, Yytoken current){
		return prepareMessage(error,current,null);
	}
	
	public SyntaxException(ErrorType error, Yytoken current) {
		this (prepareMessage(error,current)); 
	}
	public SyntaxException(ErrorType error, Yytoken current, Yytoken expected) {
		this (prepareMessage(error,current,expected)); 
	}

	public SyntaxException(String message) {
		super(message);
	}

	public SyntaxException(Throwable cause) {
		super(cause);
	}

	public SyntaxException(String message, Throwable cause) {
		super(message, cause);
	}

	public SyntaxException(String message, Throwable cause, boolean enableSuppression, boolean writableStackTrace) {
		super(message, cause, enableSuppression, writableStackTrace);
	}

}
