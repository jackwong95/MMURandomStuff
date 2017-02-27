package Model;

import java.util.ArrayList;

import Game.GlobalSetting;
/**
 * Projectile entity in game
 * 
 * @author Wong Tiong Kiat and Choe Choon Ho
 *
 */
public class Projectile extends Entity
{
	
	private boolean toCont = true;
	private boolean playerHit = false;
	
	public Projectile(EntityType type, int xPos, int yPos)
	{
		super(type, xPos, yPos);
	}
	
	//in case if animation needs to be done
	public void tick(Robot otherEntity) 
	{
		//if it clash at x or
		if(xPos == otherEntity.getXPos() && yPos == otherEntity.getYPos())
		{
			if(otherEntity.getEntityType() == EntityType.PLAYER2)
			{
				playerHit = true;
			}
			else
			{
				playerHit = false;
			}
			toCont = false;
		}
	}
	
	public boolean playerHitted()
	{
		return playerHit;
	}
	
	public boolean toContinue()
	{
		return toCont;
	}
	
}
