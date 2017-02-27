package View;

import java.awt.*;
import java.awt.event.ActionListener;
import java.util.*;
import javax.swing.*;
import javax.swing.border.*;

import Game.GlobalSetting;
import GameException.MaxMoveReachException;
import GameException.NoMoveLeftException;
import Model.EntityActionSequence;
import Model.EntitySystem;
/**
 * View of the game
 * 
 * Observer - Observe if there is a change in player's action sequence, if there is then update the label (Wong Tiong Kiat)
 * 
 * @author Lim Yun Shen
 *
 */
public class GameView implements Observer
{
	private JFrame mainFrame;
	
	private CustomGameActionButton moveDownGameButton, moveUpGameButton, moveRightGameButton, 
	moveLeftGameButton, shootDownGameButton, shootUpGameButton, shootRightGameButton,
	shootLeftGameButton;
	
	private CustomButton doneSelectionButton, quitSelectionButton, backSelectionButton, restartSelectionButton, saveSelectionButton;

	private JPanel optionPanel, actionSelectionPanel, southPanel;
	private ScoreBoard scoreBoard;
	private BoardRenderer boardRenderer;
	
	private ActionListPanel actionLabelPanel;
	
	private JFileChooser fileChooser;

	/**
     * Constructor for objects of class GameView
     */
	public GameView()
	{
		mainFrame = new JFrame("Driver Test");
		mainFrame.setLayout(new BorderLayout());
		mainFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		mainFrame.setResizable(true);
		mainFrame.setPreferredSize(new Dimension(800,600));

        // Decorations for j components.
        Border raisedetched = BorderFactory.createEtchedBorder(EtchedBorder.RAISED);
        TitledBorder leftTitled = BorderFactory.createTitledBorder("Actions To Be Performed");

        // Action List Panel where input sequence can be visibly seen.
        actionLabelPanel = new ActionListPanel(400, 50);
        actionLabelPanel.setBorder(leftTitled);

        // Action Buttons.
        moveDownGameButton = new CustomGameActionButton(EntityActionSequence.Action.DOWN,
        		"Move Down", "Moves your robot down.", 50, 40);
        moveUpGameButton = new CustomGameActionButton(EntityActionSequence.Action.UP,
        		"Move Up", "Moves your robot up.", 50, 40);
        moveRightGameButton = new CustomGameActionButton(EntityActionSequence.Action.RIGHT,
        		"Move Right", "Moves your robot right.", 50, 40);
        moveLeftGameButton = new CustomGameActionButton(EntityActionSequence.Action.LEFT,
        		"Move Left", "Moves your robot left.", 50, 40);
        shootDownGameButton = new CustomGameActionButton(EntityActionSequence.Action.SHOOTDOWN,
        		"Shoot Down", "Makes your robot shoot down.", 50, 40);
        shootUpGameButton = new CustomGameActionButton(EntityActionSequence.Action.SHOOTUP,
        		"Shoot Up", "Makes your robot shoot up.", 50, 40);
        shootRightGameButton = new CustomGameActionButton(EntityActionSequence.Action.SHOOTRIGHT,
        		"Shoot Right", "Makes your robot shoot right.", 50, 40);
        shootLeftGameButton = new CustomGameActionButton(EntityActionSequence.Action.SHOOTLEFT,
        		"Shoot Left", "Makes your robot shoot left.", 50, 40);

        // Panel to hold the action buttons.
        actionSelectionPanel = new JPanel(new GridLayout(2,4));
        actionSelectionPanel.add(moveLeftGameButton);
        actionSelectionPanel.add(moveUpGameButton);
        actionSelectionPanel.add(moveDownGameButton);
        actionSelectionPanel.add(moveRightGameButton);
        actionSelectionPanel.add(shootLeftGameButton);
        actionSelectionPanel.add(shootUpGameButton);
        actionSelectionPanel.add(shootDownGameButton);
        actionSelectionPanel.add(shootRightGameButton);
        actionSelectionPanel.setBorder(raisedetched);

        // Option buttons.
        doneSelectionButton = new CustomButton("Done", "Confirm Move", 50, 30);
        backSelectionButton = new CustomButton("Back", "Undo Last Move", 50, 30);
        quitSelectionButton = new CustomButton("Menu", "Quit Game", 50, 30);
        restartSelectionButton = new CustomButton("Restart", "Restart Game", 50, 30);
        saveSelectionButton = new CustomButton("Save", "Save Current Game", 50, 30);

        // Panel to hold the option buttons.
        optionPanel = new JPanel(new GridLayout(0,4));
        optionPanel.add(doneSelectionButton);
        optionPanel.add(backSelectionButton);
        optionPanel.add(restartSelectionButton);
        optionPanel.add(saveSelectionButton);
        optionPanel.setBorder(raisedetched);
        
        // Panel to hold Action List Panel, Action Buttons Panel and Option Buttons Panel.
        southPanel = new JPanel(new BorderLayout());
        southPanel.add(actionLabelPanel, BorderLayout.NORTH);
        southPanel.add(actionSelectionPanel, BorderLayout.CENTER);
        southPanel.add(optionPanel, BorderLayout.SOUTH);
        
        // Board
        boardRenderer = new BoardRenderer();
        boardRenderer.setBorder(raisedetched);
        
        //// Score Board
        scoreBoard = new ScoreBoard(quitSelectionButton);
        
        mainFrame.add(scoreBoard, BorderLayout.NORTH);
        mainFrame.add(boardRenderer, BorderLayout.CENTER);
        mainFrame.add(southPanel, BorderLayout.SOUTH);
		mainFrame.setLocationRelativeTo(null);
		mainFrame.pack();
		mainFrame.setVisible(true);
		
		fileChooser = new JFileChooser();
	}
    /**
     * this method is called by the observerable class
     *
     * @param  The observable object that call this observer instance
     * @param  The object class that is passed by the observable object
     * @return	void
     */
	@Override
	public void update(Observable observer, Object object) 
	{
		if(object!=null && object instanceof EntityActionSequence)
		{
			EntityActionSequence actionSequence = (EntityActionSequence) object;
			this.refreshLabel(actionSequence);
		}
	}
    /**
     * this method refresh the label (player's action sequence label at the right side of the frame)
     *
     * @param  The action sequence to be displayed
     * @return	void
     */
	private void refreshLabel(EntityActionSequence actionSequence)
	{
		if(actionSequence != null && actionSequence.getClass() == EntityActionSequence.class)
		{
			actionSequence.resetActionIndex();
			for(int i = 0; i < GlobalSetting.MAX_ACTION_ALLOWED; i ++)
			{
				EntityActionSequence.Action actionType;
				try 
				{
					actionType = actionSequence.nextAction();
					if(actionType == null) 
					{
						actionLabelPanel.updateLabel(i, " ");
					}
					else
					{
						actionLabelPanel.updateLabel(i, actionType.toString());
					}
				} 
				catch (NoMoveLeftException ex1) 
				{
					this.displayMessageDialog(ex1.getMessage(), "Error", JOptionPane.ERROR_MESSAGE); 
				}
				
			}
		}
	}
    /**
     * this method displays the dialog from the jframe
     *
     * @param  Dialog message to be displayed
     * @param  Title of the dialog
     * @param  Status of the dialog where the status can be found in the JOPtionPane class
     * @return	void
     */
	public void displayMessageDialog(String message, String dialogTitle, int status)
	{
		JOptionPane.showMessageDialog(mainFrame, message, dialogTitle, status);
	}
    /**
     * Add action listener for all the action buttons, these are attached to the same controller as they are all related to action.
     *
     * @param  action listener for all the action buttons
     * @return	void
     */
	public void addGameActionListener(ActionListener controller) 
	{
		moveDownGameButton.addActionListener(controller);
		moveUpGameButton.addActionListener(controller);
		moveRightGameButton.addActionListener(controller);
		moveLeftGameButton.addActionListener(controller);
		shootDownGameButton.addActionListener(controller);
		shootUpGameButton.addActionListener(controller);
		shootRightGameButton.addActionListener(controller);
		shootLeftGameButton.addActionListener(controller);
	}
    /**
     * Set the availability of each button, where false is disabled button where all buttons cannot be click, true meaning the button will be clickable
     *
     * @param state enable or disable all of the action buttons  
     * @return	void
     */
	public void buttonSetEnable(boolean state)
	{
		moveDownGameButton.setEnabled(state); 
		moveUpGameButton.setEnabled(state);
		moveRightGameButton.setEnabled(state); 
		moveLeftGameButton.setEnabled(state);
		shootDownGameButton.setEnabled(state);
		shootUpGameButton.setEnabled(state);
		shootRightGameButton.setEnabled(state);
		shootLeftGameButton.setEnabled(state);
		doneSelectionButton.setEnabled(state);
		quitSelectionButton.setEnabled(state); 
		backSelectionButton.setEnabled(state);
		restartSelectionButton.setEnabled(state);
		saveSelectionButton.setEnabled(state);
	}
    /**
     * Add action listener for quit button
     *
     * @param  action listener for the quit button
     * @return	void
     */
	public void addQuitListener(ActionListener controller) 
	{
		quitSelectionButton.addActionListener(controller);
	}
    /**
     * Add action listener for done button
     *
     * @param  action listener for the done button
     * @return	void
     */
	public void addDoneListener(ActionListener controller) 
	{
		doneSelectionButton.addActionListener(controller);
	}
    /**
     * Add action listener for back button
     *
     * @param  action listener for the back button
     * @return	void
     */
	public void addBackListener(ActionListener controller) 
	{
		backSelectionButton.addActionListener(controller);
	}
    /**
     * Add action listener for restart button
     *
     * @param  action listener for the restart button
     * @return	void
     */
	public void addRestartListener(ActionListener controller) 
	{
		restartSelectionButton.addActionListener(controller);
	}
    /**
     * Add action listener for save button
     *
     * @param  action listener for the save button
     * @return	void
     */
	public void addSaveListener(ActionListener controller) 
	{
		saveSelectionButton.addActionListener(controller);
	}
    /**
     * Close the game frame
     *
     * @return	void
     */
	public void closeGameFrame()
	{
		mainFrame.dispose();
	}
    /**
     * Get done custom button
     *
     * @return	CustomButton instance
     */
	public CustomButton getDoneSelectionButton() {
		return doneSelectionButton;
	}
    /**
     * Get quit custom button
     *
     * @return	CustomButton instance
     */
	public CustomButton getQuitSelectionButton() {
		return quitSelectionButton;
	}
    /**
     * Get back custom button
     *
     * @return	CustomButton instance
     */
	public CustomButton getBackSelectionButton() {
		return backSelectionButton;
	}
    /**
     * Get BoardRenderer which is a panel for the board
     *
     * @return	BoardRenderer instance
     */
	public BoardRenderer getBoardRenderer()
	{
		return boardRenderer;
	}
    /**
     * Get ScoreBoard which is a panel for the score board
     *
     * @return	ScoreBoard instance
     */
	public ScoreBoard getScoreBoard()
	{
		return scoreBoard;
	}
    /**
     * Call the file chooser to show the dialog from the main frame
     *
     * @return	integer as the status of the file chooser
     */
	public int showSaveFileChooser(){
		return fileChooser.showSaveDialog(mainFrame);
	}
    /**
     * Get the selected file path from file chooser
     *
     * @return	string of the absolute path from the location of the file
     */
	public String getSelectedFile(){
		return fileChooser.getSelectedFile().getAbsolutePath();
	}
}
class ActionListPanel extends JPanel
{
	private static final long serialVersionUID = -327849069472490427L;
	
