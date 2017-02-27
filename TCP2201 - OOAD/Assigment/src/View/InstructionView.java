package View;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Font;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTextArea;
/**
 * View of the instruction
 * 
 * Design pattern used - Singleton, can only have one instruction view at a time
 * 
 * @author Lim Yun Shen 
 *
 */
public class InstructionView implements WindowListener
{
	
	private static InstructionView instance = new InstructionView();
	
	private JPanel instructionPanel;
	private JTextArea instructionTextArea;
	private JFrame instructionFrame;
    
	/**
     * Constructor for objects of class InstructionView
     */
	private InstructionView()
	{
		instructionTextArea = new JTextArea(15,50);
		instructionTextArea.append("This game is awesome!!");   //put text here
		instructionTextArea.setWrapStyleWord(true);
		instructionTextArea.setEditable(false);
		instructionTextArea.setFont(new Font("Verdana", Font.BOLD, 12));
		instructionTextArea.setForeground(Color.BLACK);
		instructionTextArea.setBackground(Color.YELLOW);

		instructionPanel = new JPanel(new BorderLayout());
		instructionPanel.add(instructionTextArea);

		instructionFrame = new JFrame("Instructions");
		instructionFrame.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
		instructionFrame.setSize(400,400);
		instructionFrame.add(instructionPanel);
		instructionFrame.setVisible(true);
		instructionFrame.addWindowListener(this);
	}
    /**
     * get instance of Instruction view this is a singleton 
     *
     * @return      instance of InstructionView
     */
	public static InstructionView getInstance()
	{
	      return instance;
	}
    /**
     * set visibility of instruction view's frame
     *
     * @param  visibility of this frame
     * @return	void
     */
	public void setVisible(boolean visible)
	{
		instructionFrame.setVisible(visible);
	}

	@Override
	public void windowActivated(WindowEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void windowClosed(WindowEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void windowClosing(WindowEvent e) {
		this.setVisible(false);
		
	}

	@Override
	public void windowDeactivated(WindowEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void windowDeiconified(WindowEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void windowIconified(WindowEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void windowOpened(WindowEvent e) {
		// TODO Auto-generated method stub
		
	}
	
}