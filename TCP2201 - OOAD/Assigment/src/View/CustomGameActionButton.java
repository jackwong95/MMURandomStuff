package View;

import Model.EntityActionSequence;
/**
 * 
 * Custom action button represent an action
 * 
 * @author Lim Yun Shen
 *
 */
public class CustomGameActionButton extends CustomButton
{
	private static final long serialVersionUID = -5782879580927647854L;
	
	private EntityActionSequence.Action action;
    /**
     * Constructor for objects of class custom game action button, where each action button represents an action
     * 
     * @param  Action from entityactionsequence, representing which type of action this button represent
     * @param  String text, text for this button
     * @param  String description, for the descrpition of this button when hovered over
     * @param  Integer width of this button
     * @param Integer height of this button
     */
	public CustomGameActionButton(EntityActionSequence.Action action, String text, String description, int width, int height) 
	{
		super(text, description, width, height);
		this.action = action;
	}
    /**
     * getter for the button's type of action
     *
     * @return action from entity action sequence of this type of action the button is binded to
     */
	public EntityActionSequence.Action getActionType()
	{
		return this.action;
	}
	
}