package View;

import java.awt.GridLayout;
import java.util.Observable;
import java.util.Observer;

import javax.swing.*;

import Game.GlobalSetting;
import Model.EntitySystem;
import Model.EntityType;
/**
 * Board renderer - the board panel that is displayed in the center
 * 
 * Observer - Observe if there is a change in board in model, then update the board view
 * 
 * @author Wong Tiong Kiat and Choe Choon Ho 
 *
 */
public class BoardRenderer extends JPanel implements Observer
{
	
	private static final long serialVersionUID = 1L;
	private BoardPiece[][] board;
	private int playerX = GlobalSetting.PLAYER2_XPOS, playerY = GlobalSetting.PLAYER2_YPOS;
	private int enemyX = GlobalSetting.PLAYER1_XPOS, enemyY = GlobalSetting.PLAYER1_YPOS;	
    /**
     * Constructor for objects of class BoardRenderer
     * 
     */
	public BoardRenderer()
	{
		this.setLayout(new GridLayout(GlobalSetting.BOARD_GRID_SIZE, GlobalSetting.BOARD_GRID_SIZE));
		
		board = new BoardPiece[GlobalSetting.BOARD_GRID_SIZE][GlobalSetting.BOARD_GRID_SIZE];
		
		for(int y = 0; y < GlobalSetting.BOARD_GRID_SIZE; y ++)
		{
			for(int x = 0; x < GlobalSetting.BOARD_GRID_SIZE; x ++)
			{
				board[x][y] = new BoardPiece();
				this.add(board[x][y]);
			}
		}
		initializeTank();
	}
    /**
     * update the board's view based on the given entity type 2d array
     *
     * @param  2d array of entitytype representing the board
     * 
     * @return void
     */
	private void updateBoard(EntityType [][] entityBoard)
	{
		//board[enemyX][enemyY].switchType(BoardPiece.EMPTY);
		//board[playerX][playerY].switchType(BoardPiece.EMPTY);
		
		for(int x = 0; x < GlobalSetting.BOARD_GRID_SIZE; x ++)
		{
			for(int y = 0; y < GlobalSetting.BOARD_GRID_SIZE; y ++)
			{
				board[x][y].switchType(entityBoard[x][y]);
				if(entityBoard[x][y] == EntityType.PLAYER1)
				{
					enemyX = x;
					enemyY = y;
				}
				else if(entityBoard[x][y] == EntityType.PLAYER2)
				{
					playerX = x;
					playerY = y;
				}
			}
		}
	}
    /**
     * initialize tank's starting position
     *
     * 
     * @return void
     */
	private void initializeTank()
	{
		
		board[GlobalSetting.PLAYER1_XPOS][GlobalSetting.PLAYER1_YPOS].switchType(EntityType.PLAYER1);
		board[GlobalSetting.PLAYER2_XPOS][GlobalSetting.PLAYER2_YPOS].switchType(EntityType.PLAYER2);
	}
    /**
     * this method is called by the observerable class
     *
     * @param  The observable object that call this observer instance
     * @param  The object class that is passed by the observable object
     * @return	void
     */
	@Override
	public void update(Observable observerable, Object object) 
	{
		if(object!=null && object instanceof EntitySystem)
		{
			EntitySystem enSys = (EntitySystem) object;
			updateBoard(enSys.getEntityTypeBoard());

			String enemyFacedDir = enSys.getEnemyDirection();
			if(enemyFacedDir != null && enSys.hasComputerWon() && !enSys.hasGameEnded())
			{
				if(enemyFacedDir.equalsIgnoreCase("right"))
				{
					board[enemyX][enemyY].switchType("player1right");
				}
				else if(enemyFacedDir.equalsIgnoreCase("left"))
				{
						board[enemyX][enemyY].switchType("player1left");
				}
				else if(enemyFacedDir.equalsIgnoreCase("up"))
				{
						board[enemyX][enemyY].switchType("player1up");
				}
				else if(enemyFacedDir.equalsIgnoreCase("down"))
				{
						board[enemyX][enemyY].switchType("player1down");
				}
			}
			
			String playerFacedDir = enSys.getPlayerDirection();
			if(playerFacedDir != null && !enSys.hasPlayerWon() && !enSys.hasGameEnded())
			{
				if(playerFacedDir.equalsIgnoreCase("right"))
				{
					board[playerX][playerY].switchType("player2right");
				}
				else if(playerFacedDir.equalsIgnoreCase("left"))
				{
						board[playerX][playerY].switchType("player2left");
				}
				else if(playerFacedDir.equalsIgnoreCase("up"))
				{
						board[playerX][playerY].switchType("player2up");
				}
				else if(playerFacedDir.equalsIgnoreCase("down"))
				{
						board[playerX][playerY].switchType("player2down");
				}
			}
		}
	}
	
}
