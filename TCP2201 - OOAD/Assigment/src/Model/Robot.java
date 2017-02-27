package Model;

import java.util.ArrayList;

import Game.GlobalSetting;
import GameException.MaxMoveReachException;
import GameException.NoMoveLeftException;
/**
 * Robot entity in game
 * 
 * @author Wong Tiong Kiat and Choe Choon Ho
 *
 */
public class Robot extends Entity
{
	private EntityActionSequence acSeq;
	
	private Projectile projectile;
	private String direction;
    /**
     * Constructor for objects of class Robot
     * 
     * @param  EntityType to represent if the current robot is player or computer
     * @param  int current x direction position in the board
     * @param  int current y direction position in the board
     * @param  EntityActionSequence of the robot that is going to move at each tick
     */
	public Robot (EntityType type, int xPos, int yPos, EntityActionSequence acSeq)
	{
		super(type, xPos, yPos);
		
		this.acSeq = acSeq;
	}

    /**
     * what to do when a tick is called
     *
     * @param  takes in the other robot to check if they're going to location cell.
     * 
     * @return void
     */
	public void tick(Robot otherRobot)
	{
		try 
		{
			projectile = null;
			
			EntityActionSequence.Action currAction = acSeq.nextAction();
			if(!currAction.isProjectile())
			{
				int tempXPos = xPos + currAction.getXDir();
				int tempYPos = yPos + currAction.getYDir();
				//check if the place is already taken
				if(!(tempXPos == otherRobot.getXPos() && tempYPos == otherRobot.getYPos()))
				{
					if(tempXPos < GlobalSetting.BOARD_GRID_SIZE && tempXPos >= 0) 
						xPos = tempXPos;
					if(tempYPos < GlobalSetting.BOARD_GRID_SIZE && tempYPos >= 0) 
						yPos = tempYPos;
				}
				
			}
			if(currAction.isProjectile())
			{
				int tempXPos = xPos + currAction.getXDir();
				int tempYPos = yPos + currAction.getYDir();
				
				boolean toSpawn = true;
				
				if(tempXPos >= GlobalSetting.BOARD_GRID_SIZE || tempXPos < 0 || 
						tempYPos >= GlobalSetting.BOARD_GRID_SIZE || tempYPos < 0)
					toSpawn = false;
				
				if(toSpawn)
				{
					projectile = new Projectile(EntityType.BULLET, tempXPos, tempYPos);
				}
				
			}
			
			if(currAction.getXDir() == 1)
			{
				direction = "right";
			}
			else if(currAction.getXDir() == -1)
			{
				direction = "left";
			}
			else if(currAction.getYDir() == -1)
			{
				direction = "up";
			}
			else if(currAction.getYDir() == 1)
			{
				direction = "down";
			}
			
		}
		catch (NoMoveLeftException e) 
		{
			e.printStackTrace();
		}
	}

    /**
     * get which direction the robot should face
     *
     * 
     * @return string
     */
	public String getDirection()
	{
		return direction;
	}

    /**
     * get entity action sequence of the current robot
     *
     * 
     * @return EntityActionSequence
     */
	public EntityActionSequence getActionSequence()
	{
		return acSeq;
	}

    /**
     * get the projectile the robot is shooting
     *
     * 
     * @return Projectile
     */
	public Projectile getProjectile()
	{
		return this.projectile;
	}
	
}
