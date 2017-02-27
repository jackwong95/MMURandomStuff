package View;

import java.awt.*;
import java.awt.event.*;

import javax.swing.*;
/**
 * View of the menu 
 * 
 * @author Lim Yun Shen
 *
 */
public class GameMenu extends JFrame
{
	private static final long serialVersionUID = -8729649350184530657L;
	private JLabel header = new JLabel("Robot Shooting Game");
    private JButton start = new JButton("Start");
    private JButton load = new JButton("Load");
    private JButton instruction = new JButton("Instruction");
    private JButton exit = new JButton("Exit");
    
    private JPanel mainPanel = new JPanel(new BorderLayout());
    private JPanel subPanel = new JPanel(new GridLayout(4,1,20,20));
    private JPanel startPanel = new JPanel();
    private JPanel loadPanel = new JPanel(new FlowLayout());
    private JPanel exitPanel = new JPanel(new FlowLayout());
    private JPanel instructPanel = new JPanel(new FlowLayout());
    private JFileChooser fileChooser;
    
    /**
     * Constructor for objects of class GameMenu
     */
    public GameMenu()
    {
        // initialise instance variables
        this.setTitle("Robot Shooting Game");
 
        this.setSize(new Dimension(400,280));
        this.add(mainPanel);
        this.setVisible(true);
        this.setResizable(false);
        
        fileChooser = new JFileChooser();
        subPanel.setBackground(new Color(51,255,255));
        mainPanel.setBackground(new Color(51,255,255));
        startPanel.setBackground(new Color(51,255,255));
        exitPanel.setBackground(new Color(51,255,255));
        loadPanel.setBackground(new Color(51,255,255));
        instructPanel.setBackground(new Color(51,255,255));
        header.setFont(header.getFont().deriveFont (32.0f));


        
        mainPanel.add(header,BorderLayout.PAGE_START);
        header.setHorizontalAlignment(JLabel.CENTER);
        header.setVerticalAlignment(JLabel.CENTER);
        mainPanel.add(subPanel,BorderLayout.CENTER);

        startPanel.add(start);
        loadPanel.add(load);
        exitPanel.add(exit);
        instructPanel.add(instruction);

        subPanel.add(startPanel);
        subPanel.add(loadPanel);
        subPanel.add(instructPanel);
        subPanel.add(exitPanel);
        
        this.setVisible(false);
    }
    /**
     * listen actioner for start button 
     *
     * @param  ActionListener  listener for start button
     * @return      void
     */
    public void addStartListener(ActionListener listener){
    	start.addActionListener(listener);
    }
    /**
     * listen actioner for load button 
     *
     * @param  ActionListener  listener for load button
     * @return      void
     */
    public void addLoadListener(ActionListener listener){
    	load.addActionListener(listener);
    }   
    /**
     * listen actioner for instruction button 
     *
     * @param  ActionListener  listener for instruction button
     * @return      void
     */
    public void addInstructionListener(ActionListener listener){
    	instruction.addActionListener(listener);
    }   
    /**
     * listen actioner for exit button 
     *
     * @param  ActionListener  listener for exit button
     * @return      void
     */
    public void addExitListener(ActionListener listener){
    	exit.addActionListener(listener);
    }  
    /**
     * show file chooser as dialog
     *
     * @return	int representing the output of the file chooser
     */
	public int showFileChooser(){
		return fileChooser.showOpenDialog(this);
	}
    /**
     * show file chooser as dialog
     *
     * @return	int representing the output of the file chooser
     */
	public String getLoadPath(){
		return fileChooser.getSelectedFile().getAbsolutePath();
	}
    /**
     * set visibility of game menu frame
     *
     * @param  visibility of this frame
     * @return	void
     */
	public void setVisible(Boolean visibility){
		this.setVisible(visibility);
	}
}
