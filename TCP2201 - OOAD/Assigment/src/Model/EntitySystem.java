package Model;


import java.util.ArrayList;
import java.util.Observable;

import Game.GlobalSetting;
/**
 * Control the logic and flow of the game
 * 
 * Observable - If there is a change in logic, call all the observers that subscribes to it
 * 
 * @author Wong Tiong Kiat and Choe Choon Ho
 *
 */
public class EntitySystem extends Observable
{
	
	private EntityType[][] entityTypeBoard;
	
	private boolean hasEnded, playerWon, computerWon;
	
	private Robot aiRobot, humanRobot;
	//which direction is the robot facing?
	private String aiDirection, playerDirection;
	private int playerScore, round;
    /**
     * Constructor for objects of class EntitySystem
     * 
     * @param  EntityActionSequence player's action sequence
     * @param  EntityActionSequence computer's action sequence
     */
	public EntitySystem(EntityActionSequence playerSequence, EntityActionSequence aiSequence)
	{
		
		humanRobot = new Robot(EntityType.PLAYER2, GlobalSetting.PLAYER2_XPOS, GlobalSetting.PLAYER2_YPOS, playerSequence);
		aiRobot = new Robot(EntityType.PLAYER1, GlobalSetting.PLAYER1_XPOS, GlobalSetting.PLAYER1_YPOS, aiSequence);	
	
		playerScore = GlobalSetting.INITIAL_PLAYER_SCORE;
		round = 0;
		
		playerWon = false;
		computerWon = true;
		hasEnded = false;
		
		setChanged();
		notifyObservers(this);
	}
    /**
     * reset the board with the given playersequence and aisequence
     *
     * @param  EntityActionSequence player's action sequence
     * @param  EntityActionSequence computer's action sequence
     * 
     * @return void
     */
	//reset only the board but ai logic remains same 
	public void resetBoard(EntityActionSequence playerSequence, EntityActionSequence aiSequence)
	{
		humanRobot = new Robot(EntityType.PLAYER2, GlobalSetting.PLAYER2_XPOS, GlobalSetting.PLAYER2_YPOS, playerSequence);
		aiRobot = new Robot(EntityType.PLAYER1, GlobalSetting.PLAYER1_XPOS, GlobalSetting.PLAYER1_YPOS, aiSequence);
		
		playerWon = false;
		computerWon = true;
		hasEnded = false;
		
		entityTypeBoard = new EntityType[GlobalSetting.BOARD_GRID_SIZE][GlobalSetting.BOARD_GRID_SIZE];

		entityTypeBoard[humanRobot.getXPos()][humanRobot.getYPos()] = EntityType.PLAYER2;
		entityTypeBoard[aiRobot.getXPos()][aiRobot.getYPos()] = EntityType.PLAYER1;
		
		setChanged();
		notifyObservers(this);
	}
    /**
     * reset the entire game
     *
     * @param  EntityActionSequence player's action sequence
     * @param  EntityActionSequence computer's action sequence
     * 
     * @return void
     */
	//reset the whole game including the game score to 0 and to initial player score
	public void resetRound(EntityActionSequence playerSequence, EntityActionSequence aiSequence)
	{
		this.resetRound(playerSequence, aiSequence, GlobalSetting.INITIAL_PLAYER_SCORE, 0);
	}
    /**
     * reset the entire game with the given playerscore and round
     *
     * @param  EntityActionSequence player's action sequence
     * @param  EntityActionSequence computer's action sequence
     * @param  integer of player's score
     * @param  integer of the current's round
     * 
     * @return void
     */
	//reset the whole game with a specified score and round
	public void resetRound(EntityActionSequence playerSequence, EntityActionSequence aiSequence, int playerScore, int round)
	{
		resetBoard(playerSequence, aiSequence);
		
		this.playerScore = playerScore;
		this.round = round;
		
		setChanged();
		notifyObservers(this);
		
	}

