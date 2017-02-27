package Model;

import java.util.*;

import Game.GlobalSetting;
import GameException.*;
import java.io.Serializable;
/**
 * Represent each of the action a robot can have
 * 
 * Observable - Observe if there is a change in action sequence, if there is then update all subscribers(view)
 * @author Wong Tiong Kiat and Choe Choon Ho
 *
 */
//help me think of a better name if you can something direct straight forward, this applies to the AI and also the player yeah
public class EntityActionSequence extends Observable implements java.io.Serializable
{
	private static final long serialVersionUID = -6196234206426983671L;

	public enum Action
	{
		// enums associated with a unicode, x direction, y direction, and boolean to check whether it is a move action or shooting action
		UP("\u2191", 0, -1, false), DOWN("\u2193", 0, +1, false), LEFT("\u2190", -1, 0, false)
		, RIGHT("\u2192", +1, 0, false), SHOOTUP("S\u2191", 0, -1, true), SHOOTDOWN("S\u2193", 0, +1, true), 
		SHOOTLEFT("S\u2190", -1, 0, true), SHOOTRIGHT("S\u2192", +1, 0, true);

		private final int xDir, yDir;
		private final boolean isProjectile;
		private final String uniCodeSymbol;
	    /**
	     * Constructor for enum of Action
	     * 
	     * @param  String representation of the action
	     * @param  Integer x representing the position in the board
	     * @param  Integer y representing the position in the board
	     * @param  Boolean if this action is an projectile
	     */
		Action(final String uniCodeRepresentation, final int xDir, final int yDir, final boolean isProjectile)
		{
			this.uniCodeSymbol = uniCodeRepresentation;
			this.xDir = xDir;
			this.yDir = yDir;
			this.isProjectile = isProjectile; 
		}
	    /**
	     * getter for if this action is projectile
	     * 
	     * @return boolean
	     */
		public boolean isProjectile()
		{
			return isProjectile;
		}
	    /**
	     * getter of string representation of this action
	     * 
	     * @return string
	     */
		public String toString()
		{
			return uniCodeSymbol;
		}
	    /**
	     * getter of x direction of this action
	     * 
	     * @return integer
	     */
		public int getXDir() 
		{
			return this.xDir;
		}
	    /**
	     * getter of y direction of this action
	     * 
	     * @return integer
	     */
		public int getYDir() 
		{
			return this.yDir;
		}
		
		//values() containing all of enum types
		//this list cannot be modify
		//so new instance of random wouldn't be created every time for action generation
		private static final List<Action> VALUES = Collections.unmodifiableList(Arrays.asList(values()));
		private static final Random RND = new Random();
		private static final int sz = VALUES.size();

	    /**
	     * function to get random action
	     * 
	     * @return action
	     */
		public static Action getRandomAction()
		{
			return VALUES.get(RND.nextInt(sz));
		}
		
	};
	
	private Action [] actionHolder;
	
	private int idx = 0;
    /**
     * Constructor for objects of class EntityActionSequence
     * 
     */
	public EntityActionSequence()
	{
		actionHolder = new Action[GlobalSetting.MAX_ACTION_ALLOWED];
	}
    /**
     * to push an action to the current array
     * 
	 * @param  Action to be added
     * @return void
     */
	public void pushAction(Action action) throws MaxMoveReachException
	{
		if(isFull())
		{
			throw new MaxMoveReachException("Maximum moves");
		}
		for(int i = 0; i < GlobalSetting.MAX_ACTION_ALLOWED; i ++)
		{
			if(actionHolder[i] == null)
			{
				actionHolder[i] = action;
				break;
			}
		}
		setChanged();
		notifyObservers(this);
	}

    /**
     * to remove an action from the array
     * 
     * @return void
     */
	public void removeAction() throws NoMoveLeftException
	{
		if(isEmpty())
		{
			throw new NoMoveLeftException("No Moves Found");
		}

		for(int i = GlobalSetting.MAX_ACTION_ALLOWED-1; i >= 0; i --)
		{
			if(actionHolder[i] != null)
			{
				actionHolder[i] = null;
				break;
			}
		}
		setChanged();
		notifyObservers(this);
	}

    /**
     * populate the action sequence
     * 
     * @return void
     */
	public void generateActionSequence() throws MaxMoveReachException
	{
		clearAction();
		for(int i = 0; i < GlobalSetting.MAX_ACTION_ALLOWED; i ++)
		{
			EntityActionSequence.Action action = EntityActionSequence.Action.getRandomAction();
			this.pushAction(action);
		}
		setChanged();
		notifyObservers(this);
	}

    /**
     * if the action sequence is full
     * 
     * @return boolean
     */
	public boolean isFull()
	{
		return actionHolder[GlobalSetting.MAX_ACTION_ALLOWED-1] != null;
	}

    /**
     * if the action sequence is empty
     * 
     * @return boolean
     */
	public boolean isEmpty()
	{
		return actionHolder[0] == null;
	}

    /**
     * clear action sequence
     * 
     * @return void
     */
	public void clearAction()
	{
		actionHolder = new Action[GlobalSetting.MAX_ACTION_ALLOWED];
		idx = 0;
		
		setChanged();
		notifyObservers(this);
	}
	 /**
     * reset the action sequence's head 
     * 
     * @return void
     */
	public void resetActionIndex()
	{
		idx = 0;
	}

	 /**
    * set the pointer to next action sequence
    * 
    * @return void
    */
	public Action nextAction() throws NoMoveLeftException
	{
		int temp = idx ++;
		if(temp < 0) throw new NoMoveLeftException("No Moves Found");
		return actionHolder[temp];
	}
	
}
