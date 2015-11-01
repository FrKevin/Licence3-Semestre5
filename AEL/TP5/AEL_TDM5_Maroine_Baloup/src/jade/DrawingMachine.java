package jade;

import java.awt.Point;

import drawing.Drawing;
import drawing.DrawingException;
import drawing.DrawingFrame;

public class DrawingMachine implements JadeMachine {

	private Drawing frame = new DrawingFrame();
	
	
	/*
	 * Par défaut 5, comme dans le LoggingMachine()
	 */
	private int currentStepLength = 5; 
	private boolean penmode = true;
	
	
	
	public DrawingMachine() {
	}
	
	
	
	
	@Override
	public void setStepLength(int n) {
		if (n <= 0)
			throw new IllegalArgumentException("step length must be positive");
		currentStepLength = n;
	}

	@Override
	public void setPenMode(boolean active) {
		penmode = active;
	}

	@Override
	public void move(Direction d) {
		Point currentPos = frame.getCurrentPoint();
		Point targetPos = (Point)currentPos.clone();
		targetPos.x += d.x * currentStepLength;
		targetPos.y += d.y * currentStepLength;
		
		if (penmode) {
			try {
				frame.drawTo(targetPos);
			} catch (DrawingException e) { e.printStackTrace(); }
		}
		else {
			try {
				frame.goTo(targetPos);
			} catch (DrawingException e) { e.printStackTrace(); }
		}
	}

	@Override
	public void jump(int x, int y) {
		Point targetPos = new Point(x, y);
		try {
			frame.goTo(targetPos);
		} catch (DrawingException e) { e.printStackTrace(); }
	}

	@Override
	public void bye(int x, int y) {
		// à quoi servent x et y ?
		frame.reset();
	}

}
