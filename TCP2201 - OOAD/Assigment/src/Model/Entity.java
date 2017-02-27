package Model;
/**
 * Each instance in the game is an entity even an empty space, bullet (projectile), robots
 * 
 * @author Wong Tiong Kiat and Choe Choon Ho
 *
 */
public class Entity 
{

	protected int xPos, yPos;
	
	protected EntityType type;
    /**
     * Constructor for objects of class Entity
     * 
     * @param  What type of entity is this object
     * @param  integer current x position in the board
     * @param  integer current y position in the board
     */
	public Entity(EntityType type, int xPos, int yPos)
	{
		this.type = type;
		this.xPos = xPos;
		this.yPos = yPos;
	}
    /**
     * getter for the entity's type
     * 
     * @return EntityType
     */
	public EntityType getEntityType()
	{
		return this.type;
	}

    /**
     * getter for the x position in board
     * 
     * @return integer
     */
	public int getXPos ()
	{
		return xPos;
	}

    /**
     * getter for the y position in board
     * 
     * @return integer
     */
	public int getYPos ()
	{
		return yPos;
	}
}
