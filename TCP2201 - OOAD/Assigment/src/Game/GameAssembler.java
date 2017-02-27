package Game;

import Controller.GameViewController;
import Game.GlobalSetting;
import Model.EntityActionSequence;
import View.GameView;
/**
 * Object creations and subscribtion of observable pattern
 * 
 * @author Wong Tiong Kiat and Choe Choon Ho
 *
 */
public class GameAssembler 
{
	private GameAssembler(){}
	
	public static void newGame()
	{
		
		GameView gameView = new GameView();
		
		EntityActionSequence entityActionSequence = new EntityActionSequence();
			
		entityActionSequence.addObserver(gameView);
			
		GameViewController controller = new GameViewController(gameView, entityActionSequence);
	}
	/**
	 * load the game
	 * 
	 *	@param integer for the current round
	 *	@param integer for the score of the round
	 *	@param player's action sequence
	 *	@param enemy's action sequence
	 * @return      void
	 */
	public static void loadGame(int round, int score, EntityActionSequence player, EntityActionSequence enemy)
	{
		
		GameView gameView = new GameView();
			
		player.addObserver(gameView);
			
		GameViewController controller = new GameViewController(gameView, player, enemy, round, score);
	}
}

