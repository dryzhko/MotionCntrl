package MotionCntrl; 
import java.io.IOException; 
import java.awt.AWTException; 
import java.awt.GraphicsDevice; 
import java.awt.GraphicsEnvironment; 
import java.awt.MouseInfo; 
import java.awt.Point; 
import java.awt.Robot; 
import java.awt.event.InputEvent; 
import java.awt.event.KeyEvent; 
import com.leapmotion.leap.*; 
import com.leapmotion.leap.Controller.PolicyFlag; 
public class MotionCntrl {
	public static void main(String[] args) throws AWTException { 
		Controller controller = new Controller(); 
		controller.setPolicyFlags(PolicyFlag.POLICY_BACKGROUND_FRAMES);	 
SampleListener listener = new SampleListener(); 
		controller.addListener(listener); 
System.out.println("Enter to quit"); 
		try { 
			System.in.read(); 
		} catch (IOException e) { 
			e.printStackTrace(); 
		} 
		controller.removeListener(listener); 
	} 
} 

class SampleListener extends Listener {

	boolean readyForControl = false;
	int screenWidth;
	int screenHeight;
	boolean iBoxGet = false;
	InteractionBox iBox = null;
	Robot robot;
	boolean isMoving = false;

	public void onConnect(Controller controller) {
		System.out.println("Connected");
		GraphicsDevice gd = GraphicsEnvironment.getLocalGraphicsEnvironment()
				.getDefaultScreenDevice();
		screenWidth = gd.getDisplayMode().getWidth();
		screenHeight = gd.getDisplayMode().getHeight();
		System.out.println("Screen Resolution: X: " + screenWidth + ", H: "
				+ screenHeight);
		readyForControl = true;
		try {
			robot = new Robot();
			robot.setAutoDelay(5);
		} catch (AWTException e) {
			e.printStackTrace();
		}
	}

	public void onFrame(Controller controller) {
		Frame frame = controller.frame(); 
		if (!iBoxGet) {
			iBox = frame.interactionBox();
			iBoxGet = true;
			System.out.println("Interaction box set!");
		}
		Hand rightHand = frame.hands().rightmost();
		Vector palmV = rightHand.palmVelocity();
		palmV.getY();

		Point mouseLoc = MouseInfo.getPointerInfo().getLocation();
		int currentMouseX = mouseLoc.x;
		int currentMouseY = mouseLoc.y;
		

		if (readyForControl && rightHand.confidence() > .15) {
			

			float xSpeed = (palmV.getX() / 6);
			float ySpeed = (palmV.getY() / 6);

			robot.mouseMove((int) (currentMouseX + xSpeed),
					(int) (currentMouseY - ySpeed));

		}
	}
}