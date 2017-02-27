package Controller;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JFileChooser;

import View.GameMenu;
import View.InstructionView;
import Game.GameAssembler;
import SaveUtil.Decoder;
import Builder.Saver;
/**
 * Menu controller for the start of the menu.
 * 
 * @author Ng Chen Hon
 *
 */

public class GameMenuController 
{
	private GameMenu gameMenu;
    /**
     * Constructor for objects of class GameMenuController
     * 
     * @param  Gamemenu, the gamemenu to establish listeners
     */
	public GameMenuController(GameMenu gameMenu)
	{
		this.gameMenu = gameMenu;
		gameMenu.addStartListener(new StartActionListener());
		gameMenu.addLoadListener(new LoadActionListener());
		gameMenu.addInstructionListener(new InstructionActionListener());
		gameMenu.addExitListener(new ExitActionListener());
	}
	
	class StartActionListener implements ActionListener
	{

		@Override
		public void actionPerformed(ActionEvent arg0) 
		{
			// Starts a new game
			gameMenu.setVisible(false);
			GameAssembler.newGame();
		}
	}
	
	class LoadActionListener implements ActionListener
	{

		@Override
		public void actionPerformed(ActionEvent arg0) 
		{
			// Loads the game
			if(gameMenu.showFileChooser() == JFileChooser.APPROVE_OPTION)
			{
				String fileName = gameMenu.getLoadPath();
				
				if(Decoder.loadSave(fileName))
				{
					Saver save = Decoder.getSave();
					GameAssembler.loadGame(save.getRound(), save.getScore(), save.getPlayerSequence(), save.getEnemySequence());
					gameMenu.setVisible(false);
					Decoder.removeBuff();
				}
			}
		}
	}
	
	class InstructionActionListener implements ActionListener
	{

		@Override
		public void actionPerformed(ActionEvent arg0) 
		{
			// Pops up instruction window
			InstructionView iv = InstructionView.getInstance();
			iv.setVisible(true);
		}
	}
	
	class ExitActionListener implements ActionListener
	{

		@Override
		public void actionPerformed(ActionEvent arg0) 
		{
			// Exit program
			System.exit(0);
		}
	}
}
