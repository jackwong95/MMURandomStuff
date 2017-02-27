package Controller;

import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import javax.swing.BorderFactory;
import javax.swing.JFileChooser;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.SwingConstants;
import javax.swing.Timer;
import javax.swing.border.Border;
import javax.swing.border.EtchedBorder;

import Game.GameAssembler;
import Game.GlobalSetting;
import GameException.MaxMoveReachException;
import GameException.NoMoveLeftException;
import Model.EntityActionSequence;
import Model.EntitySystem;
import View.CustomButton;
import View.CustomGameActionButton;
import View.GameView;
import Builder.Saver;
import static Builder.Saver.SaveBuilder;
import SaveUtil.Encoder;
import Game.MenuAssembler;

/**
 * Game controller, control the game models and the game views, and also link creation of those instances. The part where the views are subscribed to the model using observable pattern is also done here.
 * 
 * @author Wong Tiong Kiat and Choe Choon Ho
 *
 */
public class GameViewController
{
	private EntitySystem system;
	
	private EntityActionSequence humanAcSeq, robotAcSeq;
	
	private GameView gameView;
    /**
     * Constructor for objects of class GameMenuController
     * 
     * @param  GameView, the gameview to establish listeners
     * @param  EntityActionSequence, the action listener for the player
     */
	public GameViewController(GameView gameView, EntityActionSequence entityActionSequence)
	{
		this.gameView = gameView;
		humanAcSeq = entityActionSequence;

		robotAcSeq = new EntityActionSequence();
		try 
		{
			robotAcSeq.generateActionSequence();
		} 
		catch (MaxMoveReachException e) 
		{
			e.printStackTrace();
		}
		
		gameView.addGameActionListener(new GameActionListener());
		gameView.addQuitListener(new QuitActionListener());
		gameView.addDoneListener(new DoneActionListener());
		gameView.addBackListener(new BackActionListener());
		gameView.addRestartListener(new RestartActionListener());
		gameView.addSaveListener(new SaveActionListener());

		system = new EntitySystem(humanAcSeq, robotAcSeq);
		system.addObserver(gameView.getScoreBoard());
		system.addObserver(gameView.getBoardRenderer());
	}

    /**
     * Constructor for objects of class GameMenuController
     * 
     * @param  GameView, the gameview to establish listeners
     * @param  EntityActionSequence, the action listener for the player
     * @param  EntityActionSequence, the action listener for the ai
     * @param  integer the current round
     * @param  integer the current score
     */
	public GameViewController(GameView gameView, EntityActionSequence player, EntityActionSequence enemy, int round, int score)
	{
		this.gameView = gameView;
		humanAcSeq = player;
		robotAcSeq = enemy;
		
		gameView.addGameActionListener(new GameActionListener());
		gameView.addQuitListener(new QuitActionListener());
		gameView.addDoneListener(new DoneActionListener());
		gameView.addBackListener(new BackActionListener());
		gameView.addRestartListener(new RestartActionListener());
		gameView.addSaveListener(new SaveActionListener());

		system = new EntitySystem(humanAcSeq, robotAcSeq);
		system.addObserver(gameView.getScoreBoard());
		system.addObserver(gameView.getBoardRenderer());
		system.resetRound(player, enemy, score, round);
		gameView.update(player, player);
	}
	
	class SaveActionListener implements ActionListener
	{

		@Override
		public void actionPerformed(ActionEvent e) 
		{
			int option = gameView.showSaveFileChooser();
			
			if (option == JFileChooser.APPROVE_OPTION) {
				String fileName = gameView.getSelectedFile();
				
				Saver saver = new Saver.SaveBuilder()
								.addRound(system.getRound())
								.addScore(system.getPlayerScore())
								.addPlayerSequence(humanAcSeq)
								.addEnemySequence(robotAcSeq)
								.build();
				
				if(Encoder.outputSave(saver, fileName))
					System.out.println("save success");
				else
					System.out.println("can't save");
			}
		}
	}

	class GameActionListener implements ActionListener
	{

		@Override
		public void actionPerformed(ActionEvent e) 
		{
			CustomGameActionButton btn = (CustomGameActionButton)e.getSource();
			if(btn != null)
			{
				try 
				{
					humanAcSeq.pushAction(btn.getActionType());
				} 
				catch (MaxMoveReachException ex2)
				{
					gameView.displayMessageDialog(ex2.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
				}
			}
		}
		
	}

	class QuitActionListener implements ActionListener
	{

		@Override
		public void actionPerformed(ActionEvent e) 
		{
			gameView.closeGameFrame();
			MenuAssembler.newMenu();
		}
		
	}

	class RestartActionListener implements ActionListener
	{

		@Override
		public void actionPerformed(ActionEvent event) 
		{
			gameView.closeGameFrame();
			GameAssembler.newGame();
		}
		
	}

	class BackActionListener implements ActionListener
	{

		@Override
		public void actionPerformed(ActionEvent e) 
		{
			try 
			{
				humanAcSeq.removeAction();
			} 
			catch (NoMoveLeftException ex1) 
			{
				gameView.displayMessageDialog(ex1.getMessage(), "Error", JOptionPane.ERROR_MESSAGE); 
			}
			
		}
		
	}

	class DoneActionListener implements ActionListener
	{
		
		
		private int counter = GlobalSetting.MAX_ACTION_ALLOWED;
		private Timer timer;
		private ActionListener animator;
		
		public DoneActionListener()
		{
			if(system != null)
			{
				system.resetBoard(humanAcSeq, robotAcSeq);
				humanAcSeq.resetActionIndex();
				robotAcSeq.resetActionIndex();
			}
			
			setupAction();
		}
		
		public void startTimer()
		{
			timer = new Timer(GlobalSetting.ANIMATION_DELAY, animator);
			timer.setInitialDelay(0);
			gameView.buttonSetEnable(false);
			timer.start();
		}
		
		private void setupAction()
		{
			animator = new ActionListener()
			{
				@Override
				public void actionPerformed(ActionEvent event) 
				{
					if(counter == 0 || system.hasGameEnded())
					{
						if(system.hasPlayerWon())
						{
							gameView.displayMessageDialog(GlobalSetting.PLAYER_WON_MESSAGE, "Game Ended", JOptionPane.INFORMATION_MESSAGE);
							gameView.closeGameFrame();
							GameAssembler.newGame();
							//System.out.println("System player has lost : " + system.hasPlayerLost());
							//System.out.println("Counter : " + counter);
						}
						else if(system.hasComputerWon())
						{
							gameView.displayMessageDialog(GlobalSetting.PLAYER_LOST_MESSAGE, "Game Ended", JOptionPane.INFORMATION_MESSAGE);
							system.roundEnd();
						}
						humanAcSeq.clearAction();
						//system.deleteObserver(gameView.getScoreBoard());
						//system.deleteObserver(gameView.getBoardRenderer());
						gameView.buttonSetEnable(true);
						timer.stop();
					}
					else
					{
						system.tick();
						counter --;
					}
				}
			};
		}
		
		@Override
		public void actionPerformed(ActionEvent e) 
		{
			if(humanAcSeq.isFull())
			{
				DoneActionListener animator = new DoneActionListener();
				animator.startTimer();
			}
			else if(!humanAcSeq.isFull())
			{
				gameView.displayMessageDialog("Please fill all "+ GlobalSetting.MAX_ACTION_ALLOWED+" action slots.", "Error", JOptionPane.ERROR_MESSAGE); 
			}
		}
		
	}
}



