package automata;

@SuppressWarnings("serial")
public class StateException extends RuntimeException {

	public StateException() {
	}

	public StateException(String message) {
		super(message);
	}

	public StateException(Throwable cause) {
		super(cause);
	}

	public StateException(String message, Throwable cause) {
		super(message, cause);
	}

	public StateException(String message, Throwable cause, boolean enableSuppression, boolean writableStackTrace) {
		super(message, cause, enableSuppression, writableStackTrace);
	}

}
