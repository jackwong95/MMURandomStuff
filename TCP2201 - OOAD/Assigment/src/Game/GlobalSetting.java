package Game;

import java.awt.*;
/**
 * Stores all of the common settings which are used thoroughout the project
 * 
 * @author Wong Tiong Kiat and Choe Choon Ho
 *
 */
public final class GlobalSetting
{
	private GlobalSetting(){}

    public static final String PLAYER_TANK_IMAGE_PATH = "img/Player.png";
    public static final String PLAYER_TANK_IMAGE_PATH_UP = "img/PlayerUp.png";
    public static final String PLAYER_TANK_IMAGE_PATH_DOWN = "img/PlayerDown.png";
    public static final String PLAYER_TANK_IMAGE_PATH_LEFT = "img/PlayerLeft.png";
    public static final String PLAYER_TANK_IMAGE_PATH_RIGHT = "img/PlayerRight.png";
    public static final String PLAYER_PROJECTILE_IMAGE_PATH = "img/Projectile.png";

    public static final String PLAYER_WON_MESSAGE = "Player has won!";
    public static final String PLAYER_LOST_MESSAGE = "Player has lost!";
    
    public static final Font tankTempFont = new Font("Arial", Font.BOLD, 22);
    
    public static final Color COMPLETE_WHITE_TRANSPARENT = new Color (0.5f, 0.5f, 0.5f, 1f);

	public static final int INITIAL_PLAYER_SCORE = 1000;
	public static final int PLAYER_SCORE_DECREMENT_PER_TURN = 10;
	
    public static final int ANIMATION_DELAY = 500;
	public static final int MAX_ACTION_ALLOWED = 18;
	public static final int BOARD_GRID_SIZE = 10;
    public static final int PLAYER1_XPOS = 0;
    public static final int PLAYER1_YPOS = 0;
    public static final int PLAYER2_XPOS = 9;
    public static final int PLAYER2_YPOS = 9;
    public static final int GAME_CELL_HEIGHT = 50;
    public static final int GAME_CELL_WIDTH = 50;
}
