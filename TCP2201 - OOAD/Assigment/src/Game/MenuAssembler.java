package Game;

import Controller.GameMenuController;
import View.GameMenu;
/**
 * Assembles the menu instance creation
 * 
 * @author Ng Chen Hon
 *
 */
public class MenuAssembler 
{
	private static GameMenu gameMenu = new GameMenu();
	private static GameMenuController gameMenuController = new GameMenuController(gameMenu);
 
	private MenuAssembler(){}
	/**
	 * Set game menu frame's visibility.
	 *
	 * @return      void
	 */
	public static void newMenu()
	{
		gameMenu.setVisible(true);
	}
}