    /**
     * each tick will let every entity of the board do its thing each time
     *
     * 
     * @return void
     */
	public void tick()
	{
		entityTypeBoard = new EntityType[GlobalSetting.BOARD_GRID_SIZE][GlobalSetting.BOARD_GRID_SIZE];
		
		this.performMovementAction(aiRobot, humanRobot);
		this.performMovementAction(humanRobot, aiRobot);
		this.performShootAction(aiRobot, humanRobot);
		this.performShootAction(humanRobot, aiRobot);
		
		playerScore -= GlobalSetting.PLAYER_SCORE_DECREMENT_PER_TURN;
		
		aiDirection = aiRobot.getDirection();
		playerDirection = humanRobot.getDirection();
		
		setChanged();
		notifyObservers(this);
	}

    /**
     * let the robot move 
     *
     * @param  Robot instance 
     * @param  The other robot instance for checking if the current robot is clashing with another robot 
     * 
     * @return void
     */
	private void performMovementAction(Robot robotEntity, Robot otherEntity)
	{
		robotEntity.tick(otherEntity);
		
		int xPos = robotEntity.getXPos();
		int yPos = robotEntity.getYPos();
		
		entityTypeBoard[xPos][yPos] = robotEntity.getEntityType();
		
	}

    /**
     * let the robot shoot 
     *
     * @param  Robot instance 
     * @param  The other robot instance for checking if the current robot is shooting another robot 
     * 
     * @return void
     */
	private void performShootAction(Robot robotEntity, Robot otherEntity)
	{
		Projectile projectile = robotEntity.getProjectile();
		if(projectile != null)
		{
			int projectileXPos = projectile.getXPos();
			int projectileYPos = projectile.getYPos();
			
			entityTypeBoard[projectileXPos][projectileYPos] = projectile.getEntityType();
			
			projectile.tick(otherEntity);
			//if something has been hit
			if(!projectile.toContinue())
			{
				//if player got hit
				if(projectile.playerHitted())
				{
					//System.out.println("Player got hitted");
					playerDirection = null;
					computerWon = true;
				}
				else
				{
					//System.out.println("Player won!");
					//player hit the ai
					aiDirection = null;
					playerWon = true;
					computerWon = false;
				}
				hasEnded = true;
			}
		}
	}

    /**
     * called when the round has ended
     * 
     * @return void
     */
	public void roundEnd()
	{
		round ++;
		setChanged();
		notifyObservers(this);
	}

    /**
     * getter for the player's robot direction
     * 
     * @return String
     */
	public String getPlayerDirection()
	{
		return playerDirection;
	}

    /**
     * getter for the ai's robot direction
     * 
     * @return String
     */
	public String getEnemyDirection()
	{
		return aiDirection;
	}
    /**
     * getter for player's current score
     * 
     * @return Integer
     */
	
	public int getPlayerScore()
	{
		return playerScore;
	}

    /**
     * getter for current round
     * 
     * @return Integer
     */
	public int getRound()
	{
		return round;
	}

    /**
     * getter for if the game has ended
     * 
     * @return Boolean
     */
	public boolean hasGameEnded()
	{
		return hasEnded;
	}
    /**
     * getter for if player has won
     * 
     * @return Boolean
     */
	public boolean hasPlayerWon()
	{
		return playerWon;
	}
 
	public boolean hasComputerWon()
	{
		return computerWon;
	}

    /**
     * getter for the board
     * 
     * @return EntityType[][]
     */
	public EntityType[][] getEntityTypeBoard()
	{
		return entityTypeBoard;
	}

    /**
     * setter for the current round
     * 
     * @param integer of the round
     * @return void
     */
	public void setRound(int round){
		this.round = round;
	}

    /**
     * setter for the current score
     * 
     * @param integer of the score
     * @return void
     */
	public void setScore(int score){
		this.playerScore = score;
	}
}