	private JLabel[] actionLabels;

	/**
     * Constructor for the action list panel on the right side of the main frame to display the player's action
     */
    public ActionListPanel(int width, int height) 
    {
        this.setLayout(new GridLayout(0, GlobalSetting.MAX_ACTION_ALLOWED));
        this.setPreferredSize(new Dimension(width, height));
        Border raisedetched = BorderFactory.createEtchedBorder(EtchedBorder.RAISED);
        
        actionLabels = new JLabel[GlobalSetting.MAX_ACTION_ALLOWED];
        for (int i = 0; i < GlobalSetting.MAX_ACTION_ALLOWED; i++) 
        {
        	actionLabels[i] = new JLabel(" ");
        	actionLabels[i].setBorder(raisedetched);
        	actionLabels[i].setHorizontalAlignment(SwingConstants.CENTER);
            this.add(actionLabels[i]);
        }
    }
    /**
     * Get the selected file path from file chooser
     *
     * @param  integer representing the index of action to be accessed
     * @param  update to the string at index as specified on top
     * @return	void
     */
    public void updateLabel(int idx, String text)
    {
        actionLabels[idx].setText(text);
    }
    
}

class ScoreBoard extends JPanel implements Observer
{
	private static final long serialVersionUID = 1L;
	private JLabel roundLabel, scoreLabel;
	/**
     * Constructor for the action list panel on the top of the main frame to display player's score
     */
	public ScoreBoard(CustomButton backButton)
	{
		this.setLayout(new GridLayout(0, 4));
        Border raisedetched = BorderFactory.createEtchedBorder(EtchedBorder.RAISED);
        this.scoreLabel = new JLabel(" Score: " + GlobalSetting.INITIAL_PLAYER_SCORE);
        this.scoreLabel.setBorder(raisedetched);
        
        this.roundLabel = new JLabel(" Rounds: " + 0);
        this.roundLabel.setBorder(raisedetched);
        
        JLabel blue = new JLabel();
        blue.setBackground(Color.BLUE);
        blue.setOpaque(true);
        blue.setBorder(raisedetched);
        
        JLabel red = new JLabel();
        red.setBackground(Color.RED);
        red.setOpaque(true);
        red.setBorder(raisedetched);
        
        JLabel player = new JLabel(" - Player ");
        player.setBorder(raisedetched);
        
        JLabel ai = new JLabel(" - AI ");
        ai.setBorder(raisedetched);
        
        JPanel robotsDescription = new JPanel(new GridLayout(2,2));
        robotsDescription.add(blue);
        robotsDescription.add(player);
        robotsDescription.add(red);
        robotsDescription.add(ai);
        robotsDescription.setBorder(raisedetched);
        
        this.add(scoreLabel);
        this.add(roundLabel);
        this.add(robotsDescription);
        this.add(backButton);
	}
    /**
     * Set the round label
     *
     * @param  integer representing which round the current game is
     * @return	void
     */
	public void setRound(int round)
	{
		roundLabel.setText(" Rounds: " + round);
	}
    /**
     * Set the score label
     *
     * @param  integer representing the current score of the game
     * @return	void
     */
	public void setScore(int score)
	{
		scoreLabel.setText(" Score: " + score);
	}
    /**
     * Observable design pattern, this class is a observer, where observable in model will call to update this method
     *
     * @param  the observable that called this method
     * @param  the object that is passed by the observable
     * @return	void
     */
	@Override
	public void update(Observable o, Object object) 
	{
		if(object!=null && object instanceof EntitySystem)
		{
			EntitySystem enSys = (EntitySystem) object;
			this.setScore(enSys.getPlayerScore());
			this.setRound(enSys.getRound());
		}
	}
	
}
